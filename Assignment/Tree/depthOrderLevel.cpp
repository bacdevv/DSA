#include <iostream>
using namespace std;

struct node {
    char data;
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
    while(true) {
        if (data <= current->data) {
            if (current->left == nullptr) {
                current->left = makeNode(data);
                return;
            }
            current = current->left;
        }
        else {
            if (current->right == nullptr) {
                current->right = makeNode(data);
                return;
            }
            current = current->right;
        }
    }
}

// data left right
void preOrder(node* root) {
    if (root == nullptr) return;
    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(node* root) {
    if (root == nullptr) return;
    inOrder(root->left);
    cout << root->data;
    inOrder(root->right);
}

void postOrder(node* root) {
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data;
}


int main () {
    node* root = nullptr;
    // insert(root, 'F');
    // // cout << root->data << endl;
    // insert(root, 'D');
    // // cout << root->right->data << endl;
    // insert(root, 'J');
    // // cout << root->right->left->data << endl;
    // insert(root, 'B');
    // insert(root, 'E');
    // insert(root, 'G');
    // insert(root, 'K');
    // insert(root, 'A');
    // insert(root, 'C');
    // insert(root, 'I');

    insert(root, 10);
    // cout << root->data << endl;
    insert(root, 23);
    // cout << root->right->data << endl;
    insert(root, 18);
    // cout << root->right->left->data << endl;
    insert(root, 25);
    insert(root, 39);
    insert(root, 12);

    preOrder(root);

    return 0;
}