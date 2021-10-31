#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <stdbool.h>
#include <stdlib.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

typedef struct Node
{
    int key;
    int height;
    struct Node *left;
    struct Node *right;
} * TreeNode, *AVLTree;

/**
 * @brief 初始化树
 *
 * @param tree
 * @return TreeNode
 */
extern TreeNode Init(AVLTree tree);

/**
 * @brief 销毁树
 *
 * @param tree
 * @return TreeNode
 */
extern TreeNode Destroy(AVLTree tree);

/**
 * @brief 插入元素
 *
 * @param tree
 * @param key
 * @return TreeNode
 */
extern TreeNode Insert(AVLTree tree, int key);

/**
 * @brief 移除元素
 *
 * @param tree
 * @param key
 * @return TreeNode
 */
extern TreeNode Erase(AVLTree tree, int key);

/**
 * @brief 查询最大值
 *
 * @param tree
 * @return TreeNode
 */
extern TreeNode FindMax(AVLTree tree);

/**
 * @brief 查询最小值
 *
 * @param tree
 * @return TreeNode
 */
extern TreeNode FindMin(AVLTree tree);

/**
 * @brief 查找元素
 *
 * @param tree
 * @param key
 * @return TreeNode
 */
extern TreeNode Find(AVLTree tree, int key);

#endif // AVLTREE_H_
