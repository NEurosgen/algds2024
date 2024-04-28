#pragma once

#include <stdio.h>
#include <stdlib.h>
struct Node {
	struct Node* left;
	struct Node* right;
	int data;

	int hight;

};
typedef struct Node Node;



Node* insert(Node* head, int val);

Node* erase(Node* head, int val);
