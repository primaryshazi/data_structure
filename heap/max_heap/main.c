#include "MaxHeap.h"

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
         * => 9
         * => 8
         * => 7
         * => 5
         * => 6
         * => 2
         * => 1
         * => 4
         * => 0
         * => 3
         */
        Print(&heap);

        for (int i = 0; i < HEAP_LENGTH / 2; i++)
        {
            Pop(&heap);
        }

        /**
         * => 4
         * => 3
         * => 2
         * => 1
         * => 0
         */
        Print(&heap);

        Destroy(&heap);
    }

    return 0;
}
