#ifndef SKIPLIST_H_
#define SKIPLIST_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define SKIPLIST_MAX_LEVEL  5
#define SKIPLIST_P          0.25

typedef struct SkipListNode
{
    int value;
    struct SkipListNode *backward;      // 后退指针
    struct SkipListLevel {
        struct SkipListNode *forward;   // 前进指针
    } level[];                          // 节点的层
} SkipListNode;

typedef struct SkipList
{
    struct SkipListNode *head;  // 头指针
    struct SkipListNode *tail;  // 尾指针
    unsigned int length;        // 节点数，不包含头节点
    int level;                  // 当前跳表中具有最大层数的节点的层数
} SkipList;

typedef struct SkipListNode SkipListNode;
typedef struct SkipList SkipList;
typedef struct SkipListLevel SkipListLevel;

/**
 * @brief 创建表
 *
 * @return SkipList *
 */
extern SkipList *Create();

/**
 * @brief 销毁表
 *
 * @param list
 */
extern void Destroy(SkipList *list);

/**
 * @brief 查找节点
 *
 * @param list
 * @param target
 * @return SkipListNode *
 */
extern SkipListNode *Find(SkipList *list, int target);

/**
 * @brief 添加节点
 *
 * @param list
 * @param target
 * @return SkipListNode *
 */
extern SkipListNode *Insert(SkipList *list, int target);

/**
 * @brief 删除节点
 *
 * @param list
 * @param target
 * @return bool
 */
extern bool Erase(SkipList *list, int target);

/**
 * @brief 修改值
 *
 * @param list
 * @param target
 * @param value
 * @return SkipListNode *
 */
extern SkipListNode *Modify(SkipList *list, int target, int value);

/**
 * @brief 打印表
 *
 * @param list
 */
extern void PrintList(SkipList *list);

#endif // SKIPLIST_H_
