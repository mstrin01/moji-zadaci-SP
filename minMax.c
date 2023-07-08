#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*
Napisati program koji generira 15 slučajnih brojeva u opsegu od 100 - 120 i sprema ih u vezanu
listu, po redoslijedu generiranja, a ne sortirano. U listi ne smije biti duplih vrijednosti.
a) Potrebno je pronaći minimalnu i maksimalnu vrijednost, te iz njih izračunati srednju vrijednost
((min+max)/2) i nakon toga sve vrijednosti koje su veće od srednje prebaciti na kraj liste. Ispisati
minimalnu, maksimalnu i srednju vrijednost kao i rezultantnu listu.
*/

#define gg 120
#define dg 100

struct _lista;
typedef struct _lista* position;
typedef struct _lista
{
    int broj;
    position next;
} lista;


position inicijalizacija();
int genBr(position);
int stvoriListu(position, int);
int ispis(position);
int minVr(position);
int maxVr(position);
int prebaciNaKraj(position, int);
position nadjiZadnji(position);
int oslobodiMemoriju(position);

int main()
{
    srand(time(NULL));
    position head = NULL;
    int min = 0, max = 0, srednja = 0;

    head = inicijalizacija();
    genBr(head);
    ispis(head->next);

    min = minVr(head->next);
    max = maxVr(head->next);
    printf("\nMIN: %d", min);
    printf("\nMAX: %d", max);
 

    srednja = (min + max) / 2;
    printf("\nSREDNJA: %d", srednja);
    puts(""); 

    prebaciNaKraj(head, srednja);
    puts("");
    ispis(head->next);

    printf("\nOSLOBADJANJE MEMORIJE: ");
    oslobodiMemoriju(head);
    ispis(head->next);
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

    p->broj = 0;
    p->next = NULL;
    
    return p;

}
int genBr(position p)
{
    int br = 0, i = 0;
    
    do
    {
        br = rand() % (gg - dg + 1) + dg;
        if (stvoriListu(p, br) != 1)
            ++i;

    } while (i < 15);
   

    return 0;
}
int stvoriListu(position p, int br)
{
    position q = NULL, temp = NULL;
    q = inicijalizacija();

    temp = p->next;
    while (temp != NULL)
    {
        if (temp->broj == br)
        {
            free(q);
            return 1;
        }
        temp = temp->next;
    }

    
    q->broj = br;
    q->next = p->next;
    p->next = q;
    
    return 0;
}

int ispis(position p)
{
    if (p == NULL)
    {
        printf("Lista je prazna!\n");
    }

    while (p != NULL)
    {
        printf("%d\n", p->broj);
        p = p->next;
    }

    return 0;
}

int minVr(position p)
{
    int min = 0;
    position curr = NULL;
    curr = p;

    min = curr->broj;
    while (curr != NULL)
    {
        if (curr->broj < min)
        {
            min = curr->broj;
        }
        curr = curr->next;
    }
    return min;

}
int maxVr(position p)
{
    int max = 0;
    position curr = NULL;
    curr = p;

    max = curr->broj;
    while (curr != NULL)
    {
        if (curr->broj > max)
        {
            max = curr->broj;
        }
        curr = curr->next;
    }
    return max;

}

int prebaciNaKraj(position p, int srednja)
{
    position prev = NULL, curr = NULL, zadnji = NULL;
    zadnji = nadjiZadnji(p);
    
    prev = p;
    curr = prev->next;

    while (curr != zadnji)
    {
        if (curr->broj > srednja)
        {
            prev->next = curr->next;
            curr->next = zadnji->next;
            zadnji->next = curr;
        }
        else
        {
            prev = curr;
            curr = prev->next;
        }
        curr = prev->next;
    }

    return 0;
}

position nadjiZadnji(position p)
{
    while (p->next != NULL)
        p = p->next;

    return p;
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
