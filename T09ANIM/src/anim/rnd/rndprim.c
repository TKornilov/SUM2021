/*FILE NAME: rndprim.c  
  PROGRAMMER: TK3
  DATE:21.06.2021
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "../anim.h"

/* Primitive creation function.
 * ARGUMENTS:
 *   - primitive pointer:
 *       tk3PRIM *Pr;
 *   - vertex attributes array:
 *       tk3VERTEX *V;
 *   - number of vertices:
 *       INT NumOfV;
 *   - index array (for trimesh – by 3 ones, may be NULL)
 *       INT *I;
 *   - number of indices
 *       INT NumOfI;
 * RETURNS: None.
 */
VOID TK3_RndPrimCreate( tk3PRIM *Pr, tk3VERTEX *V, INT NumOfV, INT *I, INT NumOfI )
{
  memset(Pr, 0, sizeof(tk3PRIM));   /* <-- <string.h> */

  if (V != NULL && NumOfV != 0)
  {
    glGenBuffers(1, &Pr->VBuf);
    glGenVertexArrays(1, &Pr->VA);

    glBindVertexArray(Pr->VA);
    glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tk3VERTEX) * NumOfV, V, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(tk3VERTEX),
                          (VOID *)0); /* position */
    glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(tk3VERTEX),
                          (VOID *)sizeof(VEC)); /* texture coordinates */
    glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(tk3VERTEX),
                          (VOID *)(sizeof(VEC) + sizeof(VEC2))); /* normal */
    glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(tk3VERTEX),
                          (VOID *)(sizeof(VEC) * 2 + sizeof(VEC2))); /* color */

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glBindVertexArray(0);
  }

  if (I != NULL && NumOfI != 0)
  {
    glGenBuffers(1, &Pr->IBuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NumOfI, I, GL_STATIC_DRAW);
    Pr->NumOfElements = NumOfI;
  }
  else
    Pr->NumOfElements = NumOfV;
  Pr->Trans = MatrIdentity();
  
} /* End of 'TK3_RndPrimCreate' function */

/*Destroys a primitive*/
VOID TK3_RndPrimFree( tk3PRIM *Pr )
{
  glBindVertexArray(Pr->VA);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &Pr->VBuf);

  glBindVertexArray(0);
  glDeleteVertexArrays(1, &Pr->VA);
}

/*Draws a primitive on the screen*/
VOID TK3_RndPrimDraw( tk3PRIM *Prim, MATR World )
{
  /*POINT *Proj;
  INT i;    */
  MATR wvp = MatrMulMatr(World, MatrMulMatr(TK3_RndMatrView, TK3_RndMatrProj));
  INT ProgId = TK3_RndShaders[0].ProgId;
  INT loc;
  INT gl_prim_type = Prim->Type == TK3_RND_PRIM_LINES ? GL_LINES :
                   Prim->Type == TK3_RND_PRIM_TRIMESH ? GL_TRIANGLES :
                   Prim->Type == TK3_RND_PRIM_TRISTRIP ? GL_TRIANGLE_STRIP :
                   GL_POINTS;
  glUseProgram(ProgId = 0);

  if ((loc = glGetUniformLocation(ProgId, "MatrWVP")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, wvp.M[0]);
  if ((loc = glGetUniformLocation(ProgId, "Time")) != -1)
    glUniform1f(loc, TK3_Anim.Time);

  glLoadMatrixf(wvp.M[0]);
  glBindVertexArray(Prim->VA);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Prim->IBuf);
  glDrawElements(gl_prim_type, Prim->NumOfElements, GL_UNSIGNED_INT, NULL);
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glUseProgram(0);
}


/* Load primitive from '*.OBJ' file function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       tk3PRIM *Pr;
 *   - '*.OBJ' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL TK3_RndPrimLoad( tk3PRIM *Pr, CHAR *FileName )
{
  FILE *F;
  INT i, nv = 0, nind = 0, size;
  tk3VERTEX *V;
  INT *Ind;
  static CHAR Buf[10000];
  VEC L;
  FLT nl;
  FLT r = 0, g = 1.0, b = 1.0;

  L.X = 1.0;
  L.Y = 1.0;
  L.Z = 1.0;
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
        if (isspace((UCHAR)Buf[i - 1]) && !isspace((UCHAR)Buf[i]))
          n++;
      nind += (n - 2) * 3;
    }
  }

  size = sizeof(tk3VERTEX) * nv + sizeof(INT) * nind;
  if ((V = malloc(size)) == NULL)
    return FALSE;
  Ind = (INT *)(V + nv);
  memset(V, 0, size);

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
      V[nv++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0, n0, n1, nc;

      for (i = 1; Buf[i] != 0; i++)
        if (isspace((UCHAR)Buf[i - 1]) && !isspace((UCHAR)Buf[i]))
        {
          sscanf(Buf + i, "%i", &nc);
          if (nc < 0)
            nc = nv + nc;
          else
            nc--;

          if (n == 0)
            n0 = nc;
          else if (n == 1)
            n1 = nc;
          else
          {
            Ind[nind++] = n0;
            Ind[nind++] = n1;
            Ind[nind++] = nc;
            n1 = nc;
          }
          n++;
        }
    }
  }
  for (i = 0; i < nv; i++)
      V[i].N = VecSet(0, 0, 0);
  for (i = 0; i < nind; i += 3)
    {
      VEC
        p0 = V[Ind[i]].P,
        p1 = V[Ind[i + 1]].P,
        p2 = V[Ind[i + 2]].P,
        N = VecNormalize(VecCrossVec(VecSubVec(p1, p0), VecSubVec(p2, p0)));

      V[Ind[i]].N = VecAddVec(V[Ind[i]].N, N); /* VecAddVecEq(&V[Ind[i]].N, N); */
      V[Ind[i + 1]].N = VecAddVec(V[Ind[i + 1]].N, N);
      V[Ind[i + 2]].N = VecAddVec(V[Ind[i + 2]].N, N);
    }
  for (i = 0; i < nv; i++)
  {
    V[i].N = VecNormalize(V[i].N);
    nl = VecDotVec(V[i].N, L);
    if (nl < 0.1)
      nl = 0.1;
    V[i].C = Vec4Set(r * nl, g * nl, b * nl, 1);
  }
  fclose(F);
  TK3_RndPrimCreate(Pr, V, nv, Ind, nind);
  free(V);
  return TRUE;
} /* End of 'TK3_RndPrimLoad' function */
/* Load primitive from '*.OBJ' file function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       tk3PRIM *Pr;
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