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
#include <unistd.h>
using namespace std;

struct ip_entry{
	string ip;
	int expiration_time;
	ip_entry *ptr;
};

int main() {

	ip_entry *head;
	string line, token, ip, lease_time, sleep_time, temp;
	int t1 = 0;
	time_t now = time(0);


	//Move to a function
	ifstream myfile("input.txt");
	if (myfile.is_open()) {
		while (getline(myfile, line)) {

			now = time(0);
			cout << now;

			istringstream strm(line);

			cout << now << endl;

			if(line[0] == 'P'){
				strm >> temp;// just to iterate to sleep time
				strm >> sleep_time;
				t1 = stoi(sleep_time);
				//sleep(t1);
			}else{
				strm >> ip;
				strm >> lease_time;
				t1 = stoi(lease_time);
				//cout << t1;
				ip_entry *e1 = new ip_entry();
				e1->ip = ip;
				e1->expiration_time = t1+now;
				if(head == NULL)
					head =e1;
				else{
					//add at proper location
				}
			}

		}
		myfile.close();
	}


}
