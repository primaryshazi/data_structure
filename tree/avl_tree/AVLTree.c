#include "AVLTree.h"

// 获取节点高度
static int Height(TreeNode node)
{
    return NULL == node ? -1 : node->height;
}

// 右子树向左旋
static TreeNode Left_Rotate(AVLTree tree)
{
    /**
     * 情况如下
     * 1
     *  \
     *   2
     *    \
     *     3
     *
     * 左旋如下
     *   2
     *  / \
     * 1   3
     */

    TreeNode node = tree->right;

    tree->right = node->left;
    node->left = tree;

    tree->height = MAX(Height(tree->left), Height(tree->right)) + 1;
    node->height = MAX(Height(tree->left), Height(node->right)) + 1;

    return node;
}

// 左子树向右旋
static TreeNode Right_Rotate(AVLTree tree)
{
    /**
     * 情况如下
     *     3
     *    /
     *   2
     *  /
     * 1
     *
     * 右旋如下
     *   2
     *  / \
     * 1   3
     */

    TreeNode node = node = tree->left;

    tree->left = node->right;
    node->right = tree;

    tree->height = MAX(Height(tree->left), Height(tree->right)) + 1;
    node->height = MAX(Height(node->left), Height(tree->right)) + 1;

    return node;
}

// 先右子树向左旋，然后左子树向右旋
static TreeNode LR_Rotate(AVLTree tree)
{
    /**
     * 情况如下
     * 1
     *  \
     *   3
     *  /
     * 2
     *
     * 右旋如下
     * 1
     *  \
     *   2
     *    \
     *     3
     *
     * 左旋如下
     *   2
     *  / \
     * 1   3
     */

    /**
     * 传入右子树
     *   3
     *  /
     * 2
     *
     * 右旋如下
     * 2
     *  \
     *   3
     */
    tree->right = Right_Rotate(tree->right);

    return Left_Rotate(tree);
}

// 先左子树向右旋，然后右子树向左旋
static TreeNode RL_Rotate(AVLTree tree)
{
    /**
     * 情况如下
     *   3
     *  /
     * 1
     *  \
     *   2
     *
     * 左旋如下
     *     3
     *    /
     *   2
     *  /
     * 1
     *
     * 右旋如下
     *   2
     *  / \
     * 1   3
     */

    /**
     * 传入左子树
     * 1
     *  \
     *   2
     *
     * 左旋如下
     *   2
     *  /
     * 1
     */
    tree->left = Left_Rotate(tree->left);

    return Right_Rotate(tree);
}

TreeNode Init(AVLTree tree)
{
    return Destroy(tree);
}

TreeNode Destroy(AVLTree tree)
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

TreeNode Insert(AVLTree tree, int key)
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
        tree->height = 0;
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

            // 若在其左子树插完之后，左子树比右子树高1以上
            if (Height(tree->left) - Height(tree->right) > 1)
            {
                /**
                 * 当key小于树左子节点key，形成"/"形状，则向右旋转为"^"型
                 * 当key大于树左子节点key，形成"<"形状，则左子树向左旋转为"/"型，然后再右旋转为"^"型
                 */
                if (key < tree->left->key)
                {
                    tree = Right_Rotate(tree);
                }
                else
                {
                    tree = RL_Rotate(tree);
                }
            }
        }
        else if (key > tree->key)
        {
            tree->right = Insert(tree->right, key);

            // 若在其右子树插完之后，右子树比左子树高1以上
            if (Height(tree->right) - Height(tree->left) > 1)
            {
                /**
                 * 当key大于树右子节点key，形成"\"形状，则向左旋转为"^"型
                 * 当key小于树右子节点key，形成">"形状，则右子树向左旋转为"\"型，然后再左旋转为"^"型
                 */
                if (key > tree->right->key)
                {
                    tree = Left_Rotate(tree);
                }
                else
                {
                    tree = LR_Rotate(tree);
                }
            }
        }
    }

    tree->height = MAX(Height(tree->left), Height(tree->right)) + 1;

    return tree;
}

TreeNode Erase(AVLTree tree, int key)
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

            if (Height(tree->right) - Height(tree->left) > 1)
            {
                TreeNode node = tree->right;

                /**
                 * 当右子树的左节点的高度大于右节点时，先右子树先向左旋转，后左侧向右旋转
                 * 当右子树的左节点的高度不大于右节点时，右侧向左旋转
                 */
                if (Height(node->left) > Height(node->right))
                {
                    tree = LR_Rotate(tree);
                }
                else
                {
                    tree = Left_Rotate(tree);
                }
            }
        }
        else if (key > tree->key)
        {
            tree->right = Erase(tree->right, key);

            if (Height(tree->left) - Height(tree->right) > 1)
            {
                TreeNode node = tree->left;

                /**
                 * 当左子树的右节点的高度大于左节点时，先左子树先向右旋转，后右侧向左旋转
                 * 当左子树的右节点的高度不大于左节点时，左侧向右旋转
                 */
                if (Height(node->right) > Height(node->left))
                {
                    tree = RL_Rotate(tree);
                }
                else
                {
                    tree = Right_Rotate(tree);
                }
            }
        }
        else
        {
            /**
             * 若其左右节点均不为空
             * 当左子树高度高于右子树时，从左子树中找出最大的节点替换当前节点
             * 当左子树高度不高于右子树时，从右子树中找出最小节点替换当前节点
             *
             * 若其左子树为空，则将当前节点置为右子树
             * 若其右子树为空，则将当前节点置为左子树
             */
            if (NULL != tree->left && NULL != tree->right)
            {
                if (Height(tree->left) > Height(tree->right))
                {
                    TreeNode leftMaxNode = FindMax(tree->left);

                    tree->key = leftMaxNode->key;
                    tree->left = Erase(tree->left, tree->key);
                }
                else
                {
                    TreeNode rightMinNode = FindMin(tree->right);

                    tree->key = rightMinNode->key;
                    tree->right = Erase(tree->right, tree->key);
                }
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

TreeNode FindMax(AVLTree tree)
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

TreeNode FindMin(AVLTree tree)
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

TreeNode Find(AVLTree tree, int key)
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
