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

	string line, token, ip, lease_time;
	int time = 0;
	ifstream myfile("input.txt");
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			cout << line << '\n';
			istringstream strm(line);

			cout << token << endl;
			if(line[0] == 'P'){
				//sleep
			}else{
				strm >> ip;
				strm >> lease_time;
				time = stoi(lease_time);
				cout << time;
			}

		}
		myfile.close();
	}


}
