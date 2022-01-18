#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HuffNode {
	char ch;
	int val;
	struct HuffNode *left, *right, *parent;
} HuffNode;

typedef struct node {
	HuffNode *node;
	struct node *left, *right;
} node;

typedef struct heap {
	int no_nodes;
	struct HuffNode *root;
} heap;

HuffNode *init_huffnode(char a, int val) {
	HuffNode *aux = (HuffNode*) malloc(sizeof(HuffNode));
	aux->left = NULL;
	aux->right = NULL;
	aux->ch = a;
	aux->val = val;
	return aux;
}

void init_heap(heap **h) {
	*h = malloc(sizeof(heap));
	(*h)->no_nodes = 0;
	(*h)->root = NULL;
}

void swap(HuffNode *a, HuffNode *b) {
	int aux;
	aux = a->val;
	a->val = b->val;
	b->val = aux;
	char c;
	c = a->ch;
	a->ch = b->ch;
	b->ch = c;
}

void swap_nodes(HuffNode **a, HuffNode **b) {
	HuffNode *aux = *a;
	*a = *b;
	*b = aux;
}

char *binary(int n) {
	int  i = 0, k = 1, bin = 0;
	char *a = (char*)malloc(30*sizeof(char));
	while( n > 0 )
	{
		if(n % 2 == 0) {
			a[i]='0';
		}
		else {
			a[i]='1';
		}
		n = n / 2;
		i++;
	}
	return a;
}

