#include <stdio.h>
#include <stdlib.h>

typedef struct Trie {
    int count, nrfii;
    struct Trie *child[26];
} Trie;

Trie* init() {
	Trie *nou = malloc(sizeof(Trie));
	int i;
	for(i = 0; i < 26 ; i++) {
		nou->child[i] = NULL;
    }
	nou->count = 0;
	nou->nrfii = 0;
	return nou;
}

void insert(Trie *t, char *string) {
    if(*string == '\0') {
        t->count++;
        return;
    }
    if( t->child[ *string - 'a' ] == NULL ) {
        t->child[ *string - 'a' ] = init();
        t->nrfii++;
    }
    insert(t->child[ *string - 'a' ], string + 1);

}

int delete(Trie *t, char *string) {
    if( *string == '\0' ) {
        t->count--;
    } else if(delete( t->child[ *string - 'a' ], string+1) ) {
        t->child[ *string - 'a' ] = 0;
        t->nrfii--;
    }
    if( t->count == 0 && t->nrfii == 0 && t != NULL ) {
        t = NULL;
        free(t);
        return 1;
    }
    return 0;
}

void free_trie(Trie *t) {
	if( t == NULL ) {
		return;
    }
	int i;
	for(i = 0 ; i < 26; i++) {
		free_trie(t->child[i]);
	}
	free(t);
}

int main() {
    Trie *t =init();
    char *string = "abc";
    insert(t, string);
    delete(t, string);
    return 0;
}