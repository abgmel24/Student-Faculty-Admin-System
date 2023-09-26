#ifndef LISTNODE_H
#define LISTNODE_H

#include <iostream>
using namespace std;

template <class T>
class TListNode {
    public:
        TListNode();
        TListNode(T d);
        ~TListNode();
        T data;
        TListNode<T> *next;
};

template <class T>
TListNode<T>::TListNode() {
    data = 0; //default value?
    next = NULL;
}

template <class T>
TListNode<T>::TListNode(T d) {
    data = d;
    next = NULL;
}

template <class T>
TListNode<T>::~TListNode() {
    delete next;
}

#endif