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
        cout << m_node->m_value << endl;

        if (m_node == NULL)
            return *this;

        if (m_node->m_left == NULL) {
            // nach rechts oder nach oben->rechts

            // parent von node
            TreeNode<T, Order> * parent = m_node->m_up;

            // laufe nach oben, wenn du links vom oberen bist
            //if (parent->m_left == m_node) {

                // laufe nach oben, weil du links vom oberen bist
                parent = parent->m_up; // urelter

                //
                while (parent != NULL && parent->m_up != NULL) {
                    parent = parent->m_up;

                    if (parent->m_right != NULL) {
                        break;
                    }
                }

                if (parent == NULL)
                    m_node = NULL;
                else
                    m_node = parent->m_right;
            //} else if (parent->m_right == m_node &&

            // beende wenn du rechts von deinem oberen bist und unter dir nichts mehr ist
            return *this;
        }

        // nach unten
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
