#include <string>
#include<iostream>
using namespace std;

int main() {
	string name[100];
	string age[100];
	string::size_type sz;
	int i=0;
	while (getline(cin, name[i])) {
		while (1) {
			if (cin.eof())
				break;
			cin >> age[i];
			if (age[i].at(0) < 48 || age[i].at(0) > 58)
				cout << "haha" << endl;
			else {
				cout << "hahaha" << endl;
				break;
			}
		}
		cin.ignore();
		i++;
		//cin >> name[i];
		
	}
	for (int j = 0; j < i; j++) {
		cout << name[j] << " " << age[j] << endl;
	}
	cout << "end" << endl;
	return 0;
  }