#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int daysInTheMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct person {
	int socialSecurity, birthDate, zipCode;
	string firstName, lastName;
	person(int ss, int bd, string fn, string ln, int zc) {
		socialSecurity = ss;
		birthDate = bd;
		firstName = fn;
		lastName = ln;
		zipCode = zc;
	}
	void printAll() {
		cout << socialSecurity << " " << birthDate << " " << firstName << " " << lastName << " " << zipCode << "\n";
	};
	void printNandZ(){
		cout << firstName << " " << lastName << " " << zipCode << "\n";
	}
};

class list {
protected:
	struct link {
		person * info;
		link * next;
		link(person * i, link * n) {
			info = i;
			next = n;
		}
	};
	link * start;

public:
	list() {
		start = NULL;
	}

	void addFront(person * p) {
		start = new link(p, start);
	}

	void addBack(person * p) {
		link ** prev = &start;
		link * current = start;
		while(current != NULL) {
			prev = &current->next;
			current = current->next;
		}
		*prev = new link(p, NULL);
	}

	//find a way to show everyone with same last name
	void findLN(string l) {
		link * current = start;
		while(current != NULL) {
			if (current->info->lastName == l)
				current->info->printAll();
			current = current->next;
		}
	}

	person * findPerson(string f, string l) {
		link * current = start;
		while(current != NULL) {
			if (current->info->firstName == f && current->info->lastName == l)
				return current->info;
			current = current->next;
		}
		return NULL;
	}



	int age(int bd) {
		cout << "oldest func ";
		const int curYear = 2021;
		int month = bd - (int)(bd / 10000) * 10000;
		int age = (curYear * 10000 - bd) + 1200 + daysInTheMonth[month];
		//delete year, month, day;
		return age;
	}

	person * oldest() {
		link * oldest = start;
		link * current = start->next;
		if (current == NULL)
			return oldest->info;
		while(current != NULL) {
			if(age(oldest->info->birthDate) < age(current->info->birthDate))
				oldest = current;
			current = current->next;
		}
		return oldest->info;
		
	}

	void printFive() {
		link * lol = start;
		for (int i = 0; i< 5; i++ ){
			lol->info->printAll();
			lol = lol->next;
		}
	}

	list similarZip(int zip) {
		list L;
		link * current = start;
		while(current != NULL) {
			if (current->info->zipCode == zip)
			L.addFront(current->info);
		current = current->next;
		}
		return L;
	}

	void printList(){
		link * current = start;
		while(start != NULL){
			current->info->printAll();
			current = current->next;
		}
	}
};



int main() {
	list people;
	int numPeople = 0;

	ifstream file;
	file.open("database.txt");
	if (file.fail()){
		cout << "Couldn't Open te file :(";
		exit(1);
	}

	do {
		int ss, bd, zc;
		string fn, ln;
		file >> ss >> bd >> fn >> ln >> zc;
		people.addFront(new person(ss, bd, fn, ln, zc));
		numPeople++;
	} while(!file.eof());
	
	//people.printFive();
	
	while(true){
		string userInput;
		cout << "What would you like to do? \n";
		cout << "FIND - to find a specific person \n";
		cout << "ALL - to find all the people with said last name \n";
		cout << "ZIP - to provide a list of all people with the same zip code \n";
		cout << "OLDEST - to display the oldest \n";
		cout << "EXIT - to stop the program \n >> ";
		cin >> userInput;
		//userInput = tolower(userInput);

		if(userInput == "EXIT"){
			break;
		}
		else if(userInput == "FIND"){
			string fn, ln;
			cout << "Please provide a first name and a last name: \n";
			cin >> fn >> ln;
			person * subject = people.findPerson(fn, ln);
			if(subject == NULL)
				cout << "Sorry, that person does not exist \n";
			else
				subject->printAll();
		}
		else if(userInput == "ALL"){
			string ln;
			cout << "Please provide a last name: \n>> ";
			cin >> ln;
			cout << "These are all the people with that last name: \n";
			people.findLN(ln);

		}
		else if(userInput == "ZIP"){
			int zip;
			cout << "Please enter a zip code: \n >> ";
			cin >> zip;
			cout << "A linked list has been created for the zip code " << zip << ": \n";
			list userZip = people.similarZip(zip);
			userZip.printList();
			//cout << "lol \n";
		}
		else if(userInput == "OLDEST"){
			cout << "The oldest is: ";
			person * subject2 = people.oldest();
			subject2->printNandZ();
		}
		else 
			cout << " \nSorry, could not understand that command, try to type it in all caps." << endl;
	}

	cout << "\n";
	file.close();
	return 0;
}
