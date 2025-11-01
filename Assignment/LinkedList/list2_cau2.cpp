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

int CountKLinkedList(List& list, int value) {
    node* temp = list.head;
    int count = 0;
    while (temp != nullptr) {
        if (temp->data == value) 
            ++count;
        temp = temp->next;
    }

    return count;
}


int main () {
    List sll;
    Init(sll);
    int n = 5, k = 3;
    int V[] = {1,2,3,4,5};
    AppendList(sll,V,n);
    int res = CountKLinkedList(sll,k);
    cout << res;
    return 0;
}