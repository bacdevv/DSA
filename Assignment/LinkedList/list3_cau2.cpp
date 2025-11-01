#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

// ================= CẤU TRÚC =================
struct Node {
    int data;
    Node *pNext;
};

struct List {
    Node *pHead;
    Node *pTail;
};

// =============== HÀM NỀN TẢNG ===============
void Init(List &list) {
    list.pHead = list.pTail = nullptr;
}

Node* CreateNode(int x) {
    Node* newNode = new Node;
    if (newNode == nullptr) return nullptr;
    newNode->data = x;
    newNode->pNext = nullptr;
    return newNode;
}

void InsertFirst(List &list, int x) {
    Node* newNode = CreateNode(x);
    if (!newNode) return;

    if (list.pHead == nullptr) {
        list.pHead = list.pTail = newNode;
    } else {
        newNode->pNext = list.pHead;
        list.pHead = newNode;
    }
}

void InsertLast(List &list, int x) {
    Node* newNode = CreateNode(x);
    if (!newNode) return;

    if (list.pHead == nullptr) {
        list.pHead = list.pTail = newNode;
    } else {
        list.pTail->pNext = newNode;
        list.pTail = newNode;
    }
}

void ShowList(List &list) {
    Node *temp = list.pHead;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->pNext;
    }
}

// =============== HÀM HỖ TRỢ ===============
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

bool isPalindrome(int n) {
    if (n < 0) return false;
    long long reversed = 0;
    int original = n;

    while (n > 0) {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }
    return original == reversed;
}

// =============== HÀM GIẢI ĐỀ ===============
float PaPrime(List &L, int k) {
    List L_thuong;
    List L_vip;
    Init(L_thuong);
    Init(L_vip);

    double sumPalindrome = 0;
    int countPalindrome = 0;

    for (int n = 2; n <= k; n++) {
        if (isPrime(n)) {
            if (isPalindrome(n)) {
                InsertFirst(L_vip, n);
                sumPalindrome += n;
                countPalindrome++;
            } else {
                InsertLast(L_thuong, n);
            }
        }
    }

    if (L_thuong.pHead == nullptr) {
        L.pHead = L_vip.pHead;
        L.pTail = L_vip.pTail;
    } else if (L_vip.pHead == nullptr) {
        L.pHead = L_thuong.pHead;
        L.pTail = L_thuong.pTail;
    } else {
        L_thuong.pTail->pNext = L_vip.pHead;
        L.pHead = L_thuong.pHead;
        L.pTail = L_vip.pTail;
    }

    ShowList(L);

    if (countPalindrome == 0) return 0.0f;
    return (float)(sumPalindrome / countPalindrome);
}

// =============== MAIN ===============
int main() {
    List L;
    Init(L);

    int k = 17;

    cout << "Test" << "\t\t" << "Result" << endl;
    cout << "List L;" << endl;
    cout << "printf(\"%.2f\", PaPrime(L, 17));" << "\t";

    float avg = PaPrime(L, k);

    cout << "\n";
    printf("%.2f\n", avg);

    return 0;
}
