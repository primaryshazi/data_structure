#include "MaxHeap.h"

static void Swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Init(Heap *pHeap, int length)
{
    assert(NULL != pHeap);

    pHeap->array = (int *)calloc(length, sizeof(int));

    if (NULL == pHeap->array)
    {
        return -1;
    }

    for (int i = 0; i < length; i++)
    {
        pHeap->array[i] = INT_MIN;
    }

    pHeap->length = length;
    pHeap->size = 0;

    return 0;
}

void Destroy(Heap *pHeap)
{
    assert(NULL != pHeap);

    free(pHeap->array);
    pHeap->array = NULL;
    pHeap->length = 0;
    pHeap->size = 0;
}

int Size(Heap *pHeap)
{
    assert(NULL != pHeap);

    return pHeap->size;
}

bool Full(Heap *pHeap)
{
    return Size(pHeap) == pHeap->length;
}

bool Empty(Heap *pHeap)
{
    return Size(pHeap) == 0;
}

int Top(Heap *pHeap, int *pElement)
{
    if (Empty(pHeap))
    {
        return -1;
    }

    *pElement = pHeap->array[0];

    return 0;
}

int Push(Heap *pHeap, int element)
{
    if (Full(pHeap))
    {
        return -1;
    }

    pHeap->array[pHeap->size] = element;
    pHeap->size++;

    int cur = pHeap->size - 1;
    int parent = (cur - 1) / 2;
    while (cur > 0 && pHeap->array[cur] > pHeap->array[parent])
    {
        Swap(pHeap->array + cur, pHeap->array + parent);

        cur = parent;
        parent = (cur - 1) / 2;
    }

    return 0;
}

int Pop(Heap *pHeap)
{
    if (Empty(pHeap))
    {
        return -1;
    }

    pHeap->array[0] = pHeap->array[pHeap->size - 1];
    pHeap->size--;

    int cur = 0;
    int left = 2 * cur + 1;
    int right = 2 * cur + 2;

    while (cur < pHeap->size)
    {
        int largest = cur;

        if (left < pHeap->size && pHeap->array[left] > pHeap->array[largest])
        {
            largest = left;
        }

        if (right < pHeap->size && pHeap->array[right] > pHeap->array[largest])
        {
            largest = right;
        }

        if (largest != cur)
        {
            Swap(pHeap->array + cur, pHeap->array + largest);
            cur = largest;
            left = 2 * cur + 1;
            right = 2 * cur + 2;
        }
        else
        {
            break;
        }
    }

    pHeap->array[pHeap->size] = INT_MIN;

    return 0;
}
