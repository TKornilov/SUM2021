/*FILE NAME: MTH.h  
  PROGRAMMER: TK3
  DATE:15.06.2021
*/

#ifndef __MTH_h_
#define  __MTH_h_

#pragma warning(disable: 4244)

#include <windows.h>
#include <math.h>

/* Pi math constant */
#define PI 3.14159265358979323846
/* Degrees to radians conversion */
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)

/* Base double type shortened name */
typedef double DBL;
/* 3d vector definition */
typedef struct tagVEC
{
  DBL X, Y, Z;
} VEC;
/* 4d matrix definition */
typedef struct tagMATR
{
  DBL M[4][4];
} MATR;

static MATR UnitMatrix =
{
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1},
  }
};

/*Creates a 3d vector*/
__inline VEC VecSet( DBL X, DBL Y, DBL Z )
{
  VEC v = {X, Y, Z};

  return v;
}

/*Summs two 3d vectors*/
__inline VEC VecAddVec ( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
}

/*Substracts two 3d vectors*/
__inline VEC VecSubVec ( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
}

/*Multiplies a 3d vector on a number*/
__inline VEC VecMulNum ( VEC V, DBL N )
{
  return VecSet(V.X * N, V.Y  * N, V.Z * N);
}

/*Divides a 3d vector by a number*/
__inline VEC VecDivNum ( VEC V, DBL N )
{
  return VecSet(V.X / N, V.Y  / N, V.Z / N);
}

/*Creates an opposite vector of a 3d vector*/
__inline VEC VecNeg ( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
}

/*Dot product of two 3d vectors*/
__inline DBL VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
}

/*Cross product of two 3d vectors*/
__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);  
}

/*Length of a 3d vector*/
__inline DBL VecLen( VEC V )  
{
  DBL len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return len;
  return sqrt(len);
}

/*Square length of a 3d vector*/
__inline DBL VecLen2( VEC V )  
{
  DBL len =  VecDotVec(V, V);

  return len;
}

/*Creates a 3d vector with the same direction as the initial and a length of one*/
__inline VEC VecNormalize( VEC V )  
{
  DBL len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return V;
  return VecDivNum(V, sqrt(len));
}

/*Adds one vector to another*/
__inline VEC VecAddVecEq( VEC *VRes, VEC V2 )  
{
  VRes->X += V2.X;
  VRes->Y += V2.Y;
  VRes->Z += V2.Z;
  return *VRes;
}

/*Transforms a 3d vector by a matrix 3x3*/
__inline VEC VectorTransform( VEC V, MATR M )
{ 
  return VecSet(V.X * M.M[0][0] + V.Y * M.M[0][1] + V.Z * M.M[0][2], 
                V.X * M.M[1][0] + V.Y * M.M[1][1] + V.Z * M.M[1][2], 
                V.X * M.M[2][0] + V.Y * M.M[2][1] + V.Z * M.M[2][2]);
}

/*Transforms a 3d vector by a matrix 4x3*/
__inline VEC PointTransform( VEC V, MATR M )
{ 
  return VecSet(V.X * M.M[0][0] + V.Y * M.M[0][1] + V.Z * M.M[0][2] + M.M[3][0], 
                V.X * M.M[1][0] + V.Y * M.M[1][1] + V.Z * M.M[1][2] + M.M[3][1], 
                V.X * M.M[2][0] + V.Y * M.M[2][1] + V.Z * M.M[2][2] + M.M[3][2]);
}

/*Transforms a 3d vector by a matrix 4x4*/
__inline VEC MulMatr( VEC V, MATR M )
{ 
  DBL w = V.X * M.M[0][3] + V.Y * M.M[1][3] + V.Z * M.M[2][3] + M.M[3][3];
  return VecSet((V.X * M.M[0][0] + V.Y * M.M[0][1] + V.Z * M.M[0][2] + M.M[3][0]) / w, 
                (V.X * M.M[1][0] + V.Y * M.M[1][1] + V.Z * M.M[1][2] + M.M[3][1]) / w, 
                (V.X * M.M[2][0] + V.Y * M.M[2][1] + V.Z * M.M[2][2] + M.M[3][2]) / w);
}

/*Returns a Unit Matrix (which consists of zeros and a single diagonal of ones))*/
__inline MATR MatrIdentity( VOID )
{
  return UnitMatrix;
}

/*Translates a vector to a unit matrix*/
__inline MATR MatrTranslate( VEC T )
{
  MATR m = UnitMatrix;

  m.M[3][0] = T.X;
  m.M[3][1] = T.Y;
  m.M[3][2] = T.Z;
  return m;
}

__inline MATR MatrSet( DBL00, DBL01, DBL02, DBL03, 
                       DBL10, DBL11, DBL12, DBL13, 
                       DBL20, DBL21, DBL22, DBL23, 
                       DBL30, DBL31, DBL32, DBL33 )
{
  MATR m =
  {
    {
      {DBL00, 0, 0, 0},
      {0, DBL11, DBL12, 0},
      {0, DBL21, DBL22, 0},
      {0, 0, 0, 1}
    }  
  };

  return(m);
    
}

