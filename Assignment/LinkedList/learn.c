#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

typedef struct node node;

node *makeNode(int x) {
    node *newNode = (node*)malloc(sizeof(node));
    newNode->data = x;
    newNode->next = NULL;
    return newNode;
}

void duyet(node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
}

int size(node *head) {
    int count = 0;
    while (head != NULL) {
        ++count;
        head = head->next;
    }
    return count;
}

void pushFront(node **head, int x) {
    node *newNode = makeNode(x);
    newNode->next = *head;
    *head = newNode;
}

void pushBack(node **head, int x) {
    node *newNode = makeNode(x);
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void insert(node **head, int k, int x) {
    int n = size(*head);
    if (*head == NULL) return;

    if (k < 1 || k > n + 1) {
        printf("Vi tri khong hop le\n");
        return;
    }

    if (k == 1) {
        pushFront(head, x);
    } else if (k == n + 1) {
        pushBack(head, x);
    } else {
        node *temp = *head;
        for (int i = 1; i < k - 1; i++) {
            temp = temp->next;
        }
        node *newNode = makeNode(x);
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void popFront(node **head) {
    if (*head == NULL) return;
    node *temp = *head;
    (*head) = temp->next;
    free(temp);

    // if (*head == NULL) {
    //     printf("Head null");
    // }
}

void popBack(node **head) {
    if (*head == NULL) return;
    node *temp = *head;

    if (temp->next == NULL) {
        *head = NULL;
        free(temp);
        return;
    }

    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    node *last = temp->next;
    temp->next = NULL;
    free(last);
}

void erase(node **head, int k) {
    int n = size(*head);
    if (k < 1 || k > n + 1) return;

    if (k == 1) popFront(head);
    else {
        node *temp = *head;
        for (int i = 1; i < k - 1; i++) {
            temp = temp->next;
        }
        node *del = temp->next;
        temp->next = del->next;
        free(del);
    }
}

void sort(node **head) {
    for (node *i = *head; i != NULL; i = i->next) {
            node *min = i;
        for (node *j = i->next; j != NULL; j = j->next) {
            if (j->data < min->data) {
                min = j;
            }
        }

        int tmp = min->data;
        min->data = i->data;
        i->data = tmp;
    }
}

int main() {
    node *head = NULL;

    while (1) {
        printf("\n------------------\n");
        printf("1. Them vao dau\n");
        printf("2. Them vao cuoi\n");
        printf("3. Them vao giua\n");
        printf("4. Xoa vao dau\n");
        printf("5. Xoa vao cuoi\n");
        printf("6. Xoa vao giua\n");
        printf("7. Duyet\n");
        printf("8. Dem\n");
        printf("9. Sap xep\n");
        printf("0. Thoat\n");
        printf("\n------------------\n");
        int choice, x, k;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhap du lieu: \n");
                scanf("%d", &x);
                pushFront(&head, x);
                break;
            case 2:
                printf("Nhap du lieu: \n");
                scanf("%d", &x);
                pushBack(&head,  x);
                break;
            case 3:
                printf("Nhap du lieu: \n");
                scanf("%d", &x);
                printf("Nhap cho can chen: \n");
                scanf("%d", &k);
                insert(&head, k, x);
                break;
            case 4:
                popFront(&head);
                break;
            case 5:
                popBack(&head);
                break;
            case 6:
                printf("Nhap vi tri can xoa: ");
                scanf("%d", &k);
                erase(&head, k);
                break;
            case 7:
                duyet(head);
                break;
            case 8:
                printf("%d", size(head));
                break;
            case 9:
                sort(&head);
                break;
            case 0:
                exit(0);
            default:
                printf("Du lieu khong hop le\n");
                break;
        }
    }
    return 0;
}
