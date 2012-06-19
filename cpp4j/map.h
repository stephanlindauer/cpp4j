#ifndef MAP_H
#define MAP_H

#include "pair.h"
#include "tree.h"
#include "treeiterator.h"

template <class KeyT, class ValueT, class Order> class Map {

public:

    typedef Pair<KeyT, ValueT> KVPair;

    typedef TreeIterator<KVPair, Order> iterator;
    typedef Tree<KVPair, Order> KVTree;

    ValueT& operator[](const KeyT& key) {
        iterator i = find(key);

        if (!i.isValid()) {
            ValueT dummy;
            KVPair kv (key, dummy);
            i = insert(kv);
        }

        KVPair & kv = *i;
        return kv.second();

    }

    iterator insert(const Pair<KeyT,ValueT>& kv) {
        iterator i = find(kv.first());
        if (i.isValid()) {
            // update
            *i = kv;
        } else {
            i = m_tree.insert(kv);
        }

        return i;
    }

    iterator find(const KeyT& key) {
        ValueT dummy;
        KVPair kv (key, dummy);
        return m_tree.find(kv);
    }

    iterator begin() {
        return m_tree.begin();
    }

    iterator end() {
        return m_tree.end();
    }

    iterator first() {
        return m_tree.first();
    }

    iterator last() {
        return m_tree.last();
    }

    const KeyT& min() {
        return first()->first();
    }

    const KeyT& max() {
        return last()->first();
    }

    void clear() {
        m_tree.clear();
    }

private:

    KVTree m_tree;

};

#endif // MAP_H
