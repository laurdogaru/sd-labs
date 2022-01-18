#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	void *data;
	struct node *next;
} node;

typedef struct Tlist {
	node *head;
	int len;
} Tlist;

void init(Tlist **list) {
	*list = malloc(sizeof(Tlist));
	(*list)->len = 0;
	(*list)->head = NULL;
	
}

int add(Tlist *list, int n, void *data) {
   if( n < 0 || n > list->len ) {
   	return -1;
   } else if( n==0 || list->head == NULL ) {
   		node *nou = (node *) malloc(sizeof(node));
    	nou->data = data;
    	nou->next = list->head;
    	list->head = nou;
    	list->len++;
    	return 1;
   } else {
        node *q, *nou;
        int m = n;
        nou = (node *) malloc(sizeof(node));
        nou->data = data;
        q = list->head;
        while( m-1 > 0 ) {
        	q = q->next;
        	--m;
        }
        nou->next = q->next;
        q->next = nou;
        list->len++;
        return 1;
   }
   
}

node *remove_node(Tlist *list, int n) {
	node *p = list->head;
	node *q;
	int m = n;
	if(n == 0) {
		q = list->head;
		node *r = q;
		list->head = list->head->next;
		free(q);
		return r;
	}
	while( m - 1 > 0) {
		p = p->next;
		--m;
	}
	q = p->next;
	p->next = p->next->next;
	node *r = q;
	free(q);
	return r;
}

void print_int_list(Tlist *list) {
	node *p = list->head;
	if( p == NULL) {
		printf("Lista este goala");
	}
	while( p != NULL) {
    	printf("%d ", p->data);
    	p = p->next;
    }	 
    printf("\n");
	
}

void print_string_list(Tlist *list) {
	node *p = list->head;
	if( p == NULL) {
		printf("Lista este goala");
	}
	while( p != NULL) {
    	puts( p->data);
    	p = p->next;
    }	 
}

int length(Tlist *list) {
	return list->len;
}


int main() {
    Tlist *l1, *l2;
    init(&l1);
    init(&l2);
    add(l1, 0, "da");
    add(l1, 1 ,"nu");
    remove_node(l1, 1);
    print_string_list(l1);
    add(l2, 0 , 2);
    add(l2, 1 ,3 );
    print_int_list(l2);
    remove_node(l2, 0);
    print_int_list(l2);
	return 0;

}