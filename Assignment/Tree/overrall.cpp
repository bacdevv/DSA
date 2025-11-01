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

// them co return
// node* insert(node* root, int data) {
//     if (root == nullptr) {
//         root = makeNode(data);
//     }
//     else if (data <= root->data) {
//         root->left = insert(root->left, data);
//     }
//     else {
//         root->right = insert(root->right, data);
//     }
//     return root;
// }

// them khong return
// void insert(node*& root, int data) {
//     if (root == nullptr) {
//         root = makeNode(data);
//         return;
//     }
//     else if (data <= root->data) {
//         insert(root->left, data);
//     }
//     else {
//         insert(root->right, data);
//     }
// }

// them khong de quy
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


// dung de quy max min
int findMin(node* root) {
    if (root->left == nullptr) return root->data;
    return findMin(root->left);
}

int findMax(node* root) {
    if (root->right == nullptr) return root->data;
    return findMax(root->right);
}


// khong dung de quy tim min, max
int minNoRecur(node* root) {
    if (root == nullptr) return -1;

    while(root->left != nullptr) {
        root = root->left;
    }
    return root->data;
}

int maxNoRecur(node* root) {
    if (root == nullptr) return -1;

    while (root->right != nullptr)
        root = root->right;
    return root->data;
}

// tim kiem phan tu
bool search(node* root, int data) {
    if (root == nullptr) return false;
    if (root->data == data) return true;
    if (data <= root->data) return search(root->left, data);
    else return search(root->right, data);
}

// tinh chieu cao cay de quy
int findHeight(node* root) {
    if (root == nullptr) return -1;
    return max(findHeight(root->left), findHeight(root->right)) + 1;
}

// tinh chieu cao cay khong dung de quy
int heightTree(node* root) {
    if (root == nullptr) return -1;  // đổi thành 0 nếu tính theo số node

    queue<node*> q;
    q.push(root);
    int height = -1;

    while (!q.empty()) {
        int levelSize = q.size();
        height++;

        for (int i = 0; i < levelSize; i++) {
            node* current = q.front();
            q.pop();

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }
    return height;
}

int main () {
    node* root = nullptr;

    int arr[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55, 65, 75, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    // them node co return
    // for (int i  : arr)
    //     root = insert(root, i);

    // them node khong return & khong de quy
    for (int i : arr)
        insert(root, i);

    int num;
    cout << "Enter the element be searched\n";
    cin >> num;

    cout << (search(root, num) ? "Found\n" : "Not found\n");

    // tim min max
    // int min_num_recursion = findMin(root);
    // int max_num_recursion = findMax(root);
    int min_num = minNoRecur(root);
    int max_num = maxNoRecur(root);

    cout << "Min: " << min_num << endl;
    cout << "Max: " << max_num << endl;
    // cout << "Min: " << min_num_recursion << endl;
    // cout << "Max: " << max_num_recursion << endl;


    // tim chieu cao cay
    int heightTree = findHeight(root);
    cout << "Height: " << heightTree << endl;

    return 0;
}