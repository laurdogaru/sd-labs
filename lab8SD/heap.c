#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int val;
	struct node *left, *right, *parent;
} node;

typedef struct Heap {
	int no_nodes;
	struct node *root;
} Heap;

void swap(node *a, node *b) {
	int aux;
	aux = a->val;
	a->val = b->val;
	b->val = aux;
}

void init_heap(Heap **h) {
	*h = malloc(sizeof(Heap));
	(*h)->no_nodes = 0;
	(*h)->root = NULL;
}

char *binary(int n) {
	int  i = 0, k = 1, bin = 0;
	char *a = (char*) malloc(30 * sizeof(char));
	while( n > 0 ) {
		if(n % 2 == 0) {
			a[i]='0';
		} else {
			a[i]='1';
		}
		n = n / 2;
		i++;
	}
	return a;
}

void insert(Heap *h,int val) {
	if(h->root == NULL) {
		node *nou = malloc(sizeof(node));
		nou->parent = NULL;
		nou->val = val;
		h->root = nou;
		h->no_nodes = 1;
	} else {
		if( h->root->left == NULL) {
			node *nou = malloc(sizeof(node));
			nou->parent = h->root;
			nou->val = val;
			h->root->left = nou;
			h->no_nodes++;
			if(val > h->root->val) {
				swap(h->root->left, h->root);
			}
		} else if( h->root->right == NULL) {
			node *nou = malloc(sizeof(node));
			nou->parent = h->root;
			nou->val = val;
			h->root->right = nou;
			h->no_nodes++;
			if( val > h->root->val ) {
				swap(h->root->right, h->root);
			}
		} else {
			node *nou, *aux1, *aux2;
			nou = (node*) malloc(sizeof(node));
			nou->val = val;
			int nr = h->no_nodes + 1;
			aux1 = h->root;
			char *a = binary(nr);
			int i = strlen(a) - 2;
			while(i >= 0) {
				if( a[i] == '1') {
					aux1 = aux1->right;
				} else {
					aux1 = aux1->left;
				}
				if( i == 1) {
					aux2 = aux1;
				}
				i--;
			}
			nou->parent = aux2;
			if(aux2->left == NULL) {
				aux2->left = nou;
			}
			else {
				aux2->right = nou;
			}
			h->no_nodes++;
			aux1 = nou;
			while( aux1->parent != NULL && aux1->parent->val < aux1->val )
			{
				swap(aux1, aux1->parent);
				aux1 = aux1->parent;
			}
		}
		
	}

}

void heapify(node *subroot) {
	node *st, *dr, *aux1 = subroot, *aux2;
	while( aux1->left || aux1->right ) {
		aux2 = aux1;
		st = aux1->left;
		dr = aux1->right;
		if( st->val > aux1->val ) {
			aux2 = st;
		}
		if( dr && dr->val > aux1->val ) {
			aux2 = dr;
		}
		if( aux1 == aux2 ) {
			break;
		}
		swap(aux1, aux2);
		aux1 = aux2;

	}
}

int remove_root(Heap *h) {
	int nr = h->no_nodes,hmax = h->root->val;
	char *a = binary(nr);
	node *aux1 = h->root, *aux2;
	int i = strlen(a) - 2;
	while( i >= 0 ) {
		if( a[i] == '1' ) {
			aux1 = aux1->right;
		} else {
			aux1 = aux1->left;
		}
		if( i == 1 ) {
			aux2 = aux1;
		}
		i--;
	}
	h->root->val = aux1->val;
	if( aux2->right ) {
		aux2->right = NULL;
	} else {
		aux2->left = NULL;
	}
	aux1 = NULL;
	free(aux1);
	h->no_nodes--;
	heapify(h->root);
	return hmax;
}

void in_order( node *root ) {
	if( root == NULL ) {
		return;
	}
	in_order( root->left );
	printf("%d ", root->val );
	in_order( root->right );
}


int main() {
	int n;
	Heap *h;
	init_heap(&h);
	insert(h, 25);
	insert(h, 18);
	insert(h, 3);
	insert(h, 14);
	insert(h, 21);
	insert(h, 12);
	insert(h, 7);
	
	while(h->no_nodes!=0) {
		n = remove_root(h);
		printf("%d ", n);
		heapify(h->root);
	}
	printf("\n");
	return 0;
}
