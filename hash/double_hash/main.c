#include "DoubleHash.h"

#include <stdio.h>

#define BUFFER_SIZE 64

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
        for (int i = 0; i < TABLE_LENGTH; i++)
        {
            char str[BUFFER_SIZE] = "";
            snprintf(str, BUFFER_SIZE - 1, "%03d", i * i);
            Insert(&hashTable, str);
        }

        /**
         * => NULL
         * => 049
         * => 009
         * => 100
         * => 000
         * => 001
         * => NULL
         * => 025
         * => 004
         * => 016
         * => 064
         */
        Print(&hashTable);

        for (int i = 0; i < TABLE_LENGTH / 2; i++)
        {
            char str[BUFFER_SIZE] = "";
            snprintf(str, BUFFER_SIZE - 1, "%03d", i * i);
            Erase(&hashTable, str);
        }

        /**
         * => NULL
         * => 049
         * => NULL
         * => 100
         * => NULL
         * => NULL
         * => NULL
         * => 025
         * => NULL
         * => NULL
         * => 064
         */
        Print(&hashTable);

        for (int i = 0; i < TABLE_LENGTH; i++)
        {
            char str[BUFFER_SIZE] = "";
            snprintf(str, BUFFER_SIZE - 1, "%03d", i * i);
            Insert(&hashTable, str);
        }

        /**
         * => NULL
         * => 049
         * => 009
         * => 100
         * => 000
         * => 001
         * => NULL
         * => 025
         * => 004
         * => 016
         * => 064
         */
        Print(&hashTable);

        Destroy(&hashTable);
    }

    return 0;
}
