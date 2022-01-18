#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    void *data;
    struct node *next;
    struct node *prev;
} node;

typedef struct TDoubleLinkedList {
    node *head;
    node *tail;
    int len;
} TDoubleLinkedList;

void init(TDoubleLinkedList  **list) {
    *list = malloc(sizeof(TDoubleLinkedList));
    (*list)->len = 0;
    (*list)->head = NULL;
    (*list)->tail = NULL;
}

int add(TDoubleLinkedList *list, int n, void *data) {
    node *nou =(node *)malloc(sizeof(node));
    nou->data = data;
    if ( n < 0 || n > list->len) {
        return -1;
    } else if( list->len == 0 ) {
        nou->next = NULL;
        nou->prev = NULL;
        list->head = nou;
        list->tail = nou;
        list->len++;
        return 1;
    } else if( n==0 && list->head != NULL ) {
        list->head->prev = nou;
        nou->next = list->head;
        nou->prev = NULL;
        list->head = nou;
        list->len++;
        return 1;
    } else if( n==list->len && list->tail != NULL ) {
        list->tail->next = nou;
        nou->prev = list->tail;
        nou->next = NULL;
        list->tail = nou;
        list->len++;
        return 1;
    } else {
        node *q,*nou;
        int m = n;
        if( n < list->len/2 ) {
            q = list->head;
            while( m-1 > 0)
            {
                q = q->next;
                m--;
            }
            nou->next = q->next;
            nou->prev = q;
            q->next->prev = nou;
            q->next = nou;
            list->len++;
        } else {
            q = list->tail;
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
        q = list->head;
        node *r = q;
        list->head = list->head->next;
        list->head->prev = NULL;
        free(q);
        list->len--;
        return r;
    } else if( n == list->len-1 ) {
        q = list->tail;
        node *r = q;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        free(q);
        list->len--;
        return r;
    } else if( n < list->len/2 ) {
        p = list->head;
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
        p = list->tail;
        m = list->len - n;
        while(m > 0)
        {
            p = p->prev;
            m--;
        }
        q = p->next;
        node * r = q;
        p->next = p->next->next;
        p->next->prev = p;
        free(q);
        list->len--;
        return r;
    }
}

void free_list(TDoubleLinkedList *list) {
    node *q = list->head;
    while(q != NULL) {
        list->head = list->head->next;
        free(q);
        q = list->head;
    }
}

void print_int_list(TDoubleLinkedList *list) {
    node *q=list->head;
    if(q == NULL) {
        printf("Lista este goala");
    }
    while(q != NULL) {
        printf("%d ", (int)q->data);
        q = q->next;
    }
    printf("\n");
}

void print_string_list(TDoubleLinkedList *list) {
    if(list->head == NULL) {
        printf("Lista este goala");
    }
    while(list->head != NULL) {
        puts(list->head->data);
        list->head = list->head->next;
    }

}

void print_int_list_reversed(TDoubleLinkedList *list) {
    node *q=list->tail;
    if(q == NULL) {
        printf("Lista este goala");
    }
    while(q != NULL) {
        printf("%d ", (int) q->data);
        q = q->prev;
    }
    printf("\n");
}

int add_in_order(TDoubleLinkedList *list, void * data) {
    if( list->len == 0) {
        node *nou =(node *)malloc(sizeof(node));
        nou->data = data;
        nou->next = NULL;
        nou->prev = NULL;
        list->head = nou;
        list->tail = nou;
        list->len++;
        return 1;
    } else if( (int) list->head->data >= (int) data) {
        node *nou =(node *)malloc(sizeof(node));
        nou->data = data;
        list->head->prev=nou;
        nou->next=list->head;
        nou->prev=NULL;
        list->head=nou;
        list->len++;
        return 1;
    } else if( (int) list->tail->data <= (int) data) {
        node *nou =(node *)malloc(sizeof(node));
        nou->data = data;
        list->tail->next = nou;
        nou->prev = list->tail;
        nou->next = NULL;
        list->tail = nou;
        list->len++;
        return 1;
    } else {
        node *q = list->head;
        while( (int) q->next->data <= (int) data && q->next != NULL )
            q = q->next;
        node *nou = (node *) malloc(sizeof(node));
        nou->data = data;
        nou->next = q->next;
        nou->prev = q;
        q->next->prev = nou;
        q->next = nou;
        list->len++;
        return 1;
    }
}

node *remove_duplicates(TDoubleLinkedList *list) {
    node *q,*p,*aux,*n;
    
    p = q = n =list->tail;
    q = q->prev;

    while( p != NULL ) {
        while( q != NULL && q->data != p->data ) {
            n = q;
            q = q->prev;
        }
        if( q == NULL ) {
            p = p->prev;
            if( p != NULL )
                q = p->prev;
        } else if( q->data == p->data ) {
            if( q == list->head ) {
                list->head->next->prev = NULL;
                list->head = list->head->next;
            } else {
                n->prev = q->prev;
                q->prev->next = q->next;
            }
            aux = q;
            q = q->prev;
            free(aux);
        }
    }

}

int main() {
    TDoubleLinkedList *list;
    init(&list);
    int x;
    add(list, 0, 1);
    add(list, 1, 1);
    add(list, 2, 2);
    add(list, 3, 3);
    add(list, 4, 2);

    print_int_list(list);
    remove_duplicates(list);
    print_int_list(list);
    return 0;
}