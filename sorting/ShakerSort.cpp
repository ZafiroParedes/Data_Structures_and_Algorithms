#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>
#include <sys/resource.h>

using namespace std;

double get_cpu_time()
{ struct rusage ruse;
  getrusage(RUSAGE_SELF, &ruse);
  return ruse.ru_utime.tv_sec + ruse.ru_utime.tv_usec / 1000000.0 + 
         ruse.ru_stime.tv_sec + ruse.ru_stime.tv_usec / 1000000.0; }

class person {
protected:
	int socialSecurity, birthDay, birthMonth, birthYear;
	double bankBalance;

public:
	string firstName, lastName;

	person(int ss, int bd, int bm, int by, string fn, string ln, double bb){
		socialSecurity = ss;
		birthDay = bd;
		birthMonth = bm;
		birthYear = by;
		firstName = fn;
		lastName = ln;
		bankBalance = bb;
	};

	void print(){
		cout << firstName << " " << lastName << " ";
		cout << socialSecurity << " " << birthDay << " " << birthMonth << " " << birthYear << " ";
		cout << bankBalance << "\n";
	}

};

vector<person> people;

void set(int ss, int bd, int bm, int by, string fn, string ln, double bb){
	person p(ss, bd, bm, by, fn, ln, bb);
	people.push_back(p);
}

void swap (person & a, person & b){
	person temp(0, 0, 0, 0, " ", " ", 0.0);
	temp = a;
	a = b;
	b = temp;
}

void shakerSort(int numOfElements) {
	for (int n = 0; n < numOfElements; n++) {
		// Starting from the top
		for (int startTop = n + 1; startTop < numOfElements; startTop++) {
			if (people[startTop].firstName < people[startTop - 1].firstName)
				swap(people[startTop], people[startTop - 1]);
			else if (people[startTop].firstName == people[startTop - 1].firstName) {
				if (people[startTop].lastName < people[startTop - 1].lastName)
					swap(people[startTop], people[startTop - 1]);
			}
		}
		numOfElements--;
		// Starting from the bottom
		for (int startBot = numOfElements - 1; startBot > n; startBot--) {
			if (people[startBot].firstName < people[startBot - 1].firstName)
				swap(people[startBot], people[startBot - 1]);
			else if (people[startBot].firstName == people[startBot - 1].firstName) {
				if (people[startBot].lastName < people[startBot - 1].lastName)
					swap(people[startBot], people[startBot - 1]);
			}
		}
	}
}

int main(){
	while (true){
		string userInput;
		if (userInput == "exit")
			break;

		ifstream file;
		cout << "What file would you like to see? To exit, type 'exit' \n>> ";
		cin >> userInput;
		file.open(userInput);
		if (file.fail()) {
			cout << "Could not open file :( ";
			exit(1);
		}

		int numOfElements = 0;
		do{
			int ss, bd, bm, by;
			string fn, ln;
			double bb;
			file >> ss >> bd >> bm >> by >> fn >> ln >> bb;
			set(ss, bd, bm, by, fn, ln, bb);
			numOfElements++;
		} while (!file.eof());

		//cout << people[numOfElements].firstName << "\n";

		file.close();

		/*
		for (int i = 0; i < 10; i++){
			cout << "[ "<< i << " ] : ";
			people[i].print();
		}
		*/

		//Sorting and measuring time
		double start = get_cpu_time();
		shakerSort(numOfElements);
		double end = get_cpu_time();
		cout << "It took " << end - start << " seconds to sort " << numOfElements << " of elements. \n";

		for (int i = 0; i < 10; i++){
			cout << "[ "<< i << " ] : ";
			people[i].print();
		}

		//Calc time constant
		double K = (end - start)/(numOfElements * numOfElements);
		cout << "Based on this time, the time constant 'K' is: " << K << "\n \n";

		for (int del = 0; del < numOfElements; del++)
			people.pop_back();
	}
	
	
}
