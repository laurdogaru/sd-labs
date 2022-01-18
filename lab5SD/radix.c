#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *next;
} node;

typedef struct Queue {
	struct node *tail,*head;
	int len;
} Queue;

void init_queue(Queue **q) {
	*q = malloc(sizeof(Queue));
	(*q)->len = 0;
	(*q)->tail = NULL;
	(*q)->head = NULL;
}

int add_queue(Queue *q, int val) {
	node *aux;
	aux = (node*) malloc(sizeof(node));
	if( aux == NULL ) {
		printf("memorie insuficienta\n");
		return 0;
	}
	aux->data = val;
	aux->next = NULL;
	if( q->tail == NULL && q->head == NULL ) {
		q->head = q->tail = aux;
	} else {
		q->tail->next = aux;
		q->tail = aux;
	}
	q->len++;
	return 1;
}

int pop_queue(Queue *q) {
	int a;
	node *aux;
	if( q->head == NULL ) {
		printf("coada vida\n");
		return 0;
	}
	a = q->head->data;
	aux = q->head;
	q->head = q->head->next;
	free(aux);
	q->len--;
	return a;
}

int cifra(int n,int poz) {
	int aux = n, i = poz;
	while(i > 1 ) {
		aux = aux / 10;
		i--;
	}
	return aux % 10;
}

int maxcif(int v[], int n) {
	int i, aux, contor, mx=0;
	for(i = 0; i < n; i++) {
		contor = 0;
		aux = v[i];
		while(aux > 0) {
			contor++;
			aux = aux / 10;
		}
		if( contor > mx) {
			mx = contor;
		}
	}
	return mx;
}

void print_queue(Queue *q) {
	node *aux = q->head;
	if( aux == NULL)
		;
	else {
		while( aux!=NULL ) {
			printf("%d ", aux->data);
			aux = aux->next;
		}
	}
}	

int main() {
	int i, mc, n, v[100], j, k, aux;
	Queue *coada[10];

	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &v[i]);
	}
	mc = maxcif(v, n);
	for(i = 1; i <= mc; i++) {
		for(j = 0; j < 10; j++) {
			init_queue(&coada[j]);
		}
		for(j=0; j < n; j++) {
			add_queue(coada[cifra(v[j], i)], v[j]);
		}
		k = 0;
		for(j = 0; j<10; j++) {
			while( coada[j]->head != NULL) {
				v[k] = coada[j]->head->data;
				pop_queue(coada[j]);
				k++;
			}
		}

	}
	for(i=0; i < n; i++) {
		printf("%d ",v[i]);
	}
	return 0;
}