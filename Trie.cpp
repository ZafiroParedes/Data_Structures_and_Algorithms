#include "iostream"
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct node {
	char currChar;
	vector <node *> availChars;

	node(char currC){
		currChar = currC;
	}

	void addChar(node * newchar) {
		availChars.push_back(newchar);
	}

	int numinvec(char seechar){
		for(int curr = 0; curr < availChars.size(); curr++){
			if (seechar == availChars[curr]->currChar)
				return curr;
		}
		return -1;
	}

};

void setTrie(node * trie, string newStr){
	node * current = trie;
	for (int curr = 0; curr < newStr.length(); curr++){
		int invec = current->numinvec(newStr[curr]);

		if (invec == -1){
			node * newnode = new node(newStr[curr]); //char????
			current->addChar(newnode);
			current = newnode;
		}
		else {
			current = current->availChars[invec];
		}
	}
	
}

bool searchTrie(node * trie, string searchstr){
	node * current = trie;
	for (int curr = 0; curr < searchstr.length(); curr++){
		int invec = current->numinvec(searchstr[curr]);

		if (invec == -1){
			return false;
		}
		else {
			current = current->availChars[invec];
		}
	}
	return true;
}

int main(){
	node * trie = new node('\0');

	ifstream file;
	string filename = "unix.txt";
	file.open(filename);
	if (file.fail()){
		cout << "Couldn't open file :(\n";
		exit(1);
	}
	while (!file.eof()){
		string input;
		file >> input;
		setTrie(trie, input);
	}
	file.close();

	string userinput;
	cout << "A trie has been created with the word from \n" << filename << endl;
	cout << "To find a word in the trie, type the word and press ENTER\n";
	cout << "To exit, type EXIT\n";
	cout << ">> ";

	while(true){
		
		cin >> userinput;
		if (userinput == "EXIT")
			break;

		bool intrie = searchTrie(trie, userinput);

		if (intrie) {
			cout << "The word, " << userinput << ", appears in " << filename << endl;
		}
		else {
			cout << "The word, " << userinput << ", does not appear in " << filename << endl;
		}

		cout << "Search for another word\n>> ";
	}

	return 0;
}
