#include <stdio.h>
#include <stdlib.h> // Cần thiết cho NULL và malloc

struct Node {
    int data;
    Node* pNext;
};

struct List {
    Node* pHead;
    Node* pTail;
};

void Init(List &l) {
    l.pHead = NULL;
    l.pTail = NULL;
}

Node *makeNode(int x) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = x;
    newNode->pNext = NULL;
    return newNode;
}

void InsertFirst(List &l, int x) { 
    Node *newNode = makeNode(x);
    if (l.pHead == NULL) {
        l.pHead = newNode;
    } else {
        newNode->pNext = l.pHead;
        l.pHead = newNode;
    }
}

void ShowFirst(List l) {
    if (l.pHead != NULL) {
        printf("%d", l.pHead->data);
    }
}


// --- Hàm Main để kiểm tra ---
int main()
{
    int x = 5;
    List sll;
    Init(sll);
    InsertFirst(sll,x);
    ShowFirst(sll);

    return 0;
}