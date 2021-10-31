#include "SingleList.h"

#include <stdio.h>

void Print(SingleList *pList)
{
    LinkNode node = pList->next;

    while (NULL != node)
    {
        printf("%d\n", node->element);
        node = node->next;
    }
    printf("\n");
}

int main()
{
    SingleList list;

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
     */
    Print(&list);

    /**
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
    Reversal(&list);

    Print(&list);

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
     */
    Print(&list);

    Destroy(&list);

    return 0;
}
