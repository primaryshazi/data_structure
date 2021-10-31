#ifndef RBTREE_H_
#define RBTREE_H_

#include <iostream>
#include <new>

typedef enum {
    RED = 0,
    BLACK = 1
} Color;

template <class T>
struct RBTreeNode
{
    Color _color;           // 颜色
    T _key;                 // 关键字
    RBTreeNode *_left;      // 左孩子
    RBTreeNode *_right;     // 右孩子
    RBTreeNode *_parent;    // 父节点
};

template<class T>
class RBTree
{
    typedef RBTreeNode<T> RBTreeNode;

private:
    /**
     * @brief 创建节点
     *
     * @param key
     * @return Node *
     */
    RBTreeNode *createNode(const T &key = T())
    {
        RBTreeNode *node = new RBTreeNode();

        node->_color = RED;
        node->_key = key;
        node->_left = _nil;
        node->_right = _nil;
        node->_parent = _nil;

        return node;
    }

    /**
     * @brief 查找节点
     *
     * @param root
     * @param key
     * @return Node *
     */
    RBTreeNode *find(RBTreeNode *root, const T &key) const
    {
        if (root == _nil)
        {
            return _nil;
        }

        if (key < root->_key)
        {
            return find(root->_left, key);
        }
        if (key > root->_key)
        {
            return find(root->_right, key);
        }
        else
        {
            return root;
        }
    }

    /**
     * @brief 插入节点修正
     *
     * @param node
     */
    void insertFixup(RBTreeNode *node)
    {
        while (node->_parent->_color == RED)
        {
            if (node->_parent == node->_parent->_parent->_left)
            {
                RBTreeNode *rightUncle = node->_parent->_parent->_right;

                if (rightUncle->_color == RED)
                {
                    node->_parent->_color = BLACK;
                    rightUncle->_color = BLACK;
                    node->_parent->_parent->_color = RED;
                    node = node->_parent->_parent;
                }
                else
                {
                    if (node == node->_parent->_right)
                    {
                        node = node->_parent;
                        leftRotate(node);
                    }
                    node->_parent->_color = BLACK;
                    node->_parent->_parent->_color = RED;
                }
            }
            else
            {
                RBTreeNode *leftUncle = node->_parent->_parent->_left;

                if (leftUncle->_color == RED)
                {
                    node->_parent->_color = BLACK;
                    leftUncle->_color = BLACK;
                    node->_parent->_parent->_color = RED;
                    node = node->_parent->_parent;
                }
                else
                {
                    if (node == node->_parent->_left)
                    {
                        node = node->_parent;
                        rightRotate(node);
                    }
                    node->_parent->_color = BLACK;
                    node->_parent->_parent->_color = RED;
                }
            }
        }
        _root->_color = BLACK;
    }

    /**
     * @brief 删除节点
     *
     * @param node
     */
    void erase(RBTreeNode *node)
    {
        RBTreeNode *child = _nil;
        RBTreeNode *current = node;
        Color curColor = current->_color;

        if (node->_left == _nil)
        {
            child = node->_right;
            transplant(node, node->_right);
        }
        else if (node->_right == _nil)
        {
            child = node->_left;
            transplant(node, node->_left);
        }
        else
        {
            current = minimum(node->_right);
            curColor = current->_color;
            child = current->_right;
            if (current->_parent == node)
            {
                child->_parent = current;
            }
            else
            {
                transplant(current, current->_right);
                current->_right = node->_right;
                current->_right->_parent = current;
            }
            transplant(node, current);
            current->_left = node->_left;
            node->_left->_parent = current;
            current->_color = node->_color;
        }
        if (curColor == BLACK)
        {
            eraseFixup(child);
        }
    }

