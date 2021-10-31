#include "LoopList.h"

#include <stdio.h>

void Print(LoopList *pList)
{
    LinkNode node = pList->next;

    do
    {
        if (NULL == node)
        {
            break;
        }
        printf("%d\n", node->element);
        node = node->next;
    } while (node != pList->next);
    printf("\n");
}

int main()
{
    LoopList list;

    Init(&list);

    for (int i = 0; i < 10; i++)
    {
        Insert(&list, list.next, i * 10);
    }

    /**
     * => 90
     * => 80
     * => 70
     * => 60
     * => 50
     * => 40
     * => 30
     * => 20
     * => 10
     * => 0
     */
    Print(&list);

    for (int i = 0; i < 5; i++)
    {
        Erase(&list, FindFirst(&list, i * 20, NULL));
    }

    /**
     * => 90
     * => 70
     * => 50
     * => 30
     * => 10
     */
    Print(&list);

    Destroy(&list);

    return 0;
}
