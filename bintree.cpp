#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include "bintree.h"

using namespace std;

const size_t CONTROL_SIZE = 11;

bool IsCorrectControl(char *arr) {
	char control[CONTROL_SIZE] = {'P', 'a', 's', 'W', 'D', 'L', 'a', 'b', '6', '-', '8'};
	for (size_t i = 0; i < CONTROL_SIZE; i++) {
		if (arr[i] != control[i]) {
			return false;
		}
	}
	return true;
}

BintreeStruct::BintreeStruct(Item value) {
	this->Left = NULL;
	this->Right = NULL;
	this->Value = value;
}
BintreeStruct::~BintreeStruct(void) {
	if (this->Left != NULL) {
		delete this->Left;
	}
	this->Left = NULL;

	if (this->Right != NULL) {
		delete this->Right;
	}
	this->Right = NULL;
}
void BintreeStruct::Push(Item value) {
	if (value < this->Value) {
		if (this->Left != NULL) {
			this->Left->Push(value);
			return;
		}
		this->Left = new BintreeStruct(value);
	} else {
		if (this->Right != NULL) {
			this->Right->Push(value);
			return;
		}
		this->Right = new BintreeStruct(value);
	}
}
bool BintreeStruct::Pop(Item value) {
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
		BintreeStruct *tmp = this->Right;
		this->Value = tmp->Value;
		this->Left = tmp->Left;
		this->Right = tmp->Right;
		tmp->Left = NULL;
		tmp->Right = NULL;
		delete tmp;
		return false;
	}
	if (this->Right == NULL) {
		BintreeStruct *tmp = this->Left;
		this->Value = tmp->Value;
		this->Left = tmp->Left;
		this->Right = tmp->Right;
		tmp->Left = NULL;
		tmp->Right = NULL;
		delete tmp;
		return false;
	}
	BintreeStruct *min = this->Right->Min();
	this->Value = min->Value;
	BintreeStruct *tmp = this->Right;
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
BintreeStruct *BintreeStruct::Search(Item value) {
	if (value == this->Value) {
		return this;
	}
	if (value < this->Value) {
		if (this->Left == NULL) {
			return NULL;
		}
		return this->Left->Search(value);
	} else {
		if (this->Right == NULL) {
			return NULL;
		}
		return this->Right->Search(value);
	}
}
void BintreeStruct::PrintLevel(size_t lvl) {
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
void BintreeStruct::Print(void) {
	this->PrintLevel(0);
}
BintreeStruct *BintreeStruct::Min(void) {
	if (this->Left == NULL) {
		return this;
	}
	return this->Left->Min();
}
BintreeStruct *BintreeStruct::Max(void) {
	if (this->Right == NULL) {
		return this;
	}
	return this->Right->Max();
}

BintreeStruct *BintreeStruct::GetBranchLeft(void) {
	return this->Left;
}
BintreeStruct *BintreeStruct::GetBranchRight(void) {
	return this->Right;
}
Item BintreeStruct::GetValue(void) {
	return this->Value;
}
size_t BintreeStruct::ElementsCount(void) {
	size_t res = 1;
	if (this->Left != NULL) {
		res += this->Left->ElementsCount();
	}
	if (this->Right != NULL) {
		res += this->Right->ElementsCount();
	}
	return res;
}

void BintreeStruct::Export(FILE *file) {
	this->Value.Export(file);
	if (this->Left != NULL) {
		this->Left->Export(file);
	}
	if (this->Right != NULL) {
		this->Right->Export(file);
	}
}

//===============

Bintree::Bintree(void) {
	this->Root = NULL;
}
Bintree::~Bintree(void) {
	delete this->Root;
}
void Bintree::Push(Item value) {
	if (this->Root) {
		this->Root->Push(value);
	} else {
		this->Root = new BintreeStruct(value);
	}
}
void Bintree::Pop(Item value) {
	bool del_root = false;
	if (!this->Root->GetBranchLeft() && !this->Root->GetBranchRight()
			&& this->Root->Value == value) {
		del_root = true;
	}
	this->Root->Pop(value);
	if (del_root);
	this->Root = NULL;

}
BintreeStruct *Bintree::Search(Item value) {
	if (this->Root == NULL) {
		return NULL;
	}
	return this->Root->Search(value);
}
void Bintree::Print(void) {
	this->Root->Print();
}
BintreeStruct *Bintree::GetRoot(void) {
	return this->Root;
}
BintreeStruct *Bintree::Min(void) {
	return this->Root->Min();
}
BintreeStruct *Bintree::Max(void) {
	return this->Root->Max();
}
BintreeStruct *Bintree::GetBranchLeft(void) {
	return this->Root->GetBranchLeft();
}
BintreeStruct *Bintree::GetBranchRight(void) {
	return this->Root->GetBranchRight();
}
bool Bintree::IsEmpty(void) {
	return this->Root == NULL;
}
size_t Bintree::ElementsCount(void) {
	if (!this->Root) {
		return 0;
	}
	return this->Root->ElementsCount();
}

bool Bintree::Import(std::string filename) {
	cout << "Import started..." << endl;
	FILE *file = fopen(filename.c_str(), "rb");
	if (file == NULL) {
		cout << "Import unable: no input file for import" << endl;
		return false;
	}
	char control[CONTROL_SIZE];
	fread(control, sizeof(char), CONTROL_SIZE, file);
	if (!IsCorrectControl(control)) {
		cout << "Import error: uncorrect file" << endl;
		return false;
	}
	size_t elements_cnt = 0;
	fread(&elements_cnt, sizeof(size_t), 1, file);
	for (size_t i = 0; i < elements_cnt; i++) {
		Note note_tmp;
		note_tmp.Import(file);
		this->Push(note_tmp);
	}
	fclose(file);
	cout << "Import has been successfully completed" << endl;
	return true;
}
void Bintree::Export(std::string filename) {
	cout << "Export started..." << endl;
	FILE *file = fopen(filename.c_str(), "wb");
	char control[CONTROL_SIZE] = {'P', 'a', 's', 'W', 'D', 'L', 'a', 'b', '6', '-', '8'};
	fwrite(control, sizeof(char), CONTROL_SIZE, file);
	size_t elements_cnt = this->ElementsCount();
	fwrite(&elements_cnt, sizeof(size_t), 1, file);
	this->Root->Export(file);
	fclose(file);
	cout << "Export has been successfully completed" << endl;
}
