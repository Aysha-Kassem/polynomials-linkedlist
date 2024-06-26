#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Node {
	float coef;
	int power;
	Node* next;
};


void insert(Node** head, int pow, float num) {
	while (pow < 0) {
		printf("error");

		if (*head == NULL || pow > (*head)->power) {
			Node* n = (Node*)malloc(sizeof(Node));
			n->coef = num;
			n->power = pow;
			n->next = *head;
			*head = n;
		}
		else if (pow == (*head)->power) (*head)->coef += num;
		else {
			Node* n = (Node*)malloc(sizeof(Node));
			n->coef = num;
			n->power = pow;
			n->next = NULL;
			Node* p = *head;
			while (p->next != NULL && p->next->power > pow) p = p->next;
			n->next = p->next;
			p->next = n;
		}
	}
}

void create(Node** n) {
	int x, power;
	float  coef;
	printf("number of term is: ");
	scanf_s("%d", &x);
	for (int i = 0; i < x; i++) {
		printf("the coefficient %d: ", i + 1);
		scanf_s("%fx%d", &coef, &power);
		//printf("the power %d: ", i + 1);
		//scanf_s("%d", &power);
		insert(n, power, coef);
	}
}

void print(Node* head)
{
	if (head == NULL) {
		printf("No Polynomial");
		return;
	}
	Node* p = head;
	while (p != NULL) {
		printf("(%fX^%d)", p->coef, p->power);
		p = p->next;
		if (p != NULL) printf(" + ");
		else printf("\n");
	}
}

void ADD(Node* n1, Node* n2) {
	Node* p1 = n1;
	Node* p2 = n2;
	Node* add = NULL;
	while (p1 != NULL && p2 != NULL) {
		if (p1->power == p2->power) {
			insert(&add, p1->power, p1->coef + p2->coef);
			p1 = p1->next; p2 = p2->next;
		}
		else if (p1->power > p2->power) {
			insert(&add, p1->power, p1->coef);
			p1 = p1->next;
		}
		else if (p1->power < p2->power) {
			insert(&add, p2->power, p2->coef);
			p2 = p2->next;
		}
	}
	while (p1 != NULL) {
		insert(&add, p1->power, p1->coef);
		p1 = p1->next;
	}
	while (p2 != NULL) {
		insert(&add, p2->power, p2->coef);
		p2 = p2->next;
	}
	printf("the add is: ");
	print(add);
}


void MUL(Node* n1, Node* n2) {
	Node* p1 = n1;
	Node* p2 = n2;
	Node* mul = NULL;
	if (p1 == NULL || p2 == NULL) { printf("ZERO"); return; }
	while (p1 != NULL) {
		while (p2 != NULL) {
			insert(&mul, p1->power + p2->power, p1->coef * p2->coef);
			p2 = p2->next;
		}
		p1 = p1->next;
		p2 = n2;
	}
	Node* p3 = mul;
	Node* p = NULL;
	while (p3->next != NULL) {
		if (p3->power == p3->next->power) {
			p3->coef += p3->next->coef;
			p = p3->next;
			p3->next = p3->next->next;
			delete(p);
		}
		else p3 = p3->next;
	}
	printf("the multipe is: ");
	print(mul);
}

float compute(Node* head, int x) {
	Node* p = head;
	float sum = 0;
	while (p != NULL) {
		sum += p->coef * pow(x, p->power);
		p = p->next;
	}
	return sum;
}

int main() {
	Node* n1 = NULL;
	Node* n2 = NULL;
	printf("the first polyomial\n");
	create(&n1);
	printf("the second polyomial\n");
	create(&n2);
	int op, x;
	while (true) {
		printf("Enter operation : \n1 to print\n2 to Add\n3 to mult\n4 to Evalute polynomial\n0 to exit\n");
		scanf_s("%d", &op);
		switch (op) {
		case 1:
			printf("print the first polyomial\n"); print(n1);
			printf("prinr the second polyomial\n"); print(n2);
			break;
		case 2:
			ADD(n1, n2); break;
		case 3:
			MUL(n1, n2); break;
		case 4:
			printf("Enter value of x : ");
			scanf_s("%d", &x);
			printf("result frist poly = %f\n", compute(n1, x));
			printf("result second poly = %f\n", compute(n2, x));
			break;
		case 0:
			exit(0);
		}
	}
}