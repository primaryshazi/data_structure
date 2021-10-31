#ifndef STACK_H_
#define STACK_H_

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node
{
    int element;
    struct Node *next;
} *StackNode, Stack;

/**
 * @brief 初始化栈
 *
 * @param pStack
 */
extern void Init(Stack *pStack);

/**
 * @brief 销毁栈
 *
 * @param pStack
 */
extern void Destroy(Stack *pStack);

/**
 * @brief 获取栈长度
 *
 * @param pStack
 * @return int
 */
extern int Size(Stack *pStack);

/**
 * @brief 栈是否为空
 *
 * @param pStack
 * @return bool
 */
extern bool Empty(Stack *pStack);

/**
 * @brief 获取顶部元素
 *
 * @param pStack
 * @param pElement
 * @return int
 */
extern int Top(Stack *pStack, int *pElement);

/**
 * @brief 推入栈
 *
 * @param pStack
 * @param element
 * @return int
 */
extern int Push(Stack *pStack, int element);

/**
 * @brief 推出栈
 *
 * @param pStack
 * @return int
 */
extern int Pop(Stack *pStack);

#endif // STACK_H_
