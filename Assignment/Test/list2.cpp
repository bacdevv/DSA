#include <stdio.h>
#include <stdlib.h> // Cần thiết cho NULL và malloc
#include <iostream>
using namespace std;

struct Node {
    int data;
    struct Node *pNext;
};

typedef struct Node Node;

struct List {
    Node *pHead;
    Node *pTail;
};

typedef struct List List;

Node *makeNode(int x) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = x;
    newNode->pNext = NULL;
    return newNode;
}

void Init(List &l) {
    l.pHead = NULL;
    l.pTail = NULL;
}

void InsertLast(List &l, int x) {
    Node *newNode = makeNode(x);
    if (l.pHead == NULL) {
        l.pHead = l.pTail = newNode;
    } else {
        l.pTail->pNext = newNode;
        l.pTail = newNode;
    }
}

void ShowLast(List l) {
    if (l.pTail != NULL)
        cout << l.pTail->data;
}


// --- Hàm Main để kiểm tra ---
int main()
{
    int x = 5;
    List sll;
    Init(sll);
    InsertLast(sll,x);
    ShowLast(sll);

    return 0;
}