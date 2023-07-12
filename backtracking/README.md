# Sudoku Solver by Backtracking
_March 2022_

### What is backtracking?
Backtracking is a brute force method that is meant to find all possible solutions. Utilizing constraints, solutions that do not satisfy them are discarded. 

### What constraints are used in a Sudoku?
The main constraints of a sudoku are verifying that one of each number is in a row, in a coulmn, and in the 3x3 grid. If any of these constraints are violated, them the program will backtrack using recusion because the solution is not vaild. These constraints make sure that any solution with a conflict is not pursued and the final solution follows the rules of the sudoku.

## Backtracking Process
Backtracking in the sudoku works by slowly filling the grid with possible numbers, decreasing the number of possible avilable numbers for the next box untileither the next box cannot be filled without a conflict or the entire grid is filled. When the next box cannot be filled without conflict and the grid has not been filled, then the program works backward, trying the next avilable number for the previous box until it can complete the grid. The program continues back and forth, occassionally restarting all the way at the beginning of the grid, until a solution has been found.

A great short video of the backtracking process in filling out a sudoku can be found [here](https://en.wikipedia.org/wiki/Backtracking)

## Results
Trial one saved in the top of the program is below:

![trial one](https://github.com/ZafiroParedes/Data_Structures_and_Algorithms/assets/91034132/63573d9b-4379-49e9-b4fd-4c48bd99787f)

Trail two is below:

![trail two](https://github.com/ZafiroParedes/Data_Structures_and_Algorithms/assets/91034132/53d56f05-c633-4687-96b1-eeee7b2c7e1c)

The current trial, or trial three, is shown below. First, there is a demonstration of a sudoku not having a solution after trial three was modified in row six from an 9 to an 8. This shows that the program understood the sudoku given was not possible and could not return an answer. After this test, the next run shows the result to the original trial.

![error and trial three](https://github.com/ZafiroParedes/Data_Structures_and_Algorithms/assets/91034132/e42447d9-26c3-479a-9afa-3357f7a40032)
