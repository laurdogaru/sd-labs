#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MARE 30000

typedef struct nod {
	int val;
	struct nod *leg;
	int cost;
} nod;

typedef struct graf {
	int size;
	nod **a;
}graf;

typedef struct heap {
	int v[100];
	int n;
}heap;

void init_graph(graf **g, int n) {
	int i;
	*g = malloc(sizeof(graf));
	(*g)->size = n;
	(*g)->a = (nod**) malloc((n+1)*sizeof(nod*));
	for(i = 1; i <= n; i++) {
		(*g)->a[i] = NULL;
	}
}

void add_arc(graf *g, int x, int y, int cost) {
	nod *nou = (nod*)malloc(sizeof(nod));
	nou->val = y;
	nou->cost = cost;
	nou->leg = g->a[x];
	g->a[x] = nou;
}

int arc(graf *g, int x, int y) {
	nod *aux = g->a[x];
	int c = 0;
	while( aux != NULL ) {
		if( aux->val == y ) {
			c = 1;
			break;
		}	
		aux = aux->leg;
	}
	return c;
}

void build(graf *g, int m, int *v, int *w, int *costuri) {
	int i;
	for(i = 1; i <= m ; i ++) {
		add_arc(g, v[i], w[i], costuri[i]);
	}
}

void afisare( graf *g) {
	int i;
	nod *p;
	printf("Listele de adiacenta:\n");
	for(i = 1; i <= g->size; i++ ) {
		printf("%d: ", i);
		p = g->a[i];
		while( p != NULL ) {
			printf("%d ", p->val);
			p = p->leg;
		}
		printf("\n");
	}
}

void roy_floyd(graf *g) {
	int **d, i, j, k;
	nod *p;
	d = (int**) malloc((g->size+1)*sizeof(int*));

	for(i = 1 ; i <= g->size ; i++) {
		d[i] = (int*) malloc((g->size + 1) * sizeof(int));
	}
	for(i = 1 ; i <= g->size ; i++) {
		for(j = 1; j <= g->size; j++) {
			d[i][j] = MARE;
		}
	}
	for(i = 1; i <= g->size; i++) {
		p = g->a[i];
		while( p != NULL ) {
			d[i][p->val] = p->cost;
			p = p->leg;
		}  
	}
	printf("\nMatricea de costuri initiala:\n");
	for(i = 1 ; i <= g->size; i++) {
		for(j = 1; j <= g->size; j++) {
			printf("%d ", d[i][j]);
		}
		printf("\n");
	}
	for(k = 1; k <= g->size; k++ ) {
		for(i = 1 ; i <= g->size; i++) {
			for(j = 1; j <= g->size; j++) {
				if( d[i][k] + d[k][j] < d[i][j] && i != j ) {
					d[i][j] = d[i][k] + d[k][j];
				}
				if( i == j ) {
					d[i][j] = 0;
				}
			}
		}
	}
	printf("\nMatricea de costuri finala:\n");
	for(i = 1 ; i <= g->size; i++) {
		for(j = 1; j <= g->size; j++) {
			printf("%d ", d[i][j]);
		}
		printf("\n");
	}	
}

void swap(heap *h, int i, int j) {
	int aux;
	aux = h->v[i];
	h->v[i] = h->v[j];
	h->v[j] = aux;
}

void heapify(heap *h, int i, int *d) {
	int st, dr, m = i, aux;
	st = 2 * i;
	dr = 2 * i + 1;
	if( st <= h->n && d[h->v[st]] < d[h->v[i]] ) {
		m = st;
	}
	if( dr <= h->n && d[h->v[dr]] < d[h->v[i]] ) {
		m = dr;
	}
	if( m != i ) {
		swap(h, i, m);
		heapify(h, m, d);
	}
}

int delete(heap *h, int *d) {
	int hmin;
	if( h->n <= 0 ) {
		return -1;
	}
	hmin = h->v[1];
	h->v[1] = h->v[h->n];
	h->n--;
	heapify(h, 1, d);
	return hmin;
}

void inserare(heap *h, int nod, int *poz, int *d) {
	int i;
	i = poz[nod];
	h->v[i] = nod;
	h->n++;
	while( i > 1 && d[h->v[i/2]] > d[nod] ) {
		swap(h, i, i/2);
		poz[nod] = i;
		i = i / 2;
	}
}

void dijkstra(graf *g, int source) {
	heap *h = (heap*) malloc( sizeof(heap) );
	h->n = 0 ;
	int *d, *poz, i, node;
	nod *p;
	d = (int*) malloc((g->size+1) * sizeof(int));
	poz = (int*) malloc((g->size+1) * sizeof(int));

	for(i = 1; i <= g->size; i++) {
		d[i] = MARE;
		poz[i] = -1;
	}
	d[source] = 0;
	poz[source] = 1;
	inserare(h, source, poz, d);
	while(h->n > 0) {
		node = delete(h, d);
		p = g->a[node];
		while( p != NULL ) {
			if(d[p->val] > d[node] + p->cost) {
				d[p->val] = d[node] + p->cost;
				if( poz[p->val] == -1 ) {
					poz[p->val] = h->n + 1;
					inserare(h, p->val, poz, d);
				} else {
					heapify(h, poz[p->val], d);
				}
			}
			heapify(h, poz[p->val], d);
			p = p->leg;
		}
	}
	for(i = 1; i <= g->size; i++) {
		printf("%d ", d[i]);
	}
	printf("\n");
}

void bellman_ford(graf *g, int source) {
	int i, *d, k;
	nod *p;
	d = (int*) malloc((g->size+1)*sizeof(int));

	for(i = 1; i <= g->size; i++) {
		d[i] = MARE;
	}
	d[source] = 0;

	for(k = 1; k <= g->size; k++) {
		for(i = 1; i <= g->size; i++) {
			p = g->a[i];
			while( p != NULL ) {
				if( d[p->val] > d[i] + p->cost) {
					d[p->val]  = d[i] + p->cost;
				}
				p = p->leg;
			}
		}
	}
	for(i = 1; i <= g->size; i++) {
		p = g->a[i];
		while( p != NULL ) {
			if( d[p->val] > d[i] + p->cost) {	
				printf("ciclu negativ\n");
				return;
			}
			p = p->leg;
		}
	}
	for(i = 1; i <= g->size; i++) {
		printf("%d ", d[i]);
	}
	printf("\n");
}

int main() {
	FILE *f1 = fopen("graf.in", "rt");
	int n, m, *v, *w, aux1, aux2, i, *costuri, aux3;
	fscanf(f1, "%d", &n);
	fscanf(f1, "%d", &m);
	v = (int*) malloc((m+1) * sizeof(int));
	w = (int*) malloc((m+1) * sizeof(int));	
	costuri = (int*) malloc((m+1) * sizeof(int));
	for(i = 1 ; i <= m ; i++) {
		fscanf(f1, "%d", &aux1);
		fscanf(f1, "%d", &aux2);
		fscanf(f1, "%d", &aux3);
		v[i] = aux1;
		w[i] = aux2;
		costuri[i] = aux3;
	}

	graf *g;
	init_graph(&g, n);
	build(g, m, v, w, costuri);
	afisare(g);
	printf("\nRoy-Floyd:");
	roy_floyd(g);

	printf("\nDijkstra(cu heap) pentru fiecare nod:\n");
	for(i = 1; i <= n; i++) {
		dijkstra(g,i);
	}

	printf("\nBellman-Ford pentru fiecare nod:\n");
	for(i = 1; i <= n; i++) {
		bellman_ford(g,i);
	}

	fclose(f1);
	return 0;
}