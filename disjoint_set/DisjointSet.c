#include "DisjointSet.h"

int Initialize(DisjointSet *djSet, int size)
{
    assert(NULL != djSet);

    djSet->elementSet = (int *)calloc(sizeof(int), size);

    if (NULL == djSet->elementSet)
    {
        return -1;
    }
    djSet->size = size;

    return 0;
}

int ValueOfIndex(DisjointSet *djSet, int x)
{
    assert(NULL != djSet);
    assert(x < djSet->size);

    return djSet->elementSet[x];
}

int Size(DisjointSet *djSet)
{
    assert(NULL != djSet);

    return djSet->size;
}

void UnionElement(DisjointSet *djSet, int x, int y)
{
    assert(NULL != djSet);
    assert(x < djSet->size &&y < djSet->size);

    /**
     * 若x节点比y节点深，则将y节点挂在x节点下
     * 若y节点比x节点深，则将x节点挂在y节点下
     * 若二者深度一致，则将x深度加1，并将y节点挂在x节点下
     */
    if (djSet->elementSet[x] < djSet->elementSet[y])
    {
        djSet->elementSet[y] = x;
    }
    else if (djSet->elementSet[x] > djSet->elementSet[y])
    {
        djSet->elementSet[x] = y;
    }
    else
    {
        djSet->elementSet[x]--;
        djSet->elementSet[y] = x;
    }
}

int FindRoot(DisjointSet *djSet, int element)
{
    assert(NULL != djSet);
    assert(element < djSet->size);

    if (djSet->elementSet[element] < 0)
    {
        return element;
    }
    else
    {
        return FindRoot(djSet, djSet->elementSet[element]);
    }
}
