/*FILE NAME: t04perm.c   
  PROGRAMMER: TK3
  DAY:12.06.2021
  */
#include <stdio.h>
#include <windows.h>
#define MAX 3
INT P[MAX];
BOOL IsParity;
INT x = 0;

/*Stores data to an empty file*/
VOID Store( VOID )
{
  FILE *F;
  INT i;

  F = fopen("PERM.TXT", "a");
  if (F == NULL)
    return;
  for (i = 0; i < MAX - 1; i++)
    fprintf(F, "%d, ", P[i]);
  fprintf(F, "%d - parity: %s\n", P[MAX - 1], IsParity ? "even" : "odd");
  fclose(F);
}

/*Replaces two numbers with each other*/
VOID Swap( INT *a, INT *b )
{
  INT temp;

  temp = *a;
  *a = *b;
  *b = temp;
}

/*Creates the changed lists*/
VOID f( INT Pos )
{
  int i;

  if (Pos == MAX)
    Store();
  else
    for (i = Pos; i < MAX; i++)
    {
      Swap(&P[Pos], &P[i]);
      if (Pos != i)
        if (IsParity == 1)
          IsParity = 0;
        else
          IsParity = 1;
      f(Pos + 1);
      Swap(&P[Pos], &P[i]);
      if (Pos != i)
        if (IsParity == 1)
          IsParity = 0;
        else
          IsParity = 1;
    }
}

VOID main( VOID )
{
  int i;

  IsParity = 1;
  for (i = 0; i < MAX; i++)
    P[i] = i + 1;
  f(0);
}
/*End of t04perm.c*/