#ifndef TREEITERATOR_H
#define TREEITERATOR_H

#include "treenode.h"

template <class T, template<typename> class Order > class TreeIterator {

    friend class TreeNode<T, Order>;

public:

    TreeIterator(TreeNode<T, Order> node) : m_node(node) {}

    T& operator*() {
        return m_node->m_value;
    }

    T* operator->() {
        return (T*)(m_node->m_value&);
    }

    TreeIterator<T, Order>& operator++() {
        // erst rechts prüfen, ob vorhanden
        // ansonsten solange nach oben, bis größerer gefunden
        if (m_node->m_right != NULL)
            return TreeIterator(m_right);

        TreeNode<T, Order> parent = m_node->m_up;

        Order<T> functor;
        while (functor(m_node->m_value, parent->value)) {
            parent = parent->m_up;
        }

        m_node = parent;
        return *this;
    }

    TreeIterator<T, Order>& operator--() {

    }

    bool operator==(const TreeIterator<T, Order> &rhs);
    bool operator!=(const TreeIterator<T, Order> &rhs);


private:

    TreeNode<T, O> m_node;

};



#endif // TREEITERATOR_H
