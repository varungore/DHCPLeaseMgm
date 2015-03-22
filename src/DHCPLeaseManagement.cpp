//============================================================================
// Name        : DHCPLeaseManagement.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main() {

	string line, token;

	ifstream myfile("input.txt");
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			cout << line << '\n';
			istringstream strm(line);
			strm >> token;
			cout << token << endl;
			if(line[0] == 'P'){
				//sleep
			}

		}
		myfile.close();
	}


}
