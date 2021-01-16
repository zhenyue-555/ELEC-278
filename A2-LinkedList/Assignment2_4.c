//By: Austin Greisman
#include <stdio.h>
#include <stdlib.h>

//Same header file from Question 2 and 3.
#include "LinkedListStack.h"

//Need to create the structure of a Deque. Which is basically a LinkedList
typedef struct Deque {
	LinkedList ll;
} Deque;

void initDQ(Deque *d) {
	init(&(d->ll));
}

//Adds to the front of the line
int enqueueHead(Deque *d, int x) {
	x = (double)x;
	addFront(&(d->ll), x);
	return 0;

}

//Adds to the back of the line
int enqueueTail(Deque *d, int x) {
	x = (double)x;
	addEnd(&(d->ll), x);
	return 0;
}

//Removes from the End of the line
void dequeueTail(Deque *d, int *res) {
	removeEnd(&(d->ll), res);
}

//Removes from the End of the line
void dequeueHead(Deque *d, int *res) {
	removeFront(&(d->ll), res);

}

//Just testing stuff to see if it would work.
int main(void) {

	Deque d;

	initDQ(&d);
	int x;

	enqueueTail(&d, 7);
	enqueueTail(&d, 9);

	printf("Front");
	print(&(d.ll));
	printf("Back\n");

	enqueueHead(&d, 11);
	dequeueTail(&d, &x);

	printf("Front");
	print(&(d.ll));
	printf("Back\n");
	dequeueTail(&d, &x);

	printf("Front");
	print(&(d.ll));
	printf("Back\n");

	dequeueTail(&d, &x);



	return 0;

}