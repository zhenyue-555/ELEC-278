// BDTHTRVS.C [161014]
//
// Code to show breadth-wise (instead of depth-wise) traversal of tree.
// Routine is NOT recursive - but it uses a queue.  The code from QUEUE1.C
// has been copied here.  This code implements 1 queue only.


#include <stdio.h>

// Definition of tree node.

struct _node	{
	int				value;
	struct _node	*left;
	struct _node	*right;
	};
typedef struct _node Node;


//=============================================================================
// Single queue code based on QUEUE1.C modified so that data items can be
// tree nodes.


#define bool	unsigned char
#define	false	(unsigned char) 0

// Queue implemented using an array.  Queue positions determined by only
// front index and queue length.  Structure holds all information about one
// queue.

#define MAXQLEN 10

struct _queue	{
	int     front;			// index of next element to remove
	int     length;			// number of elements currently in queue
	                        // next place to insert is (front+length)
	                        // mod MAXQLEN
	Node	*qdata[MAXQLEN];// queue of things of type pointer to Node
	};
typedef struct _queue	Queue;


Queue *qnew(void)
// Function creates a new queue and initializes front and length
{
	// Get piece of memory big enough for queue and structural information
	Queue	*q = (Queue *)malloc(sizeof(Queue));
	if (q != NULL)	{
		// malloc() successful - initialize the front and length for this
		// queue.
		q->front = 0;
		q->length = 0;
		}
	// return pointer to the newly created queue. (If the malloc() failed
	// q will be NULL; the caller should check for an error return.
	return q;
}//qnew()


void qdestroy(Queue *q)
// Called when queue no longer required - basically just frees the space
// malloc()ed to hold the queue
{
	if (q != NULL)	free (q);
}//qdestroy()


bool qempty (Queue *q)
// Determine if queue is empty
{
    return (q->length)==0;
}//qempty()


bool qfull (Queue *q)
{
    return (q->length)==MAXQLEN;
}//qfull()


bool qinsert (Queue *q, Node *n)
// Add value n to end of queue
{
    // First, check if even possible
    if (qfull(q))    return 0;
    // Can insert - new value gets placed at the end.
    q->qdata[(q->front+q->length) % MAXQLEN] = n;
    q->length++;
    return 1;
}//qinsert()


bool qremove (Queue *q, Node **n)
// Parameter n is a pointer to a pointer to a node.  Function will
// retrieve a pointer to a node from the queue.  The only way to
// return this value to calling code is for caller to supply a pointer
// to a variable that can receive the data; hence a pointer to {a pointer
// to a node}.
{
    // Check if there is anything to remove
    if (qempty(q))   return 0;
    // Front element is one to remove
    *n = q->qdata[q->front++];
	// check if updating front index overflowed
    q->front = (q->front) % MAXQLEN;
    q->length--;
    return 1;
}//qremove()

//=============================================================================


void  breadth_traverse  (Node* root)
// Function to traverse tree by level (or breadth).  In other words, process
// all nodes on level 0, then all nodes on level 1, then all nodes on level 2,
// etc. until there are no more nodes left to process.
{   
	Queue	*q = qnew();	// Set up a queue
	Node	*cNode;			// point to node currently being processed

	// Put root node of tree in queue to start
    qinsert (q, root);		

	// Keep processing nodes from queue
    while (!qempty(q))    {
        // fetch front node from queue and process it
		if (qremove(q, &cNode))	{
        	// print its value (example of processing)
        	printf (" %3d",cNode->value);
			// add children to queue of nodes to process
        	if (cNode->left)	qinsert(q,cNode->left);
        	if (cNode->right)	qinsert(q,cNode->right);
		} else	{
			// Something wrong - qempty() said that queue not empty, but
			// qremove() was not able to retrieve a node pointer
			fprintf (stderr, "ERROR: In breadth_traverse()\n");
			break;
			}//endif
        }//endwhile
	putchar ('\n');
	// finished with queue - we can throw it away
	qdestroy (q);	
}//breadth_traverse()



// Declarations of tree nodes.
// First, the leafs (or leaves).  They have no children, so initialize
// with value and NULL pointers.
Node L1 = {  2, NULL, NULL };
Node L2 = { 14, NULL, NULL };
Node L3 = { 21, NULL, NULL };
Node L4 = { 23, NULL, NULL };
Node L5 = { 31, NULL, NULL };

// Next, nodes with children.
Node P1 = { 12,  &L1,  &L2 };
Node P2 = { 18, NULL,  &L3 };
Node P3 = { 16,  &P1,  &P2 };
Node P4 = { 27,  &L4,  &L5 };
Node P5 = { 22,  &P3,  &P4 };

// Finally, pointer to root node
Node *treeroot = &P5;


int main (void)
{
    //printf ("PREORDER:\n\t");
    //preorder_print (treeroot);

    //printf ("\n\nINORDER:\n\t");
    //inorder_print (treeroot);

    //printf ("\n\nPOSTORDER:\n\t");
    //postorder_print (treeroot);

	printf ("Print by level\n");
	breadth_traverse  (treeroot);
    printf ("\nEND OF TEST\n");
    return 0;
}//main()
