#include <iostream>
#include <string>
#include "testlib.h"

using namespace std;

void swap(string & A, string & B){
	string temp = A;
	A = B;
	B = temp;
}

int split(string A[], int start, int end){
	string pivot = A[end];
	int smaller = start, current = start;
	while(current < end) {
		if (A[current] >= pivot)
			current++;
		if (A[current] < pivot){
			swap(A[smaller], A[current]);
			smaller++;
			current++;
		}
	}
	swap(A[smaller], A[end]);
	return smaller;
}

//QuickSort
void quickSort(string A[], int start, int end){
	if (end - start <= 0) // set to zero
		return;
	int mid = split(A, start, end);
	quickSort(A, start, mid - 1);
	quickSort(A, mid + 1, end);
}

//MergeSort
void split(string A[], int size, string B[], string C[]){
	int curA = 0, curB = 0, curC = 0;
	while (curA != size){
		B[curB] = A[curA];
		curA++;
		curB++;
		if (curA == size)
			break;
		C[curC] = A[curA];
		curA++;
		curC++;
	}
}

void merge(string A[], string B[], int sizeB, string C[], int sizeC){
	int curA = 0, curB = 0, curC = 0;
	while (curB < sizeB && curC < sizeC){
		if (B[curB] < C[curC]){
			A[curA] = B[curB];
			curB++;
		}
		else {
			A[curA] = C[curC];
			curC++;
		}
		curA++;
	}
	while (curB < sizeB){
		A[curA] = B[curB];
		curA++;
		curB++;
	}
	while (curC < sizeC){
		A[curA] = C[curC];
		curA++;
		curC++;
	}
}

void mergeSort(string A[], int size){
	//cout << "hi" <<endl;
	if (size <= 1)
		return;
	int sizeB = size - (size / 2);
	int sizeC = size / 2;
	string * B = new string[sizeB];
	string * C = new string[sizeC];
	split(A, size, B, C);
	mergeSort(B, sizeB);
	mergeSort(C, sizeC);
	merge(A, B, sizeB, C, sizeC);
	delete [] B;
	delete [] C;
}

//HeapSort
void moveUp(string A[], int size, int node){
	int biggest = node;
	int left = 2 * node + 1, right = left + 1;

		if (left < size && A[left] > A[biggest])
			biggest = left;
		if (right < size && A[right] > A[biggest])
			biggest = right;

		if (biggest != node){
			swap(A[node], A[biggest]);
			moveUp(A, size, biggest);
		}
}

void heapSort(string A[], int size){
	for (int i = (size / 2) - 1; i >= 0; i--){
		moveUp(A, size, i);
	}

	for (int a = size - 1; a >= 0; a--){
		swap(A[0], A[a]);
		moveUp(A, a, 0);
	}
}

int main(int argc, char * argv[]){
	string * A, * B, * C;
	tester T1(argc, argv, A);
	int size = T1.get_number();
	cout << "Quick Sort Time:" << endl;
	quickSort(A, 0, size - 1);
	T1.finish();

	tester T2(argc, argv, B);
	size = T2.get_number();
	mergeSort(B, size);
	cout << "Merge Sort Time:" << endl;
	T2.finish();

	tester T3(argc, argv, C);
	size = T3.get_number();
	heapSort(C, size);
	cout << "Heap Sort Time:" << endl;
	T3.finish();
	
	return 0;
}