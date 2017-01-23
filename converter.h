#ifndef CONVERTER_H
#define CONVERTER_H

#include <iostream>
#include <string>

bool IsSeparator(char sym);
std::string StringReverse(std::string str);
char CharToLower(char sym);
std::string StringToLower(std::string str);
std::string RemoveSpecial(std::string str);
bool IsCharNum(char sym);
bool IsStringNum(std::string str);
bool IsStringDouble(std::string str);
char UNumToChar(size_t num);
std::string UNumToString(size_t num);
size_t CharToUNum(char sym);
size_t StringToUNum(std::string str);
void StringToBas(std::string str, char *arr, size_t str_size);
std::string GetParameter(std::string str, size_t num);
std::string dtos(double x);

#endif // CONVERTER_H
