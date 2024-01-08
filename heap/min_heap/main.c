#include "MinHeap.h"

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
        for (int i = HEAP_LENGTH - 1; i >= 0; i--)
        {
            Push(&heap, i);
        }

        /**
         * => 0 1 4 3 2 8 5 9 6 7
         */
        Print(&heap);

        for (int i = 0; i < HEAP_LENGTH / 2; i++)
        {
            Pop(&heap);
        }

        /**
         * => 5 6 8 9 7
         */
        Print(&heap);

        Destroy(&heap);
    }

    return 0;
}
