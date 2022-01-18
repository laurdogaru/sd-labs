#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MARE 30000

typedef struct nod {
	int val;
	struct nod *leg;
	int cost;
} nod;

typedef struct graf {
	int size;
	nod **a;
} graf;

typedef struct heap {
	int v[100];
	int cost[100];
	int n;
} heap;

typedef struct muchie {
	int start;
	int finish;
	int cost;
}muchie;

void init_graph(graf **g, int n) {
	int i;
	*g = malloc(sizeof(graf));
	(*g)->size = n;
	(*g)->a = (nod**) malloc((n+1) * sizeof(nod*));
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

void build( graf *g, int m, int *v, int *w , int *costuri)
{
	int i;
	for(i = 1; i <= m; i++) {
		add_arc(g, v[i], w[i], costuri[i]);
	}
}

void afisare( graf *g)
{
	int i;
	nod *p;
	printf("Listele de adiacenta:\n");
	for(i = 1; i <= g->size; i++) {
		printf("%d: ",i);
		p = g->a[i];
		while( p != NULL ) {
			printf("%d(%d) ", p->val, p->cost);
			p = p->leg;
		}
		printf("\n");
	}
}

void swap(heap *h, int i, int j) {
	int aux;
	aux = h->v[i];
	h->v[i] = h->v[j];
	h->v[j] = aux;
	aux = h->cost[i];
	h->cost[i] = h->cost[j];
	h->cost[j] = aux;
}

void heapify(heap *h, int i) {
	int st,dr,m = i,aux;
	st = 2 * i;
	dr = 2 * i + 1;
	if( st <= h->n && h->cost[st] < h->cost[i] ) {
		m = st;
	}
	if( dr <= h->n && h->cost[dr] < h->cost[i] ) {
		m = dr;
	}
	if( m != i ) {
		swap(h, i, m);
		heapify(h, m);
	}
}

int delete(heap *h) {
	int hmin;
	if( h->n <= 0 ) {
		return -1;
	}
	hmin = h->v[1];
	h->v[1] = h->v[h->n];
	h->cost[1] = h->cost[h->n];
	h->n--;
	heapify(h, 1);
	return hmin;
}

int inserare(heap *h, int nod, int cost, int *poz) {
	int i;
	i = poz[nod];
	h->v[i] = nod;
	h->cost[i] = cost;
	h->n++;
	while(i > 1 && h->cost[i/2] > h->cost[i]) {
		swap(h, i, i / 2);
		poz[nod] = i;
		i = i/2;
	}
	return i;
}

void prim(graf *g, int source) {
	muchie m[6];
	heap *h = (heap*)malloc(sizeof(heap));
	h->n = 0 ;
	int *d, *poz, i,node, *parents, j = 0, total_cost = 0, aux;
	nod *p;
	d = (int*) malloc((g->size+1) * sizeof(int));
	poz = (int*) malloc((g->size+1) * sizeof(int));
	parents = (int*) malloc((g->size+1) * sizeof(int));
	for(i = 1; i <= g->size; i++) {
		d[i] = MARE;
		poz[i] = -1;
		parents[i] = -1;
	}
	d[source] = 0;
	poz[source] = 1;
	inserare(h, source, -1, poz);
	while( h->n > 0 ) {
		node = delete(h);
		if( node != source ) {
			m[j].start = parents[node];
			m[j].finish = node;
			m[j].cost = d[node];
			j++;
			total_cost += d[node];
		}
		p = g->a[node];
		while( p != NULL ) {
			if( p->cost < d[p->val] ) {
				d[p->val] = p->cost;
				parents[p->val] = node;
				if( poz[p->val] == -1 ) {
					poz[p->val] = h->n + 1;;
					inserare(h, p->val ,p->cost, poz);
				}else {
					for(i = 0; i <= h->n; i ++) {
						if( h->v[i] == p->val && p->cost < h->cost[i] ) {
							h->cost[i] = p->cost;
						}
					}
					heapify(h, poz[p->val]);
				}
			}
			heapify(h, poz[p->val]);
			p = p->leg;
		}
	}
	for(i = 0; i < j ;i++) {
		printf("Muchia %d-%d cu costul %d", m[i].start, m[i].finish, m[i].cost);
		printf("\n");
	}
	printf("Cost total: %d\n",total_cost);
}

int cmp_muchie(const void *a, const void *b) {
	muchie *ma = (muchie*)a;
	muchie *mb = (muchie*)b;
	return ma->cost - mb->cost;
}

void kruskal( graf *g, muchie *muchii, int m ) {
	qsort(muchii, m, sizeof(muchie), cmp_muchie);
	int n, i, s, f, j, aux, k, total = 0, s1, f1;
	n = g->size;
	int *tata = (int*) calloc(n+1, sizeof(int));
	for(i = 1; i <= n; i++) {
		tata[i] = 0;
	}
	k = 0;
	for(i = 1; i <= m; i++) {
		if( k == n-1 ) {
			break;
		}
		aux = 0;
		s = muchii[i].start;
		f = muchii[i].finish;
		for( j = s ; tata[j] != j ; j = tata[j] ) {
			if( j == f ) {
				aux = 1;
			}
		}
		if( aux == 0 ) {
			tata[s] = f;
			i++;
			k++;
			printf("%d %d\n", s, f);
			total = total + muchii[i].cost;
		}
	}
	printf("Cost total: %d\n", total);
}

int main() {
	FILE *f1 = fopen("graf.in", "rt");
	int n, m, *v, *w, aux1, aux2, i, *costuri, aux3;
	fscanf(f1, "%d", &n);
	fscanf(f1, "%d", &m);
	v = (int*) malloc((m+1) * sizeof(int));
	w = (int*) malloc((m+1) * sizeof(int));	
	costuri = (int*) malloc((m+1) * sizeof(int));
	for(i = 1; i <= m; i++) {
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
	printf("Arborele minim de acoperire:\n");
	prim(g, 1);

	muchie *muchii = (muchie*) malloc((m+1) * sizeof(muchie));
	for(i = 1; i <= m; i++) {
		muchii[i].start = v[i];
		muchii[i].finish = w[i];
		muchii[i].cost = costuri[i];
	}
	kruskal(g, muchii, m);
	fclose(f1);
	return 0;
}