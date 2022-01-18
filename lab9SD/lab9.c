#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nod {
	int val;
	struct nod *leg;
} nod;

typedef struct graf {
	int size;
	nod **a;
} graf;

typedef struct queue {
	nod *tail,*head;
	int len;
}queue;

void init_graph(graf **g, int n) {
	int i;
	*g = malloc(sizeof(graf));
	(*g)->size = n;
	(*g)->a = (nod**) malloc( (n+1) * sizeof(nod*));
	for(i = 1 ; i <= n ; i++) {
		(*g)->a[i] = NULL;
	}
}

void add_arc(graf *g, int x, int y) {
	nod *nou = (nod*)malloc(sizeof(nod));
	nou->val = y;
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

void build(graf *g, int m, int *v, int *w) {
	int i;
	for(i = 1; i <= m ; i ++) {
		add_arc(g, v[i], w[i]);
	}
}

void afisare( graf *g) {
	int i;
	nod *p;
	for(i = 1; i <= g->size; i++) {
		printf("%d: ", i);
		p = g->a[i];
		while( p != NULL ) {
			printf("%d ", p->val);
			p = p->leg;
		}
		printf("\n");
	}
}

void init_queue(queue **q) {
	*q = malloc(sizeof(queue));
	(*q)->len = 0;
	(*q)->tail = NULL;
	(*q)->head = NULL;
}

void enqueue(queue *q, int val) {
	nod *aux;
	aux = (nod*) malloc(sizeof(nod));
	aux->val = val;
	aux->leg = NULL;
	if( q->head == NULL ) {
		q->head = q->tail = aux;
	} else {
		q->tail->leg = aux;
		q->tail = aux;
	}
	q->len++;
}	

int dequeue(queue *q) {
	int a;
	nod *aux;
	if( q->head == NULL ) {
		return 0;
	}
	a = q->head->val;
	aux = q->head;
	q->head = q->head->leg;
	free(aux);
	q->len--;
	return a;
}

void print_queue(queue *q) {
	nod *aux = q->head;
	if( aux == NULL) {
		printf("coada este vida\n");
	}
	else {
		while( aux!=NULL ) {
			printf("%d ", aux->val);
			aux = aux->leg;
		}
		printf("\n");
	}
}	

int empty_queue(queue *q) {
	return q->len <= 0 ;
}

void bfs(graf *g, int v, int *vazut, int *d) {
	queue *q;
	nod *p;
	int x,y;
	init_queue(&q);
	enqueue(q, v);
	d[v] = 0;
	printf("Parcurgerea BFS pornind de la nodul %d: ",v);
	printf("%d ", v);
	while(q->len > 0) {
		x = dequeue(q);
		if( !x ) {
			return;
		}
		vazut[x] = 1;
		p = g->a[x];
		while( p != NULL ) {
			if( vazut[p->val] == 0 ) {
				y = p->val;
				vazut[y] = 1;
				enqueue(q, y);
				printf("%d ", y);
				d[y] = d[x] + 1;
			}
			p = p->leg;
		}
	}
	printf("\n");
}

void bf(graf *g, int v) {
	int i;
	int *vazut = (int*)calloc(g->size+1,sizeof(int));
	int *d = (int*)calloc(g->size+1,sizeof(int));
	bfs(g, v, vazut, d);
	printf("Distantele: ");
	for(i = 1; i <= g->size; i++ )
	{
		printf("%d ", d[i]);
	}
	printf("\n");
}

int time = 0;

void dfs(graf *g, int v, int *vazut, int *discover_time, int *finish_time) {
	int i;
	vazut[v] = 1;
	discover_time[v] = time++;
	printf("%d ", v);
	for(i = 1; i <= g->size; i++) {
		if(arc(g, v, i) == 1 && vazut[i] == 0)
			dfs(g, i, vazut, discover_time, finish_time);
	}
	finish_time[v] = time++;
}

void df( graf *g ) {
	int *vazut = (int*) calloc(g->size + 1, sizeof(int));
	int *discover_time = (int*) calloc(g->size + 1, sizeof(int));
	int *finish_time = (int*) calloc(g->size + 1, sizeof(int));
	int i;
	for(i = 1; i <= g->size; i++) {
		if( vazut[i] == 0 ) {
			printf("DFS incepand cu nodul %d: ", i);
			dfs(g, i, vazut,discover_time, finish_time);
		}
	}
	printf("\nDiscover times: ");
	for(i = 1; i <= g->size; i++) {
		printf("%d ", discover_time[i]);
	}
	printf("\nFinish times: ");
	for(i = 1; i <= g->size; i++) {
		printf("%d ", finish_time[i]);
	}
	printf("\n");
}


int main() {
	FILE *f1 = fopen("graf.in","rt");
	int n, m, *v, *w, aux1, aux2, i;
	fscanf(f1, "%d", &n);
	fscanf(f1, "%d", &m);
	v = (int*) malloc( (m+1) *sizeof(int));
	w = (int*) malloc( (m+1) *sizeof(int));	
	for(i = 1; i <= m; i++) {
		fscanf(f1, "%d", &aux1);
		fscanf(f1, "%d", &aux2);
		v[i] = aux1;
		w[i] = aux2;
	}

	graf *g;
	init_graph(&g, n);
	build(g, m, v, w);
	afisare(g);

	bf(g, 2);

	df(g);

	fclose(f1);
	return 0;
}
