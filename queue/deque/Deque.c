#include "Deque.h"

void Init(Deque *pDeque)
{
    assert(NULL != pDeque);

    pDeque->element = 0;
    pDeque->next = NULL;
}

void Destroy(Deque *pDeque)
{
    assert(NULL != pDeque);

    while (NULL != pDeque->next)
    {
        PopFront(pDeque);
    }

    Init(pDeque);
}

int Size(Deque *pDeque)
{
    assert(NULL != pDeque);

    return pDeque->element;
}

bool Empty(Deque *pDeque)
{
    return Size(pDeque) == 0;
}

int Front(Deque *pDeque, int *pElement)
{
    if (Empty(pDeque))
    {
        return -1;
    }

    *pElement = pDeque->next->element;

    return 0;
}

int Back(Deque *pDeque, int *pElement)
{
    if (Empty(pDeque))
    {
        return -1;
    }

    DequeNode tailNode = pDeque;

    // 找到最后一个节点
    while (NULL != tailNode->next)
    {
        tailNode = tailNode->next;
    }

    *pElement = tailNode->element;

    return -1;
}

int PushFront(Deque *pDeque, int element)
{
    assert(NULL != pDeque);

    DequeNode newNode = (DequeNode)calloc(1, sizeof(struct Node));

    if (NULL == newNode)
    {
        return -1;
    }
    newNode->element = element;
    newNode->next = pDeque->next;
    pDeque->next = newNode;
    pDeque->element++;

    return 0;
}

int PopFront(Deque *pDeque)
{
    if (Empty(pDeque))
    {
        return -1;
    }

    DequeNode topNode = pDeque->next;

    pDeque->next = topNode->next;
    free(topNode);
    topNode = NULL;
    pDeque->element--;

    return 0;
}

int PushBack(Deque *pDeque, int element)
{
    assert(NULL != pDeque);

    DequeNode newNode = (DequeNode)calloc(1, sizeof(struct Node));

    if (NULL == newNode)
    {
        return -1;
    }
    newNode->element = element;
    newNode->next = NULL;

    DequeNode tailNode = pDeque;

    // 找到最后一个节点
    while (NULL != tailNode->next)
    {
        tailNode = tailNode->next;
    }
    tailNode->next = newNode;
    pDeque->element++;

    return 0;
}

int PopBack(Deque *pDeque)
{
    if (Empty(pDeque))
    {
        return -1;
    }

    DequeNode prevNode = pDeque;

    // 找到倒数第二个节点
    while (NULL != prevNode->next->next)
    {
        prevNode = prevNode->next;
    }

    free(prevNode->next);
    prevNode->next = NULL;
    pDeque->element--;

    return 0;
}
