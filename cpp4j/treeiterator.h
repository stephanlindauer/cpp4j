#ifndef TREEITERATOR_H
#define TREEITERATOR_H

#include "treenode.h"

template <class T, template<typename> class Order > class Tree;

template <class T, template<typename> class Order > class TreeIterator {

    friend class Tree<T, Order>;

public:

    T& operator*() {
        return m_node->value();
    }

    T* operator->() {
        return m_node->value();
    }

    // zum vorherigen Element
    TreeIterator<T, Order>& operator++() {
        if (m_node == NULL)
            return *this;

        if (m_node->m_left == NULL) {
            TreeNode<T, Order> * parent = m_node;
            while (parent != NULL && parent->m_right == NULL)
                parent = parent->m_up;

            if (m_node == parent->m_right || m_node->m_up == parent->m_right)
                m_node = NULL;
            else
                m_node = parent->m_right;
            return *this;
        }

        m_node = m_node->m_left;
        return *this;
    }

    // zum naechsten Element
    TreeIterator<T, Order>& operator--() {
    }



    bool operator==(const TreeIterator<T, Order> &rhs) const {
        return this->m_node == rhs.m_node && this->m_tree == rhs.m_tree;
    }

    bool operator!=(const TreeIterator<T, Order> &rhs) const {
        return this->m_node != rhs.m_node || this->m_tree != rhs.m_tree;
    }

protected:

    TreeIterator(TreeNode<T, Order> * node, const Tree<T, Order> * tree) : m_node(node), m_tree(tree) {}

private:

    TreeNode<T, Order> * m_node;
    const Tree<T, Order> * m_tree;

};



#endif // TREEITERATOR_H
