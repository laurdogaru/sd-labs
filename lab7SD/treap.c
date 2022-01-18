#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	int priority;
	struct node *left, *right,*parent;
} node;


node *init_node(node *parent, int val, int priority) {
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

void balance(node **root) {
	if( (*root)->left &&  (*root)->left->priority > (*root)->priority ) {
		rotate_left(root);
	} else if( (*root)->right && (*root)->right->priority > (*root)->priority ) {
		rotate_right(root);
	}
}

void insert(node **root,int val, int priority) {
	if(*root == NULL) {
		*root = init_node(NULL, val, priority);
		return;
	}
	if( val < (*root)->key ) {
		if( (*root)->left == NULL ) {
			(*root)->left = init_node(*root, val, priority);
		} else {
			insert(&(*root)->left, val, priority);
		}
	} else {
		if( (*root)->right == NULL ) {
			(*root)->right = init_node(*root, val, priority);
		} else {
			insert(&(*root)->right, val, priority);
		}
	}
	balance(root);
}

void delete(node **root, int val) {
	if(root == NULL) {
		return;
	}
	if( val < (*root)->key ) {
		delete( &((*root)->left),val );
	} else if( val > (*root)->key ) {
		delete( &((*root)->right),val );
	} else {
		if( (*root)->left == NULL && (*root)->right == NULL ) {
			*root = NULL;
			free(*root);
		} else {
			if( (*root)->left &&  (*root)->left->priority > (*root)->right->priority ) {
				rotate_left(root);
			} else {
				rotate_right(root);
			}
			delete(root,val);
		}
	}
}

void free_tree(node **root) {
	if( *root==NULL ) {
		return;
	}
	free_tree( &(*root)->left );
	free_tree( &(*root)->right );
	free(root);
}

int height(node *root) {
	if( root == NULL ) {
		return 0;
	}
	if( root->left == NULL && root->right == NULL ) {
		return 1;
	}
	int left = height(root->left);
	int right = height(root->right);
	if( left < right ) {
		return 1 + right;
	} else {
		return 1 +left;
	}
}

void in_order(node *root) {
	if( root == NULL ) {
		return;
	}
	in_order(root->left);
	printf("%d ", root->key);
	in_order(root->right);
}

void pre_order( node *root ) {
	if( root == NULL ) {
		return;
	}
	printf("%d ", root->key );
	pre_order(root->left);
	pre_order(root->right);
}

void post_order(node *root) {
	if( root == NULL ) {
		return;
	}
	post_order( root->left );
	post_order( root->right );
	printf("%d ", root->key );
}

int main() {
	int n;
	node *root = NULL;
	insert(&root, 15, 39);
	insert(&root, 6, 33);
	insert(&root, 17, 21);
	insert(&root, 5, 19);
	insert(&root, 13, 29);
	insert(&root, 8, 17);
	insert(&root, 14, 15);
	insert(&root, 11, 9);
	insert(&root, 9, 51);
	delete(&root, 9);
	printf("%d %d %d \n", root->left->key, root->key, root->right->key);
	in_order(root);

	
	return 0;
}