#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	char *val;
	struct node * next;
} node;

typedef struct hashtable {
	struct node **table; 
	int nr_buckets;
	int (*hfunc) (char*, int);
	int size; 
} hashtable;

hashtable *resize(hashtable *h, int new_nr_buckets);

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
	while(exponent > 0) {
		i = i * baza;
		exponent--;
	}
	return i;
}

int hashfunc(char *s, int buckets) {
	int n = strlen(s), i, sum = 0, z;
	for(i = 0; i < n; i++) {
		sum = sum + (s[i] - 96) * power(26, n-i-1);
	}
	return sum % buckets;
}

hashtable *insert(char *s, hashtable *h) {
	int bucket = h->hfunc(s, h->nr_buckets );
	
	node *nou = (node*) malloc(sizeof(node));
	nou->val = s;
	nou->next = h->table[bucket];
	h->table[bucket] = nou;
	h->size++;

	hashtable *aux = h;
	int aux2 = h->nr_buckets;
	if( aux->size < 0.25 * aux2 ) {
		h = resize(aux, aux2 / 2 );
	}
	if( aux->size > 0.75 * aux2 ) {
		h = resize(aux, aux2 * 2 );
	}
	return h;
}

int find(char *s, hashtable *h) {
	int bucket = h->hfunc( s, h->nr_buckets ), gasit = -1;
	node *n = h->table[bucket];

	while(n != NULL) {
		if( strcmp(s,n->val) == 0 ) {
			gasit = bucket;
			break;
		}	
		n = n->next;
	}
	return gasit;
}

hashtable *delete( char *s, hashtable *h ) {
	int bucket = h->hfunc( s, h->nr_buckets );
	node *n = h->table[bucket], *p;

	if( strcmp(s, n->val) == 0 ) {
		h->table[bucket] = n->next;
		free(n);
		h->size--;
	} else {
		while( n->next != NULL ) {
			if( strcmp(s, n->next->val) == 0 ) {
				p = n->next;
				n->next = n->next->next;
				free(p);
				h->size--;
				break;
			}	
			n = n->next;
		}
	}
	
	hashtable *aux = h;
	int aux2 = h->nr_buckets;
	if( aux->size < 0.25 * aux2 ) {
		h = resize(aux, aux2 / 2);
	}
	if( aux->size > 0.75 * aux2 ) {
		h = resize(aux, aux2 * 2);
	}
	return h;
}

hashtable *resize(hashtable *h, int new_nr_buckets ) {
	hashtable *new;
	int i;
	init(&new, new_nr_buckets, hashfunc );
	new->size = h->size;
	node *p;
	int n = h->nr_buckets;
	for(i = 0; i < n; i++ ) {
		p = h->table[i];
		while( p != NULL ) {
			insert(p->val, new);
			p = p->next;
		}
	}
	return new;
}

int main() {
	hashtable *h;
	char *s1 = "abc", *s2 = "ae", *s3 = "abcd";
	init(&h, 50 , hashfunc);
	h = insert(s1, h);
	h = insert(s2, h);
	h = insert(s3, h);

	printf("%d\n", find(s1, h));
	printf("%d\n", find(s2, h));
	printf("%d\n", find(s3, h));

	delete(s1, h);
	printf("%d\n", find(s1, h));
	delete(s2, h);
	printf("%d\n",find(s2, h));


	return 0;
}