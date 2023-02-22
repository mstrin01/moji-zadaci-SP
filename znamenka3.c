#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
Napisati program koji generira 30 sluèajnih brojeva u opsegu od 0 do 100 i od generiranih brojeva gradi vezanu listu. 
Ispisati listu.
Izbaciti iz liste sve one brojeve koji su djeljivi s 3 ili imaju znamenku 3 i rezultantnu listu upisati u datoteku
u sortiranom redoslijedu od najmanjeg do najveæeg broja 
(sama lista se ne smije sortirati prije upisa u datoteku). -za ocjenu dovoljan
*/

struct _lista;
typedef struct _lista* position;
typedef struct _lista
{
	int broj;
	position next;
}lista;

position inicijalizacija(position);
int generiraj(position);
int stvoriListu(position, int);
int ispisListe(position);
int trazi(position);
int upisiUDat(position);
int oslobodiMemoriju(position);

int main()
{
	srand(time(NULL));

	position head = NULL;
	head = inicijalizacija(head);

	generiraj(head);
	ispisListe(head->next);

	puts("\n");

	trazi(head);
	ispisListe(head->next);

	upisiUDat(head);

	puts("\n");
	oslobodiMemoriju(head);
	ispisListe(head->next);

	return 0;
}

position inicijalizacija(position p)
{
	p = (position)malloc(sizeof(lista));
	if (!p)
	{
		printf("Greska u alokaciji!\n");
		return NULL;
	}

	p->broj = 0;
	p->next = NULL;

	return p;
}

int generiraj(position head)
{
	int br = 0, i = 0;

	do {
		
		br = rand() % (100 - 0 + 1) + 0;
		stvoriListu(head, br);
		++i;

	} while (i < 30);

	return 0;
}

int stvoriListu(position p, int br)
{
	position q = NULL;
	q = inicijalizacija(q);

	q->broj = br;
	q->next = p->next;
	p->next = q;

	return 0;
}

int ispisListe(position p)
{
	if (p == NULL)
	{
		printf("Prazna lista!\n");
		return NULL;
	}

	while (p != NULL)
	{
		printf("%d\n", p->broj);
		p = p->next;
	}

	return 0;
}

int trazi(position head)
{
	position temp = NULL;

	while (head->next != NULL)
	{
		if (head->next->broj % 3 == 0 || head->next->broj % 10 == 3 || head->next->broj/10 == 3)
		{
			temp = head->next;
			head->next = temp->next;
			free(temp);
		}
		else
			head = head->next;
	}

	return 0;
}
int upisiUDat(position head)
{
	char imeDat[40] = { 0 };
	FILE* fp = NULL;

	printf("Unesi ime datoteke: \n");
	scanf(" %s", imeDat);

	fp = fopen(imeDat, "w");
	if (!fp)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -2;
	}

	while (head != NULL )
	{
		fprintf(fp, "%d \n", head->broj);
		head = head->next;
	}

	

	fclose(fp);

	return 0;
}

int oslobodiMemoriju(position p)
{
	position temp = NULL;
	while (p->next != NULL)
	{
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}
	return 0;
}
