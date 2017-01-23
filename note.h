#ifndef _NOTE_H_
#define _NOTE_H_

class Note {
private:
	double Id;
	size_t Balance;

public:
	Note(void);
	Note(double id);
	Note(double id, size_t summ);
	~Note(void);

	void Push(size_t summ);
	bool Pop(size_t summ);
	size_t GetBalance(void);

	Note& operator =(Note& note);
	friend bool operator ==(Note& note1, Note& note2);
	friend bool operator !=(Note& note1, Note& note2);
	friend bool operator <(Note& note1, Note& note2);
	friend bool operator <=(Note& note1, Note& note2);
	friend bool operator >(Note& note1, Note& note2);
	friend bool operator >=(Note& note1, Note& note2);
	friend std::ostream& operator<<(std::ostream& os, const Note& note); 
};

#endif
