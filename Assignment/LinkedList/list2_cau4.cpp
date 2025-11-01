#include <iostream>
using namespace std;

struct node {
    int data;
    node* next;
};

struct List {
    node* head;
    node* tail;
};


void Init(List &list) {
    list.head = list.tail = nullptr;
}

node* makeNode(int x) {
    node* newNode = new node;
    newNode->data = x;
    newNode->next = nullptr;
    return newNode;
}

void AppendList(List& list, int a[], int n){ 
    for (int i = 0; i < n; i++) {
        node* newNode = makeNode(a[i]);

        if (list.head == nullptr) {
            list.head = list.tail = newNode;
        } else {
            list.tail->next = newNode;
            list.tail = newNode;
        }
    }
}

int RemoveNodesK(List& list, int k) {
    if(list.head == nullptr) return 0;

    node* temp = list.head;
    int count = 0;

    while (temp != nullptr) {
        if (temp->data == k) {
            ++count;
            list.head = list.head->next;
        }
        temp = temp->next;
    }

    return count;
}


int main () {
    List sll;
    Init(sll);
    int n = 1, k = 10;
    int V[] = {10};
    AppendList(sll,V,n);
    int res = RemoveNodesK(sll,k);
    cout << res << endl;
    return 0;
}