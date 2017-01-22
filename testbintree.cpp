#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//#include <stdbool.h>
#include "bintree.h"

//typedef long long Item;

/*int bintree_get_binleaves_count(Bintree *root)
{
	Bintree *left = bintree_get_branch_left(root);
	Bintree *right = bintree_get_branch_right(root);

	int cnt = 0;

	if (left != NULL && right != NULL)
		cnt++;
	if (left != NULL)
		cnt += bintree_get_binleaves_count(left);
	if (right != NULL)
		cnt += bintree_get_binleaves_count(right);

	return cnt;
}*/

int main(void)
{
	Bintree *tree = NULL;
	printf("-------------------------------------------\n");
	printf("Commands:\n");
	printf("a <value> - push to bintree\n");
	printf("d <value>- pop from bintree\n");
	//printf("c - get binarry leaves count\n");
	printf("p - print bintree\n");
	printf("q - exit\n");
	printf("-------------------------------------------\n");

	while (true) {
		//printf("%d\n", cnt);
		//cnt++;
		char cmd;
		Item value = 0;
		bool is_finished = false;
		scanf("%c", &cmd);
		switch (cmd) {
			case 'q':
				is_finished = true;
				break;
			case 'a':
				scanf("%lld", &value);
				if (tree == NULL)
					tree = new Bintree(value);
				else
					tree->Push(value);
				break;
			case 'd':
				if (tree == NULL) {
					printf("Tree is empty");
					break;
				}
				scanf("%lld", &value);
				tree->Pop(value);
				break;
			/*case 'c':
				if (tree == NULL) {
					printf("0\n");
					break;
				}
				printf("%d\n", bintree_get_binleaves_count(tree));
				break;*/
			case 'p':
				//bintree_print(tree, 0);
				tree->Print();
				break;
			case '\n':
				break;
			default:
				printf("Invalid command `%c`\n", cmd);
				break;
		}
		if (is_finished) break;
	}
	printf("Goodbye!\n");
	if (tree != NULL) {
		delete tree;
	}

	return 0;
}
