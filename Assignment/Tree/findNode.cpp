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

node* insert(node* root, int data) {
    if (root == nullptr)
        root = makeNode(data);
    else if (data <= root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);

    return root;
}

bool findNode(node* root, int data) {
    if (root == nullptr) return false;
    else if (root->data == data) return true;
    else if (data <= root->data) return findNode(root->left, data);
    else return findNode(root->right, data);
}

int main () {
    node* root = nullptr;

    root = insert(root, 10);
    root = insert(root, 23);
    root = insert(root, 18);
    root = insert(root, 25);
    root = insert(root, 39);
    root = insert(root, 12);

    int number;
    cout << "Enter number be searched\n";
    cin >> number;
    bool hasNode = findNode(root, number);
    if (hasNode) cout << "Found\n";
    else cout << "Not found\n";
    
    return 0;
}