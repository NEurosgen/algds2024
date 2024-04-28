#include "pch.h"
#include "Header.h"
void get_hight(Node* head) {
	if (head == NULL) {
		return;
	}
	if (head->left == NULL && head->right == NULL) {
		head->hight = 1;
	}
	if (head->left != NULL && head->right != NULL) {
		head->hight = head->left->hight > head->right->hight ? head->left->hight + 1 : head->right->hight + 1;
		return;
	}
	if (head->left != NULL) {
		head->hight = head->left->hight + 1;
		return;

	}
	if (head->right != NULL) {
		head->hight = head->right->hight + 1;
		return;
	}

}
Node* right_rotate(Node* head) {
	Node* ptr = head->left;
	head->left = ptr->right;
	ptr->right = head;
	get_hight(head);
	get_hight(ptr);
	return ptr;

}
Node* left_rotate(Node* head) {
	Node* ptr = head->right;
	head->right = ptr->left;
	ptr->left = head;
	get_hight(head);
	get_hight(ptr);

	return ptr;
}

int get_delta(Node* head) {
	if (head == NULL) {
		return 0;
	}
	int delta = 0;
	if (head->left == NULL && head->right == NULL) {
		delta = 0;
	}
	else if (head->left == NULL) {
		delta = -head->right->hight;
	}
	else if (head->right == NULL) {
		delta = head->left->hight;
	}
	else {
		delta = head->left->hight - head->right->hight;
	}
	return delta;
}
Node* rotate(Node* head) {
	if (head == NULL) {
		return head;
	}
	int delta_head = get_delta(head);
	int delta_right = get_delta(head->right);
	int delta_left = get_delta(head->left);
	if (delta_head == -2 && (delta_right == 0 || delta_right == -1)) {
		head = left_rotate(head);
	}
	if (delta_head == -2 && (delta_right == 1)) {
		head->right = right_rotate(head->right);
		head = left_rotate(head);
	}
	if (delta_head == 2 && (delta_left == 0 || delta_left == 1)) {
		head = right_rotate(head);
	}
	if (delta_head == 2 && delta_left == -1) {
		head->left = left_rotate(head->left);
		head = right_rotate(head);
	}
	return head;
}
Node* insert(Node* head, int val) {
	int delta = 0;
	if (head == NULL) {
		head =(Node*) malloc(sizeof(Node));
		head->right = NULL;
		head->left = NULL;
		head->data = val;
		head->hight = 1;
		return head;
	}
	if (val < (head->data)) {

		head->left = insert(head->left, val);
		get_hight(head);

	}
	if (val > (head->data)) {


		head->right = insert(head->right, val);
		get_hight(head);
	}
	head = rotate(head);

	return head;

}
void insert_merge(Node* head, Node* ptr) {
	if (ptr == NULL) {
		return;
	}
	insert_merge(head, ptr->left);
	insert(head, ptr->data);

	insert_merge(head, ptr->right);
}
Node* smaller(Node* head) {
	if (head->left == NULL) {
		return head;
	}
	smaller(head->left);
}
Node* erase(Node* head, int val);

Node* erase_chose(Node* head) {
	if (head->right == NULL && head->left == NULL) {
		free(head);
		return NULL;
	}
	if (head->right == NULL && head->left != NULL) {//Не работает ??
		Node* ptr = head->left;
		free(head);
		return ptr;
	}
	if (head->left == NULL && head->right != NULL) {//Не работает ??
		Node* ptr = head->right;
		free(head);
		return ptr;
	}
	if (head->left != NULL && head->right != NULL) {
		Node* ptr = smaller(head->right);
		int t = head->data;
		head->data = ptr->data;
		ptr->data = t;
		head->right = erase(head->right, t);
		return head;

	}
}
Node* erase(Node* head, int val) {
	if (head == NULL) {
		return head;
	}
	if (head->data == val) {
		head = erase_chose(head);
		get_hight(head);
		head = rotate(head);
		return head;
	}
	if (head->right != NULL && head->right->data == val) {
		head->right = erase_chose(head->right);
		get_hight(head);
		head = rotate(head);
		return head;
	}
	if (head->left != NULL && head->left->data == val) {
		head->left = erase_chose(head->left);
		get_hight(head);
		head = rotate(head);
		return head;
	}

	if (head->data > val) {
		head->left = erase(head->left, val);
	}
	if (head->data < val) {
		head->right = erase(head->right, val);
	}
	return head;
}