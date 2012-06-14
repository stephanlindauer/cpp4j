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

    // zum nächsten Element
    TreeIterator<T, Order>& operator++() {
        if (m_node == NULL || m_end)
            return *this;

        if (m_node->m_right != NULL) {
            m_node = m_node->m_right;
            while (m_node->m_left != NULL)
                m_node = m_node->m_left;

            return *this;
        }

        if (m_node->m_up != NULL) {
            if (m_node->m_up->m_left == m_node) {
                // wir kamen von links
                m_node = m_node->m_up;
                return *this;
            }

            TreeNode<T, Order> * node = m_node;

            // wir kamen von rechts, also so lange nach oben, bis wir einen neuen rechten Pfad haben
            while (node->m_up->m_right == node) {

                node = node->m_up;

                if (node->m_up == NULL) { // reached root, nothing else to do
                    m_end = true;
                    return *this;
                }

            }

            m_node = node->m_up;

            return *this;

        }

        m_end = true;
        return *this;

    }

    // zum vorherigen Element
    TreeIterator<T, Order>& operator--() {
        return *this;
    }

    bool operator==(const TreeIterator<T, Order> &rhs) const {
        return this->m_node == rhs.m_node && this->m_tree == rhs.m_tree && this->m_end == rhs.m_end;
    }

    bool operator!=(const TreeIterator<T, Order> &rhs) const {
        return !(*this == rhs);
    }

protected:

    TreeIterator(TreeNode<T, Order> * node, const Tree<T, Order> * tree)
        : m_node(node), m_tree(tree), m_end(false) {}

    TreeIterator(TreeNode<T, Order> * node, const Tree<T, Order> * tree, const bool end)
        : m_node(node), m_tree(tree), m_end(end) {}

private:

    TreeNode<T, Order> * m_node;
    const Tree<T, Order> * m_tree;
    bool m_end;

};

#endif // TREEITERATOR_H
