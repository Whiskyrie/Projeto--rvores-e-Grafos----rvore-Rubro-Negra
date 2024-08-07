#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

/* ---------------------------------------- */
/* tipo de dado INT */
/* ---------------------------------------- */
int ComparaInt(void *info1, void *info2)
{
   int *p1 = (int *)info1;
   int *p2 = (int *)info2;
   return *p1 - *p2;
}
/* ---------------------------------------- */
void ImprimeInt(void *info)
{
   int *pi = (int *)info;
   printf("%d - ", *pi);
}
/* ---------------------------------------- */
void *AlocaInfoInt(void *info)
{
   int *pi = (int *)malloc(sizeof(int));
   *pi = *((int *)info);
   return pi;
}
/* ---------------------------------------- */
int *AlocaInt(int n)
{
   int *pi = (int *)malloc(sizeof(int));
   *pi = n;
   return pi;
}

void LiberaInt(void *info)
{
   int *pi = (int *)info;
   free(pi);
}

int MapeiaInt(void *xxx)
{

   return *((int *)xxx);
}

/* ---------------------------------------- */
/* tipo de dado STRUCT Data */
/* ---------------------------------------- */
struct Data
{
   int dia, mes, ano;
};
/* ---------------------------------------- */
int ComparaData(void *info1, void *info2)
{
   struct Data *p1 = (struct Data *)info1;
   struct Data *p2 = (struct Data *)info2;
   return ((p2->ano - p1->ano) * 365) +
          ((p2->mes - p1->mes) * 30) +
          (p2->dia - p1->dia);
}
/* ---------------------------------------- */
void ImprimeData(void *info)
{
   struct Data *pd = (struct Data *)info;
   printf("%d/%d/%d - ", pd->dia, pd->mes, pd->ano);
}
/* ---------------------------------------- */
void *AlocaInfoData(void *info)
{
   struct Data *pd = (struct Data *)malloc(sizeof(struct Data));
   pd->dia = ((struct Data *)info)->dia;
   pd->mes = ((struct Data *)info)->mes;
   pd->ano = ((struct Data *)info)->ano;
   return pd;
}
/* ---------------------------------------- */
struct Data *AlocaData(int dia, int mes, int ano)
{
   struct Data *pd = (struct Data *)malloc(sizeof(struct Data));
   pd->dia = dia;
   pd->mes = mes;
   pd->ano = ano;
   return pd;
}

#endif /* UTILS_H */
