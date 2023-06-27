#include <iostream>
#include <string>
#include <vector>

using namespace std; 

struct missile{
	int val, row, col;

	missile(int v, int r, int c) {
		val = v;
		row = r;
		col = c;
	}

	void printMiss(){
		cout << val << " ";
	}

	void print(){
		cout << val << " " << row << " " << col << endl;
	}
};

void swap(int & A, int & B){
	int temp = A;
	A = B;
	B = temp;
}

int split(vector<int> & A, int start, int end){
	int pivot = A[end];
	int bigger = start, current = start;
	while(current < end) {
		if (A[current] <= pivot)
			current++;
		if (A[current] > pivot){
			swap(A[bigger], A[current]);
			bigger++;
			current++;
		}
	}
	swap(A[bigger], A[end]);
	return bigger;
}

void quickSort(vector<int> & A, int start, int end){
	if (end - start <= 0) // set to zero
		return;
	int mid = split(A, start, end);
	quickSort(A, start, mid - 1);
	quickSort(A, mid + 1, end);
}

bool missileInCorner(int row, int col, vector<missile> points){
	if(points[row].col == col)
		return true;
	else
		return false;
}

int max(int a, int b, int c){
	if (a > b && a > c)
		return a;
	else if (b > c)
		return b;
	else
		return c;

}

void createGrid(vector<int> rows){

	vector<int> cols = rows;
	int listsize = rows.size();
	quickSort(cols, 0, listsize-1);

	vector<missile> points;
	for (int a = 0; a < listsize; a++){
		for (int b = 0; b < listsize; b++){
			if (rows[a] == cols[b]){
				missile m(rows[a], a, b); 
				points.push_back(m);
			}
		}
	}

	int r = listsize + 1, c = listsize + 1;
	int array[r][c] = { };
	for (int i = r - 1; i >= 0; i--){
		for (int j = c - 1; j >= 0; j--){
			if ((i == r - 1) || (j == c - 1))
				array[i][j] = 0;
			else if (missileInCorner(i, j, points)){
				array[i][j] = 1 + array[i + 1][j];
			}
			else {
				array[i][j] = max(array[i + 1][j], array[i][j + 1], array[i + 1][j + 1]);
			}
		}
	}

	for (int x = 0; x < r; x++){
		for (int y = 0; y < c; y++)
			cout << array[y][x];
		cout << endl;
	}

	cout << "The maximum number of missiles that catcher can intercept: " << array[0][0] << endl;
	
	cout << "The path of missiles taken down: ";
	int currR = 0, currC = 0;
	while (currR < listsize || currC < listsize){
		if (array[currC][currR] == array[currC][currR + 1]){
			currR++;
		}
		else if (array[currC][currR] == array[currC + 1][currR]){
			currC++;
		}
		else {
			currR++;
			currC++;
			points[currC - 1].printMiss();
		}
		if (array[currC][currR] == 0)
			break;
	}


}

int main() {

	string input;
	vector<int> rows;
	cout << "What is the list of altitudes of all the missiles? Type 'END' when you are finished:" << endl;
	while (cin >> input) {
		if (input == "END") break;
		int in = stoi(input);
		rows.push_back(in);
	} 
	createGrid(rows);
	return 0;
}
