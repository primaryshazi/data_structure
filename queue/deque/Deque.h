#ifndef DEQUE_H_
#define DEQUE_H_

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node
{
    int element;
    struct Node *next;
} *DequeNode, Deque;

/**
 * @brief 初始化队列
 *
 * @param pDeque
 */
extern void Init(Deque *pDeque);

/**
 * @brief 销毁队列
 *
 * @param pDeque
 */
extern void Destroy(Deque *pDeque);

/**
 * @brief 获取队列长度
 *
 * @param pDeque
 * @return int
 */
extern int Size(Deque *pDeque);

/**
 * @brief 队列是否为空
 *
 * @param pDeque
 * @return bool
 */
extern bool Empty(Deque *pDeque);

/**
 * @brief 获取头部元素
 *
 * @param pDeque
 * @param pElement
 * @return int
 */
extern int Front(Deque *pDeque, int *pElement);

/**
 * @brief 获取尾部元素
 *
 * @param pDeque
 * @param pElement
 * @return int
 */
extern int Back(Deque *pDeque, int *pElement);

/**
 * @brief 头部插入队列
 *
 * @param pDeque
 * @param element
 * @return int
 */
extern int PushFront(Deque *pDeque, int element);

/**
 * @brief 头部推出
 *
 * @param pDeque
 * @return int
 */
extern int PopFront(Deque *pDeque);

/**
 * @brief 尾部插入队列
 *
 * @param pDeque
 * @param element
 * @return int
 */
extern int PushBack(Deque *pDeque, int element);

/**
 * @brief 尾部推出
 *
 * @param pDeque
 * @return int
 */
extern int PopBack(Deque *pDeque);

#endif // DEQUE_H_
