#include "MinHeap.h"

#include <stdio.h>

#define HEAP_LENGTH 10

void Print(Heap *pHeap)
{
    for (int i = 0; i < pHeap->size; i++)
    {
        printf("%d\n", pHeap->array[i]);
    }
    printf("\n");
}

int main()
{
    Heap heap;

    if (Init(&heap, HEAP_LENGTH) == 0)
    {
        for (int i = 0; i < HEAP_LENGTH; i++)
        {
            Push(&heap, i);
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
        Print(&heap);

        for (int i = 0; i < HEAP_LENGTH / 2; i++)
        {
            Pop(&heap);
        }

        /**
         * => 5
         * => 6
         * => 8
         * => 7
         * => 9
         */
        Print(&heap);

        Destroy(&heap);
    }

    return 0;
}
