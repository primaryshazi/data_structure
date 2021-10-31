#include "ListHash.h"

#include <stdio.h>

#define BUFFER_SIZE 64
#define TABLE_LENGTH 11

void Print(HashTable *pHashTable)
{
    for (int i = 0; i < pHashTable->length; i++)
    {
        HashNode list = pHashTable->hashList + i;
        HashNode node = list->next;

        while (NULL != node)
        {
            printf("%s->", node->element);
            node = node->next;
        }
        printf("NULL\n");
    }
    printf("\n");
}

int main()
{
    HashTable hashTable;

    if (Init(&hashTable, TABLE_LENGTH) == 0)
    {
        for (int i = 0; i < 3 * TABLE_LENGTH; i++)
        {
            char str[BUFFER_SIZE] = "";
            snprintf(str, BUFFER_SIZE - 1, "%04d", i * i);
            Insert(&hashTable, str);
        }

        /**
         * => 0000->0121->0484->NULL
         * => 0001->0100->0144->0441->0529->1024->NULL
         * => NULL
         * => 0025->0036->0256->0289->0729->0784->NULL
         * => 0004->0081->0169->0400->0576->0961->NULL
         * => 0016->0049->0225->0324->0676->0841->NULL
         * => NULL
         * => NULL
         * => NULL
         * => 0009->0064->0196->0361->0625->0900->NULL
         * => NULL
         */
        Print(&hashTable);

        for (int i = TABLE_LENGTH; i < 2 * TABLE_LENGTH; i++)
        {
            char str[BUFFER_SIZE] = "";
            snprintf(str, BUFFER_SIZE - 1, "%04d", i * i);
            Erase(&hashTable, str);
        }

        /**
         * => 0000->0484->NULL
         * => 0001->0100->0529->1024->NULL
         * => NULL
         * => 0025->0036->0729->0784->NULL
         * => 0004->0081->0576->0961->NULL
         * => 0016->0049->0676->0841->NULL
         * => NULL
         * => NULL
         * => NULL
         * => 0009->0064->0625->0900->NULL
         * => NULL
         */
        Print(&hashTable);

        Destroy(&hashTable);
    }

    return 0;
}
