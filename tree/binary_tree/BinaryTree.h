#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
} *TreeNode, *BinaryTree;

/**
 * @brief 初始化树
 *
 * @param tree
 * @return TreeNode
 */
extern TreeNode Init(BinaryTree tree);

/**
 * @brief 销毁树
 *
 * @param tree
 * @return TreeNode
 */
extern TreeNode Destroy(BinaryTree tree);

/**
 * @brief 插入元素
 *
 * @param tree
 * @param key
 * @return TreeNode
 */
extern TreeNode Insert(BinaryTree tree, int key);

/**
 * @brief 移除元素
 *
 * @param tree
 * @param key
 * @return TreeNode
 */
extern TreeNode Erase(BinaryTree tree, int key);

/**
 * @brief 查询最大值
 *
 * @param tree
 * @return TreeNode
 */
extern TreeNode FindMax(BinaryTree tree);

/**
 * @brief 查询最小值
 *
 * @param tree
 * @return TreeNode
 */
extern TreeNode FindMin(BinaryTree tree);

/**
 * @brief 查找元素
 *
 * @param tree
 * @param key
 * @return TreeNode
 */
extern TreeNode Find(BinaryTree tree, int key);

#endif // BINARYTREE_H_