    /**
     * @brief 删除节点调整
     *
     * @param node
     */
    void eraseFixup(RBTreeNode *node)
    {
        while (node != _root && node->_color == BLACK)
        {
            if (node == node->_parent->_left)
            {
                RBTreeNode *rightBrother = node->_parent->_right;

                if (rightBrother->_color == RED)
                {
                    rightBrother->_color = BLACK;
                    node->_parent->_color = RED;
                    leftRotate(node->_parent);
                    rightBrother = node->_parent->_right;
                }
                if (rightBrother->_left->_color == BLACK && rightBrother->_right->_color == BLACK)
                {
                    rightBrother->_color = RED;
                    node = node->_parent;
                }
                else
                {
                    if (rightBrother->_right->_color == BLACK)
                    {
                        rightBrother->_left->_color = BLACK;
                        rightBrother->_color = RED;
                        rightRotate(rightBrother);
                        rightBrother = node->_parent->_right;
                    }
                    rightBrother->_color = rightBrother->_parent->_color;
                    node->_parent->_color = BLACK;
                    rightBrother->_right->_color = BLACK;
                    leftRotate(node->_parent);
                    node = _root;
                }
            }
            else
            {
                RBTreeNode *leftBrother = node->_parent->_left;

                if (leftBrother->_color == RED)
                {
                    leftBrother->_parent->_color = RED;
                    node->_color = BLACK;
                    rightRotate(node->_parent);
                    leftBrother = node->_parent->_left;
                }
                if (leftBrother->_right->_color == BLACK && leftBrother->_left->_color == BLACK)
                {
                    leftBrother->_color = RED;
                    node = node->_parent;
                }
                else
                {
                    if (leftBrother->_left->_color == BLACK)
                    {
                        leftBrother->_right->_color = BLACK;
                        leftBrother->_color = RED;
                        leftRotate(leftBrother);
                        leftBrother = node->_parent->_left;
                    }
                    leftBrother->_color = node->_parent->_color;
                    node->_parent->_color = BLACK;
                    leftBrother->_left->_color = BLACK;
                    rightRotate(node->_parent);
                    node = _root;
                }
            }
        }
        node->_color = BLACK;
    }

    /**
     * @brief 左旋
     *
     * @param node
     */
    void leftRotate(RBTreeNode *node)
    {
        RBTreeNode *right = node->_right;

        node->_right = right->_left;
        if (right->_left != _nil)
        {
            right->_left->_parent = node;
        }

        right->_parent = node->_parent;
        if (node->_parent == _nil)
        {
            _root = right;
        }
        else
        {
            if (node == node->_parent->_left)
            {
                node->_parent->_left = right;
            }
            else
            {
                node->_parent->_right = right;
            }
        }

        right->_left = node;
        node->_parent = right;
    }

    /**
     * @brief 右旋
     *
     * @param node
     */
    void rightRotate(RBTreeNode *node)
    {
        RBTreeNode *left = node->_left;

        node->_left = left->_right;
        if (left->_right != _nil)
        {
            left->_right->_parent = node;
        }

        left->_parent = node->_parent;
        if (node->_parent == node)
        {
            _root = left;
        }
        else
        {
            if (node == node->_parent->_right)
            {
                node->_parent->_right = left;
            }
            else
            {
                node->_parent->_left = left;
            }
        }

        left->_right = node;
        node->_parent = left;
    }

    /**
     * @brief 转换节点
     *
     * @param node
     * @param child
     */
    void transplant(RBTreeNode *node, RBTreeNode *child)
    {
        if (node->_parent == _nil)
        {
            _root = child;
        }
        else if (node == node->_parent->_left)
        {
            node->_parent->_left = child;
        }
        else
        {
            node->_parent->_right = child;
        }
        child->_parent = node->_parent;
    }

    /**
     * @brief 最大节点
     *
     * @param node
     * @return Node *
     */
    RBTreeNode *maximum(RBTreeNode *node)
    {
        if (node->_right == _nil)
        {
            return node;
        }
        return maximum(node->_right);
    }

    /**
     * @brief 最小节点
     *
     * @param node
     * @return Node *
     */
    RBTreeNode *minimum(RBTreeNode *node)
    {
        if (node->_left == _nil)
        {
            return node;
        }
        return minimum(node->_left);
    }

    /**
     * @brief 销毁节点
     *
     * @param node
     */
    void destroy(RBTreeNode *node)
    {
        if (node != nullptr && node != _nil)
        {
            destroy(node->_left);
            destroy(node->_right);
            delete node;
            node = nullptr;
        }
    }

