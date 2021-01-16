/*
 * heaps.c
 *
 *  Created on: Nov 1, 2016
 *      Author: hisham
 */
#include <stdio.h>
#include <stdlib.h>
typedef struct Heap {
	int* a;
	int last;
	int maxSize;
} Heap;
Heap* initHeap(int size) {
	Heap* h = malloc(sizeof(Heap));
	h->a = malloc(sizeof(int) * size);
	h->last = -1;
	h->maxSize = size;
	return h;
}

void swap(int* heap, int i, int j) {
	int t = heap[i];
	heap[i] = heap[j];
	heap[j] = t;
}
void reheapUp(Heap* heap, int index) {
	if (index <= 0)
		return;
	int parent_index = (index - 1) / 2;
	if (heap->a[index] < heap->a[parent_index])
		swap(heap->a, index, parent_index);
	else
		return;
	reheapUp(heap, parent_index);
}
void reheapDown(Heap* heap, int i) {
	int left;
	int right;
	int smallest;
	int smallestIndex;
	if (2 * i + 1 <= heap->last) {
		left = heap->a[2 * i + 1];
		if (2 * i + 2 <= heap->last) {
			right = heap->a[2 * i + 2];
		} else {
			right = -1;
		}
		if (left < right || right == -1) {
			smallest = left;
			smallestIndex = 2 * i + 1;
		} else {
			smallest = right;
			smallestIndex = 2 * i + 2;
		}
		if (heap->a[i] > smallest) {
			swap(heap->a, i, smallestIndex);
			reheapDown(heap, smallestIndex);
		}
	}

}
int withdrawMin(Heap* h) {
	int min = h->a[0];
	h->a[0] = h->a[h->last];
	h->last--;
	reheapDown(h, 0);
	return min;
}
void insert(Heap* heap, int x) {
	if (heap->last == heap->maxSize - 1)
		return;
	heap->a[++heap->last] = x;
	reheapUp(heap, heap->last);
}
void print(Heap* heap) {
	printf("Heap: ");
	int i = 0;
	for (i = 0; i <= heap->last; i++) {
		printf("%d, ", heap->a[i]);
	}
	printf("\n");
}
Heap* heapify(int a[], int size) {
	Heap* h = malloc(sizeof(Heap));
	h->maxSize = size;
	h->a = a;
	h->last = 0;
	int i = 0;
	for (i = 1; i < size; i++) {
		h->last++;
		reheapUp(h, h->last);
	}
	return h;
}
int findMin(Heap* h) {
	if (h->last != -1)
		return h->a[0];
	return -1;
}
int main() {
	int a[] = { 23, 7, 92, 6, 12, 14, 40, 44, 20, 21 };
	Heap* h = heapify(a, 10);
	print(h);
	withdrawMin(h);
	print(h);
	withdrawMin(h);
	print(h);
	withdrawMin(h);
	print(h);
	/*
	 Heap* h = initHeap(32);
	 insert(h, 10);
	 print(h);
	 insert(h, 2);
	 print(h);
	 insert(h, 4);
	 print(h);
	 insert(h, 1);
	 print(h);
	 insert(h, 5);
	 print(h);
	 insert(h, 3);
	 print(h);



	 while(h->last!=-1){
	 printf("%d is withdrawn\n",withdrawMin(h));
	 print(h);
	 }
	 */
}

