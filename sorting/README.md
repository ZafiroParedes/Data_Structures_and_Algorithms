# Sorting Algorithms

## Executing Shaker Sort
To compile the ShakerSort file, type the command:

  `g++ ShakerSort.cpp`
  
To run the shaker sort, type the command:

  `a.out`
  
It will have the prompt to select a file with information for people. The used database file is [here](database_extra.txt) but other files with the following format can be used.

> social_security birth_day birth_month birth_year first_name last_name bank_balance
  
## Executing Heap, Merge, and Quick Sorts
These sorts use a testlib library to provide randomly generated strings for the algorithm to sort and then provides tests to vaildate if the sorting was done correctly. The library also provides further details on the sorting algorithm such as total time for time complexity analysis.
To use the testlib.cpp file, it needs to be compiled first:

  `g++ -c testlib.cpp`
  
To compile the heap, merge, and quick sorts, type the command:

  `g++ sortFile.cpp testlib.o -o sortFile`
  
*sortFile* is the resulting executable file named differently then a.out because of the -o command. 
To run each sort, the executable file and the number of items needs to typed as:

  `sortFile numItems`
  
For example, the list of commands for quick sort:

  `g++ -c testlib.cpp`
  
  `g++ QuickSort.cpp testlib.o -o quicksort`
  
  `quicksort 10`
  
This list of commands will run quicksort on 10 random strings

## Results
The results of each sorting algorithm are shown below. Each run has a different number of random strings and the results show that the strings have been properly sorted with the verification of the testlib library. There is also details about how much time the program needed to sort the random strings along with the nlogn and the ratio.

### Shaker Sort
![shaker sort run picture](pictures/shakersort.jpg)
### Quick Sort
![quick sort run picture](pictures/quicksort.jpg)
### Merge Sort
![merge sort run first picture](pictures/mergesort.jpg)

![merge sort run secound picture](pictures/mergesort2.jpg)

