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
* Recursive function that adds a node (sets parent to the next free node, 
* gives it a value and color)
* @param *root pointer to the root node
* @param *node the node to be added
*/
int insert(struct node *start, struct node *node) {
	//TODO
	if (node->value < start->value) {
		if (start->left == NULL) {
			node->parent = start;
			start->left = node;
			node->color = 1;
			printf("Added node with value %d to node with value %d on left\n", node->value, start->value);
			return 1;
		} else {
			return insert(start->left, node);
		}
	
	} else { //node->value >= start->value
		if (start->right == NULL) {
			node->parent = start;
			start->right = node;
			node->color = 1;
			printf("Added node with value %d to node with value %d on right\n", node->value, start->value);	
			return 1;
		} else {
			return insert(start->right, node);
		}
	}
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
			n->left = NULL;
			n->right = NULL;
			root = n;
		} else {
			struct node *n = malloc(sizeof(node));
			n->value = x;
			n->parent = NULL;
			n->left = NULL;
			n->right = NULL;
			if (!insert(root, n)) {
				printf("Something's gone horribly wrong");
				exit(1);
			}
		}
		//TODO replace this with the insert and balancing methods
		count++;
	}

	printf("\n");

	printf("root value: %d\n", root->value);
	return 0;
}
