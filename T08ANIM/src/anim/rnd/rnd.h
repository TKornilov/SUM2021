/*FILE NAME: rnd.h   
  PROGRAMMER: TK3
  DATE:17.06.2021
*/
#ifndef __rnd_h_
#define __rnd_h_

#include "../../def.h"

typedef struct tagtk3VERTEX
{
 VEC P;
} tk3VERTEX; /*3d Vector for primitives*/

typedef struct tagtk3PRIM
{
 tk3VERTEX *V;
 INT NumOfV;
 INT *I;
 INT NumOfI;
 MATR Trans;
} tk3PRIM;  /*Ptimitive and the amount of vectors and matrixes defining it*/

extern HWND TK3_hRndWnd;
extern HDC TK3_hRndDCFrame;
extern HBITMAP TK3_hRndBmFrame;
extern INT TK3_RndFrameW, TK3_RndFrameH;
extern DBL
  TK3_RndProjSize,
  TK3_RndProjDist,
  TK3_RndProjFarClip;
extern MATR
  TK3_RndMatrView,
  TK3_RndMatrProj,
  TK3_RndMatrVP;  

VOID TK3_RndInit( HWND hWnd );
VOID TK3_RndClose( VOID );
VOID TK3_RndStart( VOID );
VOID TK3_RndEnd( VOID );
VOID TK3_RndResize( INT W, INT H );
VOID TK3_RndProjSet( VOID );
VOID TK3_RndCopyFrame( HDC hDC );
VOID TK3_RndCamSet( VEC Loc, VEC At, VEC Up );
BOOL TK3_RndPrimCreate( tk3PRIM *Pr, INT NoofV, INT NoofI );
VOID TK3_RndPrimFree( tk3PRIM *Pr );
VOID TK3_RndPrimDraw( tk3PRIM *Prim, MATR World );
BOOL TK3_RndPrimLoad( tk3PRIM *Pr, CHAR *FileName );


#endif /*__rnd_h*/

/*End of 'rnd.h' file*/