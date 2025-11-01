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

node *makeNode(int x) {
    node* newNode = new node;
    newNode->data = x;
    newNode->next = nullptr;
    return newNode;
}

void Init(List& list) {
    list.head = list.tail = nullptr;
}

void InsertLast(List& list, int x) {
    node* newNode = makeNode(x);
    if (list.head == nullptr) {
        list.head = list.tail = newNode;
    } else {
        list.tail->next = newNode;
        list.tail = newNode;
    }

}

void ShowLast(List& list) {
    if (list.tail != nullptr) {
        cout << list.tail->data;
    }
}

int main () {
    int x = 5;
    List sll;
    Init(sll);
    InsertLast(sll,x);
    ShowLast(sll);
    return 0;
}