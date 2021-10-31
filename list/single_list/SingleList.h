#ifndef SINGLELIST_H_
#define SINGLELIST_H_

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node
{
    int element;
    struct Node *next;
} *LinkNode, *Position, SingleList;

/**
 * @brief 初始化链表
 *
 * @param pList
 */
extern void Init(SingleList *pList);

/**
 * @brief 销毁链表
 *
 * @param pList
 */
extern void Destroy(SingleList *pList);

/**
 * @brief 链表长度
 *
 * @param pList
 * @return int
 */
extern int Size(SingleList *pList);

/**
 * @brief 链表是否为空
 *
 * @param pList
 * @return true
 * @return false
 */
extern bool Empty(SingleList *pList);

/**
 * @brief 通过索引查找
 *
 * @param pList
 * @param index
 * @return Position
 */
extern Position Index(SingleList *pList, int index);

/**
 * @brief 查找第一个的位置
 *
 * @param pList
 * @param element
 * @param position
 * @return Position
 */
extern Position FindFirst(SingleList *pList, int element, Position fromPos);

/**
 * @brief 查找最后一个的位置
 *
 * @param pList
 * @param element
 * @param position
 * @return Position
 */
extern Position FindLast(SingleList *pList, int element, Position fromPos);

/**
 * @brief 指定位置之前插入
 *
 * @param pList
 * @param linkNode
 * @param element
 * @return int
 */
extern int Insert(SingleList *pList, Position position, int element);

/**
 * @brief 指定位置删除
 *
 * @param pList
 * @param linkNode
 * @return int
 */
extern int Erase(SingleList *pList, Position position);

/**
 * @brief 反转链表
 *
 * @param pList
 */
extern void Reversal(SingleList *pList);

#endif  // SINGLELIST_H_
