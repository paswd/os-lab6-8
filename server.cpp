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

string Parser(Bintree *tree, string cmd) {
	//cmd = StringToLower(cmd);
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
		if (!IsStringNum(summ_str)) {
			ans += "Сумма задана некорректно";
			return ans;
		}
		size_t summ = StringToUNum(summ_str);
		if (!element) {
			ans += "Создание счёта...\n";
			note_tmp.Push(summ);
			tree->Push(note_tmp);
		} else {
			element->Value.Push(summ);
		}
		ans += "Ваш счёт успешно пополнен на " + summ_str + " единиц";
		return ans;
	}
	if (action == "pop") {
		string summ_str = GetParameter(cmd, 2);
		if (!IsStringNum(summ_str)) {
			ans += "Сумма задана некорректно";
			return ans;
		}
		size_t summ = StringToUNum(summ_str);
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
		ans += "Ваш счёт успешно уменьшен на " + summ_str + " единиц";
		return ans;
	}
	if (action == "transfer") {
		string summ_str = GetParameter(cmd, 3);
		if (!IsStringNum(summ_str)) {
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
		size_t summ = StringToUNum(summ_str);
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
			ans += "Ваш баланс составляет 0 единиц";
		} else {
			size_t balance = element->Value.GetBalance();
			ans += "Ваш баланс составляет " + UNumToString(balance) + " единиц";
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
	cout << "Server starting..." << endl;
	//void* context = zmq_ctx_new();
	//void* respond = zmq_socket(context, ZMQ_REP);
	size_t server_id = 0;
	string str_server_id = "";
	cout << "Select server ID [default 4040]: " << endl;
	//cin >> server_id;
	getline(cin, str_server_id);
	server_id = StringToUNum(str_server_id);

	if (server_id == 0) {
		server_id = SERVER_ID_DEFAULT;
	}
	string server_id_str = UNumToString(server_id);
	//string server_bind = "tcp://" + "*:" + server_id_str;
	//zmq_bind(respond, server_bind.c_str());
	cout << "Bank server started" << endl;

	Bintree tree;
	string db_filename = ".bank_database_" + UNumToString(server_id);
	tree.Import(db_filename);
	
	while (true) {
		string cmd = "";
		getline(cin, cmd); //Получение команды от клиента
		//string id_str = GetParameter(cmd, 0);
		cmd = StringToLower(cmd);
		bool exit = false;
		string ans = "";
		string action = GetParameter(cmd, 1);
		if (cmd == "poweroff" || action == "poweroff") {
			exit = true;
			ans = "Server power off...";
		} else {
			ans = Parser(&tree, cmd);
		}

		cout << ans << endl;
		if (exit) {
			break;
		}
	}

	tree.Export(db_filename);

	return 0;
}
