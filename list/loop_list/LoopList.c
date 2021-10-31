#include "LoopList.h"

void Init(LoopList *pList)
{
    assert(NULL != pList);

    pList->next = NULL;
    pList->element = 0;
}

void Destroy(LoopList *pList)
{
    assert(NULL != pList);

    LinkNode headNode = pList->next;
    int size = pList->element;

    while (size-- > 0)
    {
        pList->next = pList->next->next;
        free(headNode);
        headNode = pList->next;
    }
    Init(pList);
}

int Size(LoopList *pList)
{
    assert(NULL != pList);

    return pList->element;
}

bool Empty(LoopList *pList)
{
    return Size(pList) == 0;
}

Position Index(LoopList *pList, int index)
{
    assert(NULL != pList);

    if (index < 0 && index >= pList->element)
    {
        return NULL;
    }

    int tempIndex = 0;

    LinkNode tempNode = pList->next;

    while (tempIndex < pList->element)
    {
        if (tempIndex == index)
        {
            return tempNode;
        }
        tempNode = tempNode->next;
        tempIndex++;
    }

    return NULL;
}

Position FindFirst(LoopList *pList, int element, Position fromPos)
{
    assert(NULL != pList);

    if (pList == fromPos)
    {
        return NULL;
    }

    LinkNode tempNode = (NULL == fromPos ? pList->next : fromPos);
    int size = pList->element;

    while (size-- > 0)
    {
        if (element == tempNode->element)
        {
            return tempNode;
        }
        tempNode = tempNode->next;
    }

    return NULL;
}

Position FindLast(LoopList *pList, int element, Position fromPos)
{
    assert(NULL != pList);

    if (pList == fromPos)
    {
        return NULL;
    }

    LinkNode tempNode = (NULL == fromPos ? pList->next : fromPos);
    LinkNode lastNode = NULL;
    int size = pList->element;

    while (size-- > 0)
    {
        if (element == tempNode->element)
        {
            lastNode = tempNode;
        }
        tempNode = tempNode->next;
    }

    return lastNode;
}

int Insert(LoopList *pList, Position position, int element)
{
    assert(NULL != pList);

    if (pList == position)
    {
        return -1;
    }

    LinkNode newNode = (LinkNode)calloc(1, sizeof(struct Node));

    if (NULL == newNode)
    {
        return -1;
    }

    newNode->element = element;
    newNode->next = position;

    LinkNode prevNode = pList;
    int size = pList->element;

    // 当链表为空，在空指针之前插入第一个元素，进行一次循环
    if (0 == size && NULL == position)
    {
        size = 1;
    }

    while (size-- > 0)
    {
        if (prevNode->next == position)
        {
            /**
             * 当插入第一节点时，将链表头指针指向新节点，新节点指向自己
             * 当插入头节点之前时，获取最后一个节点，将链表头指针指向新节点，尾节点下一个指向新节点
             * 当差入中间节点之前时，将前节点指向新节点
             */
            if (NULL == position)
            {
                prevNode->next = newNode;
                newNode->next = pList->next;
            }
            else if (pList->next == position)
            {
                prevNode = position;
                // 获取最后一个节点
                while (pList->next != prevNode->next)
                {
                    prevNode = prevNode->next;
                }
                pList->next = newNode;
                prevNode->next = newNode;
            }
            else
            {
                prevNode->next = newNode;
            }
            pList->element++;

            return 0;
        }
        prevNode = prevNode->next;
    }

    return -1;
}

int Erase(LoopList *pList, Position position)
{
    assert(NULL != pList);

    if (NULL == position || pList == position)
    {
        return -1;
    }

    LinkNode prevNode = pList;
    int size = pList->element;

    while (size-- > 0)
    {
        if (prevNode->next == position)
        {
            if (1 == pList->element) // 当只有一个节点时，将链表头指针指向空
            {
                pList->next = NULL;
            }
            else
            {
                /**
                 * 当删除头节点时，找到最后一个节点，将链表头指针指向头节点的下一个，尾节点的下一个指向新头节点
                 * 当删除非头节点时，将前前节点指向指定位置的下一个
                 */
                if (pList->next == position)
                {
                    prevNode = position;
                    // 获取最后一个节点
                    while (pList->next != prevNode->next)
                    {
                        prevNode = prevNode->next;
                    }
                    pList->next = position->next;
                    prevNode->next = pList->next;
                }
                else
                {
                    prevNode->next = position->next;
                }
            }

            free(position);
            position = NULL;
            pList->element--;

            return 0;
        }
        prevNode = prevNode->next;
    }

    return -1;
}
