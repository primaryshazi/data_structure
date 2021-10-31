#include "Queue.h"

void Init(Queue *pQueue)
{
    assert(NULL != pQueue);

    pQueue->element = 0;
    pQueue->next = NULL;
}

void Destroy(Queue *pQueue)
{
    assert(NULL != pQueue);

    while (NULL != pQueue->next)
    {
        Pop(pQueue);
    }

    Init(pQueue);
}

int Size(Queue *pQueue)
{
    assert(NULL != pQueue);

    return pQueue->element;
}

bool Empty(Queue *pQueue)
{
    return Size(pQueue) == 0;
}

int Top(Queue *pQueue, int *pElement)
{
    if (Empty(pQueue))
    {
        return -1;
    }

    *pElement = pQueue->next->element;

    return 0;
}

int Push(Queue *pQueue, int element)
{
    assert(NULL != pQueue);

    QueueNode newNode = (QueueNode)calloc(1, sizeof(struct Node));

    if (NULL == newNode)
    {
        return -1;
    }
    newNode->element = element;
    newNode->next = NULL;

    QueueNode tailNode = pQueue;

    // 找到最后一个节点
    while (NULL != tailNode->next)
    {
        tailNode = tailNode->next;
    }
    tailNode->next = newNode;
    pQueue->element++;

    return 0;
}

int Pop(Queue *pQueue)
{
    if (Empty(pQueue))
    {
        return -1;
    }

    QueueNode topNode = pQueue->next;

    pQueue->next = topNode->next;
    free(topNode);
    topNode = NULL;
    pQueue->element--;

    return 0;
}
