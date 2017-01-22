#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include "bintree.h"

using namespace std;

Bintree::Bintree(Item value) {
	this->Left = NULL;
	this->Right = NULL;
	this->Value = value;
}
Bintree::~Bintree(void) {
	if (this->Left != NULL) {
		delete this->Left;
	}
	this->Left = NULL;

	if (this->Right != NULL) {
		delete this->Right;
	}
	this->Right = NULL;
}
void Bintree::Push(Item value) {
	if (value < this->Value) {
		if (this->Left != NULL) {
			this->Left->Push(value);
			return;
		}
		this->Left = new Bintree(value);
	} else {
		if (this->Right != NULL) {
			this->Right->Push(value);
			return;
		}
		this->Right = new Bintree(value);
	}
}
bool Bintree::Pop(Item value) {
	if (value < this->Value) {
		if (this->Left != NULL) {
			if (this->Left->Pop(value)) {
				this->Left = NULL;
			}
		}
		return false;
	}
	if (value > this->Value) {
		if (this->Right != NULL) {
			if (this->Right->Pop(value)) {
				this->Right = NULL;
			}
		}
		return false;
	}

	if (this->Left == NULL && this->Right == NULL) {
		delete this;
		return true;
	}
	if (this->Left == NULL) {
		Bintree *tmp = this->Right;
		this->Value = tmp->Value;
		this->Left = tmp->Left;
		this->Right = tmp->Right;
		tmp->Left = NULL;
		tmp->Right = NULL;
		delete tmp;
		return false;
	}
	if (this->Right == NULL) {
		Bintree *tmp = this->Left;
		this->Value = tmp->Value;
		this->Left = tmp->Left;
		this->Right = tmp->Right;
		tmp->Left = NULL;
		tmp->Right = NULL;
		delete tmp;
		return false;
	}
	Bintree *min = this->Right->Min();
	this->Value = min->Value;
	Bintree *tmp = this->Right;
	if (tmp == min) {
		this->Right = NULL;
		delete tmp;
		return false;
	}
	while (tmp->Left != min) {
		tmp = tmp->Left;
	}
	delete tmp->Left;
	tmp->Left = NULL;
	return false;
}
void Bintree::PrintLevel(size_t lvl) {
	if (this == NULL) {
		printf("Tree is empty\n");
		return;
	}
	for (int i = 0; i < lvl; i++)
		printf("  ");
	cout << this->Value << endl;
	if (this->Left != NULL)
		this->Left->PrintLevel(lvl + 1);
	if (this->Right != NULL)
		this->Right->PrintLevel(lvl + 1);
}
void Bintree::Print(void) {
	this->PrintLevel(0);
}
Bintree *Bintree::Min(void) {
	if (this->Left == NULL) {
		return this;
	}
	return this->Left->Min();
}
Bintree *Bintree::Max(void) {
	if (this->Right == NULL) {
		return this;
	}
	return this->Right->Max();
}

Bintree *Bintree::GetBranchLeft(void) {
	return this->Left;
}
Bintree *Bintree::GetBranchRight(void) {
	return this->Right;
}
Item Bintree::GetValue(void) {
	return this->Value;
}
