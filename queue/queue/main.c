#include "Queue.h"

#include <stdio.h>

void Print(Queue *pQueue)
{
    QueueNode node = pQueue->next;

    while (NULL != node)
    {
        printf("%d\n", node->element);
        node = node->next;
    }
    printf("\n");
}

int main()
{
    Queue queue;

    Init(&queue);

    for (int i = 0; i < 10; i++)
    {
        Push(&queue, i);
    }

    /**
     * => 0
     * => 1
     * => 2
     * => 3
     * => 4
     * => 5
     * => 6
     * => 7
     * => 8
     * => 9
     */
    Print(&queue);

    for (int i = 0; i < 5; i++)
    {
        Pop(&queue);
    }

    /**
     * => 5
     * => 6
     * => 7
     * => 8
     * => 9
     */
    Print(&queue);

    Destroy(&queue);

    return 0;
}
