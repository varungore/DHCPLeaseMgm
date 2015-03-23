//============================================================================
// Name        : DHCPLeaseManagement.cpp
// Description : DHCPLeaseManagement C++, Ansi-style
//============================================================================

#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <map>

std::map<std::string, int> ip_map;

std::mutex thread_mutex;

using namespace std;

void* read_input_ips(void*);
void print_ll();
void* remove_inactive_ips(void*);

struct ip_entry {
	string ip;
	int expiration_time;
	ip_entry *next;
};

ip_entry *head;

int main() {
	pthread_t threads[2];

	pthread_create(&threads[0], NULL, read_input_ips, NULL);
	pthread_create(&threads[1], NULL, remove_inactive_ips, NULL);
	(void) pthread_join(threads[0], NULL);
	(void) pthread_join(threads[1], NULL);
	print_ll();
}

void print_ll() {
	thread_mutex.lock();
	ip_entry *current_node = head;
	while (current_node != NULL) {
		cout << "\nprinting " << current_node->ip << " :: "
				<< current_node->expiration_time << endl;
		current_node = current_node->next;
	}
	thread_mutex.unlock();
}

void *remove_inactive_ips(void* ptr) {

	ip_entry *current_node;
	time_t now = time(0);
	while (1) {
		thread_mutex.lock();
		current_node = head;
		time_t now = time(0);
		while (current_node != NULL && current_node->expiration_time <= now) {
			cout << "\nDeleting head:";
			ip_map[current_node->ip] = 0;
			cout << current_node->ip << endl;
			head = current_node->next;
			current_node = head;
		}
		thread_mutex.unlock();
	}
}

void *read_input_ips(void*) {

	string line, token, ip, lease_time, sleep_time, temp;
	int t1 = 0;
	time_t now = time(0);

	ifstream myfile("input.txt");

	if (myfile.is_open()) {
		while (getline(myfile, line)) {

			now = time(0);

			istringstream strm(line);

			if (line[0] == 'P') {
				strm >> temp; // just to iterate to sleep time
				strm >> sleep_time;

				t1 = stoi(sleep_time) / 1000;
				thread_mutex.lock(); //lock to clearly print
				cout << "\nSleeping for " << t1 << "\n";
				thread_mutex.unlock();
				sleep(t1);
			} else {
				thread_mutex.lock();//locked here to have clear couts
				strm >> ip;
				cout << now << " " << ip << endl;
				strm >> lease_time;
				t1 = stoi(lease_time);
				ip_entry *e1 = new ip_entry();
				e1->ip = ip;
				e1->expiration_time = (t1 / 1000) + now;
				e1->next = NULL;

				if (head == NULL) {
					head = e1;
					ip_map[ip] = 1;
				} else {
					ip_entry *next_node, *current_node;

					next_node = head;

					if (ip_map[ip] == 1) {
						//delete existing entry
						while (next_node != NULL && next_node->ip != ip){//never should next_node be NULL
								current_node = next_node;
								next_node = next_node->next;
						}
						cout << "\nUpdating lease for: " << ip;
						if(next_node == head){
							head = head->next;
							delete next_node;
						}else{
							current_node->next = next_node->next;
							ip_map[next_node->ip] = 0;
							delete next_node;
							next_node = current_node->next;
						}
					}
					//add ip with new lease time// Redundant can be optimized
					next_node = head;
					while (next_node != NULL
							&& next_node->expiration_time < e1->expiration_time) {
						current_node = next_node;
						next_node = next_node->next;
					}
					ip_map[e1->ip] = 1;
					e1->next = next_node;
					if (next_node == head) {
						head = e1;
					} else {
						current_node->next = e1;
					}
				}
				thread_mutex.unlock();
			}

		}
		myfile.close();
	}
}

