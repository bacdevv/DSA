#include <iostream>
#include <queue>
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

// delete node
node* deleteNode(node* root, int key) {
    if (root == nullptr) return root;

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    }

    /*
        2 thang if else truoc lam gi ?
        no di tim node can xoa trong cay
        root = nullptr thi tra ve null
        con khong thi di tiep vao ben trai neu key nho hon root->data
        hoac di tiep ben phai neu key lon hon root->data
        neu tim duoc node can xoa (key == root->data) thi thuc hien xoa
    */
    else {
        
        if (root->left == nullptr) {
            node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            node* temp = root->left;
            delete root;
            return temp;
        }

        /*
            sao khong dung root = root->right;
            vi neu lam vay se mat con trai cua node can xoa
            neu dung temp thi con trai van duoc giu lai
            vi du cay la:
                 15
                /  \
               10   20
              / \
             8  12
            neu xoa 15 va root = root->right thi con 10 se bi mat
            neu dung temp thi con trai van duoc giu lai

            neu xoa nut 20 thi no 2 if else tren hoat dong nhu the nao
            thi no se tro ve nut con trai cua 20 neu co, neu khong co thi tro ve nullptr
            cai gi tra ve nullptr temp = root->right, root->left luc nay la bao nhieu ?
            neu 20 khong co con trai thi root->left la nullptr, temp = nullptr
            neu 20 co con trai thi root->left la con trai cua 20, temp
            se tro ve con trai cua 20

        */

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        node* temp = root->right;
        while (temp && temp->left != nullptr) {
            temp = temp->left;
        }

        // Copy the inorder successor's content to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// delete without return value node*
void deleteNodeNoReturn(node*& root, int key) {
    if (root == nullptr) return;

    if (key < root->data) {
        deleteNodeNoReturn(root->left, key);
    }
    else if (key > root->data) {
        deleteNodeNoReturn(root->right, key);
    }
    else {
        if (root->left == nullptr) {
            node* temp = root->right;
            delete root;
            root = temp;
        }
        else if (root->right == nullptr) {
            node* temp = root->left;
            delete root;
            root = temp;
        }
        else {
            node* temp = root->right;
            while (temp && temp->left != nullptr) {
                temp = temp->left;
            }
            root->data = temp->data;
            deleteNodeNoReturn(root->right, temp->data);
        }
    }
}

// inorder traversal
void inorderTraversal(node* root) {
    if (root == nullptr) return;
    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}

int main (){
    // Example usage:
    node* root = makeNode(10);
    root->left = makeNode(5);
    root->right = makeNode(15);
    // add more
    root->left->left = makeNode(3);
    root->left->right = makeNode(7);
    root->right->right = makeNode(18);

    /*
        The tree structure is:
              10
             /  \
            5    15
           / \     \
          3   7    18
    */

    cout << "Level Order Traversal before deletion: ";
    inorderTraversal(root);
    cout << endl;

    int key = 5;
    root = deleteNode(root, key);
    cout << "Level Order Traversal after deleting " << key << ": ";
    inorderTraversal(root);
    cout << endl;

    return 0;
}