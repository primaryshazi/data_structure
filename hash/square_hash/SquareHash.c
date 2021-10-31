#include "SquareHash.h"

int Hash(const char *key, int size)
{
    unsigned int value = 0;

    while (*key != '\0')
    {
        value = (value << 5) + *key++;
    }

    return value % size;
}

int Init(HashTable *pHashTable, int length)
{
    assert(NULL != pHashTable);

    if (length <= 0)
    {
        return -1;
    }

    // 申请length个哈希链表节点
    HashNode node = (HashNode)calloc(length, sizeof(struct Node));

    if (NULL == pHashTable)
    {
        return -1;
    }
    for (int i = 0; i < length; i++)
    {
        node[i].element = NULL;
        node[i].status = Node_Empty;
    }

    pHashTable->table = node;    // 指向哈希链表节点
    pHashTable->length = length; // 哈希表长度
    pHashTable->size = 0;        // 哈希表元素数量

    return 0;
}

void Destroy(HashTable *pHashTable)
{
    assert(NULL != pHashTable);

    // 遍历所有哈希链表
    for (int i = 0; i < pHashTable->length; i++)
    {
        if (pHashTable->table[i].status == Node_Full)
        {
            free(pHashTable->table[i].element);
            pHashTable->table[i].element = NULL;
            pHashTable->table[i].status = Node_Empty;
        }
    }

    free(pHashTable->table);
    pHashTable->table = NULL;
    pHashTable->length = 0;
    pHashTable->size = 0;
}

int Size(HashTable *pHashTable)
{
    assert(NULL != pHashTable);

    return pHashTable->size;
}

bool Empty(HashTable *pHashTable)
{
    return Size(pHashTable) == 0;
}

HashNode Find(HashTable *pHashTable, const char *key)
{
    assert(NULL != pHashTable);

    int index = Hash(key, pHashTable->length); // 求指定key的哈希值
    int squareIndex = 0;

    while (Node_Empty != pHashTable->table[index].status && strcmp(pHashTable->table[index].element, key) != 0)
    {
        index += 2 * ++squareIndex - 1;
        if (index >= pHashTable->length)
        {
            index -= pHashTable->length;

            if (index >= pHashTable->length)
            {
                index %= pHashTable->length;
                break;
            }
        }
    }

    return &(pHashTable->table[index]);
}

int Insert(HashTable *pHashTable, const char *key)
{
    assert(NULL != pHashTable);

    HashNode insertNode = Find(pHashTable, key);

    if (Node_Full == insertNode->status)
    {
        return -1;
    }
    insertNode->element = (char *)calloc(strlen(key) + 1, sizeof(char));

    if (NULL == insertNode->element)
    {
        return -1;
    }

    memcpy(insertNode->element, key, strlen(key));
    insertNode->status = Node_Full;
    pHashTable->size++;

    return 0;
}

int Erase(HashTable *pHashTable, const char *key)
{
    HashNode pos = Find(pHashTable, key);

    if (NULL == pos)
    {
        return -1;
    }

    free(pos->element);
    pos->element = NULL;
    pos->status = Node_Empty;
    pHashTable->size--;

    return 0;
}
