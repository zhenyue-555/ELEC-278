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

void swapH(int* heap, int i, int j) {
	int t = heap[i];
	heap[i] = heap[j];
	heap[j] = t;
}
void reheapUp(Heap* heap, int index) {
	if (index <= 0)
		return;
	int parent_index = (index - 1) / 2;
	if (heap->a[index] > heap->a[parent_index])
		swapH(heap->a, index, parent_index);
	else
		return;
	reheapUp(heap, parent_index);
}
long reheapDown(Heap* heap, int i) {
	int left;
	int right;
	int largest;
	int largestIndex;
	long swaps = 0;
	if (2 * i + 1 <= heap->last) {
		left = heap->a[2 * i + 1];
		if (2 * i + 2 <= heap->last) {
			right = heap->a[2 * i + 2];
		} else {
			right = -1;
		}
		if (left > right || right == -1) {
			largest = left;
			largestIndex = 2 * i + 1;
		} else {
			largest = right;
			largestIndex = 2 * i + 2;
		}
		if (heap->a[i] < largest) {
			swapH(heap->a, i, largestIndex);
			swaps++;
			reheapDown(heap, largestIndex);
		}
	}
	return swaps;
}
int withdrawMax(Heap* h) {
	int max = h->a[0];
	h->a[0] = h->a[h->last];
	h->last--;
	reheapDown(h, 0);
	return max;
}
void insert(Heap* heap, int x) {
	if (heap->last == heap->maxSize - 1)
		return;
	heap->a[++heap->last] = x;
	reheapUp(heap, heap->last);
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
Heap* heapify2(int a[], int size) {
	Heap* h = malloc(sizeof(Heap));
	h->maxSize = size;
	h->a = a;
	h->last = size-1;
	int i;
	for (i = size/2; i >= 0; i--) {
		reheapDown(h, i);
	}
	return h;
}
int findMax(Heap* h) {
	if (h->last != -1)
		return h->a[0];
	return -1;
}
