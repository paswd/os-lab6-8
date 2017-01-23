#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include "zmq.h"
#include "converter.h"
#include "bintree.h"
#include "note.h"

using namespace std;

const size_t SERVER_ID_DEFAULT = 4040;
const size_t MESSAGE_SIZE = 512;
const string CURRENCY_TITLE = " руб.";

string Parser(Bintree *tree, string cmd) {
	string id_str = GetParameter(cmd, 0);
	if (!IsStringDouble(id_str)) {
		return "Неправильный идентификатор";
	}
	double user_id = stod(id_str);
	Note note_tmp(user_id);
	BintreeStruct *element = tree->Search(note_tmp);

	string ans = "";

	string action = GetParameter(cmd, 1);
	if (action == "push") {
		string summ_str = GetParameter(cmd, 2);
		if (!IsStringDouble(summ_str)) {
			ans += "Сумма задана некорректно";
			return ans;
		}
		double summ = stod(summ_str);
		if (!element) {
			ans += "Создание счёта...\n";
			note_tmp.Push(summ);
			tree->Push(note_tmp);
		} else {
			element->Value.Push(summ);
		}
		ans += "Ваш счёт успешно пополнен на " + summ_str + CURRENCY_TITLE;
		return ans;
	}
	if (action == "pop") {
		string summ_str = GetParameter(cmd, 2);
		if (!IsStringDouble(summ_str)) {
			ans += "Сумма задана некорректно";
			return ans;
		}
		double summ = stod(summ_str);
		if (!element) {
			ans += "Создание счёта...\n";
			tree->Push(note_tmp);
			ans +=  "На вашем счёте недостаточно средств";
			return ans;
		}
		if (element->Value.GetBalance() < summ) {
			ans += "На вашем счёте недостаточно средств";
			return ans;
		}
		element->Value.Pop(summ);
		ans += "Ваш счёт успешно уменьшен на " + summ_str + CURRENCY_TITLE;
		return ans;
	}
	if (action == "transfer") {
		string summ_str = GetParameter(cmd, 3);
		if (!IsStringDouble(summ_str)) {
			ans += "Сумма задана некорректно";
			return ans;
		}
		string subject_str = GetParameter(cmd, 2);
		if (!IsStringDouble(subject_str)) {
			ans = "Идентификатор клиента задан неверно";
			return ans;
		}
		double subject_id = stod(subject_str);
		Note subject_tmp(subject_id);
		BintreeStruct *subject_element = tree->Search(subject_tmp);
		if (!subject_element) {
			ans = "Клиент не найден";
			return ans;
		}
		double summ = stod(summ_str);
		if (!element) {
			ans += "Создание счёта...\n";
			tree->Push(note_tmp);
			ans +=  "На вашем счёте недостаточно средств";
			return ans;
		}
		if (element->Value.GetBalance() < summ) {
			ans += "На вашем счёте недостаточно средств";
			return ans;
		}

		element->Value.Pop(summ);
		subject_element->Value.Push(summ);
		ans += summ_str + " единиц были успешно перечислены клиенту `" + subject_str + "`";
		return ans;
	}
	if (action == "balance") {
		if (!element) {
			ans += "Создание счёта...\n";
			tree->Push(note_tmp);
			ans += "Ваш баланс составляет 0" + CURRENCY_TITLE;
		} else {
			double balance = element->Value.GetBalance();
			ans += "Ваш баланс составляет " + dtos(balance) + CURRENCY_TITLE;
		}
		return ans;
	}
	if (action == "help") {
		ans += "Список команд:\n";
		ans += "push <n> - пополнить счёт на `n` единиц\n";
		ans += "pop <n> - снять со счёта `n` единиц\n";
		ans += "transfer <id> <n> - перевести `n` единиц клиенту `id`\n";
		ans += "balance - отобразить текущий баланс\n";
		ans += "help - отобразить список доступных команд\n";
		ans += "poweroff - выключить банковский сервер";
		return ans;
	}
	ans += "Команда `" + action + "` не распознана";
	return ans;
}

int main(void) {
	bool server_start = true;
	
	cout << "Server starting..." << endl;
		
	size_t server_id = 0;
	string str_server_id = "";
	cout << "Select server ID [default 4040]: " << endl;
	getline(cin, str_server_id);
	server_id = StringToUNum(str_server_id);

	if (server_id == 0) {
		server_id = SERVER_ID_DEFAULT;
	}
	string server_id_str = UNumToString(server_id);
	string server_bind = "tcp://";
	server_bind += "*:";
	server_bind += server_id_str;
		
	while (server_start) {
		server_start = false;
		void* context = zmq_ctx_new();
		void* respond = zmq_socket(context, ZMQ_REP);
		zmq_bind(respond, server_bind.c_str());

		cout << "Bank server started" << endl;

		Bintree tree;
		string db_filename = ".bank_database_" + UNumToString(server_id);
		tree.Import(db_filename);

		while (true) {
			char str_tmp[MESSAGE_SIZE];
			str_tmp[MESSAGE_SIZE - 1] = '\0';
			zmq_msg_t request;
			zmq_msg_init(&request);
			zmq_msg_recv(&request, respond, 0);
			memcpy(&str_tmp, zmq_msg_data(&request), MESSAGE_SIZE);
			str_tmp[MESSAGE_SIZE - 1] = '\0';
			cout << "Got command: `" << str_tmp << "`" << endl;
			string cmd(str_tmp);
			zmq_msg_close(&request);
			
			cmd = StringToLower(cmd);
			bool exit = false;
			string ans = "";
			string action = GetParameter(cmd, 1);
			if (cmd == "poweroff" || action == "poweroff") {
				exit = true;
				ans = "Server power off...";
			} else if (cmd == "reboot" || action == "reboot") {
				exit = true;
				server_start = true;
				ans = "Server is rebooting...";
			} else {
				ans = Parser(&tree, cmd);
			}
			strcpy(str_tmp, ans.c_str());
			cout << "Answer: " << str_tmp << endl;
			zmq_msg_t reply;
			zmq_msg_init_size(&reply, MESSAGE_SIZE);
			memcpy(zmq_msg_data(&reply), str_tmp, MESSAGE_SIZE);
			zmq_msg_send(&reply, respond, 0);
			zmq_msg_close(&reply);
			if (exit) {
				break;
			}
		}

		tree.Export(db_filename);

		zmq_close(respond);
		zmq_ctx_destroy(context);
	}
	return 0;
}
