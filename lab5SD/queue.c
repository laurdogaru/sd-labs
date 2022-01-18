#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *next;
} node;

typedef struct Queue {
	struct node *tail, *head;
	int len;
} Queue;

void init_queue(Queue **q) {
	*q = malloc(sizeof(Queue));
	(*q)->len = 0;
	(*q)->tail = NULL;
	(*q)->head = NULL;
}

void free_queue(Queue **q) {
	node *aux = (*q)->head;
	while( aux != NULL ) {
		(*q)->head = (*q)->head->next;
		free(aux);
		aux = (*q)->head;
	}
}

int add_queue(Queue *q,int val) {
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

int pop(Queue *q) {
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

void print_queue(Queue *q) {
	node *aux = q->head;
	if( aux == NULL) {
		printf("coada este vida\n");
	}
	else {
		while( aux != NULL ) {
			printf("%d ", aux->data);
			aux = aux->next;
		}
		printf("\n");
	}

}	

int main() {
	int i;
	Queue *q;
	init_queue(&q);
	for(i = 0; i < 10; i++) {
		add_queue(q, i);
	}
	print_queue(q);
	pop(q);
	print_queue(q);
	free_queue(&q);
	print_queue(q);
}
