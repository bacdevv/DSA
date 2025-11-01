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

// insert with return
// node* insert(node* root, int data) {
//     if (root == nullptr) {
//         root = makeNode(data);
//         return root;
//     }

//     if (data <= root->data) {
//         root->left = insert(root->left, data);
//     } else {
//         root->right = insert(root->right, data);
//     }
//     return root;
// }


// insert without return
// pass by reference to change root
// void insert(node*& root, int data) {
//     if (root == nullptr) {
//         root = makeNode(data);
//         return;
//     }

//     if (data <= root->data) {
//         insert(root->left, data);
//     } else {
//         insert(root->right, data);
//     }
// }

// insert without recursion
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
            if (current->right == nullptr)  {
                current->right = makeNode(data);
                return;
            }
            current = current->right;
        }
    }
}


bool search(node* root, int data) {
    if (root == nullptr) {
        return false;
    }
    else if (root->data == data) {
        return true;
    }
    else if (data <= root->data) {
        return search(root->left, data);
    }
    else {
        return search(root->right, data);
    }
}

int main () {
    node* root = nullptr;

    // insert with return
    // root = insert(root, 10);
    // root = insert(root, 23);
    // root = insert(root, 18);
    // root = insert(root, 25);
    // root = insert(root, 39);
    // root = insert(root, 12);

    // insert without return and recursion
    insert(root, 10);
    // cout << root->data << endl;
    insert(root, 23);
    // cout << root->right->data << endl;
    insert(root, 18);
    // cout << root->right->left->data << endl;
    insert(root, 25);
    insert(root, 39);
    insert(root, 12);

    
    // int number;
    // cout << "Enter number be searched\n";
    // cin >> number;
    // bool hasNode = search(root, number);
    // if (hasNode) cout << "Found\n";
    // else cout << "Not found\n";
    
    
    return 0;
}