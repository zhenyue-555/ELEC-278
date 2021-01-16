//By: Austin Greisman

/*You don't need the includes in the header file as long as
you put them in the main file */

//Defining a Node
typedef struct Node {
	struct Node *next;
	struct Node *prev;
	double value;
} Node;

//Defining a LinkedList
typedef struct LinkedList {
	int size;
	Node *head;
} LinkedList;

//Initalizing the LinkedList structure and stuff
void init(LinkedList *ll) {
	//Creates the Sentinel, which sounds quite badass..
	Node *sentinel = malloc(sizeof(Node));
	//Assign the head of the LinkedList to the Sentinal
	ll->head = sentinel;
	ll->size = 0;
	//Need to assign values to the Sentinel as well
	sentinel->next = NULL;
	sentinel->prev = NULL;
	sentinel->value = 0;
}

void addFront(LinkedList *ll, double x) {
	//Creating new Node as well as temp sentinel
	Node *ptr = malloc(sizeof(Node));
	Node *sentinel = ll->head;

	//If the sentinel is empty
	if (sentinel->value == 0)
	{
		sentinel->next = ptr;
		sentinel->prev = ptr;
		sentinel->value = 1;

		//Assigning the ptr back to the sentinel

		ptr->next = sentinel;
		ptr->prev = sentinel;
		ptr->value = x;
		return;
	}

	//Assigning the current Node in front to a variable.
	Node *ptrOld = sentinel->next;
	//Assigning the Sentinel next to new Node
	sentinel->next = ptr;
	//Assigning new Node to Sentinel
	ptr->prev = sentinel;
	//Assinging the old Node to the new Node and vise versa
	ptrOld->prev = ptr;
	ptr->next = ptrOld;
	ptr->value = x;

	sentinel->value++;
}

void addEnd(LinkedList *ll, double x) {
	//Creating new Node as well as temp sentinel
	Node *ptr = malloc(sizeof(Node));
	Node *sentinel = ll->head;

	if (sentinel->value == 0)
	{
		sentinel->next = ptr;
		sentinel->prev = ptr;
		sentinel->value = 1;

		//Assigning the ptr back to the sentinel

		ptr->next = sentinel;
		ptr->prev = sentinel;
		ptr->value = x;
		return;
	}

	//Assigning the current Node in front to a variable.
	Node *ptrOld = sentinel->prev;
	//Assigning the Sentinel prev to new Node
	sentinel->prev = ptr;
	//Assigning new Node to Sentinel
	ptr->next = sentinel;
	//Assinging the old Node to the new Node and vise versa
	ptrOld->next = ptr;
	ptr->prev = ptrOld;

	ptr->value = x;

	sentinel->value++;

}

//Needed to change the removeFront so it returns the value it... removes..
double removeFront(LinkedList *ll, int *x) {
	//Checks to see if the sentinel is already empty
	Node *sentinel = ll->head;

	if (sentinel->value == 0)
	{
		printf("LinkedList is empty!\n");
		return 0;
	}
	//If there is only one Node in the LinkedList
	else if (sentinel->value == 1)
	{
		Node *ptrdelete = sentinel->prev;
		sentinel->next = NULL;
		sentinel->prev = NULL;
		sentinel->value = 0;

		//One difference in remove Front - gotta pop the value out.
		//They seem to want the x to be an int...
		*x = (int)ptrdelete->value;

		free(ptrdelete);
		return 0;
	}

	//Assigning the front Node as well as the NewFront
	Node *ptrdelete = sentinel->next;
	Node *ptrNewFront = sentinel->next->next;


	//Changing the new front prev to sentinel
	ptrNewFront->prev = sentinel;

	//Changing the sentinel location to the next -> next node
	sentinel->next = ptrNewFront;

	sentinel->value--;

	//Same as in the loop, need a way to pop the value out.
	//They seem to want the x to be an int...
	*x = (int)ptrdelete->value;

	//Freeing up old Node
	free(ptrdelete);
	return 0;

}

//Needed to modify so that it will output the value it removes
double removeEnd(LinkedList *ll, int *x) {
	//Checks to see if the sentinel is already empty
	Node *sentinel = ll->head;

	if (sentinel->value == 0)
	{
		printf("LinkedList is empty!\n");
		return 0;
	}
	//If there is only one Node in the LinkedList
	else if (sentinel->value == 1)
	{
		Node *ptrdelete = sentinel->prev;
		sentinel->next = NULL;
		sentinel->prev = NULL;
		sentinel->value = 0;

		//Sending the value away
		*x = ptrdelete->value;

		free(ptrdelete);
		return 0;
	}

	//Assigning the front Node as well as the NewFront
	Node *ptrdelete = sentinel->prev;
	Node *ptrNewBack = sentinel->prev->prev;


	//Changing the new front next to sentinel
	ptrNewBack->next = sentinel;

	//Changing the sentinel location to the next -> next node
	sentinel->prev = ptrNewBack;

	sentinel->value--;

	//Sending the value away
	*x = ptrdelete->value;

	//Freeing up old Node
	free(ptrdelete);
	return 0;

}

void print(LinkedList *ll) {
	//Connects to the sentinel and the node just before.
	Node *sentinel = ll->head;
	Node *ptr = sentinel->next;

	//Checks to see if the LinkedList is empty
	if (sentinel->value == 0)
	{
		printf("LinkedList is empty!\n");
		return;
	}
	//I felt like being fancy
	printf("[");

	//Loops through whole LinkedList until it hits the sentinel
	while (sentinel != ptr)
	{
		printf("%.2f, ", ptr->value);

		ptr = ptr->next;
	}
	printf("]");
//	printf("\n");

}
