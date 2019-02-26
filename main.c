#include <stdio.h>
#include <stdlib.h>

#include "node.h"

const struct node *root;

/**
* Recursive function that adds a node (sets parent to the next free node, 
* gives it a value and color)
* @param *root pointer to the root node
* @param *node the node to be added
*/
void insert(struct node *node) {
	//TODO
}

int main(void) {
	
	printf("Enter size of data entry: ");
	char read[6];
	char *ptr;
	fgets(read, 6, stdin);
	int size = (int) strtol(read, &ptr, 10); 
	printf("Reading %d entries: begin entering data:\n", size); 

	int data[2 * size]; 
	//Because we'll need at least 2 * ceil(log2(size)) Nil leaf nodes,
	//We'll oversize the array to twice the size, which will always be enough
	int count = 0;
	int x;
	while(count < size) {
		scanf("%d", &x);
		if (count == 0) {
			struct node *n = malloc(sizeof(node)); 
			n->parent = NULL;
			n->value = x;
			n->color = 0;
			root = n;
		} 
		else {
			struct node n = malloc(sizeof(node));
			insert(n);
		}
		//TODO replace this with the insert and balancing methods
		//TODO need some way to keep track of the 
		data[count] = x;
		count++;
	}

	for (int i = 0; i < size; i++) {
		printf("%d, ", data[i]);
	}
	printf("\n");

	printf("root value: %d\n", root->value);
	return 0;
}
