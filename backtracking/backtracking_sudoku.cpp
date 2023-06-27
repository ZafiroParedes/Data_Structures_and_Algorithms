#include "iostream"
#include <string>

using namespace std;

int grid[9][9] =
{ { 9, 0, 0, 2, 0, 0, 5, 4, 0 },
  { 2, 4, 0, 0, 0, 0, 0, 0, 7 },
  { 0, 0, 1, 0, 6, 0, 0, 8, 0 },
  { 0, 0, 0, 0, 0, 3, 9, 0, 1 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 3, 0, 4, 6, 0, 0, 0, 0, 0 },
  { 0, 8, 0, 0, 5, 0, 3, 0, 0 },
  { 4, 0, 0, 0, 0, 0, 0, 1, 2 },
  { 0, 7, 3, 0, 0, 9, 0, 0, 5 } };

/* Trial Two
{ { 0, 0, 8, 0, 7, 0, 0, 0, 4 },
  { 0, 4, 0, 0, 0, 8, 0, 5, 0 },
  { 1, 9, 0, 4, 0, 0, 2, 0, 0 },
  { 0, 7, 4, 0, 0, 0, 0, 0, 3 },
  { 5, 0, 6, 0, 0, 0, 9, 0, 2 },
  { 2, 0, 0, 0, 0, 0, 5, 6, 0 },
  { 0, 0, 9, 0, 0, 6, 0, 3, 1 },
  { 0, 3, 0, 1, 0, 0, 0, 2, 0 },
  { 4, 0, 0, 0, 2, 0, 6, 0, 0 } };
 */

/* Trial One
{ { 6, 0, 0, 0, 0, 3, 0, 4, 0 },
  { 0, 3, 0, 0, 0, 0, 5, 0, 9 },
  { 0, 0, 0, 0, 1, 0, 8, 0, 0 },
  { 0, 0, 0, 0, 8, 0, 9, 0, 3 },
  { 0, 6, 0, 0, 9, 0, 0, 2, 0 },
  { 1, 0, 3, 0, 5, 0, 0, 0, 0 },
  { 0, 0, 5, 0, 3, 0, 0, 0, 0 },
  { 2, 0, 4, 0, 0, 0, 0, 5, 0 },
  { 0, 8, 0, 4, 0, 0, 0, 0, 1 } };
*/

 void printgrid(){
 	cout << "\n";
 	for (int r = 0; r < 9; r++){
 		for (int c = 0; c < 9; c++){
 			cout << grid[r][c] << " ";
 		}
 		cout << "\n";
 	}
 }

bool allAgree(int c, int r, int num){
	//checking if the whole column agrees
	for (int col = 0; col < 9; col++){
		if (grid[r][col] == num)
			return false;
	}

	//checking if the whole row agrees
	for (int row = 0; row < 9; row++){
		if (grid[row][c] == num)
			return false;
	}

	//checking the 3x3 grid
	int gC = c / 3, gR = r / 3; //the 3x3 grid coordinates, which grid is it

	for (int roww = (gR * 3); roww < (gR * 3 + 3); roww++){
		for (int coll = (gC * 3); coll < (gC * 3 + 3);coll++){
			if (grid[roww][coll] == num)
				return false;
		}
	}
	return true;
}

void sudoku(int c, int r) {

	if (c >= 9) { //end of the individual row, includes 8 to do calculations
		if (r == 8){
			cout << "\nSolution: ";
			printgrid(); //at the end of the grid, success
			exit(0);
		}
		sudoku(0, r + 1);
	}

	bool changeNum = true;
	//will force any perm num to be skipped and stay unchanged

	if (grid[r][c] != 0){
		changeNum = false; //no longer a number that can be changed
		sudoku(c + 1, r); //there is already a number
	}

	if (changeNum) {
		for(int N = 1; N <= 9; N++){ //
			if (allAgree(c, r, N)){
				grid[r][c] = N;
				sudoku(c + 1, r);
				//if there is no agree for next place, returns here and tries next digit
			}
		}
		//no digit works, returns to previous place
		grid[r][c] = 0; //finished loop from a changeable num with no agree, revert
	}	
}

int main() {
	cout << "\nOriginal: ";
	printgrid();

	sudoku(0, 0);
	cout << "No Answer?\n";
	exit(1);

	return 0;
}
