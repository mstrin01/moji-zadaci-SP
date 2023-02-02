#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*
Napisati program kojim se slucajnim uzorkom generira 100 brojeva iz opsega od 300 do 700,
te ih sprema u binarno stablo pretraživanja. Zatim ispišemo to stablo u preorder naèinu ispisa.
*/

struct _stablo;
typedef struct _stablo* pokazivac;
typedef struct _stablo {
	int broj;
	pokazivac left;
	pokazivac right;
}stablo;


pokazivac inicijalizacija(pokazivac);
int generiranje(pokazivac);
pokazivac unesiUStablo(pokazivac, int);
int preorder(pokazivac);

int main()
{
	srand(time(NULL));

	pokazivac root = NULL;

	root = inicijalizacija(root);
	generiranje(root);
	preorder(root);
	
	return 0;
}

pokazivac inicijalizacija(pokazivac p)
{
	p = (pokazivac)malloc(sizeof(stablo));
	if (!p)
	{
		printf("Greska u alokaciji!\n");
		return NULL;
	}

	p->broj = 0;
	p->left = NULL;
	p->right = NULL;

	return p;
}

int generiranje(pokazivac p)
{
	int br = 0, i = 0;
	
	do {
		br = (rand() % (700 - 300 + 1) + 300);
		p = unesiUStablo(p, br);
		++i;

	} while (i < 100);

	return 0;
}

pokazivac unesiUStablo(pokazivac p, int br)
{
	if (p == NULL)
	{
		p = inicijalizacija(p);
		p->broj = br;
		
	}

	else if (p->broj < br)
	{
		p->right = unesiUStablo(p->right, br);
	}

	else if (p->broj > br)
	{
		p->left = unesiUStablo(p->left, br);
	}

	return p;
}

int preorder(pokazivac p)
{
	if (p != NULL) 
	{
		printf("%d\n", p->broj);
		preorder(p->left);
		preorder(p->right);

	}
	return 0;
}
