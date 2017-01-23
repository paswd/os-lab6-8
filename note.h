#ifndef _NOTE_H_
#define _NOTE_H_

class Note {
private:
	double Id;
	double Balance;

public:
	Note(void);
	Note(double id);
	Note(double id, double summ);
	~Note(void);

	void Push(double summ);
	bool Pop(double summ);
	double GetBalance(void);

	Note& operator =(Note& note);
	friend bool operator ==(Note& note1, Note& note2);
	friend bool operator !=(Note& note1, Note& note2);
	friend bool operator <(Note& note1, Note& note2);
	friend bool operator <=(Note& note1, Note& note2);
	friend bool operator >(Note& note1, Note& note2);
	friend bool operator >=(Note& note1, Note& note2);
	friend std::ostream& operator<<(std::ostream& os, const Note& note);

	void Import(FILE *file);
	void Export(FILE *file);
};

#endif
