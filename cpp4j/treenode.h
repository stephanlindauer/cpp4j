#ifndef TREENODE_H
#define TREENODE_H

template <class T, template<typename> class Order > class Tree;
template <class T, template<typename> class Order > class TreeIterator;

template <class T, template<typename> class Order > class TreeNode {

    friend class Tree<T, Order>;
    friend class TreeIterator<T, Order>;

public:

    T& value(void) {
        return m_value;
    }

    TreeNode<T, Order>* find(const T& value) {
        Order<T> order; //less<int>
        if (order(m_value, value))
            return m_left->find(value);

        if (order(value, m_value))
            return m_right->find(value);

        if (m_value == value)
            return this;

        return NULL;

    }

    TreeNode<T, Order>* findFirst(void) {
        if (m_left != NULL)
            return m_left->findFirst();

        return this;
    }

    TreeNode<T, Order>* findLast(void) {
        if (m_right != NULL)
            return m_right->findLast();

        return this;
    }

    /*bool operator==(const TreeNode<T, Order> &rhs) const {
        return     this->m_value == rhs.m_value
                && this->m_up == rhs.m_up
                && this->m_left == rhs.m_left
                && this->m_right == rhs.m_right;
    }*/


protected:

    T m_value;
    TreeNode<T, Order>* m_up;
    TreeNode<T, Order>* m_left;
    TreeNode<T, Order>* m_right;

    // create a leaf node
    TreeNode<T, Order>(const T value, TreeNode<T, Order> * up = NULL)
        : m_value(value), m_up(up), m_left(NULL), m_right(NULL) {}

    // create a branch node
    TreeNode<T, Order>(const T value, TreeNode<T, Order> * up, TreeNode<T, Order> * left, TreeNode<T, Order> * right)
        : m_value(value), m_up(up), m_left(left), m_right(right) {}

};

#endif // TREENODE_H
