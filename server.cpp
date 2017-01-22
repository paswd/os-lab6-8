#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include "zmq.h"

using namespace std;

int main(void) {
	cout << "Server starting..." << endl;
	//void* context = zmq_ctx_new();
	//void* respond = zmq_socket(context, ZMQ_REP);
	
	//zmq_bind(respond, "tcp://*:4040");
	cout << "Bank server started" << endl;

	while (true) {
		string cmd = "";
		getline(cin, cmd); //Получение команды от клиента

	}

	return 0;
}
