#include "SkipList.h"

int main()
{
    SkipList *skipList = Create();

    for (int i = 0; i < 10; i++)
    {
        Insert(skipList, i);
    }

    PrintList(skipList);
    printf("\n");

    Erase(skipList, 3);
    PrintList(skipList);
    printf("\n");

    Modify(skipList, 5, 10);
    PrintList(skipList);
    printf("\n");

    Destroy(skipList);

    return 0;
}
