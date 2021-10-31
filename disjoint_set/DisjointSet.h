#ifndef DISJOINTSET_H_
#define DISJOINTSET_H_

#include <assert.h>
#include <stdlib.h>

typedef struct DSet
{
    int *elementSet;
    int size;
} DisjointSet;

/**
 * @brief 初始化集合
 *
 * @param djSet
 * @param size
 * @return int
 */
extern int Initialize(DisjointSet *djSet, int size);

/**
 * @brief 索引位置的值
 *
 * @param djSet
 * @param x
 * @return int
 */
extern int ValueOfIndex(DisjointSet *djSet, int x);

/**
 * @brief 元素数量
 *
 * @param djSet
 * @return int
 */
extern int Size(DisjointSet *djSet);

/**
 * @brief 合并节点
 *
 * @param djSet
 * @param x
 * @param y
 */
extern void UnionElement(DisjointSet *djSet, int x, int y);

/**
 * @brief 查找根节点
 *
 * @param djSet
 * @param x
 * @return int
 */
extern int FindRoot(DisjointSet *djSet, int element);

#endif  // DISJOINTSET_H_
