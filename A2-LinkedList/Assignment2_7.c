//By: Austin Greisman
#include <stdio.h>
#include <stdlib.h>

//This file just has functions in it, it's like I copied and pasted everything inside it
//into this program. It's just so that it's easier to read for me.
#include "LinkedListStack.h"

//Start of Stack code
typedef struct Stack {
	LinkedList ll;
} Stack;

void initS(Stack *s) {
	//Using the previously created function for init the linkedlist
	init(&(s->ll));
}

void Push(Stack *s, int x) {
	//The Node in the LinkedLists take doubles not integers
	x = (double)x;
	//Pushes add to front
	addFront(&(s->ll), x);
}

int Pop(Stack *s, int *res) {
	//Just checks to see if the LinkedList (Stack) is empty before is does anything.
	if (s->ll.head->value == 0)
	{
		printf("Stack is empty!\n");
		return 1;
	}

	removeFront(&(s->ll), res);
	return 0;
}

int isEmptyS(Stack *s) {
	//Just checks to see if the LinkedList (Stack) is empty before is does anything.
	if (s->ll.head->value == 0)
	{
		return 1;
	}

	//You're supposed to return 0 if it's not empty
	return 0;

}

//Now for the Queue code

typedef struct Queue {
	LinkedList ll;
} Queue;

void initQ(Queue *q) {
	init(&(q->ll));
}

//Adds to the end of the line
void enqueue(Queue *q, int x) {
	x = (double)x;
	addEnd(&(q->ll), x);

}

//Removes from the front of the line
int dequeue(Queue *q, int *res) {
	removeFront(&(q->ll), res);
	return 0;

}

int isEmptyQueue(Queue *q) {
	if (q->ll.head->value == 0)
	{
		return 1;
	}
	return 0;
}

void Print(Stack *sEven, Stack *sOdd){
	printf("This prints the Event and Odd Stack\n");

	printf("Even Stack: Head [");

	Node *ptrE = sEven->ll.head->next;

	for (int i = 0; i < sEven->ll.head->value; ++i)
	{
		printf("%.0f, ", ptrE->value);
		ptrE = ptrE->next;
	}
	printf("] Tail\n");

	//Printing the Odd now

	Node *ptrO = sOdd->ll.head->next;

	printf("Odd Stack: Head [");

	for (int i = 0; i < sOdd->ll.head->value; ++i)
	{
		printf("%.0f, ", ptrO->value);
		ptrO = ptrO->next;
	}
	printf("] Tail\n");
}

/*-----------------------------------------------------
---------------- The Actual Question ------------------
-----------------------------------------------------*/

//I didn't use any queues. He didn't say you needed to, only that you could
//only use their functions.

void Seperator(Stack *Start, Stack *sEven, Stack *sOdd, Stack *holder) {
	//The ll.head is there because in my header file, I defined the LinkedList as an acutal
	//variable, not a pointer. So I need to use a "." instead of a "->"
	int size = Start->ll.head->value;
	int res = 0;

	for (int i = 0; i < size; ++i)
	{
		//First Pop from the inital stack
		Pop(Start, &res);
		//Checks to see if the value is divisible by 2
		if (res % 2 != 0)
		{
			Push(sOdd, res);
		}
		else{
			//Pushes to temp stack
			Push(holder, res);
		}
	}

	//After you've sorted a bit
	//Need to put the even values back into sEven Stack

	//Pops and pushes the values from holder into the even.
	//This flips them back to normal
	while (!isEmptyS(holder)){
		Pop(holder, &res);
		Push(sEven, res);
		
	}
	return;


}


int main(void) {

	Stack holder, sEven, sOdd, Start;

	initS(&Start);
	initS(&sEven);
	initS(&sOdd);
	initS(&holder);


	Push(&Start, 13);
	Push(&Start, 11);
	Push(&Start, 6);
	Push(&Start, 3);
	Push(&Start, 4);

	Print(&sEven, &sOdd);
	printf("Initially ^^\n");
	printf("c\n");

	Seperator(&Start, &sEven, &sOdd, &holder);

	Print(&sEven, &sOdd);





	return 0;

}