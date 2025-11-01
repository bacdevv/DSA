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

void ShowList(List& list) {
    node *temp = list.head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
}

void InsertFirst(List& list, int x) {
    node* newNode = makeNode(x);
    newNode->next = list.head;
    list.head = newNode;
}

void FindAndInsert(List& list, int key, int value) {
    node* temp = list.head;
    while (temp != nullptr) {
        if (temp->data == key) {
            break;
        }
        temp = temp->next;
    }

    if (temp != nullptr) {
        node* newNode = makeNode(value);
        if (newNode == nullptr) return;

        newNode->next = temp->next;
        temp->next = newNode;

        if (temp == list.tail) {
            list.tail = newNode;
        }
    } else {
        InsertFirst(list, value);
    }
}


int main () {

    List sll;
    Init(sll);
    int key = 5, value = 10;
    InsertFirst(sll,7);
    InsertFirst(sll,5);
    InsertFirst(sll,3);
    FindAndInsert(sll,key,value);
    ShowList(sll);

    return 0;
}
