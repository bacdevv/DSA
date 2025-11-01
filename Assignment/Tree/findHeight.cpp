#include <iostream>
using namespace std;

struct BstNode {
    int data;
    BstNode* left;
    BstNode* right;
};

BstNode* makeNode(int data) {
    BstNode* newNode = new BstNode();
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

BstNode* Insert(BstNode* root, int data) {
    if (root == NULL) {
        root = makeNode(data);
    }
    else if (data <= root->data) {
        root->left =  Insert(root->left, data);
    }
    else {
        root->right = Insert(root->right, data);
    }
    return root;
}

bool Search(BstNode* root, int data) {
    if (root == NULL) return false;
    else if (root->data == data) return true;
    else if (data <= root->data) return Search(root->left, data);
    else return Search(root->right, data);
}

int max(BstNode* root) {
    if (root == NULL) return -1;
    if (root->right == NULL) return root->data;
    return max(root->right);
}

int FindHeight(BstNode* root) {
    if (root == NULL) return -1;

    return 1 + max(FindHeight(root->left), FindHeight(root->right));
}


int main () {
    BstNode* root = NULL;

    root = Insert(root, 10);
    root = Insert(root, 9);
    root = Insert(root, 25);
    root = Insert(root, 12);
    root = Insert(root, 3);
    root = Insert(root, 30);

    // int number;
    // cout << "Enter the number be searched\n";
    // cin >> number;

    int res = FindHeight(root);
    cout << res << endl;
    // bool haveElement = Search(root, number);
    // if(haveElement) cout << "Found\n";
    // else cout << "Not found\n";
    
    return 0;
}