#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
		int val;
		struct Node *next;
		struct Node *prev;
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
			newNode->prev = NULL;
			l->head = newNode;
		} else {
			Node *oldHead = l->head;
			l->head = newNode;
			newNode->next = oldHead;
			newNode->prev = NULL;
			newNode->val = value;
			oldHead->prev = newNode;
		}
	}
}

Node *getNextNode(Node *n) {
	return n->next;
}

Node *getPrevNode(Node *n) {
	return n->prev;
}

void insertEnd(List *l, int value) {
	Node *newNode = malloc(sizeof(Node));
	if (newNode != NULL) {
		l->size++;
		if (isEmpty(l)) {
			newNode->val = value;
			newNode->next = NULL;
			newNode->prev = NULL;
		} else {
			Node *current = l->head;
			while (current->next != NULL) {
				current = getNextNode(current);
			}
			current->next = newNode;
			newNode->val = value;
			newNode->next = NULL;
			newNode->prev = current;
			
			
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
			l->size--;
		} else {
			Node *oldHead = l->head;
			Node *newHead = oldHead->next;
			newHead->prev = NULL;

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
		while (current->next != NULL) {
			current = current->next;
		}
		current->prev->next = NULL;
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
		Node *current = l->head->next;
		while (count < index) {
			current = current->next;
			count++;
		}
		Node *newNode = (Node *)malloc(sizeof(Node));
		newNode->val = value;
		newNode->next = current;
		newNode->prev = current->prev;

		current->prev->next = newNode; // get prev node to point to new node
		current->prev = newNode; // overwrite currents' prev node to be new node
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
		Node *current = l->head->next;
		while (current->val != value) {
			if (current->next == NULL) {
				printf("node with value %d not found in list", value);
				return 0;
			}
			current = current->next;
		}
		Node *prevptr = current->prev;
		Node *nextptr = current->next;
		prevptr->next = nextptr;
		nextptr->prev = prevptr;
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
		char sprev[80];
		char snext[80];
		if (curr->prev == NULL) {
			sprintf(sprev, "(%s", "NULL");
		} else {
			sprintf(sprev, "->(%d", curr->prev->val);
		}
		
		if (curr->next == NULL) {
			sprintf(snext, "%s)", "NULL");
		} else {
			sprintf(snext, "%d)<-", curr->next->val);
		}
		
		printf("%s<-%d->%s", sprev, curr->val, snext);
		curr = curr->next;
	}
	printf("\n\n");
	
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

	insertNodeAtLocation(&linkedList, 3, 7);

	removeNode(&linkedList, 5);

	deleteEnd(&linkedList);

	deleteFront(&linkedList);

	printf("Current state of list:\n");
	printLinkedList(&linkedList);
}
