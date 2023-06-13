#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

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
		cout << "Social Security: " << socialSecurity << " Birthdate: " << birthDate << " Name: " << firstName << " " << lastName << " Zipcode: " << zipCode << "\n";
	}
	void printName() {
		cout << "Name: " << firstName << " " << lastName << endl;
	}
	void printNandZ(){
		cout << "Name: " << firstName << " " << lastName << " Zipcode: " << zipCode << "\n";
	}
};

struct node {
	person * info;
	node * left, * right;

	node (person * i, node * l, node * r) {
		info = i;
		left = l;
		right = r;
	}
};

class BinaryTree {
protected:
	node * root;

public:
	BinaryTree(){
		root = NULL;
	}

	node * insertIndivid(node * n, person * p){
		if (n == NULL)
			return new node(p, NULL, NULL);
		else {
			if (p->lastName < n->info->lastName)
				n->left = insertIndivid(n->left, p);
			else if (p->lastName > n->info->lastName)
				n->right = insertIndivid(n->right, p);
			else if (p->lastName == n->info->lastName){
				if (p->firstName < n->info->firstName)
					n->left = insertIndivid(n->left, p);
				else 
					n->right = insertIndivid (n->right, p);
			}
			return n;
		}
	}

	void insertIndivid(person * p){ 
		if (root != NULL) {
			root = insertIndivid(root, p);
		}
		else
			root = new node(p, NULL, NULL);
	}

	void findPerson(node * n, string fn, string ln){
		if (n == NULL)
			return;

		if (ln < n->info->lastName)
			findPerson(n->left, fn, ln);
		else if (ln > n->info->lastName)
			findPerson(n->right, fn, ln);
		else if (ln == n->info->lastName){
			if (fn < n->info->firstName)
				findPerson(n->left, fn, ln);
			if (fn > n->info->firstName)
				findPerson(n->right, fn, ln);
			else if (fn == n->info->firstName)
				n->info->printAll();
		}
	}

	void findPerson(string fn, string ln){
		findPerson(root, fn, ln);
	}

	void printAlphabetically(node * n){
		if (n != NULL){
			//return;
		printAlphabetically(n->left);
		n->info->printAll();
		printAlphabetically(n->right);
		}
	}

	void printAlphabetically(){
		printAlphabetically(root);
	}

	void searchZip(node * n, int zip){
		if (n == NULL)
			return;
		searchZip(n->left, zip);
		if (n->info->zipCode == zip)
			n->info->printName();
		searchZip(n->right, zip);
	}

	void searchZip(int zip){
		searchZip(root, zip);
	}

	node * oldest(node * n){
		if (n == NULL)
			return n;
		else {
			node * oldestP = n;
			node * oldestL = oldest(n->left);
			if(oldestL != NULL){
				if (oldestP->info->birthDate > oldestL->info->birthDate)
					oldestP = oldestL;
			}
			node * oldestR = oldest(n->right);
			if(oldestR != NULL){
				if (oldestP->info->birthDate > oldestR->info->birthDate)
					oldestP = oldestR;
			}
		return oldestP;
		}
	}

	void oldest(){
		node * temp = oldest(root);
		temp->info->printNandZ();
	}

	node * deletePerson(node * n, string fn, string ln) {
		if (n == NULL)
			return NULL;

		if (ln < n->info->lastName)
			n->left = deletePerson(n->left, fn, ln);
		else if (ln > n->info->lastName)
			n->right = deletePerson(n->right, fn, ln);
		else {
			if (fn < n->info->firstName)
				n->left = deletePerson(n->left, fn, ln);
			else if (fn > n->info->firstName)
				n->right = deletePerson(n->left, fn, ln);
			else if (fn == n->info->firstName) {
				if (n->left == NULL && n->right == NULL)
					return NULL;
				else if (n->left == NULL) {
					node * copy = n->right;
					delete n;
					return copy;
				}
				else if (n->right == NULL){
					node * copy = n->left;
					delete n;
					return copy;
				}
				node * copy = n->right;
				while (copy != NULL && copy->left != NULL) {
					copy = copy->left;
				}
				//putting the copy into its place
				n->info = copy->info;
				n->right = deletePerson(n->right, copy->info->firstName, copy->info->lastName);
			}
		}
		return n;
	}

	void deletePerson(string fn, string ln){
		root = deletePerson(root, fn, ln);
	}

};

int main() {
	BinaryTree people;

	ifstream file;
	file.open("database.txt");
	if (file.fail()){
		cout << "Couldn't Open the file :(";
		exit(1);
	}

	int ss, bd, zc;
	string fn, ln;
	
	while (file >> ss >> bd >> fn >> ln >> zc){
		people.insertIndivid(new person(ss, bd, fn, ln, zc));
	}
	file.close();

	// Loop after file is read
	while (true){
		string userInput;
		cout << "What would you like to do? \n";
		cout << "FIND - to find a specific person \n";
		cout << "PRINT- to print all the people in alphabetical order \n";
		cout << "ZIP - to provide a list of all people with the same zip code \n";
		cout << "OLDEST - to display the oldest and their zipcode \n";
		cout << "DELETE - to delete a specific person \n";
		cout << "EXIT - to stop the program \n >> ";
		cin >> userInput;

		if(userInput == "EXIT"){
			break;
		}
		else if(userInput == "FIND"){
			string fn, ln;
			cout << "Please provide a first name and a last name: \n >> ";
			cin >> fn >> ln;
			people.findPerson(fn, ln);
		}
		else if(userInput == "PRINT"){
			people.printAlphabetically();
		}
		else if(userInput == "ZIP"){
			int zip;
			cout << "Please enter a zip code: \n >> ";
			cin >> zip;
			people.searchZip(zip);
		}
		else if(userInput == "OLDEST"){
			cout << "The oldest is: ";
			people.oldest();
		}
		else if(userInput == "DELETE"){
			cout << "Please provide a first name and a last name: \n >> ";
			cin >> fn >> ln;
			people.deletePerson(fn, ln);
		}
		else 
			cout << " \nSorry, could not understand that command, try to type it in all caps." << endl;
		cout << endl;
	}

	
	
	return 0;
	
}
