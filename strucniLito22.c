#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Napisati program koji iz datoteke èita prezime i ime osobe i datum roðenja (dan, mjesec, godina). 
Od tih podataka se gradi sortirana vezana lista od najstarije do najmlaðe osobe (ne smije se lista naknadno sortirati). 
Ispisati listu.
Nakon toga se od korisnika traži da upiše ime osobe i iz liste se ispisuju datumi roðenja samo
za one osobe koje se tako zovu.
*/

struct _lista;
typedef struct _lista* position;
typedef struct _lista
{
	char ime[20];
	int dan;
	int mjesec;
	int godina;
	position next;
}lista;

position inicijalizacija();
int citajDat(position);
int stvoriListu(position, char*, int, int, int);
int dateCmp(position,position);
int ispis(position);
int traziOsobe(position);

int main()
{
	position head = NULL;
	head = inicijalizacija();

	citajDat(head);
	ispis(head->next);

	traziOsobe(head->next);

	return 0;
}

position inicijalizacija()
{
	position p = NULL;
	p = (position)malloc(sizeof(lista));
	if (!p)
	{
		printf("Greska u alokaciji!\n");
		return NULL;
	}

	strcpy(p->ime, "");
	p->godina = 0;
	p->mjesec = 0;
	p->dan = 0;
	p->next = NULL;

	return p;

}
int citajDat(position p)
{
	FILE* fp = NULL;
	char ime[20] = { 0 };
	int dan = 0, godina = 0, mjesec = 0;
	

	fp = fopen("a.txt", "r");
	if (!fp)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -2;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %d-%d-%d", ime, &dan, &mjesec, &godina);
		stvoriListu(p, ime, dan, mjesec, godina);
	}

	fclose(fp);

	return 0;
}
int stvoriListu(position p, char* ime, int dan, int mjesec, int godina)
{
	position q = NULL;
	q = inicijalizacija();

	strcpy(q->ime, ime);
	q->dan = dan;
	q->mjesec = mjesec;
	q->godina = godina;

	while (p->next != NULL && dateCmp(p->next, q) > 0)
		p = p->next;

	q->next = p->next;
	p->next = q;

	return 0;
}
int dateCmp(position p1, position p2)
{
	int result = 0;

	result = p1->godina - p2->godina;
	if (result == 0)
	{
		result = p1->mjesec - p2->mjesec;
		if (result == 0)
		{
			result = p1->dan - p2->dan;
		}
	}

	return result;
}
int ispis(position p)
{
	if (p == NULL)
	{
		printf("Lista je prazna!\n");
		return NULL;
	}
	while(p!=NULL)
	{
		printf("%s %d-%d-%d\n", p->ime, p->dan, p->mjesec, p->godina);
		p = p->next;
	}

	return 0;
}

int traziOsobe(position p)
{
	char trazenoIme[20] = { 0 };
	printf("\nUnesi ime osoba ciji datum rodjenja zelis saznati: ");
	scanf(" %s", trazenoIme);
	puts("\n");
	
	while (p != NULL)
	{
		if (strcmp(p->ime, trazenoIme) == 0)
		{
			printf("%d-%d-%d\n", p->dan, p->mjesec, p->godina);
		}
		
		
		p = p->next;
	}

	return 0;
}
