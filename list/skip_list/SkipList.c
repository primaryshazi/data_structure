#include "SkipList.h"

/**
 * @brief 申请新节点
 *
 * @param level
 * @return SkipListNode *
 */
static SkipListNode *CreateNode(int level)
{
    return (SkipListNode *)calloc(1, sizeof(SkipListNode) + level * sizeof(SkipListLevel));
}

/**
 * @brief 生成随机层级
 *
 * @return int
 */
static int RandomLevel()
{
    int level = 1;

    while ((rand() & 0xFFFF) < (SKIPLIST_P * 0xFFFF))
    {
        level += 1;
    }

    return (level < SKIPLIST_MAX_LEVEL) ? level : SKIPLIST_MAX_LEVEL;
}

/**
 * @brief 删除节点
 *
 * @param list
 * @param node
 * @param prev
 */
static void EraseNode(SkipList *list, SkipListNode *node, SkipListNode *prev[])
{
    // 从新节点的层级开始，每一层进行类似于单链表删除错误
    for (int i = list->level - 1; i >= 0; i--)
    {
        if (prev[i]->level[i].forward == node)
        {
            prev[i]->level[i].forward = node->level[i].forward;
        }
    }

    /**
     * 若目标节点不为最后一个，则将目标节点的forward指向的backward指向目标节点的前节点
     * 若目标节点是最后一个则将尾节点置为目标节点
     */
    if (node->level[0].forward)
    {
        node->level[0].forward->backward = node->backward;
    }
    else
    {
        list->tail = node->backward;
    }

    // 若最高层级为空则去除最高层级
    while ((list->level > 1) && (list->head->level[list->level - 1].forward == NULL))
    {
        list->level--;
    }
    list->length--;
}


SkipList *Create()
{
    srand((unsigned int)time(NULL));

    SkipList *skipList = (SkipList *)calloc(1, sizeof(SkipList));
    if (!skipList)
    {
        return NULL;
    }

    skipList->length = 0;
    skipList->level = 1;
    skipList->tail = NULL;
    skipList->head = CreateNode(SKIPLIST_MAX_LEVEL);
    if (!skipList->head)
    {
        free(skipList);
        return NULL;
    }

    skipList->head->value = -1;
    skipList->head->backward = NULL;
    for (int i = 0; i < SKIPLIST_MAX_LEVEL; i++)
    {
        skipList->head->level[i].forward = NULL;
    }

    return skipList;
}

void Destroy(SkipList *list)
{
    SkipListNode *prev = NULL;
    SkipListNode *node = NULL;

    node = list->head->level[0].forward;
    while (node)
    {
        prev = node;
        node = node->level[0].forward;
        free(prev);
    }

    free(list->head);
    list->head = NULL;

    free(list);
}

SkipListNode *Find(SkipList *list, int target)
{
    SkipListNode *node = list->head;

    // 遍历每个层级
    for (int i = list->level - 1; i >= 0; i--)
    {
        // 找到指定层级的不小于目标值的节点
        while (node->level[i].forward && (node->level[i].forward->value < target))
        {
            node = node->level[i].forward;
        }

        if (node->level[i].forward && (node->level[i].forward->value == target))
        {
            return node->level[i].forward;
        }
    }

    return NULL;
}

SkipListNode *Insert(SkipList *list, int target)
{
    SkipListNode *prev[SKIPLIST_MAX_LEVEL] = { NULL };
    SkipListNode *node = list->head;

    // 从最高层级开始，找到每一层比target小的节点，没有则为头节点
    for (int i = list->level - 1; i >= 0; i--)
    {
        while (node->level[i].forward && node->level[i].forward->value < target)
        {
            node = node->level[i].forward;
        }
        prev[i] = node;
    }

    int level = RandomLevel();
    // 若新节点的层级比当前最大层级大，则将增加层级的前节点均置为头节点
    if (list->level < level)
    {
        for (int i = list->level; i < level; i++)
        {
            prev[i] = list->head;
        }
        list->level = level;
    }

    node = CreateNode(level);
    if (NULL == node)
    {
        return NULL;
    }

    // 从新节点的层级开始，每一层进行类似于单链表插入操作
    for (int i = 0; i < level; i++)
    {
        node->level[i].forward = prev[i]->level[i].forward;
        prev[i]->level[i].forward = node;
    }
    node->value = target;
    // 若新节点的前节点为头节点则将backward置为空
    node->backward = (prev[0] == list->head) ? NULL : prev[0];

    /**
     * 若新节点不为最后一个，则将新节点的forward指向的backward指向新节点
     * 若新节点是最后一个则将尾节点置为新节点
     */
    if (node->level[0].forward)
    {
        node->level[0].forward->backward = node;
    }
    else
    {
        list->tail = node;
    }

    list->length++;

    return node;
}

bool Erase(SkipList *list, int target)
{
    SkipListNode *prev[SKIPLIST_MAX_LEVEL] = { NULL };
    SkipListNode *node = list->head;

    // 从最高层级开始，找到每一层比target小的节点，没有则为头节点
    for (int i = list->level - 1; i >= 0; i--)
    {
        while (node->level[i].forward && node->level[i].forward->value < target)
        {
            node = node->level[i].forward;
        }
        prev[i] = node;
    }

    // 若找到目标节点则删除节点
    node = node->level[0].forward;
    if (node && (node->value == target))
    {
        EraseNode(list, node, prev);
        free(node);

        return true;
    }

    return false;
}

SkipListNode *Modify(SkipList *list, int target, int value)
{
    SkipListNode *prev[SKIPLIST_MAX_LEVEL] = { NULL };
    SkipListNode *node = list->head;

    // 从最高层级开始，找到每一层比target小的节点，没有则为头节点
    for (int i = list->level - 1; i >= 0; i--)
    {
        while (node->level[i].forward && node->level[i].forward->value < target)
        {
            node = node->level[i].forward;
        }
        prev[i] = node;
    }

    // 找不到目标节点则返回空
    node = node->level[0].forward;
    if (!node || (node->value != target))
    {
        return NULL;
    }

    /**
     * 若只有一个节点
     * 若为第一个节点且修改值小于后节点的值
     * 若为最后一个节点且修改值大于前节点的值
     * 满足任意一条则直接修改节点值
     */
    if ((node->backward == NULL || node->backward->value < value) &&
        (node->level[0].forward == NULL || node->level[0].forward->value > value))
    {
        node->value = value;
        return node;
    }

    // 先删除节点后插入节点
    EraseNode(list, node, prev);
    free(node);
    node = Insert(list, value);

    return node;
}

void PrintList(SkipList *list)
{
    SkipListNode *node = NULL;

    // 打印每个层级
    for (int i = list->level - 1; i >= 0; i--)
    {
        node = list->head->level[i].forward;
        printf("[%4d] ", i);
        while (node)
        {
            printf("%4d -> ", node->value);

            node = node->level[i].forward;
        }
        printf("null\n");
    }
}
