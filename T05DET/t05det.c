/*FILE NAME: t05det.c   
  PROGRAMMER: TK3
  DAY:12.06.2021
  */
#include <stdio.h>
#include <windows.h>

typedef DOUBLE DBL;

#define MAX 10
DBL A[MAX][MAX];
INT N;
DBL prod = 1.0, Determinant = 0.0;

INT P[MAX];
BOOL IsParity;

/*Replaces two numbers with each other*/
VOID Swap( INT *a, INT *b )
{
  INT temp;

  temp = *a;
  *a = *b;
  *b = temp;
}


VOID f( INT Pos )
{
  int i;

  if (Pos == N)
  {
    for (i = Pos; i < N; i++)
      prod *= A[i][P[i]];
    Determinant += (IsParity * 2 - 1) * prod;
  }
  else
    for (i = Pos; i < N; i++)
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


BOOL LoadMatrix( CHAR *FileName )
{
  FILE *F;
  INT i, j;

  N = 0;
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;
  
  fscanf(F, "%d", &N);
  if (N < 0)
    N = 0;
  else
    if (N > MAX)
      N = MAX;

  for(i = 0; i < N; i++)
    for(j = 0; j < N; j ++)
      fscanf(F, "%lf", &A[i][j]);

  fclose(F);
  return TRUE;
}

VOID main ( VOID )
{
  INT i;

  if (LoadMatrix("m1.txt"))
  {
    IsParity = 1;
    for (i = 0; i < N; i++)
      P[i] = i + 1;
    f(0);
    printf("%lf", Determinant);
    getchar();
  }
}

/*End of t05det.c file*/