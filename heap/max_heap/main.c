#include "MaxHeap.h"

#include <stdio.h>

#define HEAP_LENGTH 10

void Print(Heap *pHeap)
{
    for (int i = 0; i < pHeap->size; i++)
    {
        printf("%d ", pHeap->array[i]);
    }
    printf("\n\n");
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
         * => 9 8 5 6 7 1 4 0 3 2
         */
        Print(&heap);

        for (int i = 0; i < HEAP_LENGTH / 2; i++)
        {
            Pop(&heap);
        }

        /**
         * => 4 3 1 0 2
         */
        Print(&heap);

        Destroy(&heap);
    }

    return 0;
}
