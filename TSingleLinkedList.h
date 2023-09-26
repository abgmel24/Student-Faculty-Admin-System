#ifndef SINGLELINKEDLIST_H
#define SINGLELINKEDLIST_H

#include "TListNode.h"
#include <iostream>
#include <fstream>
#include <exception>

using namespace std;
template <class T>
class TSingleLinkedList {
    public:
        TSingleLinkedList();
        ~TSingleLinkedList();

        void insertFront(T d);
        T removeFront(); //return item
        T remove(T d);

        T find(T value); //return index
        bool isEmpty();
        unsigned int getSize();
        void toFile(ostream& os);
    
    private:
        TListNode<T>* head;
        unsigned int numElements;
};

template <class T>
TSingleLinkedList<T>::TSingleLinkedList() {
    head = NULL;
    numElements = 0;
}

template <class T>
TSingleLinkedList<T>::~TSingleLinkedList() {
    while(numElements > 0) {
        removeFront();
    }
}

template <class T>
void TSingleLinkedList<T>::insertFront(T d) {
    TListNode<T>* node = new TListNode<T>(d);

    node->next = head;
    head = node;
    numElements++;
}

template <class T>
T TSingleLinkedList<T>::removeFront() { //return item
    if(isEmpty()) {
        throw runtime_error("List is empty");
    }
    T temp = head->data;
    TListNode<T>* newHead = head;
    head = head->next;
    newHead->next = NULL;

    numElements--;

    delete newHead;
    return temp;
}

template <class T>
T TSingleLinkedList<T>::find(T value) { //return index
    TListNode<T>* node = head;
    while(node->data != value) {
        node = node->next;
    }

    return node->data;
}

template <class T>
T TSingleLinkedList<T>::remove(T d) {
    if(isEmpty()) {
        throw runtime_error("List is empty");
    }

    if(d == head->data) {
        return removeFront();
    }

    TListNode<T> *node = head;
    TListNode<T> *prev = NULL;
    while(node->data != d) {
        prev = node;
        node = node->next;
    }
    T temp = node->data;
    prev->next = node->next;
    node->next = NULL;
    delete node;
    return temp;
}

template <class T>
bool TSingleLinkedList<T>::isEmpty() {
    return numElements == 0;
}

template <class T>
unsigned int TSingleLinkedList<T>::getSize() {
    return numElements;
}

template <class T>
void TSingleLinkedList<T>::toFile(ostream& os) {
    if(isEmpty()) {
        os << "none";
        return;
    }
    TListNode<T>* node = head;
    while(node != NULL) {
        os << node->data;
        if(node->next != NULL)
            os << ", ";
        node = node->next;
    }

    node = NULL;
}


#endif