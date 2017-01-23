#include <iostream>
#include "note.h"

using namespace std;
Note::Note(void) {
	this->Id = 0.0;
	this->Balance = 0;
}

Note::Note(double id) {
	this->Id = id;
	this->Balance = 0;
}
Note::Note(double id, size_t summ) {
	this->Id = id;
	this->Balance = summ;
}
Note::~Note(void) {

}
void Note::Push(size_t summ) {
	this->Balance += summ;
}
bool Note::Pop(size_t summ) {
	if (summ > this->Balance) {
		return false;
	}
	this->Balance -= summ;
	return true;
}
size_t Note::GetBalance(void) {
	return this->Balance;
}

Note& Note::operator =(Note& note) {
	this->Id = note.Id;
	this->Balance = note.Balance;
	return *this;
}
bool operator ==(Note& note1, Note& note2) {
	return note1.Id == note2.Id;
}
bool operator !=(Note& note1, Note& note2) {
	return !(note1 == note2);
}
bool operator <(Note& note1, Note& note2) {
	return note1.Id < note2.Id;
}
bool operator <=(Note& note1, Note& note2) {
	return note1.Id <= note2.Id;
}
bool operator >(Note& note1, Note& note2) {
	return note1.Id > note2.Id;
}
bool operator >=(Note& note1, Note& note2) {
	return note1.Id >= note2.Id;
}
ostream& operator<<(ostream& os, const Note& note)  
{  
    os << note.Id << ':' << note.Balance;  
    return os;  
}