#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	char name[32];
	datePos date;
	int income;
	position next;
}hotel;

/* JA
Napisati program koji cita datoteku koja sadrzi podatke o hotelima te kreirati vezanu listu hotela
 sortiranu po datumu izgradnje hotela. Uz datum izgradnje, u datoteci se nalazi i naziv hotela te njegov
 godisnji prihod.
 Ocjena 2: ispisati vezanu listu hotela sortiranu po datumu izgradnje hotela.
 Izracunati srednju vrijednost godisnjih prihoda svih hotela
 pa modificirati vezanu listu hotela tako da se hoteli, ciji je godisnji prihod manji od izracunate
 srednje vrijednosti, prebace na kraj vezane liste.
*/

position inicijalizacija(position);
datePos inic_datum(datePos);
int citajDat(position);
int stvoriListu(position, char*, int, int, int, int);
int dateCmp(datePos, datePos);
int ispis(position);
int nadjiSrednju(position);
int prebaciNaKraj(position, int);
int nadjiZadnji(position);

int main()
{
	position head = NULL;
	int srednjaVrijednost = 0;

	head = inicijalizacija(head);

	citajDat(head);
	ispis(head->next);

	srednjaVrijednost = nadjiSrednju(head->next);
	printf("\nSREDNJA VRIJEDNOST PRIHODA: %d\n", srednjaVrijednost);

	prebaciNaKraj(head,srednjaVrijednost);
	printf("\n");
	ispis(head->next);
	

	return 0;
}

position inicijalizacija(position p)
{
	p = (position)malloc(sizeof(hotel));
	if (!p)
	{
		printf("Greska u alokaciji (hoteli)!\n");
		return NULL;
	}

	strcpy(p->name, "");
	p->income = 0;
	p->date = inic_datum(p->date);
	p->next = NULL;

	return p;
}
datePos inic_datum(datePos p)
{
	p = (datePos)malloc(sizeof(date));
	if (!p)
	{
		printf("Greska u alokaciji (date)!\n");
		return NULL;
	}

	p->day = 0;
	p->month = 0;
	p->year = 0;

	return p;
}

int citajDat(position p)
{
	FILE* fp = NULL;
	char imeDat[32] = { 0 };
	char imeHotela[32] = { 0 };
	int dan = 0, mjesec = 0, godina = 0, prihod = 0;

	strcpy(imeDat, "hotel.txt");

	fp = fopen(imeDat, "r");
	if (!fp)
	{
		printf("Greska u otvaranju hotel.txt\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %d-%d-%d %d", imeHotela, &godina, &mjesec, &dan, &prihod);
		stvoriListu(p, imeHotela, godina, mjesec, dan, prihod);
	}
	fclose(fp);

	return 0;
}

int stvoriListu(position head, char* ime, int godina, int mjesec, int dan, int prihod)
{
	position p = head;
	position novi = NULL;
	novi = inicijalizacija(novi);

	strcpy(novi->name, ime);
	novi->income = prihod;

	novi->date = inic_datum(novi->date);

	novi->date->year = godina;
	novi->date->month = mjesec;
	novi->date->day = dan;

	if (p->next == NULL)
	{
		novi->next = p->next;
		p->next = novi;
	}
	else
	{
		while (p->next != NULL && dateCmp(p->next->date, novi->date) > 0)
			p = p->next;

		novi->next = p->next;
		p->next = novi;
	}


	return 0;
}

int dateCmp(datePos d1, datePos d2)
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
		printf("%s | %d-%d-%d | %d\n", p->name, p->date->year, p->date->month, p->date->day, p->income);
		p = p->next;
	}

	return 0;
}

int nadjiSrednju(position p)
{
	int srednja = 0, brojac = 0, suma = 0;

	while (p != NULL)
	{
		suma += p->income;
		++brojac;
		p = p->next;
	}

	return suma / brojac;
}

int prebaciNaKraj(position head, int srednja)
{
	position curr = NULL, prev = NULL, zadnji = NULL;
	
	prev = head;
	curr = prev->next;

	zadnji = nadjiZadnji(head);

	while (curr != zadnji)
	{
		if (curr->income < srednja)
		{
			prev->next = curr->next;

			curr->next = zadnji->next;
			zadnji->next = curr;
		}
		else {
			prev = prev->next;
			curr = curr->next;
		}
		curr = prev->next;
	}

	return 0;
}

int nadjiZadnji(position p)
{
	while (p->next != NULL)
		p = p->next;

	return p;
}