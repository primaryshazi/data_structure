#ifndef BUILDHEAP_H_
#define BUILDHEAP_H_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

typedef enum HeapType
{
    Heap_Max,
    Heap_Min
} HeapType;

typedef struct Heap
{
    int length;
    int size;
    int *array;
    HeapType type;
} Heap;

/**
 * @brief 初始化堆
 *
 * @param pHeap
 * @param length
 * @param type
 * @return int
 */
extern int Init(Heap *pHeap, int length, HeapType type);

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

/**
 * @brief 修改堆中的值
 *
 * @param pHeap
 * @param index
 * @param element
 * @return int
 */
extern int Modify(Heap *pHeap, int index, int element);

/**
 * @brief 构建堆
 *
 * @param pHeap
 * @return int
 */
extern int BuildHeap(Heap *pHeap);

#endif // BUILDHEAP_H_
