#include "ReHash.h"

#include <stdio.h>

#define BUFFER_SIZE 64
#define TABLE_LENGTH 11

void Print(HashTable *pHashTable)
{
    for (int i = 0; i < pHashTable->length; i++)
    {
        if (Node_Full == pHashTable->table[i].status)
        {
            printf("%s\n", pHashTable->table[i].element);
        }
        else
        {
            printf("%s\n", "NULL");
        }
    }

    printf("\n");
}

int main()
{
    HashTable hashTable;

    if (Init(&hashTable, TABLE_LENGTH) == 0)
    {
        for (int i = 0; i < 2 * TABLE_LENGTH; i++)
        {
            char str[BUFFER_SIZE] = "";
            snprintf(str, BUFFER_SIZE - 1, "%03d", i * i);
            Insert(&hashTable, str);
        }

        /**
         * => 256
         * => 169
         * => 064
         * => 196
         * => 000
         * => 001
         * => 441
         * => 025
         * => 004
         * => 049
         * => 225
         * => 289
         * => 400
         * => 009
         * => 361
         * => 121
         * => 100
         * => 144
         * => 036
         * => 081
         * => 016
         * => 324
         */
        Print(&hashTable);

        for (int i = 0; i < TABLE_LENGTH; i++)
        {
            char str[BUFFER_SIZE] = "";
            snprintf(str, BUFFER_SIZE - 1, "%03d", i * i);
            Erase(&hashTable, str);
        }

        /**
         * => 256
         * => 169
         * => NULL
         * => 196
         * => NULL
         * => NULL
         * => 441
         * => NULL
         * => NULL
         * => 225
         * => 289
         * => 400
         * => NULL
         * => 361
         * => 121
         * => NULL
         * => 144
         * => NULL
         * => NULL
         * => NULL
         * => 324
         */
        Print(&hashTable);

        for (int i = 0; i < TABLE_LENGTH; i++)
        {
            char str[BUFFER_SIZE] = "";
            snprintf(str, BUFFER_SIZE - 1, "%03d", i * i);
            Insert(&hashTable, str);
        }

        /**
         * => 256
         * => 169
         * => 064
         * => 196
         * => 000
         * => 001
         * => 441
         * => 025
         * => 004
         * => 049
         * => 225
         * => 289
         * => 400
         * => 009
         * => 361
         * => 121
         * => 100
         * => 144
         * => 036
         * => 081
         * => 016
         * => 324
         */
        Print(&hashTable);

        Destroy(&hashTable);
    }

    return 0;
}
