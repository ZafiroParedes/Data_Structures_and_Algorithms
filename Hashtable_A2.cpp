#include <iostream> 
#include <fstream>
#include <string>

using namespace std;

struct place{
	int numCode, pop, roadIntCode;
	string state, name; 
	double area, latitude, longitude, disInter;

	place(int nu, string s, string na, int p, double a, double la, double lo, int r, double d) {
		numCode = nu;
		state = s;
		name = na;
		pop = p;
		area = a;
		latitude = la;
		longitude = lo;
		roadIntCode = r;
		disInter = d;
	}

	void printName(){
		cout << name << ", " << state << endl;
	}
	void print(){
		cout << "State: " << state << ", Name: " << name << ", Numeric code: " << numCode << ", Population:" << pop;
		cout << ", Area: " << area << ", Latitude: " << latitude << ", Longitude: " << longitude << ", Road Intersection Code: " << roadIntCode;
		cout << ", Distance: " << disInter << endl;
	}
};

unsigned int hashFunc(string placeName) {
	unsigned int h = 987123654;
	for (int i = 0; i < placeName.length(); i++)
		h = h * 691 + placeName[i];
	if (h < 0)
		h = -h;
	return h;
};

struct link {
	place * info;
	link * next;

	link(place * i, link * n) {
		info = i;
		next = n;
	}
};

int stringStop(string s) {
	int num = 0;
	while(!(s.at(num) == ' ' && s.at(num + 1) == ' ')){
		num++;
	}
	return num;
}

void parseCommands(string all, string &command, string &pName, string &pState){
	int num = 0;
	//finding command
	while(all.at(num) == ' ')
		num++;
	command = all.at(num);
	// finding the end for state inital
	int end = all.length() - 1;
	while(all.at(end) == ' ')
		end--;

	int stateNum = 1;
	while(all.at(end) != ' '){
		pState.at(stateNum) = all.at(end);
		stateNum--;
		end--;
	}
	cout << "State: " << pState << " end " << end <<endl;
	num ++;
	int i = 0;
	while(num < end){
		if (all.at(num) == ' ' && all.at(num + 1) == ' ' )
			//num++;
		if (all.at(num) != ' '){
			pName.at(i) = all.at(num);
			cout << i << ": " << pName.at(i) << " " << all.at(num) << endl;
			num++;
		}
		else if (all.at(num) == ' ' && all.at(num + 1) != ' ')
			pName.at(i) = all.at(num);
		i++;
	}
	pName = pName.substr(0, i);
	cout << pName << "!" << endl;
}

int main(int argc, char * argv[]) {
	if (argc != 3) {
		cerr << "Wrong arguments\n";
		exit(1);
	}
	int size = atoi(argv[1]);
	ifstream file(argv[2]);

	link * * hashtable = new link * [size];
	for(int i = 0; i < size; i++) {
		hashtable[i] = NULL;
	}
	
	while(true) {
		if (file.fail())
			break;

		string currentLine;
		place * p;

		getline(file, currentLine);
		if (!(file.eof())){
			int numCode = stoi(currentLine.substr(0,8));
			string state = currentLine.substr(8,2);
			string name = currentLine.substr(10, stringStop(currentLine.substr(10, 49)));
			int pop = stoi(currentLine.substr(59, 11));
			double area = stod(currentLine.substr(70,11));
			double latitude = stod(currentLine.substr(81, 100));
			double longitude = stod(currentLine.substr(91,10));
			double roadIntCode = stoi(currentLine.substr(102, 5));
			double disInter = stod(currentLine.substr(107,7));
			p = new place(numCode, state, name, pop, area, latitude, longitude, roadIntCode, disInter);
		}
		else
			break;

		unsigned int h = hashFunc(p->name);
		h = h % size; 
		link * ptr = hashtable[h];
		while (ptr != NULL) {
			if (ptr->info->name == p->name &&ptr->info->state == p->state)
					break;
			ptr = ptr->next;
		}
		if (ptr == NULL) {
			hashtable[h] = new link(p, hashtable[h]);
		}

	}

	file.close();

	cout << "Hello!" << endl;
	while (true) {
		string all, command, pName, pState;
		cout << "There are two ways to find all the named-placed in the US:" << endl;
		cout << "  S: to find the information of the specific place by providing name and state" << endl;
		cout << "  N: to get a list of places with the provided name" << endl;
		cout << "  Q: to quit the program" << endl << ">> ";
		getline(cin, command);
		//getline(cin, all);
		//pName = all;
		//parseCommands(all, command, pName, pState);
		if (command == "S"){
			cout << "Enter place name:" << endl << ">> ";
			getline(cin, pName);
			cout << "Enter State initals:" << endl;
			getline(cin, pState);

			unsigned int pInt = hashFunc(pName);
			pInt = pInt % size;
			link * P = hashtable[pInt];
			if (P == NULL)
				cout << "Sorry, we couldnt find what you're looking for. Check your spelling or capitalize the first letter." << endl;
			while (P != NULL){
					if (P->info->name == pName && P->info->state == pState){
						P->info->print();
						break;
					}
					else{
						if (P->next != NULL){
							P = P->next;
						}
						else{
						cout << "Sorry, we couldnt find what you're looking for. Check your spelling or capitalize the first letter." << endl;
						break;
						}
					}	
			}
		}
		else if (command == "N"){
			cout << "Enter place name:" << endl << ">> ";
			getline(cin, pName);
			unsigned int pInt = hashFunc(pName);
			pInt = pInt % size;
			link * P = hashtable[pInt];
			if (P == NULL)
				cout << "Sorry, we couldnt find what you're looking for. Check your spelling or capitalize the first letter." << endl;
			while (P != NULL){
					if (P->info->name == pName){
						P->info->print();
						P = P->next;
					}
					else{
						cout << "Sorry, we couldnt find what you're looking for. Check your spelling or capitalize the first letter." << endl;
						break;
					}
			}
		}
		else if (command == "Q"){
			break;
		}
		else
			cout << "Sorry, that is not a recognized command. Please try again.";
		
	}
}