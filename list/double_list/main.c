#include "DoubleList.h"

#include <stdio.h>

void Print(DoubleList *pList, bool reverse)
{
    LinkNode node = (reverse ? pList->prev : pList->next);

    while (NULL != node)
    {
        printf("%d\n", node->element);
        node = (reverse ? node->prev : node->next);
    }
    printf("\n");
}

int main()
{
    DoubleList list;

    Init(&list);

    for (int i = 0; i < 10; i++)
    {
        Insert(&list, FindFirst(&list, 50, NULL), i * 10);
    }

    /**
     * => 0
     * => 10
     * => 20
     * => 30
     * => 40
     * => 60
     * => 70
     * => 80
     * => 90
     * => 50
     *
     * => 50
     * => 90
     * => 80
     * => 70
     * => 60
     * => 40
     * => 30
     * => 20
     * => 10
     * => 0
     */
    Print(&list, false);
    Print(&list, true);

    for (int i = 0; i < 5; i++)
    {
        Erase(&list, FindLast(&list, i * 20, NULL));
    }

    /**
     * => 10
     * => 30
     * => 70
     * => 90
     * => 50
     *
     * => 50
     * => 90
     * => 70
     * => 30
     * => 10
     */
    Print(&list, false);
    Print(&list, true);

    Destroy(&list);

    return 0;
}
