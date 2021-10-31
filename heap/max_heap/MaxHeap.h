#ifndef MAXHEAP_H_
#define MAXHEAP_H_

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

typedef struct Heap
{
    int length;
    int size;
    int *array;
} Heap;

/**
 * @brief 初始化堆
 *
 * @param pHeap
 * @param length
 * @return int
 */
extern int Init(Heap *pHeap, int length);

/**
 * @brief 销毁堆
 *
 * @param pHeap
 * @return void
 */
extern void Destroy(Heap *pHeap);

/**
 * @brief 元素数量
 *
 * @param pHeap
 * @return int
 */
extern int Size(Heap *pHeap);

/**
 * @brief 是否存满
 *
 * @param pHeap
 * @return bool
 */
extern bool Full(Heap *pHeap);

/**
 * @brief 是否为空
 *
 * @param pHeap
 * @return bool
 */
extern bool Empty(Heap *pHeap);

/**
 * @brief 堆顶元素
 *
 * @param pHeap
 * @param pElement
 * @return int
 */
extern int Top(Heap *pHeap, int *pElement);

/**
 * @brief 推入元素
 *
 * @param pHeap
 * @param element
 * @return int
 */
extern int Push(Heap *pHeap, int element);

/**
 * @brief 推出元素
 *
 * @param pHeap
 * @return int
 */
extern int Pop(Heap *pHeap);

#endif // MAXHEAP_H_
