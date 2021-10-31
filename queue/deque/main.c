#include "Deque.h"

#include <stdio.h>

void Print(Deque *pDeque)
{
    DequeNode node = pDeque->next;

    while (NULL != node)
    {
        printf("%d\n", node->element);
        node = node->next;
    }
    printf("\n");
}

int main()
{
    Deque deque;

    Init(&deque);

    for (int i = 0; i < 5; i++)
    {
        PushFront(&deque, i);
        PushBack(&deque, i);
    }

    /**
     * => 4
     * => 3
     * => 2
     * => 1
     * => 0
     * => 0
     * => 1
     * => 2
     * => 3
     * => 4
     */
    Print(&deque);

    for (int i = 0; i < 3; i++)
    {
        PopFront(&deque);
        PopBack(&deque);
    }

    /**
     * => 1
     * => 0
     * => 0
     * => 1
     */
    Print(&deque);

    Destroy(&deque);

    return 0;
}
