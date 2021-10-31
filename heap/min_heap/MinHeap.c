#include "MinHeap.h"

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
        pHeap->array[i] = INT_MAX;
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

    int index = pHeap->size;

    /**
     * 子节点均小于左右节点，子节点i，左节点2 * i + 1，右节点2 * i + 2
     * 若其父节点大于子节点，则将父节点与子节点交换
     */
    while (index > 0 && pHeap->array[index / 2] > element)
    {
        pHeap->array[index] = pHeap->array[index / 2];
        index /= 2;
    }
    pHeap->array[index] = element;
    pHeap->size++;

    return 0;
}

int Pop(Heap *pHeap)
{
    if (Empty(pHeap))
    {
        return -1;
    }

    int size = --pHeap->size;
    int last = pHeap->array[size];
    int index = 0;
    int child = 0;

    pHeap->array[size] = INT_MAX;

    for (index = 0; index * 2 < size; index = child)
    {
        child = index * 2 + 1;

        /**
         * 获取最小子节点的索引
         * 若存在右节点且左节点大于右节点则定位至右索引
         */
        if (child + 1 < size && pHeap->array[child] > pHeap->array[child + 1])
        {
            child++;
        }

        /**
         * 当最后一个元素小于其子节点时则退出
         * 当最后一个元素不小于其子节点时，与其最小子节点互换
         */
        if (last < pHeap->array[child])
        {
            break;
        }
        else
        {
            pHeap->array[index] = pHeap->array[child];
        }
    }
    pHeap->array[index] = last;

    return 0;
}
