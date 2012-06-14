#ifndef TREE_H
#define TREE_H

#include "less.h"
#include "treeiterator.h"
#include "treenode.h"

template <class T, template<class> class Order = Less > class Tree {

public:

    Tree():m_root(NULL) {}

    typedef TreeIterator<T,Order> iterator;
    typedef TreeNode<T,Order> node;

    iterator insert(const T& value) {

        if (m_root == NULL) {
            m_root = new node(value);
            return begin();
        } else {
            return insert_internal (iterator (m_root, this), value);
        }
    }

    void clear() {
        // leaky-leaky
        m_root = NULL;
    }

    // lowest key
    const iterator begin() const {
        TreeNode<T, Order> * node = m_root;
        while (node != NULL) {
            if (node->m_left != NULL)
                node = node->m_left;
            else
                break;
        }

        return iterator (node, this, node == NULL);
    }

    // highest key
    const iterator end() const {
        TreeNode<T, Order> * node = m_root;
        while (node != NULL) {
            if (node->m_right != NULL)
                node = node->m_right;
            else
                break;
        }

        return iterator (node, this, true);
    }

    /*iterator first();
    iterator last();
    iterator find(const T& value);*/


protected:
    TreeNode<T, Order> * m_root;

    iterator insert_internal(iterator i, const T& value) {
        Order<T> order;

        if (order(value, i.m_node->m_value)) { // links
            iterator prev = iterator (i.m_node->m_left, this);
            if (prev.m_node == NULL) {
                prev.m_node = new node(value);
                prev.m_node->m_up = i.m_node;
                i.m_node->m_left = prev.m_node;
                return prev;

            } else
                return insert_internal (prev, value);


        } else if (order(i.m_node->m_value, value)) { // rechts
            iterator next = iterator (i.m_node->m_right, this);
            if (next.m_node == NULL) {
                next.m_node = new node(value);
                next.m_node->m_up = i.m_node;
                i.m_node->m_right = next.m_node;
                return next;

            } else
                return insert_internal (next, value);


        } else {
            i.m_node->m_value = value;
            return i;
        }
    }


};



#endif // TREE_H
