#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char *key;
	int priority;
	struct node *left, *right,*parent;
} node;

typedef struct hashtable {
	struct node **table; 
	int nr_buckets;
	int (*hfunc) (char*, int);
	int size; 
} hashtable;

void init(hashtable **h, int buckets, int (*func)(char*, int)) {
	int i;
	*h = malloc(sizeof(hashtable));
	(*h)->nr_buckets = buckets;
	(*h)->size = 0;
	(*h)->table = (node**) malloc(buckets*sizeof(node*));
	(*h)->hfunc = func;
	for(i = 0; i < buckets; i++) {
		(*h)->table[i] = NULL;
	}
}

int power(int baza, int exponent) {
	int i = 1;
	while( exponent > 0 ) {
		i = i * baza;
		exponent--;
	}
	return i;
}

int hashfunc(char *s, int buckets) {
	int n = strlen(s), i, sum = 0, z;
	for(i = 0; i < n; i++ ) {
		sum = sum + (s[i]-96) * power(26, n-i-1);
	}
	return sum % buckets;
}

node *init_node(node *parent, char *val, int priority) {
	node *nou = malloc(sizeof(node));
	nou->parent = parent;
	nou->left = NULL;
	nou->right = NULL;
	nou->key = val;
	nou->priority = priority;
	return nou;
}

void rotate_left(node **root) {
	node *n = (*root)->left;
	(*root)->left = n->right;
	n->right = *root;
	*root = n;
}

void rotate_right(node **root) {
	node *n  = (*root)->right;
	(*root)->right = n->left;
	n->left = *root;
	*root = n;
}

void balance( node **root ) {
	if( (*root)->left &&  (*root)->left->priority > (*root)->priority ) {
		rotate_left(root);
	} else if( (*root)->right && (*root)->right->priority > (*root)->priority ) {
		rotate_right(root);
	}
}

void insert_in_treap(node **root,char *val, int priority) {
	if(*root == NULL) {
		*root = init_node(NULL, val, priority);
		return;
	}
	if(strcmp(val, (*root)->key) < 0) {
		if( (*root)->left == NULL ) {
			(*root)->left = init_node(*root, val, priority);
		} else {
			insert_in_treap(&(*root)->left, val, priority);
		}
	} else {
		if( (*root)->right == NULL ) {
			(*root)->right = init_node(*root, val, priority);
		} else {
			insert_in_treap(&(*root)->right, val, priority);
		}
	}
	balance(root);
}

void delete_from_treap(node **root, char *val) {
	if(root==NULL) {
		return;
	}
	if(strcmp(val, (*root)->key ) < 0) {
		delete_from_treap(&((*root)->left), val);
	} else if( strcmp( val, (*root)->key ) > 0 ) {
		delete_from_treap(&((*root)->right), val);
	} else {
		if((*root)->left == NULL && (*root)->right == NULL) {
			*root = NULL;
			free(*root);
		} else {
			if((*root)->left &&  (*root)->left->priority > (*root)->right->priority) {
				rotate_left(root);
			} else {
				rotate_right(root);
			}
			delete_from_treap(root,val);
		}
	}
}

void insert(char *s, hashtable *h) {
	int bucket = h->hfunc(s, h->nr_buckets);
	int priority = rand();
	insert_in_treap(&(h->table[bucket]), s, priority);
	h->size++;
}

int find(node *root, char *s) {
	if( root == NULL ) {
		return 0;
	}
	if( strcmp(s, root->key) == 0 ) {
		return 1;
	} else if(strcmp(s, root->key) < 0) {
		find(root->left, s);
	} else {
		find(root->right, s);
	}
}

void delete(char *s, hashtable *h) {
	int bucket = h->hfunc(s, h->nr_buckets);
	node *n = h->table[bucket], *p;
	delete_from_treap(&(h->table[bucket]), s);
	h->size--;
}


int main() {
	hashtable *h;
	char *s1 = "abc", *s2 = "ae", *s3 = "abcd";
	
	init(&h, 50 , hashfunc);
	insert(s1, h);
	insert(s2, h);
	insert(s3, h);

	printf("%d\n", find(h->table[h->hfunc(s1,h->nr_buckets)],s1));
	printf("%d\n", find(h->table[h->hfunc(s2,h->nr_buckets)],s2));
	printf("%d\n", find(h->table[h->hfunc(s3,h->nr_buckets)],s3));
	
	delete(s1, h);
	printf("%d\n", find(h->table[h->hfunc(s1, h->nr_buckets)], s1));
	delete(s2, h);
	printf("%d\n", find(h->table[h->hfunc(s2, h->nr_buckets)], s2));

	return 0;
}