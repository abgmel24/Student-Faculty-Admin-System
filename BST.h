#include "TreeNode.h"
#include <fstream>
using namespace std;

template <class T>
class BST {
    protected:
        TreeNode<T>* root;
        unsigned int size;

    public:
        BST();
        ~BST();

        virtual void insert(T data);
        virtual TreeNode<T>* remove(T data);
        virtual bool contains(T data);
        virtual T find(T data);

        TreeNode<T>* getRoot();
        T getMin();
        T getMax();

        bool isEmpty();

        void recursivePrint(TreeNode<T> *node);
        void printTree();

        void toFile(ostream& os);
        void recursiveFileStream(ostream& os, TreeNode<T>* node);

        TreeNode<T>* getSuccessor(TreeNode<T> *n);

};

template <class T>
BST<T>::BST() {
    root = NULL;
    size = 0;
}

template <class T>
BST<T>::~BST() {
    while(this->size > 0) {
        cout << "deleting root" << endl;
        remove(this->root->key);
    }
    delete this->root;
}

template <class T>
void BST<T>::insert(T data) {
    TreeNode<T> *node = new TreeNode<T>(data);
    if(isEmpty()) {
        root = node;
        size++;

        node = NULL;
        return;
    }

    TreeNode<T> *curr = root;
    TreeNode<T> *parent = NULL;
    while(true) {
        parent = curr; //curr will get a new value

        if(data < curr->key) {
            curr = curr->left;

            if(curr == NULL) { //leaf node
                parent->left = node;
                size++;
                break;
            }
        }
        else if(data > curr->key) {
            curr = curr->right;

            if(curr == NULL) { //leaf node
                parent->right = node;
                size++;
                break;
            }

        } else {
            throw runtime_error("Cannot have duplicate values in a BST");
        }
    }
}

template <class T>
TreeNode<T>* BST<T>::remove(T data) {
    //first, find the node to delete
    //0 children
        //just move on
    //1 child
        //child is left child
            //child replaces node
            //child is node's parent's left child
        //child is right child
            //child is node's parent's right child
    //2 children
        //


    if(isEmpty()) {
        return NULL;
    }

    TreeNode<T> *curr = root;
    TreeNode<T> *parent = NULL;
    bool isLeftChild = true;

    while(curr->key != data) {
        parent = curr;

        if(data < curr->key) {
            curr = curr->left;
        } else {
            isLeftChild = false;
            curr = curr->right;
        }

        if(curr == NULL) //not found to delete
            return NULL;
    }

    //0 children
    if(curr->left == NULL && curr->right == NULL) {
        if(curr == root) {
            root = NULL;
        } else if(isLeftChild) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
    }

    //1 child on the left
    else if(curr->right == NULL) {
        if(curr == root) {
            root = curr->left;
        } else if(isLeftChild) {
            parent->left = curr->left;
        } else {
            parent->right = curr->left;
        }
    }

    //1 child on the right
    else if(curr->left == NULL) {
        if(curr == root) {
            root = curr->right;
        } else if(!isLeftChild) {
            parent->left = curr->right;
        } else {
            parent->right = curr->left;
        }
    }

    //2 children
    else {
        TreeNode<T>* successor = getSuccessor(curr);

        if(curr == root) {
            root = successor;
        } else if(isLeftChild) {
            parent->left = successor;
        } else {
            parent->right = successor;
        }

        successor->left = curr->left;
        curr->left = NULL;
        curr->right = NULL;
    }

    size--;
}

template <class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T>* n) {
    TreeNode<T>* successorParent = n;
    TreeNode<T>* successor = n;

    TreeNode<T>* curr = n->right;

    while(curr != NULL) {
        successorParent = successor;
        successor = curr;
        curr = curr->left;
    }

    if(successor != n->right) {
        successorParent->left = successor->right;
        successor->right = n->right;
    }

    return successor;
}

template <class T>
bool BST<T>::contains(T data) {
    if(isEmpty())
        return false;

    TreeNode<T> *curr = root;
    while(curr->key != data) {
        if(data < curr->key) {
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
T BST<T>::find(T data) {
    if(isEmpty())
        return NULL;

    TreeNode<T> *curr = root;
    while(curr->key != data) {
        if(data < curr->key) {
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
TreeNode<T>* BST<T>::getRoot() {
    return root;
}

template <class T>
T BST<T>::getMin() {
    if(isEmpty()) {
        return NULL;
    }

    TreeNode<T> *curr = root;
    while(curr->left != NULL) {
        curr = curr->left;
    }

    return curr->key;
}

template <class T>
T BST<T>::getMax() {
    if(isEmpty()) {
        return NULL;
    }

    TreeNode<T> *curr = root;
    while(curr->right != NULL) {
        curr = curr->right;
    }

    return curr->key;
}

template <class T>
bool BST<T>::isEmpty() {
    return root == NULL;
}

template <class T>
void BST<T>::recursivePrint(TreeNode<T> *node) {
    if(node == NULL) {
        cout << "NULL ";
        return;
    }
    // cout << node->key << " ";
    cout << "Node: " << node->key << " ";
    recursivePrint(node->left);
    recursivePrint(node->right);
}

template <class T>
void BST<T>::printTree() {
    recursivePrint(root);
    cout << endl;
}

template <class T>
void BST<T>::toFile(ostream &os) {
    recursiveFileStream(os, this->root);
    os << endl;
}

template <class T>
void BST<T>::recursiveFileStream(ostream &os, TreeNode<T>* node) {
    if(node ==  NULL) {
        return;
    }

    recursiveFileStream(os, node->left);
    node->key->toFile(os);
    recursiveFileStream(os, node->right);

}