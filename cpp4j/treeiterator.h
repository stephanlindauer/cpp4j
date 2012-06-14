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
        if (m_node == NULL || m_mode == end) {
            return *this;
        }

        m_mode = middle;

        //
        // Was kann sonst sein?
        //

        // versuche, nach links zu gehen
        if (m_node->m_left != NULL) {
            m_node = m_node->m_left;
            return *this;
        }

        // wenn links nicht moeglich, versuche nach rechts zu gehen
        if (m_node->m_right != NULL) {
            m_node = m_node->m_right;
            return *this;
        }

        // wenn rechts nicht moeglich, versuche so weit nach oben zu gehen, dass du einen neuen rechten Weg hast
        TreeNode<T, Order> * child = m_node;
        TreeNode<T, Order> * parent = child->m_up;

        while (parent != NULL) {

            // sind wir das linke Kind des Elter?
            if (child == parent->m_left) {

                // haben wir Geschwister?
                if (parent->m_right != NULL) {

                    // naechster gefunden
                    m_node = parent->m_right;
                    return *this;
                }
            }

            // wir sind nicht das linke Kind (sondern das rechte)
            child = parent;
            parent = parent->m_up;
        }

        // wenn nichts moeglich ist, sind wir bereits am Ende
        m_mode = end;
        return *this;
    }

    // zum vorherigen Element
    TreeIterator<T, Order>& operator--() {
        if (m_node == NULL || m_mode == begin) {
            return *this;
        }

        m_mode = middle;

        //
        // Was kann sonst sein?
        //

        // wenn rechts nicht moeglich, versuche so weit nach oben zu gehen, dass du einen neuen rechten Weg hast
        TreeNode<T, Order> * child = m_node;
        TreeNode<T, Order> * parent = child->m_up;

        while (parent != NULL) {

            // sind wir das linke Kind des Elter?
            if (child == parent->m_right) {

                // haben wir Geschwister?
                if (parent->m_left != NULL) {

                    // naechster gefunden
                    m_node = parent->m_left;
                    return *this;
                }
            }

            // wir sind nicht das linke Kind (sondern das rechte)
            child = parent;
            parent = parent->m_up;
        }

        // wenn links nicht moeglich, versuche nach rechts zu gehen
        if (m_node->m_left != NULL) {
            m_node = m_node->m_left;
            return *this;
        }

        // versuche, nach links zu gehen
        if (m_node->m_right != NULL) {
            m_node = m_node->m_right;
            return *this;
        }

        // wenn nichts moeglich ist, sind wir bereits am Ende
        m_mode = begin;
        return *this;
    }

    bool operator==(const TreeIterator<T, Order> &rhs) const {
        return this->m_node == rhs.m_node && this->m_tree == rhs.m_tree && this->m_mode == rhs.m_mode;
    }

    bool operator!=(const TreeIterator<T, Order> &rhs) const {
        return !(this->m_node == rhs.m_node && this->m_tree == rhs.m_tree && this->m_mode == rhs.m_mode);
    }

protected:

    enum iterator_mode { begin, middle, end };
    iterator_mode m_mode;

    TreeIterator(TreeNode<T, Order> * node, const Tree<T, Order> * tree, const iterator_mode mode)
        : m_node(node), m_tree(tree), m_mode(mode) {}

private:

    TreeNode<T, Order> * m_node;
    const Tree<T, Order> * m_tree;

};

#endif // TREEITERATOR_H
