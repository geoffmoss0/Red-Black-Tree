/**
* Apparently this has to go in a header file, so here it is
*/

#ifndef NODE
#define NODE
typedef struct node {
	struct node *parent, *right, *left;
	int color; //0 for black, 1 for red
	int value;
} node;
#endif
