#include "Stack.h"

void Init(Stack *pStack)
{
    assert(NULL != pStack);

    pStack->element = 0;
    pStack->next = NULL;
}

void Destroy(Stack *pStack)
{
    assert(NULL != pStack);

    while (NULL != pStack->next)
    {
        Pop(pStack);
    }

    Init(pStack);
}

int Size(Stack *pStack)
{
    assert(NULL != pStack);

    return pStack->element;
}

bool Empty(Stack *pStack)
{
    return Size(pStack) == 0;
}

int Top(Stack *pStack, int *pElement)
{
    if (Empty(pStack))
    {
        return -1;
    }

    *pElement = pStack->next->element;

    return 0;
}

int Push(Stack *pStack, int element)
{
    assert(NULL != pStack);

    StackNode newNode = (StackNode)calloc(1, sizeof(struct Node));

    if (NULL == newNode)
    {
        return -1;
    }
    newNode->element = element;
    newNode->next = pStack->next;
    pStack->next = newNode;
    pStack->element++;

    return 0;
}

int Pop(Stack *pStack)
{
    if (Empty(pStack))
    {
        return -1;
    }

    StackNode topNode = pStack->next;

    pStack->next = topNode->next;
    free(topNode);
    topNode = NULL;
    pStack->element--;

    return 0;
}
