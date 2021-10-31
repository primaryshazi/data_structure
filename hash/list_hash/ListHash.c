#include "ListHash.h"

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
    HashList hashList = (HashNode)calloc(length, sizeof(struct Node));

    if (NULL == pHashTable)
    {
        return -1;
    }
    for (int i = 0; i < length; i++)
    {
        hashList[i].element = NULL;
        hashList[i].next = NULL;
    }
    pHashTable->hashList = hashList; // 指向哈希链表节点
    pHashTable->length = length;     // 哈希表长度
    pHashTable->size = 0;            // 哈希表元素数量

    return 0;
}

void Destroy(HashTable *pHashTable)
{
    assert(NULL != pHashTable);

    // 遍历所有哈希链表
    for (int i = 0; i < pHashTable->length; i++)
    {
        HashNode list = pHashTable->hashList + i; // 指向每个哈希链表
        HashNode node = list->next;               // 指向该哈希链表的头节点

        // 删除每个哈希链表的节点
        while (NULL != node)
        {
            list->next = list->next->next;

            free(node->element);
            node->element = NULL;
            free(node);
            node = NULL;

            node = list->next;
        }
    }

    free(pHashTable->hashList);
    pHashTable->length = 0;
    pHashTable->size = 0;
    pHashTable->hashList = NULL;
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
    if (Empty(pHashTable))
    {
        return NULL;
    }

    int index = Hash(key, pHashTable->length); // 求指定key的哈希值

    HashList list = pHashTable->hashList + index; // 找到对应哈希链表
    HashNode node = list->next;

    // 遍历该哈希链表下的所有节点
    while (NULL != node)
    {
        if (strcmp(node->element, key) == 0)
        {
            return node;
        }
        node = node->next;
    }

    return NULL;
}

int Insert(HashTable *pHashTable, const char *key)
{
    assert(NULL != pHashTable);

    int index = Hash(key, pHashTable->length); // 求指定key的哈希值

    HashList list = pHashTable->hashList + index; // 找到对应哈希链表
    HashNode tailNode = list;                     // 获取哈希表的尾节点

    while (NULL != tailNode->next)
    {
        if (strcmp(tailNode->next->element, key) == 0)
        {
            return -1;
        }
        tailNode = tailNode->next;
    }

    HashNode newNode = (HashNode)calloc(1, sizeof(struct Node));

    if (NULL == newNode)
    {
        return -1;
    }

    // 申请元素内存
    newNode->element = (char *)calloc(strlen(key) + 1, sizeof(char));

    if (NULL == newNode->element)
    {
        free(newNode);
        return -1;
    }

    memcpy(newNode->element, key, strlen(key));

    newNode->next = NULL;
    tailNode->next = newNode;
    pHashTable->size++;

    return 0;
}

int Erase(HashTable *pHashTable, const char *key)
{
    if (Empty(pHashTable))
    {
        return -1;
    }

    int index = Hash(key, pHashTable->length);      // 求指定key的哈希值

    HashList list = pHashTable->hashList + index;   // 找到对应哈希链表
    HashNode prevNode = list;                       // 指定哈希节点的前节点

    while (NULL != prevNode->next)
    {
        if (strcmp(prevNode->next->element, key) == 0)
        {
            HashNode node = prevNode->next;

            prevNode->next = prevNode->next->next;
            free(node->element);
            node->element = NULL;
            free(node);
            node = NULL;

            pHashTable->size--;

            return 0;
        }
        prevNode = prevNode->next;
    }

    return 0;
}
