#ifndef TREE_H
#define TREE_H

#include "less.h"
#include "treenode.h"

template <class T, template<typename> class Order = Less > class Tree {

private:
    TreeNode<T, Order> m_root;

};

#endif // TREE_H
