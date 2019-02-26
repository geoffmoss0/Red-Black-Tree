#include <stdio.h>
#include <stdlib.h>

#include "node.h"

struct node *root;

/**
* Recursive function that adds a node (sets parent to the next free node, 
* gives it a value and color)
* @param *root pointer to the root node
* @param *node the node to be added
*/
int insert(struct node *start, struct node *node) {
	//TODO
	if (start->left == NULL) {
		node->parent = start;
		start->left = node;
		node->color = 1;
		printf("Added node with value %d to node with value %d on left\n", node->value, start->value);
		return 1;
	} else if (start->right == NULL) {
		node->parent = start;
		start->right = node;
		node->color = 1;
		printf("Added node with value %d to node with value %d on right\n", node->value, start->value);	
		return 1;
	} else {
		if (insert(start->left, node)) {
			return 1;
		} else if (insert(start->right, node)) {
			return 1;
		} else {
			return 0;
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
	printf("last value: %d\n", root->left->left->value);
	return 0;
}
