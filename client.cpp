#include <iostream>
#include <string>
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include "zmq.h"
#include "converter.h"

using namespace std;

const size_t MESSAGE_SIZE = 512;

int main(void) {
	bool first = true;
	string bank_str = "";
	size_t bank_id = 0;
	do {
		if (first) {
			first = false;
		} else {
			cout << "Номер банка введён некорректно" << endl;
		}
		cout << "Введите номер банка:" << endl;
		getline(cin, bank_str);
		bank_id = StringToUNum(bank_str);
	} while (!IsStringDouble(bank_str) || bank_id == 0);

	first = true;
	string id_str = "";
	double user_id = 0.0;
	do {
		if (first) {
			first = false;
		} else {
			cout << "Номер лицевого счёта введён некорректно" << endl;
		}
		cout << "Введите номер Вашего лицевого счёта:" << endl;
		getline(cin, id_str);
		user_id = stod(id_str);
	} while (!IsStringDouble(id_str) || user_id == 0.0);

	cout << "Настройка клиента закончена" << endl;

	void* context = zmq_ctx_new();
	
	void* request = zmq_socket(context, ZMQ_REQ);
	string address = "tcp://localhost:";
	address += UNumToString(bank_id);
	zmq_connect(request, address.c_str());

	id_str += " ";

	while (true) {
		char str_tmp[MESSAGE_SIZE];
		cout << ">>> ";
		string cmd = "";
		getline(cin, cmd);
		//cout << "Point 0" << endl;
		if (cmd == "" || cmd == "exit") {
			if (cmd == "") {
				cout << "exit" << endl;
			}
			break;
		}
		cmd = id_str + cmd;
		zmq_msg_t req;
		zmq_msg_init_size(&req, MESSAGE_SIZE);
		strcpy(str_tmp, cmd.c_str());
		memcpy(zmq_msg_data(&req), str_tmp, MESSAGE_SIZE);
		zmq_msg_send(&req, request, 0);
		zmq_msg_close(&req);
		zmq_msg_t reply;
		zmq_msg_init(&reply);
		zmq_msg_recv(&reply, request, 0);
		memcpy(&str_tmp, zmq_msg_data(&reply), MESSAGE_SIZE);
		str_tmp[MESSAGE_SIZE - 1] = '\0';
		cout << str_tmp << endl;
		zmq_msg_close(&reply);
		
	}

	zmq_close(request);
	zmq_ctx_destroy(context);

	cout << "До свидания!" << endl;
	
	return 0;
}
