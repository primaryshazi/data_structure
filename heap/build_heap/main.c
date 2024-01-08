#include "BuildHeap.h"

#include <stdio.h>
#include <time.h>

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

    if (Init(&heap, HEAP_LENGTH, Heap_Max) == 0)
    {
        for (int i = 0; i < HEAP_LENGTH; i++)
        {
            Push(&heap, i);
        }

        /**
         * => 9 8 5 6 7 1 4 0 3 2
         */
        Print(&heap);

        srand(HEAP_LENGTH);
        for (int i = 0; i < HEAP_LENGTH; i++)
        {
            Modify(&heap, i, rand() % HEAP_LENGTH);
        }

        /**
         * => 1 9 2 4 7 6 2 2 6 9
         */
        Print(&heap);

        BuildHeap(&heap);

        /**
         * => 9 9 6 6 7 2 2 2 4 1
         */
        Print(&heap);

        Destroy(&heap);
    }

    return 0;
}
