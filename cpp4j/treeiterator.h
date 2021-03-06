#ifndef TREEITERATOR_H
#define TREEITERATOR_H

#include "treenode.h"

template <class T, class Order > class Tree;

template <class T, class Order > class TreeIterator {

    friend class Tree<T, Order>;

public:

    enum iteration_mode { begin, middle, end };
    TreeIterator(TreeNode<T, Order> * node, const Tree<T, Order> * tree, const iteration_mode mode = middle)
        : m_mode(mode), m_node(node), m_tree(tree) {}

    bool isValid(void) {
        return m_node != NULL;
    }

    T& operator*() {
        return m_node->value();
    }

    T* operator->() {
        return &m_node->m_value;
    }

    // zum nächsten Element
    TreeIterator<T, Order>& operator++() {
        if (m_node == NULL || m_mode == end)
            return *this;

        m_mode = middle;

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
                    m_mode = end;
                    return *this;
                }

            }

            m_node = node->m_up;

            return *this;

        }

        m_mode = end;
        return *this;

    }

    // zum vorherigen Element
    TreeIterator<T, Order>& operator--() {
        if (m_node == NULL || m_mode == begin)
            return *this;

        m_mode = middle;

        if (m_node->m_left != NULL) {
            m_node = m_node->m_left;
            while (m_node->m_right != NULL)
                m_node = m_node->m_right;

            return *this;
        }

        if (m_node->m_up != NULL) {
            if (m_node->m_up->m_right == m_node) {
                // wir kamen von rechts
                m_node = m_node->m_up;
                return *this;
            }

            TreeNode<T, Order> * node = m_node;

            // wir kamen von links, also so lange nach oben, bis wir einen neuen linken Pfad haben
            while (node->m_up->m_left == node) {

                node = node->m_up;

                if (node->m_up == NULL) { // reached root, nothing else to do
                    m_mode = begin;
                    return *this;
                }

            }

            m_node = node->m_up;

            return *this;

        }

        m_mode = end;
        return *this;
    }

    bool operator==(const TreeIterator<T, Order> &rhs) const {
        return this->m_node == rhs.m_node && this->m_tree == rhs.m_tree && this->m_mode == rhs.m_mode;
    }

    bool operator!=(const TreeIterator<T, Order> &rhs) const {
        return !(*this == rhs);
    }

protected:

    iteration_mode m_mode;

    TreeNode<T, Order> * m_node;

private:

    const Tree<T, Order> * m_tree;
};

#endif // TREEITERATOR_H
