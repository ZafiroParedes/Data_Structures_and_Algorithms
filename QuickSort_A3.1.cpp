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

void quickSort(string A[], int start, int end){
	if (end - start <= 0) // set to zero
		return;
	int mid = split(A, start, end);
	quickSort(A, start, mid - 1);
	quickSort(A, mid + 1, end);
}

int main(int argc, char * argv[]){
	string * A;
	tester T(argc, argv, A);
	int size = T.get_number();

	quickSort(A, 0, size - 1);

	T.finish();

	for (int i = 0; i < size; i++){
		cout << A[i] << endl;
	}
	
	return 0;
}