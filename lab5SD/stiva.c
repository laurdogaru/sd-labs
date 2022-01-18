#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *next;
} node;

typedef struct Stack {
	struct node *top;
	int len;
} Stack;

void init_stack(Stack **s) {
	*s = malloc(sizeof(Stack));
	(*s)->len = 0;
	(*s)->top = NULL;
}

void free_stack( Stack **s) {
	node *q = (*s)->top;
	while( q != NULL ) {
		(*s)->top = (*s)->top->next;
		free(q);
		q = (*s)->top;
	}
}

int add_stack(Stack *s, int val) {
	node *q;
	q =(node *)malloc(sizeof(node));
	if( q==NULL ) {
		return 0;
	}
	q->data = val;
	q->next = s->top;
	s->top = q;
	s->len++;
	return 1;
}

int pop_stack(Stack *s) {
	int aux;
	node *q;
	if( s->top == NULL ) {
		printf("stiva vida\n");
		return 0;
	}
    aux = s->top->data;
    q = s->top;
    s->top = s->top->next;
    free(q);
    s->len--;
    return aux;
}

void print_stack(Stack *s) {
	node *q= s->top;
	if( q == NULL) {
		printf("stiva este vida\n");
	} else {
		while( q != NULL) {
			printf("%d ",q->data);
			q = q->next;
		}
		printf("\n");
	}
}


int main() {
	int i;
	Stack *s;
	init_stack(&s);
	for(i = 0 ; i < 10; i++) {
		add_stack(s, i);
	}
	print_stack(s);
	print_stack(s);
	free_stack(&s);
	print_stack(s);
	return 0;
}

