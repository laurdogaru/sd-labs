#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char data;
	struct node *next;
}node;

typedef struct Stack {
	struct node *top;
	int len;
}Stack;

void init_stack(Stack **s) {
	*s = malloc(sizeof(Stack));
	(*s)->len = 0;
	(*s)->top = NULL;
}

int add_stack(Stack *s,char val) {
	node *q;
	q = (node*) malloc(sizeof(node));
	if( q == NULL ) {
		return 0;
	}
	q->data = val;
	q->next = s->top;
	s->top = q;
	s->len++;
	return 1;
}

char pop_stack(Stack *s) {
	char aux;
	node *q;
	if( s->top == NULL ) {
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
	node *q = s->top;
	if( q == NULL) {
		printf("stiva este vida\n");
	} else {
		while( q != NULL) {
			printf("%c ",q->data);
			q = q->next;
		}
		printf("\n");
	}
}

int main() {
	char a[30];
	int i;
	Stack *s;

	init_stack(&s);
	add_stack(s, 's'); //pe post de santinela

	fgets(a, 30, stdin);

	for(i = 0; i <= strlen(a); i++) {
		if(a[i] == '(') {
			add_stack(s, a[i]);
		}
		if(a[i] == ')') {
			pop_stack(s);
		}
	}
	/*Daca singurul element ramas nu este santinela,
	atunci sirul este incorect parantezat*/
	if(s->top == NULL) {
		printf("incorect parantezat\n");
	} else if( s->top->data == 's' ) {
		printf("corect parantezat\n");
	} else {
		printf("incorect parantezat\n");
	}
	return 0;
}