void insert_in_max(heap *h, HuffNode *nou) {
	if(h->root == NULL) {
		nou->parent = NULL;
		h->root = nou;
		h->no_nodes = 1;
	} else {
		if( h->root->left == NULL) {
			nou->parent = h->root;
			h->root->left = nou;
			h->no_nodes++;
			if(nou->val > h->root->val)
			{
				swap_nodes(&(h->root->left), &(h->root));
			}
		} else if( h->root->right == NULL) {
			nou->parent = h->root;
			h->root->right = nou;
			h->no_nodes++;
			if( nou->val > h->root->val ) {
				swap_nodes(&(h->root->right), &(h->root));
			}
		} else {
			HuffNode *aux1, *aux2;
			int nr = h->no_nodes + 1;
			aux1 = h->root;
			char *a = binary(nr);
			int i = strlen(a) - 2;
			while( i >= 0) {
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
			while( aux1->parent != NULL && aux1->parent->val < aux1->val ) {
				swap_nodes(&(aux1), &(aux1->parent));
				aux1 = aux1->parent;
			}
		}
	}

}

void insert_in_min(heap *h, int val, char ch) {
	HuffNode *nou = init_huffnode(ch, val);
	if(h->root == NULL) {
		nou->parent = NULL;
		h->root = nou;
		h->no_nodes = 1;
	} else {
		if( h->root->left == NULL) {
			nou->parent = h->root;
			h->root->left = nou;
			h->no_nodes++;
			if(val < h->root->val) {
				swap(h->root->left, h->root);
			}
		} else if( h->root->right == NULL) {
			nou->parent = h->root;
			h->root->right = nou;
			h->no_nodes++;
			if( val < h->root->val ) {
				swap(h->root->right, h->root);
			}
		}
		else {
			HuffNode *aux1, *aux2;
			int nr = h->no_nodes + 1;
			aux1 = h->root;
			char *a = binary(nr);
			int i = strlen(a) - 2;
			while( i >= 0) {
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
			} else {
				aux2->right = nou;
			}
			h->no_nodes++;
			aux1 = nou;
			while( aux1->parent != NULL && aux1->parent->val > aux1->val ) {
				swap(aux1, aux1->parent);
				aux1 = aux1->parent;
			}
		}
	}
}

void heapify_max(HuffNode *subroot) {
	HuffNode *st, *dr, *aux1 = subroot, *aux2;
	while( aux1->left ) {
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

void heapify_min(HuffNode *subroot) {
	HuffNode *st, *dr, *aux1 = subroot, *aux2;
	while( aux1->left ) {
		aux2 = aux1;
		st = aux1->left;
		dr = aux1->right;
		if( st->val < aux1->val ) {
			aux2 = st;
		}
		if( dr && dr->val < aux1->val ) {
			aux2 = dr;
		}
		if( aux1 == aux2 ) {
			break;
		}
		swap(aux1, aux2);
		aux1 = aux2;
	}
}

int remove_root_max(heap *h) {
	int nr = h->no_nodes, hmax = h->root->val;
	char *a = binary(nr);
	HuffNode *aux1 = h->root, *aux2;
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
	}
	else {
		aux2->left = NULL;
	}
	aux1 = NULL;
	free(aux1);
	h->no_nodes--;
	heapify_max(h->root);
	return hmax;
}

HuffNode *remove_root_min(heap *h) {
	int nr = h->no_nodes;
	char *a = binary(nr);
	HuffNode *aux1 = h->root,*aux2,*r = h->root;
	int i = strlen(a) - 2;
	while( i >= 0 ) {
		if( a[i] == '1' ) {
			aux1 = aux1->right;
		} else if( a[i] == '0') {
			aux1 = aux1->left;
		}
		if( i == 1 ) {
			aux2 = aux1;
		}
		i--;
	}
	h->root->val = aux1->val;
	h->root->ch = aux1->ch;
	if( aux2->right ) {
		aux2->right = NULL;
	} else {
		aux2->left = NULL;
	}
	aux1 = NULL;
	free(aux1);
	h->no_nodes--;
	heapify_min(h->root);
	return r;
}

int *frecventa(char *a, int n) {
	int i,*f;
	f =(int*)calloc(27,sizeof(int));
	for(i = 0; i < n; i++) {
		if( a[i] == ' ') {
			f[0]++;
		} else {
			f[a[i] - 96]++;
		}
	}
	return f;
}

void *create_min_heap(heap *h, int *v) {
	int i;
	if( v[0] != 0  ) {
		insert_in_min(h,v[0],' ');
	}
	for(i = 1; i < 27 ; i++) {	
		if(v[i] > 0) {
			insert_in_min(h,v[i],i+96);
		}
	}
}

heap *create_max_heap(heap *h) {
	int sum;
	HuffNode *aux1, *aux2;
	heap *max;
	init_heap(&max);
	while( h->no_nodes > 0 ) {
		HuffNode *nou = (HuffNode*) sizeof(HuffNode);
		aux1 = remove_root_min(h);
		heapify_min(h->root);
		aux2 = remove_root_min(h);
		heapify_min(h->root);
		nou->left = aux1;
		nou->right = aux2;
		aux1->parent = nou;
		aux2->parent = nou;
		nou->val = aux1->val + aux2->val;
		nou->ch = '$';
		insert_in_max(max, nou);
	}	
	return max;
}

void printcod(HuffNode *max, int cod[], int vf) {
	int i;
	if( max->left ) {
		cod[vf] = 0;
		printcod(max->left,cod,vf+1);
	}
	if( max->right ) {
		cod[vf] = 1;
		printcod(max->right, cod, vf+1);
	}
	if( max->right == NULL && max->left == NULL ) {
		printf("%c ", max->ch);
		for(i = 0; i < vf; i++)
			printf("%d", cod[i]);
		printf("\n");
	}
}

void Huffman(int *v) {
	heap *h;
	init_heap(&h);
	create_min_heap(h, v);
	heap *max = create_max_heap(h);
	int cod[10], vf = 0;
	printcod(max->root, cod, vf);
}
void in_order( HuffNode *root ) {
	if( root == NULL ) {
		return;
	}
	in_order(root->left);
	printf("%c ", root->ch);
	in_order(root->right);
}

int main() {
	int i;
	heap *h;
	init_heap(&h);
	char *a = "ana are mere andrei are pere";
	int *v = frecventa(a, strlen(a));

	create_min_heap(h,v);
	in_order(h->root);

}	