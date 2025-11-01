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

bool IsSubtreeLesser(node* root, int value) {
    if (root == nullptr) return true;
    if (root->data <= value && IsSubtreeLesser(root->left, value) && IsSubtreeLesser(root->right, value)) {
        return true;
    }
    else return false;
}

bool IsSubtreeGreater(node* root, int value) {
    if (root == nullptr) return true;
    if (root->data <= value && IsSubtreeGreater(root->left, value) && IsSubtreeGreater(root->right, value)) {
        return true;
    }
    else return false;
}

bool IsBinarySearchTree(node* root) {
    if (root == nullptr) return true;

    if (IsSubtreeLesser(root->left,root->data) && IsSubtreeGreater(root->right, root->data) && IsBinarySearchTree(root->left) && IsBinarySearchTree(root->right)) {
        return true;
    }
    else {
        return false;
    }
}

int main () {
    node* root = nullptr;

    
    return 0;
}