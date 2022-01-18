#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    void *data;
    struct node *next;
    struct node *prev;
} node;

typedef struct TDoubleLinkedList {
    node *sentinel;
    int len;
} TDoubleLinkedList;

void init(TDoubleLinkedList  **list) {
    *list = malloc(sizeof(TDoubleLinkedList));
    (*list)->sentinel = (node*)malloc(sizeof(node));
    (*list)->len = 0;
}

int add(TDoubleLinkedList *list, int n, void *data) {
    if ( n<0 || n> list->len) {
        return -1;
    } else if( list->len==0 ) {
        node *nou = (node *) malloc(sizeof(node));
        nou->data = data;
        nou->next = list->sentinel;
        nou->prev = list->sentinel;
        list->sentinel->prev = nou;
        list->sentinel->next = nou;
        list->len++;
        return 1;
    } else if( n==0 && list->sentinel->next != NULL ) {
        node *nou = (node *) malloc(sizeof(node));
        nou->data = data;
        nou->next = list->sentinel->next;
        nou->prev = list->sentinel;
        list->sentinel->next->prev = nou;
        list->sentinel->next = nou;
        list->len++;
        return 1; 
    } else if( n==list->len && list->sentinel->prev != NULL ) {
        node *nou = (node *) malloc(sizeof(node));
        nou->data = data;
        nou->next = list->sentinel;
        nou->prev = list->sentinel->prev;
        list->sentinel->prev->next = nou;
        list->sentinel->prev = nou;
        list->len++;
        return 1;
    } else {
        node *q,*nou;
        int m = n;
        nou = (node *) malloc(sizeof(node));
        nou->data = data;
        if( n < list->len/2) {
            q = list->sentinel->next;
            while( m-1 > 0) {
                q = q->next;
                m--;
            }
            nou->next = q->next;
            nou->prev = q;
            q->next->prev = nou;
            q->next = nou;
            list->len++;
        } else {
            q = list->sentinel->prev;
            m = list->len - n;
            while(m > 0) {
                q = q->prev;
                m--;
            }
            nou->next = q->next;
            nou->prev = q;
            q->next->prev = nou;
            q->next = nou;
            list->len++;
        }
        return 1;
    }
}

node *remove_node(TDoubleLinkedList *list, int n) {
    node *p, *q;
    int m;
    if( n == 0) {
        q = list->sentinel->next;
        node *r = q;
        list->sentinel->next = list->sentinel->next->next;
        list->sentinel->next->prev = list->sentinel;
        free(q);
        list->len--;
        return r;
    }
    if( n == list->len) {
        q = list->sentinel->prev;
        node *r = q;
        list->sentinel->prev = list->sentinel->prev->prev;
        list->sentinel->prev->next = list->sentinel;
        free(q);
        list->len--;
        return r;
    }
    if( n < list->len/2 ) {
        p = list->sentinel->next;
        m = n;
        while( m-1 > 0)
        {
            p = p->next;
            m--;
        }
        q = p->next;
        node *r = q;
        p->next = p->next->next;
        p->next->prev = p;
        free(q);
        list->len--;
        return r;
    } else {
        p = list->sentinel->prev;
        m = list->len - n;
        while(m > 0)
        {
            p = p->prev;
            m--;
        }
        q = p->next;
        node *r = q;
        p->next = p->next->next;
        p->next->prev = p;
        free(q);
        list->len--;
        return r;
    }
}

void free_list(TDoubleLinkedList *list) {
    node *q = list->sentinel->next;
    while(q != NULL) {
        list->sentinel->next = list->sentinel->next->next;
        free(q);
        q = list->sentinel->next;
    }
}

void print_int_list(TDoubleLinkedList *list) {
    node *q = list->sentinel->next;
    if(q == NULL)
        printf("Lista este goala");
    while(q != list->sentinel) {
        printf("%d ",(int)q->data);
        q = q->next;
    }
    printf("\n");
}

void print_int_list_reversed(TDoubleLinkedList *list) {
    node *q = list->sentinel->prev;
    if(q == NULL)
        printf("Lista este goala");
    while(q != list->sentinel) {
        printf("%d ",(int)q->data);
        q = q->prev;
    }
    printf("\n");
}

int add_in_order(TDoubleLinkedList *list, void * data) {
    if( list->len == 0) {
        node *nou = (node *) malloc(sizeof(node));
        nou->data = data;
        nou->next = list->sentinel;
        nou->prev = list->sentinel;
        list->sentinel->prev = nou;
        list->sentinel->next = nou;
        list->len++;
        return 1;
    } else if( (int)list->sentinel->next->data > (int) data) {
        node *nou = (node *) malloc(sizeof(node));
        nou->data = data;
        nou->next = list->sentinel->next;
        nou->prev = list->sentinel;
        list->sentinel->next->prev = nou;
        list->sentinel->next = nou;
        list->len++;
        return 1;
    } else if( (int)list->sentinel->prev->data < (int) data) {
        node *nou = (node *) malloc(sizeof(node));
        nou->data = data;
        nou->next = list->sentinel;
        nou->prev = list->sentinel->prev;
        list->sentinel->prev->next = nou;
        list->sentinel->prev = nou;
        list->len++;
        return 1;
    } else {
        node *q = list->sentinel->next;
        while( (int) q->data < (int) data && q->next == NULL ) {
            q = q->next;
        }
        node *nou =(node *)malloc(sizeof(node));
        nou->data = data;
        nou->next = q->next;
        nou->prev = q;
        q->next->prev = nou;
        q->next = nou;
        list->len++;
        return 1;
    }
}

int main() {
    TDoubleLinkedList *list;
    init(&list);
    add_in_order(list, 7);
    add_in_order(list, 4);
    add_in_order(list, 3);
    add_in_order(list, 2);
    add_in_order(list, 1);
    remove_node(list, 1);
    print_int_list(list);
    print_int_list_reversed(list);
    return 0;
}

