#include "SingleList.h"

void Init(SingleList *pList)
{
    assert(NULL != pList);

    pList->next = NULL;     // 指向头节点
    pList->element = 0;     // 链表长度
}

void Destroy(SingleList *pList)
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

int Size(SingleList *pList)
{
    assert(NULL != pList);

    return pList->element;
}

bool Empty(SingleList *pList)
{
    return Size(pList) == 0;
}

Position Index(SingleList *pList, int index)
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

Position FindFirst(SingleList *pList, int element, Position fromPos)
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

Position FindLast(SingleList *pList, int element, Position fromPos)
{
    assert(NULL != pList);

    if (pList == fromPos)
    {
        return NULL;
    }

    LinkNode tempNode = (NULL == fromPos ? pList->next : fromPos);
    LinkNode lastNode = NULL;

    while (NULL != tempNode)
    {
        if (element == tempNode->element)
        {
            lastNode = tempNode;
        }
        tempNode = tempNode->next;
    }

    return lastNode;
}

int Insert(SingleList *pList, Position position, int element)
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
            prevNode->next = newNode;
            pList->element++;

            return 0;
        }
        prevNode = prevNode->next;
    }

    return -1;
}

int Erase(SingleList *pList, Position position)
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
            prevNode->next = position->next;
            free(position);
            position = NULL;
            pList->element--;

            return 0;
        }
        prevNode = prevNode->next;
    }

    return -1;
}

void Reversal(SingleList *pList)
{
    if (Size(pList) < 2)
    {
        return;
    }

    /**
     * first指向第一个元素
     * second指向first->next元素
     */
    LinkNode first = pList->next;
    LinkNode second = first->next;

    /**
     * 将first->next指向second->next
     * 将second指向当前第一个元素
     * 将头节点指向second
     * 将second指向first->next
     */
    while (NULL != second)
    {
        first->next = second->next;
        second->next = pList->next;
        pList->next = second;
        second = first->next;
    }
}
