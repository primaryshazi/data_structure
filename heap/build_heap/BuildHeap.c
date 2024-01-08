#include "BuildHeap.h"

/**
 * @brief 交换值
 *
 * @param x
 * @param y
 */
static void Swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

/**
 * @brief 构建最大堆数组
 *
 * @param array
 * @param length
 * @param index
 */
static void BuildMax(int array[], int length, int index)
{
    int father = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < length && array[left] > array[father])
    {
        father = left;
    }
    if (right < length && array[right] > array[father])
    {
        father = right;
    }

    if (father != index)
    {
        Swap(&(array[father]), &(array[index]));
        BuildMax(array, length, father);
    }
}

/**
 * @brief 构建最小堆数组
 *
 * @param array
 * @param length
 * @param index
 */
static void BuildMin(int array[], int length, int index)
{
    int father = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < length && array[left] < array[father])
    {
        father = left;
    }
    if (right < length && array[right] < array[father])
    {
        father = right;
    }

    if (father != index)
    {
        Swap(&(array[father]), &(array[index]));
        BuildMin(array, length, father);
    }
}

int Init(Heap *pHeap, int length, HeapType type)
{
    assert(NULL != pHeap);

    pHeap->array = (int *)calloc(length, sizeof(int));

    if (NULL == pHeap->array)
    {
        return -1;
    }

    for (int i = 0; i < length; i++)
    {
        pHeap->array[i] = Heap_Max == type ? INT_MIN : INT_MAX;
    }

    pHeap->length = length;
    pHeap->size = 0;
    pHeap->type = type;

    return 0;
}

void Destroy(Heap *pHeap)
{
    assert(NULL != pHeap);

    free(pHeap->array);
    pHeap->array = NULL;
    pHeap->length = 0;
    pHeap->size = 0;
    pHeap->type = Heap_Max;
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
    if (Heap_Max == pHeap->type)
    {
        while (cur > 0 && pHeap->array[cur] > pHeap->array[parent])
        {
            Swap(pHeap->array + cur, pHeap->array + parent);

            cur = parent;
            parent = (cur - 1) / 2;
        }
    }
    else
    {
        while (cur > 0 && pHeap->array[cur] < pHeap->array[parent])
        {
            Swap(pHeap->array + cur, pHeap->array + parent);

            cur = parent;
            parent = (cur - 1) / 2;
        }
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

    if (Heap_Max == pHeap->type)
    {
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
    }
    else
    {
        while (cur < pHeap->size)
        {
            int largest = cur;

            if (left < pHeap->size && pHeap->array[left] < pHeap->array[largest])
            {
                largest = left;
            }

            if (right < pHeap->size && pHeap->array[right] < pHeap->array[largest])
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
        pHeap->array[pHeap->size] = INT_MAX;
    }

    return 0;
}

int Modify(Heap *pHeap, int index, int element)
{
    if (Size(pHeap) <= index)
    {
        return -1;
    }

    pHeap->array[index] = element;

    return -1;
}

int BuildHeap(Heap *pHeap)
{
    if (Empty(pHeap))
    {
        return -1;
    }

    if (Heap_Max == pHeap->type)
    {
        for (int i = pHeap->size - 1; i >= 0; i--)
        {
            BuildMax(pHeap->array, pHeap->size, i);
        }
    }
    else
    {
        for (int i = pHeap->size - 1; i >= 0; i--)
        {
            BuildMin(pHeap->array, pHeap->size, i);
        }
    }

    return 0;
}
