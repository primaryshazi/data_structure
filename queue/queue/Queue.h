#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node
{
    int element;
    struct Node *next;
} *QueueNode, Queue;

/**
 * @brief 初始化队列
 *
 * @param pQueue
 */
extern void Init(Queue *pQueue);

/**
 * @brief 销毁队列
 *
 * @param pQueue
 */
extern void Destroy(Queue *pQueue);

/**
 * @brief 获取队列长度
 *
 * @param pQueue
 * @return int
 */
extern int Size(Queue *pQueue);

/**
 * @brief 队列是否为空
 *
 * @param pQueue
 * @return bool
 */
extern bool Empty(Queue *pQueue);

/**
 * @brief 获取头部元素
 *
 * @param pQueue
 * @param pElement
 * @return int
 */
extern int Top(Queue *pQueue, int *pElement);

/**
 * @brief 推入队列
 *
 * @param pQueue
 * @param element
 * @return int
 */
extern int Push(Queue *pQueue, int element);

/**
 * @brief 推出队列
 *
 * @param pQueue
 * @return int
 */
extern int Pop(Queue *pQueue);

#endif // QUEUE_H_
