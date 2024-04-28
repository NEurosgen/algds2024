#include "pch.h"
#include "Header.h"

struct mas {
	int* ptr;
	int size = 0 ;
};
typedef struct mas mas;
void recursive(Node* head, mas* A) {
	
	     if (head == NULL) {
	    return;
		}
	
		recursive(head->left,A);
		A->ptr[A->size]=head->data;
		A->size++;
		recursive(head->right, A);


}
int test(int n,Node* head) {
	mas A;
	A.ptr =(int*)malloc(sizeof(int) * n);
	A.size = 0;
	recursive(head, &A);
	for (int i = 0; i < n; ++i) {
		if (A.ptr[i] != i) {
			return 0;
		}
	}
	return 1;
}


TEST(InsertTest, Nulltest) {
  Node* head = NULL;
  head = insert(head, 3);
  EXPECT_EQ(head->data, 3);
  EXPECT_EQ((void*)head->left, (void*)NULL);
  EXPECT_EQ((void*)head->right, (void*)NULL);
  EXPECT_TRUE(true);
}

TEST(InsertTest, sort_test_1000) {
	Node* head = NULL;


	for (int i = 0; i < 1000; ++i) {
		head = insert(head, i);
	}
	EXPECT_EQ(test(1000,head), 1);
	
	EXPECT_TRUE(true);
}
TEST(InsertTest, unsort_test_1000) {
	Node* head = NULL;
	for (int i = 999; i >=0; --i) {
		head = insert(head, i);
	}
	EXPECT_EQ(test(1000, head), 1);

	EXPECT_TRUE(true);
}

#if 1

TEST(EraseTest, nulltest) {
	Node* head = NULL;
	head = erase(head, 2);
	EXPECT_EQ(head, (Node*)NULL);

	EXPECT_TRUE(true);
}

TEST(EraseTest, one_element_test) {
	Node* head = NULL;
	head = insert(head, 1);
	head = erase(head, 1);
	EXPECT_EQ(head, (Node*)NULL);

	EXPECT_TRUE(true);
}
#endif
TEST(EraseTest, three_element_test) {
	Node* head = NULL;
	head = insert(head, 1);
	head = insert(head, 0);
	head = insert(head, 2);
	head = erase(head, 1);
	EXPECT_EQ(head->data, 2);

	EXPECT_TRUE(true);
}
TEST(EraseTest, missing_element_test) {
	Node* head = NULL;
	for (int i = 999; i >= 0; --i) {
		head = insert(head, i);
	}
	head = erase(head, -4);
	head = erase(head, -5);
	head = erase(head, 1001);
	EXPECT_EQ(test(1000,head), 1);

	EXPECT_TRUE(true);
}
