#ifndef _BINTREE_H_
#define _BINTREE_H_

#include "note.h"

typedef Note Item;

class BintreeStruct {
private:
	BintreeStruct *Left;
	BintreeStruct *Right;

	void PrintLevel(size_t lvl);

public:
	Item Value;

	BintreeStruct(Item value);
	~BintreeStruct(void);

	void Push(Item value);
	bool Pop(Item value);
	BintreeStruct *Search(Item value);
	void Print(void);
	BintreeStruct *Min(void);
	BintreeStruct *Max(void);
	BintreeStruct *GetBranchLeft(void);
	BintreeStruct *GetBranchRight(void);
	Item GetValue(void);
	size_t ElementsCount(void);

	void Export(FILE *file);
};

class Bintree {
private:
	BintreeStruct *Root;

public:
	Bintree(void);
	~Bintree(void);

	void Push(Item value);
	void Pop(Item value);
	BintreeStruct *Search(Item value);
	void Print(void);
	BintreeStruct *GetRoot(void);
	BintreeStruct *Min(void);
	BintreeStruct *Max(void);
	BintreeStruct *GetBranchLeft(void);
	BintreeStruct *GetBranchRight(void);
	bool IsEmpty(void);
	size_t ElementsCount(void);

	bool Import(std::string filename);
	void Export(std::string filename);
};

#endif
