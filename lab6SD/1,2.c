#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left, *right,*parent;
} node;


node *init_node(node *parent, int val) {
	node *nou = malloc(sizeof(node));
	nou->parent = parent;
	nou->left = NULL;
	nou->right = NULL;
	nou->key = val;
	return nou;
}

void insert(node **root, int val) {
	if(*root == NULL) {
		*root = init_node(NULL,val);
		return;
	}
	if( val < (*root)->key ) {
		if( (*root)->left == NULL ) {
			(*root)->left = init_node(*root,val);
		} else {
			insert(&(*root)->left,val);
		}
	} else {
		if( (*root)->right == NULL ) {
			(*root)->right = init_node(*root,val);
		} else {
			insert(&(*root)->right,val);
		}
	}
}


node *search( node *root, int val ) {
	if( root == NULL ) {
		return 0;
	}
	if( root->key == val ) {
		return root;
	}
	if( val > root->key ) {
		return search(root->right,val);
	}
	return search(root->left,val);
}
node *getSuccesor(node *nod) {
	node *succesor_parent = nod;
	node *succesor = nod;
	node *current = nod->right;
	while( current != NULL ) {
		succesor_parent = succesor;
		succesor = current;
		current = current->left;
	}
	if( succesor != nod->right ) {
		succesor_parent->left = succesor->right;
		succesor->right = nod->right;
	}
	return succesor;
}

void delete(node **root, int val) {
	if(root == NULL) {
		return;
	}
	node *aux;
	node *current = search(*root, val);
	/*cazul in care nodul este o frunza*/
	if( current->left == NULL && current->right == NULL ) {
		if(current == current->parent->left) {
			current->parent->left = NULL;
		} else {
			current->parent->right = NULL;
		}
		free(current);
		return ;
	}
	/*cazul in care nodul are doar un fiu*/
	else if( current->left == NULL || current->right == NULL ) {
		if( current == current->parent->left ) {
			if(current->left) {
				current->left->parent = current->parent;
				current->parent->left = current->left;
				current->left->parent = current->parent;
			} else {
				current->parent->left = current->right;
				current->right->parent = current->parent;
			}
		} else {
			if(current->left) {
				current->parent->right = current->left;
				current->left->parent = current->parent;
			} else {
				current->parent->right = current->right;
				current->right->parent = current->parent;
			}
		}
		free(current);
		return ;
	} else {
		node *succesor = getSuccesor(current);
		if( current == *root ) {
			*root = succesor;
		} else {
			if( current->left ) {
				current->parent->left = succesor;
			} else {
				current->parent->right = succesor;
			}
		}
		succesor->left = current->left;
		free(current);
		return ;
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

void in_order( node *root ) {
	if( root == NULL ) {
		return;
	}
	in_order( root->left );
	printf("%d ", root->key );
	in_order( root->right );
}

void pre_order( node *root ) {
	if( root == NULL ) {
		return;
	}
	printf("%d ", root->key );
	pre_order( root->left );
	pre_order( root->right );
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
	while ( scanf("%d",&n) ) {
		insert(&root,n);
	}
	delete(&root, 30);
	printf("%d\n",root->key);
	pre_order(root);

	return 0;
}