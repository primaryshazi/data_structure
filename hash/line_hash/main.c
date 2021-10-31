#include "LineHash.h"

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
        for (int i = 0; i < TABLE_LENGTH; i++)
        {
            char str[BUFFER_SIZE] = "";
            snprintf(str, BUFFER_SIZE - 1, "%03d", i * i);
            Insert(&hashTable, str);
        }

        /**
         * => 049
         * => 081
         * => 009
         * => 064
         * => 000
         * => 001
         * => 100
         * => 025
         * => 004
         * => 016
         * => 036
         */
        Print(&hashTable);

        for (int i = 0; i < TABLE_LENGTH / 2; i++)
        {
            char str[BUFFER_SIZE] = "";
            snprintf(str, BUFFER_SIZE - 1, "%03d", i * i);
            Erase(&hashTable, str);
        }

        /**
         * => 049
         * => 081
         * => NULL
         * => 064
         * => NULL
         * => NULL
         * => 100
         * => 025
         * => NULL
         * => NULL
         * => 036
         */
        Print(&hashTable);

        for (int i = 0; i < TABLE_LENGTH; i++)
        {
            char str[BUFFER_SIZE] = "";
            snprintf(str, BUFFER_SIZE - 1, "%03d", i * i);
            Insert(&hashTable, str);
        }

        /**
         * => 049
         * => 081
         * => 009
         * => 064
         * => 000
         * => 001
         * => 100
         * => 025
         * => 004
         * => 016
         * => 036
         */
        Print(&hashTable);

        Destroy(&hashTable);
    }

    return 0;
}
