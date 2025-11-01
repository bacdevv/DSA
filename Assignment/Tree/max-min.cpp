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

void insert(node*& root, int data) {
    if (root == nullptr) {
        root = makeNode(data);
        return;
    }

    node* current = root;
    while (true) {
        if (data <= current->data) {
            if (current->left == nullptr) {
                current->left = makeNode(data);
                return;
            }
            current = current->left;
        }
        else {
            if(current->right == nullptr) {
                current->right = makeNode(data);
                return;
            }
            current = current->right;
        }
    }
}

bool hasNode(node* root, int data) {
    if (root == nullptr) return false;
    if (data == root->data) return true;
    else if (data <= root->data) return hasNode(root->left, data);
    else return hasNode(root->right, data); 
}

int main () {
    node* root = nullptr;

    root = insert(root, 10);
    root = insert(root, 23);
    root = insert(root, 18);
    root = insert(root, 25);
    root = insert(root, 39);
    root = insert(root, 12);


    return 0;
}