#include <iostream>
#include <queue>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;
};

void LevelOrder(Node* root) {
    if (root == nullptr) return;
    queue<Node*> Q;
    Q.push(root);

    while(!Q.empty()) {
        Node* current = Q.front();
        cout << current-> data << " ";
        if (current->left != nullptr) {
            Q.push(current->left);
        }
        if (current->right != nullptr) {
            Q.push(current->right);
        }
        Q.pop(); // removing the element at front
    }
}

int main () {
    node* root = nullptr;

    insert(root, 10);
    // cout << root->data << endl;
    insert(root, 23);
    // cout << root->right->data << endl;
    insert(root, 18);
    // cout << root->right->left->data << endl;
    insert(root, 25);
    insert(root, 39);
    insert(root, 12);

    return 0; 
}