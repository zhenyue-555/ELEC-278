
#include <stdio.h>
#include <stdlib.h>

/*Parent to child
-left = 2i + 1
-right = 2i + 2

Child to parent
-left c (i-1/2) Truncate
-right c (i-1/2) Truncate
*/


//Defines the first structure
typedef struct Heap
{
	int *a; //Array
	int last; //Know where the last is
	int maxsize; //the total size of array

} Heap;

Heap *initHeap(int size)
{
	//Initalizes the heap in memory
	Heap *h = malloc(sizeof(Heap));

	//makes the array in memory
	h->a = malloc(sizeof(int) * size);

	h->last = -1; //Says the heap is empty

	h->maxsize = size;

	return h;


}


void swap(Heap *heap, int index, int parent_index)
{
	//This just swaps the values
	int temp = heap->a[index];
	heap->a[index] = heap->a[parent_index];
	heap->a[parent_index] = temp;
}

void reHeapUp(Heap *heap, int index)
{
	if (index <= 0)
	{
		return; //You don't need to fix anything if there's only 1 or less in the heap
	}
	int parent_index = (index - 1) / 2;
	if (heap->a[index] < heap->a[parent_index])
	{
		swap(heap, index, parent_index);
	}
	else
	{
		return;
	}
	reHeapUp(heap, parent_index); //ReHeapUp again incase it's still not balanced
}

void reHeapDown(Heap *heap, int index)
{
	int left, right, smallest, smallestIndex;
	int leftIndex = 2 * index + 1;
	int rightIndex = 2 * index + 2;

	if (leftIndex <= heap->last) //Checks to see if theoretical leftIndex is actually there
	{
		left = heap->a[leftIndex];
		if (rightIndex <= heap->last) //Makes sure if there is a theoretical rightIndex there.
		{
			right = heap->a[rightIndex];
		} else
		{
			right = -1;//If the right isn't there. Then set it to a value that will be greater than left
			//This assumes all values inputted into heap are positive!
		}
		if (left < right || right == -1)
		{
			smallest = left;
			smallestIndex = leftIndex;
		} else
		{
			smallest = right;
			smallestIndex = rightIndex;
		}
		if (heap->a[index] > smallest)
		{
			swap(heap, index, smallestIndex);
			reHeapDown(heap, smallestIndex);
		}
	}
}

int withdrawMin(Heap *heap)
{
	//Swap the top of the heap with the last value
	int min = heap->a[0];
	heap->a[0] = heap->a[heap->last];
	heap->a[heap->last] = min;
	--heap->last;
	reHeapDown(heap, 0);

	return min;


}

void insert(Heap *heap, int x)
{
	//If you're at max size you can't add anymore
	if (heap->last == heap->maxsize)
	{
		return;
	}

	heap->a[++heap->last] = x; //Increase the value of heap->last and put the x into that spot;

	reHeapUp(heap, heap->last); //Always call this because logic to see if this is needed is in the function

}

void print(Heap *heap)
{
	if (heap->last <= 0)
	{
		printf("Nothing to Print!\n");
	}
	else
	{
		for (int i = 0; i <= heap->last; ++i)
		{
			printf("%d, ", heap->a[i]);
		}
		printf("\n");
	}
}

//Creates a heap from an array
Heap *heapify(int a[], int size)
{
	Heap *h = malloc(sizeof(Heap));
	h->last = -1;
	h->maxsize = size;
	h->a = a;
	for (int i = 0; i < size; ++i)
	{
		h->last++;
		reHeapUp(h, h->last);


	}
	return h;
}

//Problem 5

int findKth(Heap *h, int k, int size)
{
	int *temp = malloc(sizeof(int) * size); //Create a temp array
	int sizeOfTemp;

	for (int i = 0; i < k; ++i)
	{
		int withdrew = withdrawMin(h); //Withdraw it
		temp[i] = withdrew; //Store into temp
	}
	for (int i = 0; i < k; ++i)
	{
		insert(h, temp[i]); //Put everything that was in temp back into heap
	}
	return temp[k - 1]; //Return the kth smallest value

}

int main(void) {

	//Just creating my own heap.
	Heap *h = initHeap(7);

	insert(h, 2);
	insert(h, 5);
	insert(h, 7);
	insert(h, 8);
	insert(h, 2);
	insert(h, 3);
	insert(h, 6);

	printf("The Heap I created normally\n");
	print(h);
	int a[] = {23, 7, 92, 6, 12, 14, 40, 44, 20, 21, 98};

	//Using Heapify
	Heap *hh = heapify(a, 11);
	printf("The Heapify heap\n");
	print(hh);
	printf("The min value is: %d\n", withdrawMin(hh));
	print(hh);

	printf("The 3rd smallest value is %d\n", findKth(hh, 3, 10));
	print(hh);

	return 0;

}
