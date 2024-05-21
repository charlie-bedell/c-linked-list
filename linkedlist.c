#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
		int val;
		struct Node *next;
} Node;

typedef struct List {
	int size;
	struct Node *head;
} List;

void initList(struct List *l) {
	l->head = NULL;
	l->size = 0;
}

int isEmpty(struct List *l) {
	return (l->head == NULL);
}

void insertFront(List *l, int value) {
	Node *newNode = malloc(sizeof(Node));
	if (newNode != NULL) {
		l->size++;
		if (isEmpty(l)) {
			newNode->val = value;
			newNode->next = NULL;
			l->head = newNode;
		} else {
			newNode->val = value;
			newNode->next = l->head;
			l->head = newNode;
		}
	}
}

Node *getNextNode(Node *n) {
	return n->next;
}

void insertEnd(List *l, int value) {
	Node *newNode = malloc(sizeof(Node));
	if (newNode != NULL) {
		l->size++;
		if (isEmpty(l)) {
			newNode->val = value;
			newNode->next = NULL;
		} else {
			Node *current = l->head;
			while (current->next != NULL) {
				current = getNextNode(current);
			}
			newNode->val = value;
			newNode->next = NULL;
			current->next = newNode;
		}
	}
}

void deleteFront(List *l) {
	// delete first node of list
	if (l->head != NULL) {
		if (l->size == 1) {
			Node *n = l->head;
			l->head = NULL;
			free(n);
		} else {
		Node *oldHead = l->head;
		Node *newHead = l->head->next;
		l->head = newHead;
		free(oldHead);
		l->size--;
		}
	}
}

void deleteEnd(List *l) {
	// remove last node of list
	if (!isEmpty(l)) {
		Node *current = l->head;
		Node *prev = l->head;
		while (current->next != NULL) {
			prev = current;
			current = current->next;
		}
		prev->next = NULL;
		free(current);
		l->size--;
	}
}

int insertNodeAtLocation(List *l, int index, int value) {
	// insert new node with value at index
	if (index > l->size || index < 0) {
		printf("invalid index %d in list of size %d", index, l->size);
		return -1;
	}
	if (index == 0) {
		insertFront(l, value);
		return 0;
	} else if (index == l->size) {
		insertEnd(l, value);
		return 0;
	} else {
		int count = 1;
		Node *prev = l->head;
		Node *current = l->head->next;
		while (count < index) {
			prev = current;
			current = current->next;
			count++;
		}
		Node *newNode = (Node *)malloc(sizeof(Node));
		newNode->val = value;
		newNode->next = current;
		prev->next = newNode;
		l->size++;
		return 0;
	}
}

int removeNode(List *l, int value) {
	// remove node with the specified value
	if (isEmpty(l)) {
		printf("provided list is empty\n");
		return -1;
	}
	if (l->head->val == value) {
		deleteFront(l);
		return 0;
	} else {
		Node *prev = l->head;
		Node *current = l->head->next;
		while (current->val != value) {
			if (current->next == NULL) {
				printf("node with value %d not found in list", value);
				return 0;
			}
			prev = current;
			current = current->next;
		}
		prev->next = current->next;
		free(current);
		l->size--;
		return 0;
	}
}

void printLinkedList(List *l) {
	Node *curr = l->head;

	if (isEmpty(l)) printf("list is empty");
	printf("the linked list has %d nodes\n\n", l->size);
	while(curr != NULL) {
		printf("%d->", curr->val);
		curr = curr->next;
	}
	printf("NULL\n\n");
}

int main(void) {
	List linkedList;
	printf("Linked list Demo\n\n");

	initList(&linkedList);

	insertFront(&linkedList, 5);
	insertFront(&linkedList, 3);
	insertFront(&linkedList, 1);

	insertEnd(&linkedList, 9);
	insertEnd(&linkedList, 21);

	printf("Current state of list:\n");
	printLinkedList(&linkedList);

	insertNodeAtLocation(&linkedList, 3, 7);
	printLinkedList(&linkedList);

	removeNode(&linkedList, 5);
	printLinkedList(&linkedList);

	deleteEnd(&linkedList);
	printLinkedList(&linkedList);

	deleteFront(&linkedList);
	printLinkedList(&linkedList);
}
