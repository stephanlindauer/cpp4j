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

    // zum naechsten Element
    TreeIterator<T, Order>& operator++() {
        // erst rechts prüfen, ob vorhanden
        // ansonsten solange nach oben, bis größerer gefunden
        if (m_node->m_right != NULL) {
            m_node = m_node->m_right;
            return *this;
        }

        TreeNode<T, Order> * parent = m_node;

        Order<T> functor;
        do {

            parent = parent->m_up;

            // keep position
            if (parent == NULL)
                return *this;


        } while (functor(m_node->m_value, parent->m_value));

        m_node = parent;
        return *this;
    }

    // zum vorherigen Element
    TreeIterator<T, Order>& operator--() {
        if (m_node->m_left != NULL) {
            TreeNode<T, Order> node = m_node.m_left;
            while (node->m_right != NULL)
                node = node->m_right;

            m_node = node;
        } else if (m_node->m_up != NULL) {
            TreeNode<T, Order> * parent = m_node;

            Order<T> functor;
            do {
                parent = parent->m_up;
                // keep position
                if (parent == NULL)
                    return *this;

            } while (functor(m_node->m_value, parent->m_value));

            m_node=parent;
        }

        return *this;
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
