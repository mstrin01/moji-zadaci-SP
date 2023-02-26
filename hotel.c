#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 32

struct _date;
typedef struct _date* datePos;
typedef struct _date {
	int year;
	int month;
	int day;
}date;

struct _hotel;
typedef struct _hotel* position;
typedef struct _hotel {
	char name[MAX];
	datePos date;
	int income;
	position next;
}hotel;

/*
Napisati program koji cita datoteku koja sadrzi podatke o hotelima te kreirati vezanu listu hotela
 sortiranu po datumu izgradnje hotela. Uz datum izgradnje, u datoteci se nalazi i naziv hotela te njegov
 godisnji prihod.
 Ocjena 2: ispisati vezanu listu hotela sortiranu po datumu izgradnje hotela. 
 Izracunati srednju vrijednost godisnjih prihoda svih hotela
 pa modificirati vezanu listu hotela tako da se hoteli, ciji je godisnji prihod manji od izracunate 
 srednje vrijednosti, prebace na kraj vezane liste.
*/

position hotel_inic(position);
datePos datum_inic(datePos);
int citajHotele(position);
int stvoriListu(position, char*, int, int, int, int);
position kreirajElement(char*, int, int , int dan, int prihod);
int dateCompare(datePos, datePos);
int ispis(position);
int srednjaVri(position);
int prebaciNaKraj(position, int);
position nadjiZadnji(position p);

int main()
{
	position head = NULL;
	int srednja = 0;

	head = hotel_inic(head);

	citajHotele(head);
	printf("\n");
	ispis(head->next);

	srednja = srednjaVri(head->next);
	printf("\nSrednja vrijednost prihoda: %d \n", srednja);

	printf("\nLista nakon prebacivanja: \n");
	prebaciNaKraj(head, srednja);
	ispis(head->next);

	return 0;
}

position hotel_inic(position p)
{
	p = (position)malloc(sizeof(hotel));
	if (!p)
	{
		printf("Greska u inicijalizaciji (hoteli)!\n");
		return NULL;
	}

	strcpy(p->name, "");
	p->income = 0;
	p->date = NULL;
	p->next = NULL;

	return p;
}
/*datePos datum_inic(datePos p)
{
	p = (datePos)malloc(sizeof(date));
	if (!p)
	{
		printf("Greska u inicijalizaciji (datum)!\n");
		return NULL;
	}

	p->year = 0;
	p->month = 0;
	p->day = 0;
	
	return p;
}*/

int citajHotele(position head)
{
	FILE* fp = NULL;
	char imeDat[20] = { 0 }, imeHotela[30] = { 0 };
	int dan = 0, mjesec = 0, godina = 0, prihod = 0;

	printf("Unesi ime datoteke: ");
	scanf(" %s", imeDat);

	fp = fopen(imeDat, "r");
	if (!fp)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %d-%d-%d %d", imeHotela, &godina, &mjesec, &dan, &prihod);
		stvoriListu(head, imeHotela, godina, mjesec, dan, prihod);
	}

	fclose(fp);

	return 0;
}

int stvoriListu(position head, char* imeHotela, int godina, int mjesec, int dan, int prihod)
{
	position noviEl = NULL;
	position current = NULL, prev = NULL;

	prev = head;
	current = head->next;

	noviEl = kreirajElement(imeHotela, godina, mjesec, dan, prihod);

	if (current == NULL)
	{
		noviEl->next = prev->next;
		prev->next = noviEl;
	}

	else 
	{
		while (current != NULL && dateCompare(current->date, noviEl->date) > 0)
		{
			prev = prev->next;
			current = current->next;
		}

		noviEl->next = prev->next;
		prev->next = noviEl;
	}
	

	return 0;
}

position kreirajElement(char* imeHotela, int godina, int mjesec, int dan, int prihod)
{
	position noviEl = NULL;
	noviEl = hotel_inic(noviEl);

	noviEl->date = (datePos)malloc(sizeof(date)); //!!!!!

	strcpy(noviEl->name, imeHotela);

	noviEl->date->year = godina;
	noviEl->date->month = mjesec;
	noviEl->date->day = dan;
	noviEl->income = prihod;
	

	return noviEl;
}

int dateCompare(datePos d1, datePos d2)
{
	int result = 0;

	result = d1->year - d2->year;

	if (result == 0)
	{
		result = d1->month - d2->month;
		if (result == 0)
		{
			result = d1->day - d2->day;
		}
	}

	return result;
}

int ispis(position p)
{
	while (p != NULL)
	{
		printf("%s %d-%d-%d %d\n", p->name, p->date->year, p->date->month, p->date->day, p->income);
		p = p->next;
	}
	return 0;
}

int srednjaVri(position p)
{
	int brojac = 0, suma = 0;

	while (p != NULL)
	{
		suma = suma + p->income;
		++brojac;
		p = p->next;
	}

	return suma / brojac;
}

int prebaciNaKraj(position p, int srednja)
{ //ako je manji od srednje, prebaci na kraj

	position zadnji = NULL, current = NULL, prev = NULL, noviZadnji = NULL;
	zadnji = nadjiZadnji(p);

	prev = p;
	current = prev->next;

	while (current != zadnji)
	{
		if (current->income < srednja)
		{
			prev->next = current->next;

			current->next = zadnji->next;
			zadnji->next = current;
		}
		else
		{
			prev = current;
			current = current->next;
		}
		current = prev->next;
	}

	return 0;
}
position nadjiZadnji(position p)
{
	while (p->next != NULL)
		p = p->next;

	return p;
}