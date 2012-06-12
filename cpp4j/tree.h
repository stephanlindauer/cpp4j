#ifndef TREE_H
#define TREE_H

#include "less.h"
#include "treeiterator.h"
#include "treenode.h"

template <class T, template<typename> class Order = Less > class Tree {

public:

    Tree():m_root(NULL) {}

    typedef TreeIterator<T,Order> iterator;
    typedef TreeNode<T,Order> node;

    iterator insert(const T& value) {
        if (m_root == NULL) {
            m_root = new node(value);
            return iterator(m_root, this);

        } else {
            iterator i (m_root, this);
            return insert_internal (i, value);

        }
    }

    //void clear();
    iterator begin() {
        if (m_root == NULL)
            return iterator(NULL, this);

        return iterator (m_root->findFirst(), this);
    }

    iterator end() {
        if (m_root == NULL)
            return iterator(NULL, this);

        return iterator (m_root->findLast(), this);
    }

    /*iterator first();
    iterator last();
    iterator find(const T& value);*/


private:
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
                i.m_node->m_left = next.m_node;
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
