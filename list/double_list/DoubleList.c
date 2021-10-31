#include "DoubleList.h"

void Init(DoubleList *pList)
{
    assert(NULL != pList);

    pList->prev = NULL;     // 指向尾节点
    pList->next = NULL;     // 指向头节点
    pList->element = 0;     // 链表长度
}

void Destroy(DoubleList *pList)
{
    assert(NULL != pList);

    LinkNode headNode = pList->next;

    while (NULL != headNode)
    {
        pList->next = pList->next->next;
        free(headNode);
        headNode = pList->next;
    }
    Init(pList);
}

int Size(DoubleList *pList)
{
    assert(NULL != pList);

    return pList->element;
}

bool Empty(DoubleList *pList)
{
    return Size(pList) == 0;
}

Position Index(DoubleList *pList, int index)
{
    assert(NULL != pList);

    if (index < 0 && index >= pList->element)
    {
        return NULL;
    }

    int tempIndex = 0;

    LinkNode tempNode = pList->next;

    while (NULL != tempNode)
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

Position FindFirst(DoubleList *pList, int element, Position fromPos)
{
    assert(NULL != pList);

    if (pList == fromPos)
    {
        return NULL;
    }

    LinkNode tempNode = (NULL == fromPos ? pList->next : fromPos);

    while (NULL != tempNode)
    {
        if (element == tempNode->element)
        {
            return tempNode;
        }
        tempNode = tempNode->next;
    }

    return NULL;
}

Position FindLast(DoubleList *pList, int element, Position fromPos)
{
    assert(NULL != pList);

    if (pList == fromPos)
    {
        return NULL;
    }

    LinkNode tempNode = (NULL == fromPos ? pList->prev : fromPos);

    while (NULL != tempNode)
    {
        if (element == tempNode->element)
        {
            return tempNode;
        }
        tempNode = tempNode->prev;
    }

    return NULL;
}

int Insert(DoubleList *pList, Position position, int element)
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

    while (NULL != prevNode)
    {
        if (prevNode->next == position)
        {
            prevNode->next = newNode; // 前节点的下一个指向新节点

            /**
             * 当指定位置为空时，向尾部插入
             * 当指定位置非空时，向指定位置之前插入
             */
            if (NULL == position)
            {
                /**
                 * 若链表为空时，将新节点的上一个指向空
                 * 若链表非空时，将新节点的上一个指向前节点
                 */
                if (0 == pList->element)
                {
                    newNode->prev = NULL;
                }
                else
                {
                    newNode->prev = prevNode;
                }
                pList->prev = newNode; // 链表尾指针指向新节点
            }
            else
            {
                newNode->prev = prevNode;
                prevNode->next = newNode;
                position->prev = newNode;
            }

            pList->element++;

            return 0;
        }
        prevNode = prevNode->next;
    }

    return -1;
}

int Erase(DoubleList *pList, Position position)
{
    assert(NULL != pList);

    if (NULL == position || pList == position)
    {
        return -1;
    }

    LinkNode prevNode = pList;

    while (NULL != prevNode)
    {
        if (prevNode->next == position)
        {
            prevNode->next = position->next; // 前节点的下一个指向指定位置的下一个

            if (1 == pList->element) // 当只有一个元素时，直接将链表头尾指针均指向空
            {
                pList->next = NULL;
                pList->prev = NULL;
            }
            else
            {
                /**
                 * 当删除头节点时，将头节点的下一个的上一个指向尾空
                 * 当删除尾节点时，将链表尾指针指向前节点，前节点的下一个指向空
                 * 当删除中间节点时，将前节点的下一个指向指定位置的下一个，指定位置的上一个指向前节点
                 */
                if (NULL == position->prev)
                {
                    position->next->prev = NULL;
                }
                else if (NULL == position->next)
                {
                    pList->prev = prevNode;
                    prevNode->next = NULL;
                }
                else
                {
                    prevNode->next = position->next;
                    position->next->prev = prevNode;
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
