#ifndef TREEITERATOR_H
#define TREEITERATOR_H

#include "tree.h"
#include "treenode.h"

template <class T, template<typename> class Order > class TreeIterator {

    friend class TreeNode<T, Order>;

public:

    TreeIterator(TreeNode<T, Order> node) : m_node(node) {}

    T& operator*() {
        return m_node->value();
    }

    T* operator->() {
        return m_node->value();
    }

    TreeIterator<T, Order>& operator++() {
        // erst rechts prüfen, ob vorhanden
        // ansonsten solange nach oben, bis größerer gefunden
        if (m_node->m_right != NULL)
            return TreeIterator(m_right);

        TreeNode<T, Order> parent = m_node;

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

    TreeIterator<T, Order>& operator--() {
        if (m_node->m_left != NULL) {
            TreeNode<T, Order> node = m_node.m_left;
            while (node->m_right != NULL)
                node = m_right;

            m_node = node;
        } else if (m_node->m_up != NULL) {
            TreeNode<T, Order> parent = m_node;

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

    bool operator==(const TreeIterator<T, Order> &rhs) {
       return this->m_node == rhs.m_node;


    }

    bool operator!=(const TreeIterator<T, Order> &rhs);


private:

    TreeNode<T, Order> m_node;
    Tree<T, Order> m_tree;

};



#endif // TREEITERATOR_H
