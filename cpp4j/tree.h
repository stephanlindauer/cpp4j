#ifndef TREE_H
#define TREE_H

#include "less.h"
#include "treeiterator.h"
#include "treenode.h"

template <class T, template<class> class Order = Less > class Tree {

public:

    Tree():m_root(NULL),m_last(NULL) {}

    typedef TreeIterator<T,Order> iterator;
    typedef TreeNode<T,Order> node;

    iterator insert(const T& value) {

        if (m_root == NULL && m_last == NULL) {
            m_root = new node(value);
            reset_last();
            return iterator(m_root, this, iterator::begin);

        } else {
            const iterator i (m_root, this, iterator::begin);
            iterator result = insert_internal (i, value);
            reset_last();
            return result;

        }
    }

    void clear() {
        // leaky-leaky
        m_last = m_root = NULL;
    }

    const iterator begin() const {
        return iterator (m_root, this, m_root == NULL ? iterator::end : iterator::begin);
    }

    const iterator end() const {
        return iterator (m_last, this, iterator::end);
    }

    /*iterator first();
    iterator last();
    iterator find(const T& value);*/


protected:
    TreeNode<T, Order> * m_root;
    TreeNode<T, Order> * m_last;

    void reset_last(void) {
        TreeNode<T, Order> * t = m_root;
        while (t != NULL) {

            if (t->m_right == NULL) {
                if (t->m_left == NULL) {
                    break;

                } else {
                    t = t->m_left;
                }

            } else {
                t = t->m_right;
            }
        }
        m_last = t;
    }

    iterator insert_internal(iterator i, const T& value) {
        Order<T> order;

        if (order(value, i.m_node->m_value)) { // links
            iterator prev = iterator (i.m_node->m_left, this, iterator::middle);
            if (prev.m_node == NULL) {
                prev.m_node = new node(value);
                prev.m_node->m_up = i.m_node;
                i.m_node->m_left = prev.m_node;
                return prev;

            } else
                return insert_internal (prev, value);


        } else if (order(i.m_node->m_value, value)) { // rechts
            iterator next = iterator (i.m_node->m_right, this, iterator::middle);
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
