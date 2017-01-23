#include "converter.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

bool IsSeparator(char sym) {
	switch (sym) {
		case '\t':
		case '\n':
		case '\v':
		case '\f':
		case '\r':
		case ' ':
		case '\0':
			return true;
		default:
			return false;
	}
}
string StringReverse(std::string str) {
	string new_str = "";
	for (size_t i = str.size(); i > 0; i--) {
		new_str += str[i - 1];
	}
	return new_str;
}

char CharToLower(char sym) {
	int diff = 'a' - 'A';
	if (sym >= 'A' && sym <= 'Z') {
		sym += diff;
	}
	return (char) sym;
}

string StringToLower(string str) {
	for (size_t i = 0; i < str.size(); i++) {
		str[i] = CharToLower(str[i]);
	}
	return str;
}

string RemoveSpecial(string str) {
	string new_str = "";
	bool is_first_space = true;
	for (size_t i = 0; i < str.size(); i++) {
		if (!IsSeparator(str[i])) {
			is_first_space = true;
		}
		bool is_set_space = false;
		if (str[i] == ' ' && is_first_space) {
			is_set_space = true;
			is_first_space = false;
		}

		if (!IsSeparator(str[i]) || is_set_space) {
			new_str += str[i];
		}
	}
	return new_str;
}

bool IsCharNum(char sym) {
	return sym >= '0' && sym <= '9';
}
bool IsStringNum(string str) {
	if (str.size() == 0) {
		return false;
	}
	for (size_t i = 0; i < str.size(); i++) {
		if (!IsCharNum(str[i])) {
			return false;
		}
	}
	return true;
}
bool IsStringDouble(string str) {
	if (str.size() == 0) {
		return false;
	}
	bool is_point = false;
	for (size_t i = 0; i < str.size(); i++) {
		if (!IsCharNum(str[i]) && !(str[i] == '.' && !is_point)) {
			return false;
		}
		if (str[i] == '.') {
			is_point = true;
		}
	}
	return true; 
}

char UNumToChar(size_t num) {
	return num + '0';
}
string UNumToString(size_t num) {
	string str = "";
	while (num > 0) {
		size_t md = num % 10;
		num /= 10;
		str += UNumToChar(md);
	}
	if (str == "") {
		str = "0";
	}
	return StringReverse(str);
}
size_t CharToUNum(char sym) {
	if (IsCharNum(sym)) {
		return sym - '0';
	}
	return 0;
}
size_t StringToUNum(string str) {
	size_t res = 0;
	for (size_t i = 0; i < str.size(); i++) {
		res *= 10;
		res += CharToUNum(str[i]);
	}
	return res;
}
void StringToBas(string str, char *arr, size_t str_size) {
	size_t i = 0;
	for (; i < min((size_t) str.size(), str_size - 1); i++) {
		arr[i] = str[i];
	}
	arr[i] = '\0';
}
string GetParameter(string str, size_t num) {
	str = RemoveSpecial(str);
	size_t cnt = 0;
	int i;
	bool special = false;
	for (i = 0; cnt < num && i < str.size(); i++) {
		if (special) {
			special = false;
			continue;
		}
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t') {
			cnt++;
		}
		if (str[i] == '\\') {
		   special = true;
		}
	}

	special = false;
	string res = "";
	for (; cnt == num && i < str.size(); i++) {
		if (special) {
			res += str[i];
			special = false;
			continue;
		}

		if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t') {
			break;
		}
		if (str[i] == '\\') {
		   special = true;
		   continue;
		}
		res += str[i];
	}
	return res;
}
string dtos(double x) {
    std::stringstream s;
    s << x;
    return s.str();
}
