#include "AVLTree.h"

#include <stdio.h>
#include <stdlib.h>

void PrintFirst(TreeNode tree)
{
    if (tree != NULL)
    {
        printf("%d\n", tree->key);
        PrintFirst(tree->left);
        PrintFirst(tree->right);
    }
}

void PrintMid(TreeNode tree)
{
    if (tree != NULL)
    {
        PrintMid(tree->left);
        printf("%d\n", tree->key);
        PrintMid(tree->right);
    }
}

void PrintLast(TreeNode tree)
{
    if (tree != NULL)
    {
        PrintLast(tree->left);
        PrintLast(tree->right);
        printf("%d\n", tree->key);
    }
}

int main()
{
    const int size = 10;
    AVLTree tree = NULL;

    tree = Init(tree);

    for (int i = 0; i < size; i++)
    {
        tree = Insert(tree, i);
    }

    /**
     * => 0
     * => 1
     * => 2
     * => 3
     * => 4
     * => 5
     * => 6
     * => 7
     * => 8
     * => 9
     */
    PrintMid(tree);

    for (int i = 0; i < size / 2; i++)
    {
        tree = Erase(tree, i);
    }

    /**
     * => 5
     * => 6
     * => 7
     * => 8
     * => 9
     */
    PrintMid(tree);

    tree = Destroy(tree);

    return 0;
}
