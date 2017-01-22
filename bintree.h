#ifndef _BINTREE_H_
#define _BINTREE_H_

typedef long long Item;

class Bintree {
private:
	Item Value;
	Bintree *Left;
	Bintree *Right;

	void PrintLevel(size_t lvl);

public:
	Bintree(Item value);
	~Bintree(void);

	void Push(Item value);
	bool Pop(Item value);
	void Print(void);
	Bintree *Min(void);
	Bintree *Max(void);
	Bintree *GetBranchLeft(void);
	Bintree *GetBranchRight(void);
	Item GetValue(void);
};

#endif
