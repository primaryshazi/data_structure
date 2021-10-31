#include "RBTRee.h"

int main()
{
    RBTree<int> tree;

    tree.insert(100);
    tree.insert(1000);
    tree.insert(10000);
    tree.insert(100000);

    std::cout << "SIZE:" << tree.size() << std::endl;
    tree.inOrder();

    tree.clear();
    std::cout << "SIZE:" << tree.size() << std::endl;
    tree.inOrder();

    tree.insert(5);
    tree.insert(4);
    tree.insert(6);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(8);
    tree.insert(1);
    tree.insert(9);
    tree.insert(0);

    std::cout << "SIZE:" << tree.size() << std::endl;
    tree.inOrder();

    if (tree.find(4) != nullptr)
    {
        tree.erase(4);
    }
    if (tree.find(5) != nullptr)
    {
        tree.erase(5);
    }
    if (tree.find(6) != nullptr)
    {
        tree.erase(6);
    }

    std::cout << "SIZE:" << tree.size() << std::endl;
    tree.inOrder();

    tree.clear();

    return 0;
}
