#include <iostream>
using namespace std;

struct node {
    int data;
    node* left;
    node* right;
};

node* makeNode(int data) {
    node* newNode = new node();
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

bool isBSTUtil(node* root, int min, int max) {
    if (root == nullptr) return true;
    if (root->data < min || root->data > max) return false;
    return isBSTUtil(root->left, root->data, max) && isBSTUtil(root->right, min, root->data);
}

int main () {
    // Example usage:
    node* root = makeNode(10);
    root->left = makeNode(5);
    root->right = makeNode(15);
    root->left->left = makeNode(2);
    root->left->right = makeNode(7);
    root->right->right = makeNode(20);

    /*
        The tree structure is:
              10
             /  \
            5    15
           / \     \
          2   7     20
    */
    
    if (isBSTUtil(root, INT_MIN, INT_MAX)) {
        cout << "The tree is a Binary Search Tree." << endl;
    } else {
        cout << "The tree is not a Binary Search Tree." << endl;
    }

    return 0;
}