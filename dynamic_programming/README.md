_In Progress..._
# Finding Maximum Amount of Missiles Hit
_February 2022_

Given a list of altitudes of where a set of missiles are currently at, dynamic programming is used to find the maximum number of missiles that could be hit with another missle going diagonally from the top left of a grid.

## Process
First the program calls for a list of altitudes so that they could be then saved in a vector. Then the list is used to create a grid using the altitude as y-axis and the order of the list as the x-axis. To find the maximum amount of missiles going from the top, the program begins at the bottom right of the grid to fill the grid with the possible number of missiles hit in each intersection. 

A bool function is used to return a value based on whether a missle is nearby or not. If a missile is nearby, the current box in the grid will add one to the value stored in the box beside it and save it in the current box. If there is not a missile diagonally from the box, then the value of it is the maximum value of the boxes to the right, bottom, or diagonally from that box. 

After the program has found the maxium number of missiles, seen in the top left position, the grid can then be used to find the path taken to maximize the number of missiles. Starting at the top left, the current position moves down until the value below is not the same as the current then the position shifts right. If the value below and the right do not have the same value as the current value, then the postion can move diagnally down one since there is a missile it has hit and saving it to return it at the end. 

The image below shows the path the program will take to list all the misiles. Furthermore, it shows the dynamc programming method to find the maximum number of missiles.

![missile path](https://github.com/ZafiroParedes/Data_Structures_and_Algorithms/assets/91034132/f497ddb3-ffa3-41ee-a6e6-f2da01a4a113)


## Results
Below are the results showing a set of two lists of altitudes and the ideal path to take to hit the maximum number of missiles.
![missile](https://github.com/ZafiroParedes/Data_Structures_and_Algorithms/assets/91034132/650416f7-20d3-4e34-9802-b972996d35bd)
