
/*
    Vorlesung "C++ für Java Programmierer"
    Medieninformatik Bachelor
    Aufgabe 3, Sommersemester 2012
    (C)opyright Hartmut Schirmacher
    http://hschirmacher.beuth-hochschule.de
*/

#include "assert.h"
#include <iostream>
#include <string>
using namespace std;

// include your own header files here...
#include "pair.h"
#include "less.h"
#include "greater.h"
#include "maptofirst.h"
//#include "order.h"
#include "tree.h"
#include "map.h"

// you should define your own namespace for
// the templates/classes in this project

//using namespace mystl;

// explicit template instantiation for compiling / debugging
//template class Pair<int,string>;
//template class Tree< int,Less<int> >;
//template class Map<int, string>;

// list and count all nodes in a set using an iterator
template<class Container>
int printAndCount(Container & c) {

    int n=0;
    for(typename Container::iterator i=c.begin(); i!=c.end(); ++i, ++n)
        cout << *i << " ";

    cout << "(" << n << " elements)." << endl;

    return n;
}

// list backwards and count all nodes in a set
template<class Container>
int printAndCountBackwards(Container & c) {
    int n = 0;
    typename Container::iterator i = c.end();
    while(i != c.begin()) {
        // had to swap the following two lines?
        cout << *i << " ";
        --i;

        n++;
    }
    cout << endl;
    return n;
}

int testTemplates(void)
{

    cout << "Starting..." << endl;

    /////////////////////////////////////////
    // TEST PAIR

    Pair<int,float> i_f(2,3.14);
    Pair<int,float> i_f2(4,3.14);
    Pair<string,string> s_s("Hello","World!");
    cout << i_f << " " << s_s << endl;


    /////////////////////////////////////////
    // TEST ORDER
    Less<int> lessInt;
    cout << "2<3 == " << lessInt(2,3) << endl;
    cout << "4<3 == " << lessInt(4,3) << endl;

    Greater<int> greaterInt;
    assert ( greaterInt(4,3) == 1 );
    assert ( greaterInt(3,4) == 0 );
    assert ( greaterInt(3,3) == 0 );

    Greater<string> greaterString;
    cout << "Hallo > Welt == " << greaterString("Hallo","Welt") << endl;
    assert(!greaterString("Hallo","Welt"));

    /////////////////////////////////////////
    // TEST PAIR ORDER
    MapToFirst< int, float, Less<int> > lessPair;
    cout << i_f << " < " << i_f2 << " == " << lessPair(i_f, i_f2) << endl;
    assert(lessPair(i_f, i_f2));

    /////////////////////////////////////////
    // TEST TREE

    // construct empty tree
    Tree<int> t;
    cout << "empty tree: ";
    assert(printAndCount(t) == 0);

    /*                                              */t.insert(50);
    /*                */t.insert(25);/*                                          */t.insert(75);
    /**/t.insert(20);/*               */t.insert(30);/*           */t.insert(70);/*             */t.insert(80);
    t.insert(17);t.insert(23);/**/t.insert(27);t.insert(33);/**/t.insert(67);t.insert(73);/**/t.insert(77);t.insert(83);
    cout << "tree 50-25-75-20-30-70-80-17-23-27-33-67-73-77-83: ";
    assert(printAndCount(t) == 15);
    t.clear();

    // insert elements in a certain order
    t.insert(4);
    t.insert(3);
    t.insert(2);
    t.insert(1);
    t.insert(5);
    cout << "tree 4-3-2-1-5: ";
    assert(printAndCount(t) == 5);

    // test clear()
    t.clear();
    cout << "after clear(): ";
    assert(printAndCount(t) == 0);

    // try another insertion order
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(5);
    t.insert(4);
    cout << "tree 1-2-3-5-4: ";
    assert(printAndCount(t) == 5);

    // and yet another insertion sequence
    t.clear();
    t.insert(45);
    t.insert(4);
    t.insert(89);
    t.insert(9);
    t.insert(7);
    t.insert(3);
    cout << "6-element tree: ";
    assert(printAndCount(t) == 6);

    // and yet another insertion sequence (compined from the above)
    t.clear();
    t.insert(8); t.insert(4); t.insert(3); t.insert(2); t.insert(1);
    t.insert(5); t.insert(1); t.insert(2); t.insert(3); t.insert(5);
    t.insert(4); t.insert(45); t.insert(4); t.insert(89); t.insert(9);
    t.insert(7); t.insert(3);
    cout << "10-element tree: ";
    assert(printAndCount(t) == 10);

    // now we contruct a tree with a "reverse" order
    //typedef Tree< float, Greater<float> > RevFloatTree; // had to replace this line by the following
    typedef Tree< float, Greater<float> > RevFloatTree;
    RevFloatTree ft;
    ft.insert(3.1);
    ft.insert(6.2);
    ft.insert(4.3332);
    ft.insert(17.20);
    cout << "reverse-sorted 4-float tree: ";
    assert(printAndCount(ft) == 4);

    // if we list elements backwards, they should be
    //   in the same order as with the function Less<>
    cout << "listing backwards: ";
    assert(printAndCountBackwards(ft) == 4);

    /////////////////////////////////////////
    // TEST MAP

    Pair<int,string> p42(42,"Douglas Adams");
    Pair<int,string> p3(3,"Nummer 3");
    Pair<int,string> p1(1,"Nummer 1");
    Pair<int,string> p7(7,"James Bond");
    string value;

    Map<int,string, MapToFirst<int, string, Less<int> > > m;
    // insert pairs of (key,value)
    m.insert(p42);
    m.insert(p7);
    cout << "map 42-7: ";
    assert(printAndCount(m) == 2);

    // test finding elements via operator()
    cout << "find 42 in map: " << (value=m[42]) << endl;
    assert(value == p42.second());
    cout << "find 3 in map: " << (value=m[3]) << endl;
    assert(value == string());

    // direct write access via operator[]
    cout << "setting m[3] and m[1]." << endl;
    m[1] = p1.second();
    m[3] = p3.second();
    cout << "find 1 in map: " << (value=m[1]) << endl;
    assert(value == p1.second());
    cout << "find 3 in map: " << (value=m[3]) << endl;
    assert(value == p3.second());

    cout << "resulting map: ";
    assert(printAndCount(m) == 4);

    // test first() and last(), min() and max()
    Map<int,string, MapToFirst<int, string, Less<int> > >::iterator first = m.first();
    Map<int,string, MapToFirst<int, string, Less<int> > >::iterator last = m.last();
    cout << "first in map: " << *first << endl;
    cout << "last in map: " << *last << endl;
    assert(first->first() == 1);
    assert(last->first() == 42);
    assert(m.min() == first->first());
    assert(m.max() == last->first());

#if 0 // move this line down while your implementation proceeds...


#endif

    cout << "Success!" << endl;

    return 0;
}

