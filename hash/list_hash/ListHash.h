#ifndef LISTHASH_H_
#define LISTHASH_H_

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct Node
{
    char *element;
    struct Node *next;
} *HashNode, *HashList;

typedef struct HashTable
{
    int length;
    int size;
    HashList hashList;
} HashTable;

/**
 * @brief 哈希函数
 *
 * @param key
 * @param size
 * @return int
 */
extern int Hash(const char *key, int size);

/**
 * @brief 初始化哈希表
 *
 * @param pHashTable
 * @param size
 * @return int
 */
extern int Init(HashTable *pHashTable, int size);

/**
 * @brief 销毁哈希表
 *
 * @param pHashTable
 */
extern void Destroy(HashTable *pHashTable);

/**
 * @brief 元素数量
 *
 * @param pHashTable
 * @return int
 */
extern int Size(HashTable *pHashTable);

/**
 * @brief 是否为空
 *
 * @param pHashTable
 * @return bool
 */
extern bool Empty(HashTable *pHashTable);

/**
 * @brief 查找哈希值
 *
 * @param pHashTable
 * @param key
 * @return HashNode
 */
extern HashNode Find(HashTable *pHashTable, const char *key);

/**
 * @brief 插入哈希值
 *
 * @param pHashTable
 * @param key
 * @return int
 */
extern int Insert(HashTable *pHashTable, const char *key);

/**
 * @brief 删除哈希值
 *
 * @param pHastList
 * @param key
 * @return int
 */
extern int Erase(HashTable *pHashTable, const char *key);

#endif // LISTHASH_H_
