#ifndef TREENODE_H
#define TREENODE_H

template <class T, template<typename> class Order > class TreeNode {

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

protected:

    T m_value;
    TreeNode<T, Order>* m_up;
    TreeNode<T, Order>* m_left;
    TreeNode<T, Order>* m_right;

};

#endif // TREENODE_H