/*Scales a vector into the dioganal of 3d matrix*/
__inline MATR MatrScale( VEC S )
{
  return MatrSet(S.X, 0, 0, 0,
                 0, S.Y, 0, 0,
                 0, 0, S.Y, 0,
                 0, 0, 0, 1);
}


/*Rotates a vector around x axis*/
__inline MATR MatrRotateX( DBL AngleInDegree )
{
  DBL a = D2R(AngleInDegree), s = sin(a), c = cos(a);
  MATR m =
  {
    {
      {1, 0, 0, 0},
      {0, c, s, 0},
      {0, -s, c, 0},
      {0, 0, 0, 1}
    }  
  };

  return m;
}

/*Rotates a vector around y axis*/
__inline MATR MatrRotateY( DBL AngleInDegree )
{
  DBL a = D2R(AngleInDegree), s = sin(a), c = cos(a);
  MATR m =
  {
    {
      {c, 0, -s, 0},
      {0, 1, 0, 0},
      {s, 0, c, 0},
      {0, 0, 0, 1}
    }  
  };

  return m;
} 

/*Rotates a vector around z axis*/
__inline MATR MatrRotateZ( DBL AngleInDegree )
{
  DBL a = D2R(AngleInDegree), s = sin(a), c = cos(a);
  MATR m =
  {
    {
      {c, s, 0, 0},
      {-s, c, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
    }  
  };

  return m;
}

/*Rotates a vector without an axis*/
__inline MATR MatrRotate( DBL AngleInDegree, VEC V )
{
  DBL a = D2R(AngleInDegree), s = sin(a), c = cos(a);
  VEC A = VecNormalize(V);
  MATR m =
  {
    {
      {c + A.X * A.X * (1 - c), A.X * A.Y * (1 - c) + A.Z * s, A.X * A.Z * (1 - c) - (A.Y * s), 0},
      {A.X * A.Y * (1 - c) - A.Z * s, c + A.Y * A.Y * (1 - c), A.Y * A.Z * (1 - c) + A.X * s, 0},
      {A.Z * A.X * (1 - c) + A.Y * s, A.Z * A.Y * (1 - c) - A.X * s, c + A.Z * A.Z * (1 - c), 0},
      {0, 0, 0, 1}
    }  
  };

  return m;
}


/*Multiplication */
__inline MATR MatrMulMatr( MATR M1, MATR M2 ) 
{
  MATR r = {{{0}}};
  INT i, j, k;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (r.M[i][j] = 0, k = 0; k < 4; k++)
        r.M[i][j] += M1.M[i][k] * M2.M[k][j];
  return r;
}

__inline MATR MatrTranspose( MATR M )
{
  return MatrSet(M.M[0][0], M.M[1][0], M.M[2][0], M.M[3][0],
                 M.M[0][1], M.M[1][1], M.M[2][1], M.M[3][1],
                 M.M[0][2], M.M[1][2], M.M[2][2], M.M[3][2],
                 M.M[0][3], M.M[1][3], M.M[2][3], M.M[3][3]);
}

/*Determinant of a 3d matrix*/
__inline DBL MatrDeterm3x3( DBL A11, DBL A12, DBL A13,
                   DBL A21, DBL A22, DBL A23,
                   DBL A31, DBL A32, DBL A33 )
{
  return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 -
         A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
}

/*Determinant of a 4d matrix*/
__inline DBL MatrDeterm( MATR M )
{
  return
    M.M[0][0] * MatrDeterm3x3(M.M[1][1], M.M[1][2], M.M[1][3],
                               M.M[2][1], M.M[2][2], M.M[2][3],
                               M.M[3][1], M.M[3][2], M.M[3][3]) 
    - M.M[0][1] * MatrDeterm3x3(M.M[1][0], M.M[1][2], M.M[1][3],
                               M.M[2][0], M.M[2][2], M.M[2][3],
                               M.M[3][0], M.M[3][2], M.M[3][3]) 
    + M.M[0][2] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][3],
                               M.M[2][0], M.M[2][1], M.M[2][3],
                               M.M[3][0], M.M[3][1], M.M[3][3]) 
    - M.M[0][3] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][2],
                               M.M[2][0], M.M[2][1], M.M[2][2],
                               M.M[3][0], M.M[3][1], M.M[3][2]);
}

/*Creates an inverse version of a matrix*/
__inline MATR MatrInverse( MATR M )
{
  MATR r;
  DBL det = MatrDeterm(M);
  INT s, i, j, P[][3] = {{1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 2}};

  if (det == 0)
    return MatrIdentity();

  for (s = 1, i = 0; i < 4; i++)
    for (j = 0; j < 4; j++, s = -s)
      r.M[j][i] =
        s * MatrDeterm3x3(M.M[P[i][0]][P[j][0]], M.M[P[i][0]][P[j][1]], M.M[P[i][0]][P[j][2]],
                          M.M[P[i][1]][P[j][0]], M.M[P[i][1]][P[j][1]], M.M[P[i][1]][P[j][2]],
                          M.M[P[i][2]][P[j][0]], M.M[P[i][2]][P[j][1]], M.M[P[i][2]][P[j][2]]) / det;
  return r;
}



#endif /*  __MTH_h_ */
/*End of mth.h file*/