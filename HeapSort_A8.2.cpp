#include <iostream>
#include <string>
#include "testlib.h"

using namespace std;

void swap(string & A, string & B){
	string temp = A;
	A = B;
	B = temp;
}

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
	string * A;
	tester T(argc, argv, A);
	int size = T.get_number();

	heapSort(A, size );

	T.finish();

	for (int i = 0; i < size; i++){
		cout << A[i] << endl;
	}
	
	return 0;
}