    /**
     * @brief 前序遍历
     *
     * @param node
     */
    void preOrder(RBTreeNode *node) const
    {
        if (node != nullptr && node != _nil)
        {
            std::cout << node->_key << " [" << (node->_color == BLACK ? "BLACK" : "RED") << "]" << std::endl;
            preOrder(node->_left);
            preOrder(node->_right);
        }
    }

    /**
     * @brief 中序遍历
     *
     * @param node
     */
    void inOrder(RBTreeNode *node) const
    {
        if (node != nullptr && node != _nil)
        {
            inOrder(node->_left);
            std::cout << node->_key << " [" << (node->_color == BLACK ? "BLACK" : "RED") << "]" << std::endl;
            inOrder(node->_right);
        }
    }

    /**
     * @brief 后续遍历
     *
     * @param node
     */
    void postOrder(RBTreeNode *node) const
    {
        if (node != nullptr && node != _nil)
        {
            postOrder(node->_left);
            postOrder(node->_right);
            std::cout << node->_key << " [" << (node->_color == BLACK ? "BLACK" : "RED") << "]" << std::endl;
        }
    }

public:
    RBTree()
    {
        _nil = createNode();
        _root = _nil;
        _nil->_color = BLACK;
        _size = 0;
    }

    ~RBTree()
    {
        destroy(_root);
        delete _nil;
        _nil = nullptr;
    }

    RBTree(const RBTree &) = delete;

    RBTree &operator=(const RBTree &) = delete;

    /**
     * @brief 插入节点
     *
     * @param key
     * @return bool
     */
    bool insert(const T &key)
    {
        RBTreeNode *parent = _nil;
        RBTreeNode *current = _root;

        // 查找到插入节点的父节点，若根节点为空，则父节点为空
        while (current != _nil)
        {
            parent = current;
            if (key < current->_key)
            {
                current = current->_left;
            }
            else if (key > current->_key)
            {
                current = current->_right;
            }
            else
            {
                return false;
            }
        }

        RBTreeNode *node = createNode(key);

        node->_parent = parent;

        /**
         * 若父节点为空则将根节点置为新节点
         * 若新节点值小于父节点则新节点作为左子节点，若新节点值大于父节点则新节点作为右子节点
         */
        if (parent == _nil)
        {
            _root = node;
        }
        else
        {
            if (node->_key < parent->_key)
            {
                parent->_left = node;
            }
            else
            {
                parent->_right = node;
            }
        }
        insertFixup(node);
        _size++;

        return true;
    }

    /**
     * @brief 删除节点
     *
     * @param key
     * @return bool
     */
    bool erase(const T &key)
    {
        RBTreeNode *node = find(_root, key);

        if (_nil == node)
        {
            return false;
        }
        erase(node);
        _size--;

        return true;
    }

    /**
     * @brief 删除节点
     *
     * @param node
     * @return
     */
    bool erase(const RBTreeNode *&node)
    {
        if (nullptr == node || _nil == node)
        {
            return false;
        }
        erase(node);
        _size--;

        return false;
    }

    /**
     * @brief 查找节点
     *
     * @param key
     * @return Node *
     */
    RBTreeNode *find(const T &key) const
    {
        RBTreeNode *node = find(_root, key);

        if (node == _nil)
        {
            return nullptr;
        }
        return node;
    }

    /**
     * @brief 元素数量
     *
     * @return size_t
     */
    size_t size() const
    {
        return _size;
    }

    void clear()
    {
        destroy(_root);
        _root = _nil;
        _size = 0;
    }

    /**
     * @brief 前序遍历
     */
    void preOrder() const
    {
        preOrder(_root);
        std::cout << std::endl;
    }

    /**
     * @brief 中序遍历
     */
    void inOrder() const
    {
        inOrder(_root);
        std::cout << std::endl;
    }

    /**
     * @brief 后续遍历
     */
    void postOrder() const
    {
        postOrder(_root);
        std::cout << std::endl;
    }

private:
    RBTreeNode *_root;  // 根节点
    RBTreeNode *_nil;   // 外部黑节点表示空
    size_t _size;       // 元素数量
};

#endif // RBTREE_H_
