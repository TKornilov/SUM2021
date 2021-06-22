/*FILE NAME: MTH.h  
  PROGRAMMER: TK3
  DATE:21.06.2021
*/

#ifndef __MTH_h_
#define  __MTH_h_

#pragma warning(disable: 4244 4305)

#include <windows.h>
#include <math.h>

/* Pi math constant */
#define PI 3.14159265358979323846
/* Degrees to radians conversion */
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)

/* Base double type shortened name */
typedef double DBL;
typedef float FLT;
/* 2d vector definition */
typedef struct tagVEC2
{
  FLT X, Y;
} VEC2;
/* 3d vector definition */
typedef struct tagVEC
{
  FLT X, Y, Z;
} VEC;
/* 4d vector definition */
typedef struct tagVEC4
{
  FLT X, Y, Z, W;
} VEC4;
/* 4d matrix definition */
typedef struct tagMATR
{
  FLT M[4][4];
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
__inline VEC VecSet( FLT X, FLT Y, FLT Z )
{
  VEC v = {X, Y, Z};

  return v;
}

/*Creates a 2d vector*/
__inline VEC2 Vec2Set( FLT X, FLT Y, FLT Z )
{
  VEC2 v = {X, Y};

  return v;
}

/*Creates a 4d vector*/
__inline VEC4 Vec4Set( FLT X, FLT Y, FLT Z, FLT W )
{
  VEC4 v = {X, Y, Z, W};

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
__inline VEC VecMulNum ( VEC V, FLT N )
{
  return VecSet(V.X * N, V.Y  * N, V.Z * N);
}

/*Divides a 3d vector by a number*/
__inline VEC VecDivNum ( VEC V, FLT N )
{
  return VecSet(V.X / N, V.Y  / N, V.Z / N);
}

/*Creates an opposite vector of a 3d vector*/
__inline VEC VecNeg ( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
}

/*Dot product of two 3d vectors*/
__inline FLT VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
}

/*Cross product of two 3d vectors*/
__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);  
}

/*Length of a 3d vector*/
__inline FLT VecLen( VEC V )  
{
  FLT len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return len;
  return sqrt(len);
}

/*Square length of a 3d vector*/
__inline FLT VecLen2( VEC V )  
{
  FLT len =  VecDotVec(V, V);

  return len;
}

/*Creates a 3d vector with the same direction as the initial and a length of one*/
__inline VEC VecNormalize( VEC V )  
{
  FLT len = VecDotVec(V, V);

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
  FLT w = V.X * M.M[0][3] + V.Y * M.M[1][3] + V.Z * M.M[2][3] + M.M[3][3];
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

/*Defines a matrix*/
__inline MATR MatrSet( FLT DBL00, FLT DBL01, FLT DBL02, FLT DBL03, 
                       FLT DBL10, FLT DBL11, FLT DBL12, FLT DBL13, 
                       FLT DBL20, FLT DBL21, FLT DBL22, FLT DBL23, 
                       FLT DBL30, FLT DBL31, FLT DBL32, FLT DBL33 )
{
  MATR m =
  {
    {
      {DBL00, DBL01, DBL02, DBL03},
      {DBL10, DBL11, DBL12, DBL13},
      {DBL20, DBL21, DBL22, DBL23},
      {DBL30, DBL31, DBL32, DBL33}
    }  
  };

  return(m);
    
}

/*Scales a vector into the dioganal of 3d matrix*/
__inline MATR MatrScale( VEC S )
{
  MATR M;
  M = MatrSet(S.X, 0.0, 0.0, 0.0,
              0.0, S.Y, 0.0, 0.0,
              0.0, 0.0, S.Z, 0.0,
              0.0, 0.0, 0.0, 1.0);
  return M;
}


/*Rotates a vector around x axis*/
__inline MATR MatrRotateX( FLT AngleInDegree )
{
  FLT a = D2R(AngleInDegree), s = sin(a), c = cos(a);
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
__inline MATR MatrRotateY( FLT AngleInDegree )
{
  FLT a = D2R(AngleInDegree), s = sin(a), c = cos(a);
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
__inline MATR MatrRotateZ( FLT AngleInDegree )
{
  FLT a = D2R(AngleInDegree), s = sin(a), c = cos(a);
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
__inline MATR MatrRotate( FLT AngleInDegree, VEC V )
{
  FLT a = D2R(AngleInDegree), s = sin(a), c = cos(a);
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
      for (k = 0; k < 4; k++)
        r.M[i][j] += M1.M[i][k] * M2.M[k][j];
  return r;
}

/*Creates a natrix for viewing objects*/
__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC
    Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCrossVec(Dir, Up1)),
    Up = VecNormalize(VecCrossVec(Right, Dir));
  MATR m =
  {
    {
      {Right.X, Up.X, -Dir.X, 0}, {Right.Y, Up.Y, -Dir.Y, 0}, {Right.Z, Up.Z, -Dir.Z, 0},
      {-VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1}
    }
  };

  return m;
}

__inline MATR MatrOrto( FLT Left, FLT Right, FLT Bottom, FLT Top, FLT Near, FLT Far)
{
  MATR m =
  {
    {
      {2/ (Right - Left), 0, 0, 0}, 
      {0, 2 / (Top - Bottom), 0, 0}, 
      {0, 0, -2 / (Far - Near), 0},
      {-1 * (Right + Left) / (Right - Left), -1 * (Top + Bottom) / (Top - Bottom), -1 * (Far + Near) / (Far - Near), 1}
    }
  };

  return m;
} 

__inline MATR MatrFrustum( FLT Left, FLT Right, FLT Bottom, FLT Top, FLT Near, FLT Far)
{
  MATR m =
  {
    {
      {2 * Near / (Right - Left), 0, 0, 0}, 
      {0, 2  * Near / (Top - Bottom) , 0, 0}, 
      {(Right + Left) / (Right - Left), (Top + Bottom) / (Top - Bottom), -1 * (Far + Near) / (Far - Near), -1},
      {0, 0, -2 * Near * Far / (Far - Near), 0}
    }
  };

  return m;
} 

/*Swaps the lines and the columns of the matrix(transposition)*/
__inline MATR MatrTranspose( MATR M )
{
  return MatrSet(M.M[0][0], M.M[1][0], M.M[2][0], M.M[3][0],
                 M.M[0][1], M.M[1][1], M.M[2][1], M.M[3][1],
                 M.M[0][2], M.M[1][2], M.M[2][2], M.M[3][2],
                 M.M[0][3], M.M[1][3], M.M[2][3], M.M[3][3]);
}

/*Determinant of a 3d matrix*/
__inline FLT MatrDeterm3x3( FLT A11, FLT A12, FLT A13,
                   FLT A21, FLT A22, FLT A23,
                   FLT A31, FLT A32, FLT A33 )
{
  return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 -
         A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
}

/*Determinant of a 4d matrix*/
__inline FLT MatrDeterm( MATR M )
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
  FLT det = MatrDeterm(M);
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