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

void read_input_ips();
void print_ll();

struct ip_entry {
	string ip;
	int expiration_time;
	ip_entry *next = NULL;
};
ip_entry *head;


int main() {
	read_input_ips();
	print_ll();
}

void print_ll(){
	ip_entry *current_node = head;
	while(current_node != NULL){
		cout << "printing " << current_node->ip << " :: " << current_node->expiration_time << endl;
		current_node = current_node->next;
	}
}
void read_input_ips() {

	string line, token, ip, lease_time, sleep_time, temp;
	int t1 = 0;
	time_t now = time(0);

	ifstream myfile("input.txt");

	if (myfile.is_open()) {
		while (getline(myfile, line)) {

			now = time(0);
			cout << now;

			istringstream strm(line);

			cout << now;

			if (line[0] == 'P') {
				strm >> temp; // just to iterate to sleep time
				strm >> sleep_time;
				t1 = stoi(sleep_time);
				//sleep(t1);
			} else {
				strm >> ip;
				cout << " " << ip << endl;
				strm >> lease_time;
				t1 = stoi(lease_time);
				ip_entry *e1 = new ip_entry();
				e1->ip = ip;
				e1->expiration_time = t1 + now;
				if (head == NULL)
					head = e1;
				else {
					ip_entry *next_node, *current_node;
					next_node = head;
					while(next_node != NULL && next_node->expiration_time < e1->expiration_time){
						current_node = next_node;
						next_node = next_node->next;
					}

					e1->next = next_node;
					if(next_node == head)
						head = e1;
					else
						current_node->next = e1;

				}
			}

		}
		myfile.close();
	}
}

