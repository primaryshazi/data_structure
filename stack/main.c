#include "Stack.h"

#include <stdio.h>

void Print(Stack *pStack)
{
    StackNode node = pStack->next;

    while (NULL != node)
    {
        printf("%d\n", node->element);
        node = node->next;
    }
    printf("\n");
}

int main()
{
    Stack stack;

    Init(&stack);

    for (int i = 0; i < 10; i++)
    {
        Push(&stack, i);
    }

    /**
     * => 9
     * => 8
     * => 7
     * => 6
     * => 5
     * => 4
     * => 3
     * => 2
     * => 1
     * => 0
     */
    Print(&stack);

    for (int i = 0; i < 5; i++)
    {
        Pop(&stack);
    }

    /**
     * => 4
     * => 3
     * => 2
     * => 1
     * => 0
     */
    Print(&stack);

    Destroy(&stack);

    return 0;
}
