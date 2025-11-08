#include <iostream>
using namespace std;

struct Node {
	int data;
	Node *pleft;
	Node *pright;
};
typedef Node* TREE;

void Init(TREE &t) {
	t = NULL;
}

Node* CreateNewNode(int x) {
	Node *p = new Node;
	if (p == NULL) {
		cout << "Loi: khong du bo nho!" << endl;
		return NULL;
	}
	
	p->data = x;
	p->pleft = NULL;
	p->pright = NULL;
	return p;
}

// them node vao cay
void ThemNodeVaoCay(TREE &t, int x) {
	if (t == NULL) {
		t = CreateNewNode(x);
	}
	else {
		if (x < t->data) {
			ThemNodeVaoCay(t->pleft, x);
		}
		else {
			ThemNodeVaoCay(t->pright, x);
		}
	}
}

// doc file va tao cay
void doc_file(char *tenfile, TREE &t) {
	FILE *f = fopen(tenfile, "r");
	if (f == NULL) {
		cout << "Loi: khong mo duoc file " << tenfile << endl;
		return;
	}
	int x;
	while (fscanf(f, "%d", &x) != EOF) {
		ThemNodeVaoCay(t, x);
	}
	
	fclose(f);
	cout << "Da doc file va tao cay thanh cong" << endl;	
}

int main () {
	TREE t;
	Init(t);
	
	FILE *f = fopen("input.txt", "w");
	if (f != NULL) {
		fprintf(f, "50 30 70 20 40 60 80 35 11");
		fclose(f);
	}
	
	doc_file("input.txt", t);

	
    ThemNodeVaoCay(t, 50);
    ThemNodeVaoCay(t, 30);
    ThemNodeVaoCay(t, 70);
    ThemNodeVaoCay(t, 20);
    ThemNodeVaoCay(t, 40);
    ThemNodeVaoCay(t, 60);
    ThemNodeVaoCay(t, 80);
    ThemNodeVaoCay(t, 35);
    ThemNodeVaoCay(t, 11);
	
    return 0;
}
























