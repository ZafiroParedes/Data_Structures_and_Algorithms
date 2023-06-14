#include <iostream>
#include <string>
#include "testlib.h"

using namespace std;

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

void print(string A[], int size){
	for (int i = 0; i < size; i++){
		cout << A[i] << endl;
	}
}

int main(int argc, char * argv[]){
	string * A;
	tester T(argc, argv, A);
	int size = T.get_number();
	
	mergeSort(A, size);

	T.finish();

	print(A, size);
	
	return 0;
}
