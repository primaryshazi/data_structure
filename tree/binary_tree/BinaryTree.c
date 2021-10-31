#include "BinaryTree.h"

TreeNode Init(BinaryTree tree)
{
    return Destroy(tree);
}

TreeNode Destroy(BinaryTree tree)
{
    if (NULL != tree)
    {
        Destroy(tree->left);
        Destroy(tree->right);
        free(tree);
        tree = NULL;
    }

    return NULL;
}

TreeNode Insert(BinaryTree tree, int key)
{
    if (NULL == tree)
    {
        // 当前节点为空则表示找到合适位置
        tree = (TreeNode)calloc(1, sizeof(struct Node));
        if (NULL == tree)
        {
            return NULL;
        }

        tree->key = key;
        tree->left = NULL;
        tree->right = NULL;
    }
    else
    {
        /**
         * 若key小于当前节点key，则在其左子树插入，并返回左子树
         * 若key大于当前节点key，则在其右子树插入，并返回右子树
         * 若相等则不作为直接返回子树
         */
        if (key < tree->key)
        {
            tree->left = Insert(tree->left, key);
        }
        else if (key > tree->key)
        {
            tree->right = Insert(tree->right, key);
        }
    }

    return tree;
}

TreeNode Erase(BinaryTree tree, int key)
{
    if (NULL != tree)
    {
        /**
         * 若key小于当前节点key，则在左子树删除节点
         * 若key大于当前节点key，则在右子树删除节点
         * 若相等则删除节点
         */
        if (key < tree->key)
        {
            tree->left = Erase(tree->left, key);
        }
        else if (key > tree->key)
        {
            tree->right = Erase(tree->right, key);
        }
        else
        {
            /**
             * 若其左右节点均不为空，则找到右子树最小值，将其赋予当前节点，并删除右子树中最小节点
             * 若其左子树为空，则将当前节点置为右子树
             * 若其右子树为空，则将当前节点置为左子树
             */
            if (NULL != tree->right && NULL != tree->left)
            {
                TreeNode node = FindMin(tree->right);

                tree->key = node->key;
                tree->right = Erase(tree->right, tree->key);
            }
            else
            {
                TreeNode node = tree;

                tree = NULL == tree->left ? tree->right : tree->left;
                free(node);
                node = NULL;
            }
        }
    }

    return tree;
}

TreeNode FindMax(BinaryTree tree)
{
    if (NULL != tree)
    {
        while (NULL != tree->right)
        {
            tree = tree->right;
        }
    }

    return tree;
}

TreeNode FindMin(BinaryTree tree)
{
    if (NULL != tree)
    {
        while (NULL != tree->left)
        {
            tree = tree->left;
        }
    }

    return tree;
}

TreeNode Find(BinaryTree tree, int key)
{
    if (NULL == tree)
    {
        return NULL;
    }

    if (key < tree->key)
    {
        return Find(tree->left, key);
    }
    else if (key > tree->key)
    {
        return Find(tree->right, key);
    }
    else
    {
        return tree;
    }
}
