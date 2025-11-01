#include <iostream>
using namespace std;

struct BirthDay {
    int day;
    int month;
    int year;
};

struct Student {
    string ID;
    string Name;
    string Gender;
    BirthDay Born;
};

struct node {
    Student data;
    node* next;
};

struct ListStudent {
    node* head;
    node* tail;
};

node* makeNode(Student st) {
    node* newNode = new node;
    newNode->data = st;
    newNode->next = nullptr;
    return newNode;
}

void Initial(ListStudent& list) {
    list.head = list.tail = nullptr;
}

void InsertLast(ListStudent& list, Student st) {
    node* newNode = makeNode(st);

    if (list.head == nullptr) {
        list.head = list.tail = newNode;
    } else {
        list.tail->next = newNode;
        list.tail = newNode;
    }
}

void ShowListStudent(ListStudent& list) {
    node* temp = list.head;

    while(temp != nullptr){ 
            cout << temp->data.ID << "\t"
            << temp->data.Name << "\t"
            << temp->data.Gender << "\t"
            << temp->data.Born.month << "/"
            << temp->data.Born.day << "/"
            << temp->data.Born.year << endl;
        temp = temp->next;
    }
    
    delete temp;
}


int main () {
    Student st1 = {"100","An","Male",{1, 1, 200}};
    Student st2 = {"120","Han","FeMale",{10,10,2000}};
    Student st3 = {"130","Chu","FeMale",{12,10,2000}};
    Student st4 = {"140","Nhung","FeMale",{12,5,2000}};
    ListStudent L;
    Initial(L);
    InsertLast(L,st1);
    InsertLast(L,st2);
    InsertLast(L,st3);
    InsertLast(L,st4);
    ShowListStudent(L);

    return 0;
}