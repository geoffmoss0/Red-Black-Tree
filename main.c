#include <stdio.h>
#include <stdlib.h>

#include "node.h"

struct node *root;

/**
* Rotate the tree left
* I'm just trusting that this algorithm works because I'm only implementing pseudocode here
* @param node the node to rotate around
*/
void left_rotate(struct node *node) {
	struct node *other = node->right;
	printf("other: %d\n", other->value);
	node->right = other->left;
	if (other->left != NULL) {
		other->left->parent = node;
	}
	other->parent = node->parent;
	if (node->parent == NULL) {
		root = other; //This operation changes the root of the tree to the right child
	} else {
		if (node == (node->parent)->left) {
			node->parent->left = other;
		} else {
			node->parent->right = other;
		}
	}
	other->left = node; //Original node is now the left child of its former right child
	node->parent = other;
}


/**
* Rotate the tree right
* @param node the node to rotate around
*/
void right_rotate(struct node *node) {
	struct node *other = node->left;
	node->left = other->right;
	if (other->right != NULL) {
		other->right->parent = node;
	}
	other->parent = node->parent;
	if (node->parent == NULL) {
		root = other; //This operation changes the root of the tree to the right child
	} else {
		if (node == (node->parent)->right) {
			node->parent->right = other;
		} else {
			node->parent->left = other;
		}
	}
	other->right = node; //Original node is now the left child of its former right child
	node->parent = other;
}

/**
* repair the red-black property of the tree
* again, just used pseudocode, haven't proved any of this
* @param node the node inserted most recently
*/
void repair(struct node *node) {
	while ( (node != root) && (node->parent->color)) { //red evaluates to true, black to false
		if (node->parent == node->parent->parent->left) {

			struct node *other = node->parent->parent->right;
			if (other->color) { //again, red is true, black is false
				node->parent->color = 0;
				other->color = 0;
				node->parent->parent->color = 1;
				//set x to x's grandparent (this always works because we check x's uncle, 
				//and if it's red it has to have a parent)
				node = node->parent->parent;
			} else { //uncle is a black node
				if (node == node->parent->right) {
					node = node->parent;
					left_rotate(node);
				}
				node->parent->color = 0;
				node->parent->parent->color = 1;
				right_rotate(node->parent->parent);
			}
		} else { //node->parent == node->parent->parent->right
			struct node *other = node->parent->parent->left;
			if (other->color) { //again, red is true, black is false
				node->parent->color = 0;
				other->color = 0;
				node->parent->parent->color = 1;
				node = node->parent->parent;
			} else { //uncle is a black node
				if (node == node->parent->left) {
					node = node->parent;
					right_rotate(node);
				}
				node->parent->color = 0;
				node->parent->parent->color = 1;
				left_rotate(node->parent->parent);
			}
		}
	}
	root->color = 0;
	printf("root value: %d\n", root->value);
}


/**
* Recursive function that adds a node (sets parent to the next free node, 
* gives it a value and color)
* @param *root pointer to the root node
* @param *node the node to be added
*/
int insert(struct node *start, int val) {
	if (val < start->value) {
		if (start->left->value == 0) {
			
			//Make the NULL leaf nodes for the node we just made a non-leaf node
			struct node *left = malloc(sizeof(node));
			left->parent = start->left;
			left->right = NULL;
			left->left = NULL;
			left->color = 0;
			left->value = 0;

			struct node *right = malloc(sizeof(node));
			right->parent = start->left;
			right->right = NULL;
			right->left = NULL;
			right->color = 0;
			right->value = 0;

			start->left->color = 1;
			start->left->value = val;
			start->left->left = left;
			start->left->right = right;

			printf("Added node with value %d to node with value %d on left\n", start->left->value, start->value);
			printf("Repairing...\n");
			repair(start->left);
			return 1;
		} else {
			return insert(start->left, val);
		}
	
	} else { //node->value >= start->value
		if (start->right->value == 0) {

			struct node *left = malloc(sizeof(node));
			left->parent = start->right;
			left->right = NULL;
			left->left = NULL;
			left->color = 0;
			left->value = 0;

			struct node *right = malloc(sizeof(node));
			right->parent = start->right;
			right->right = NULL;
			right->left = NULL;
			right->color = 0;
			right->value = 0;

			start->right->color = 1;
			start->right->value = val;
			start->right->left = left;
			start->right->right = right;
			printf("Added node with value %d to node with value %d on right\n", start->right->value, start->value);	
			printf("Repairing...\n");
			repair(start->right);
			return 1;
		} else {
			return insert(start->right, val);
		}
	}
}


void free_all(struct node *start) {
	if (start->left->value == 0) {
		free(start->left);
	} else {
		free_all(start->left);
	}

	if (start->right->value == 0) {
		free(start->right);
	} else {
		free_all(start->right);
	}

	free(start);
}

int main(void) {
	
	printf("Enter size of data entry: ");
	char read[6];
	char *ptr;
	fgets(read, 6, stdin);
	int size = (int) strtol(read, &ptr, 10); 
	printf("Reading %d entries: begin entering data:\n", size); 

	int count = 0;
	int x;
	while(count < size) {
		scanf("%d", &x);
		if (count == 0) {
			struct node *n = malloc(sizeof(node)); 
			n->parent = NULL;
			n->value = x;
			n->color = 0;
			
			struct node *left = malloc(sizeof(node));
			left->parent = n;
			left->value = 0;
			left->color = 0;
			left->left = NULL;
			left->right = NULL;

			struct node *right = malloc(sizeof(node));
			right->parent = n;
			right->value = 0;
			right->color = 0;
			right->right = NULL;
			right->left = NULL;

			n->left = left;
			n->right = right;
			root = n;
		} else {
			if (!insert(root, x)) {
				printf("Something's gone horribly wrong");
				exit(1);
			}
		}
		count++;
	}

	printf("\n");

	printf("root value: %d\n", root->value);
	free_all(root);
	return 0;
}
