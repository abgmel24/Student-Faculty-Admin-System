#ifndef LazyBST_H
#define LazyBST_H

#include "BST.h"
using namespace std;

template <class T>
class LazyBST : public BST<T> {
    public:
        LazyBST();
        ~LazyBST();

        void insert(T data);
        TreeNode<T>* remove(T data);
        bool contains(T data);
        T find(T data);

        void balance();    
        void addToArray(T* array, int &index, TreeNode<T>* node);
        void balanceHelper(int front, int rear, T* array);

        unsigned getLeftHeight();
        unsigned getRightHeight();
        bool isBalanced();
    private:
        bool balancing;
        unsigned int leftHeight;
        unsigned int rightHeight;
};

template <class T>
LazyBST<T>::LazyBST() {
    this->root = NULL;
    this->size = 0;
    leftHeight = 1;
    rightHeight = 1;
    balancing = false;
}

template <class T>
LazyBST<T>::~LazyBST() {
    while(this->size > 0) {
        remove(this->root->key);
    }
    delete this->root;
}

template <class T>
void LazyBST<T>::insert(T data) {
    TreeNode<T> *node = new TreeNode<T>(data);
    if(this->isEmpty()) {
        this->root = node;
        if(!balancing)
            this->size++;
        node = NULL;
        return;
    }

    bool onRight = true;
    if(*data < this->root->key) {
        onRight = false;
    }

    TreeNode<T> *curr = this->root;
    TreeNode<T> *parent = NULL;
    while(true) {
        parent = curr; //curr will get a new value

        if(*data < curr->key) {
            curr = curr->left;

            if(curr == NULL) { //leaf node
                parent->left = node;
                if(!balancing) {
                    this->size++;
                }

                if(parent->right == NULL && parent != this->root) {
                    if(onRight) {
                        rightHeight++;
                    } else {
                        leftHeight++;
                    }
                }

                break;
            }
        }
        else if(*data > curr->key) {
            curr = curr->right;

            if(curr == NULL) { //leaf node
                parent->right = node;
                if(!balancing) {
                    this->size++;
                }
                
                if(parent->left == NULL && parent != this->root) {
                    if(onRight) {
                        rightHeight++;
                    } else {
                        leftHeight++;
                    }
                }
                break;
            }

        } else {
            throw runtime_error("Cannot have duplicate values in a BST");
        }
    }
    if(!isBalanced() && !balancing) {
        balance();
    }
}

template <class T>
TreeNode<T>* LazyBST<T>::remove(T data) {
    if(this->isEmpty()) {
        return NULL;
    }

    TreeNode<T> *curr = this->root;
    TreeNode<T> *parent = NULL;
    bool isLeftChild = true;

    while(!(*data == curr->key)) {
        parent = curr;

        if(*data < curr->key) {
            curr = curr->left;
        } else {
            isLeftChild = false;
            curr = curr->right;
        }

        if(curr == NULL) //not found to delete
            return NULL;
    }

    bool onRight = true;
    if(*data < this->root->key)
        onRight = false;

    //0 children
    if(curr->left == NULL && curr->right == NULL) {
        if(curr == this->root) {
            this->root = NULL;
            leftHeight = 1;
            rightHeight = 1;
        } else if(isLeftChild) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
    }

    //1 child on the left
    else if(curr->right == NULL) {
        if(curr == this->root) {
            this->root = curr->left;
            //leftHeight decreased
            //rightHeight = height of curr->left->right
        } else if(isLeftChild) {
            parent->left = curr->left;
        } else {
            parent->right = curr->left;
        }
    }

    //1 child on the right
    else if(curr->left == NULL) {
        if(curr == this->root) {
            this->root = curr->right;
        } else if(!isLeftChild) {
            parent->left = curr->right;
        } else {
            parent->right = curr->left;
        }
    }

    //2 children
    else {
        TreeNode<T>* successor = this->getSuccessor(curr);

        if(curr == this->root) {
            this->root = successor;
        } else if(isLeftChild) {
            parent->left = successor;
        } else {
            parent->right = successor;
        }

        successor->left = curr->left;
        curr->left = NULL;
        curr->right = NULL;
    }

    if(onRight)
        rightHeight--;
    else
        leftHeight--;

    this->size--;
    if(leftHeight < 1)
        leftHeight = 1;
    if(rightHeight < 1)
        rightHeight = 1;

    if(!isBalanced() && !balancing) {
        balance();
    }

    return curr;
}

template <class T>
bool LazyBST<T>::contains(T data) {
    if(this->isEmpty())
        return false;

    TreeNode<T> *curr = this->root;
    while(!(*data == curr->key)) {
        if(*data < curr->key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }

        if(curr == NULL)
            return false;
    }
    return true;
}

template <class T>
T LazyBST<T>::find(T data) {
    if(this->isEmpty())
        return NULL;

    TreeNode<T> *curr = this->root;
    while(!(*data == curr->key)) {
        if(*data < curr->key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }

        if(curr == NULL)
            return NULL;
    }
    return curr->key;
}

template <class T>
void LazyBST<T>::balance() {
    T* array = new T[this->size];

   int currPos = 0;
    addToArray(array, currPos, this->root);

    this->root = NULL;
    leftHeight = 1; rightHeight = 1;

    balancing = true;
    balanceHelper(0, this->size - 1, array);
    balancing = false;

    delete array;
}

template <class T>
void LazyBST<T>::addToArray(T* array, int &index, TreeNode<T>* node) {
    if(node == NULL) {
        return;
    }

    addToArray(array, index, node->left);

    array[index++] = node->key;

    addToArray(array, index, node->right);

    delete node;
}

template <class T>
void LazyBST<T>::balanceHelper(int front, int rear, T* array) {
    if(front > rear || rear < front) {
        return;
    }

    if(front == rear) {
        insert(array[front]);
        return;
    }
    
    int mid = (front + rear) / 2;
    insert(array[mid]);
    
    balanceHelper(front, mid - 1 , array);
    balanceHelper(mid + 1, rear, array);
}

template <class T>
unsigned int LazyBST<T>::getLeftHeight() {
    return leftHeight;
}

template <class T>
unsigned int LazyBST<T>::getRightHeight() {
    return rightHeight;
}

template <class T>
bool LazyBST<T>::isBalanced() {
    if(leftHeight / (double) rightHeight > 1.5) {
        return false;
    }
    if(rightHeight / (double) leftHeight > 1.5) {
        return false;
    }
    return true;
}

#endif