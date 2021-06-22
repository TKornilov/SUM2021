/*FILE NAME: rndprim.c  
  PROGRAMMER: TK3
  DATE:21.06.2021
*/

#include <ctype.h>
#include <string.h>
#include "rnd.h"

/*Creates a primitive*/
BOOL TK3_RndPrimCreate( tk3PRIM *Pr, INT NoofV, INT NoofI )
{
  INT size;

  memset(Pr, 0, sizeof(tk3PRIM));   
  size = sizeof(tk3VERTEX) * NoofV + sizeof(INT) * NoofI;

  if ((Pr->V = malloc(size)) == NULL)
    return FALSE;
  Pr->I = (INT *)(Pr->V + NoofV);
  Pr->NumOfV = NoofV;
  Pr->NumOfI = NoofI;
  Pr->Trans = MatrIdentity();
  memset(Pr->V, 0, size);

  return TRUE;
}

/*Destroys a primitive*/
VOID TK3_RndPrimFree( tk3PRIM *Pr )
{
  if (Pr->V != NULL)
    free(Pr->V);
  memset(Pr, 0, sizeof(tk3PRIM));
}

/*Draws a primitive on the screen*/
VOID TK3_RndPrimDraw( tk3PRIM *Prim, MATR World )
{
  POINT *Proj;
  INT i;
  MATR wvp = MatrMulMatr(World, TK3_RndMatrVP);

  if ((Proj = malloc(sizeof(POINT) * Prim->NumOfV)) == NULL)
    return;

  /* Send matrix to OpenGL /v.1.0 */
  glLoadMatrixf(wvp.M[0]);
  /* Draw triangles */
  glBegin(GL_TRIANGLES);
  for (i = 0; i < Prim->NumOfI; i++)
  {
    if(i < Prim->NumOfI / 4)
      glColor3d(1.0, 1.0, 1.0);
    else if(i < Prim->NumOfI / 2)
      glColor3d(0.0, 0.0, 1.0);
    else if(i < Prim->NumOfI / 4 * 3)
      glColor3d(0.0, 1.0, 0.0);
    else
      glColor3d(1.0, 0.0, 0.0); 
    glVertex3fv(&Prim->V[Prim->I[i]].P.X);
  }
  glEnd();
  

  /*for (i = 0; i < Prim->NumOfV; i++)
  {
    VEC P = MulMatr(Prim->V[i].P, wvp);

    Proj[i].x = (INT)((P.X + 1) * TK3_RndFrameW / 2);
    Proj[i].y = (INT)((-P.Y + 1) * TK3_RndFrameH / 2);
  }

  for (i = 0; i < Prim->NumOfI; i += 3)
  {
    POINT p[3];

    p[0] = Proj[Prim->I[i]];
    p[1] = Proj[Prim->I[i + 1]];
    p[2] = Proj[Prim->I[i + 2]];
    Polygon(TK3_hRndDC, p, 3);
  } */
}


BOOL TK3_RndPrimLoad( tk3PRIM *Pr, CHAR *FileName )
{
  FILE *F;
  INT i, nv = 0, nind = 0;
  static CHAR Buf[1000];

  memset(Pr, 0, sizeof(tk3PRIM));
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count vertexes and indexes */
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0;

      for (i = 1; Buf[i] != 0; i++)
        if (Buf[i - 1] == ' ' && Buf[i] != ' ')
          n++;
      nind += (n - 2) * 3;
    }
  }

  if (!TK3_RndPrimCreate(Pr, nv, nind))
  {
    fclose(F);
    return FALSE;
  }

  /* Load primitive */
  rewind(F);
  nv = 0;
  nind = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      Pr->V[nv++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0, n0, n1, nc;

      for (i = 1; Buf[i] != 0; i++)
        if (Buf[i - 1] == ' ' && Buf[i] != ' ')
        {
          sscanf(Buf + i, "%i", &nc);
          nc--;

          if (n == 0)
            n0 = nc;
          else if (n == 1)
            n1 = nc;
          else
          {
            Pr->I[nind++] = n0;
            Pr->I[nind++] = n1;
            Pr->I[nind++] = nc;
            n1 = nc;
          }
          n++;
        }
    }
  }

  fclose(F);
  return TRUE;
} 
/* Load primitive from '*.OBJ' file function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       vg4PRIM *Pr;
 *   - '*.OBJ' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
/*BOOL TK3_RndPrimLoad( tk3PRIM *Pr, CHAR *FileName )
{
  INT nv, nf;
  tk3VERTEX VertV;
  FILE *F;
  CHAR Buf[1000];

  memset(Pr, 0, sizeof(tk3PRIM));
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;
  nv = nf = 0;
  while (fgets(Buf, sizeof(Buf), F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if(Buf[0] == 'f' && Buf[1] == ' ')
      nf++;
  if(!TK3_RndPrimCreate(Pr, nv, nf))
  {
    fclose(F);
    return FALSE;
  }

  rewind(F);
  nv = nf = 0;
  while (fgets(Buf, sizeof(Buf), F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      VertV.P = VecSet(x, y, z);
      Pr->V[nv++] = VertV;
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n, n1, n2, n3;
      CHAR
        *f1 = "%d %d %d",
        *f2 = "%d/%*d %d/%*d %d/%*d",
        *f3 = "%d//%*d %d//%*d %d//%*d",
        *f4 = "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d";

      sscanf(Buf + 2, f4, &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, f3, &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, f2, &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, f1, &n1, &n2, &n3) == 3;
      Pr->I[nf++] = n1 - 1;
      Pr->I[nf++] = n2 - 1;
      Pr->I[nf++] = n3 - 1;
    }
    fclose(F);
    return TRUE;
}

/*End of 'rndprim.c' file*/