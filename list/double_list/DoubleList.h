#ifndef DOUBLELIST_H_
#define DOUBLELIST_H_

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node
{
    int element;
    struct Node *prev;
    struct Node *next;
} *LinkNode, *Position, DoubleList;

/**
 * @brief 初始化链表
 *
 * @param pList
 */
extern void Init(DoubleList *pList);

/**
 * @brief 销毁链表
 *
 * @param pList
 */
extern void Destroy(DoubleList *pList);

/**
 * @brief 链表长度
 *
 * @param pList
 * @return int
 */
extern int Size(DoubleList *pList);

/**
 * @brief 链表是否为空
 *
 * @param pList
 * @return true
 * @return false
 */
extern bool Empty(DoubleList *pList);

/**
 * @brief 通过索引查找
 *
 * @param pList
 * @param index
 * @return Position
 */
extern Position Index(DoubleList *pList, int index);

/**
 * @brief 查找第一个的位置
 *
 * @param pList
 * @param element
 * @param position
 * @return Position
 */
extern Position FindFirst(DoubleList *pList, int element, Position fromPos);

/**
 * @brief 查找最后一个的位置
 *
 * @param pList
 * @param element
 * @param position
 * @return Position
 */
extern Position FindLast(DoubleList *pList, int element, Position fromPos);

/**
 * @brief 指定位置之前插入
 *
 * @param pList
 * @param linkNode
 * @param element
 * @return int
 */
extern int Insert(DoubleList *pList, Position position, int element);

/**
 * @brief 指定位置删除
 *
 * @param pList
 * @param linkNode
 * @return int
 */
extern int Erase(DoubleList *pList, Position position);

#endif // DOUBLELIST_H_
