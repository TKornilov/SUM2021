/*FILE NAME: rnd.h   
  PROGRAMMER: TK3
  DATE:21.06.2021
*/
#ifndef __rnd_h_
#define __rnd_h_

#define GLEW_STATIC
#include <glew.h>
#include "../../def.h"
#define TK3_MAX_SHADERS 30
#define TK3_STR_MAX 300

typedef struct tagtk3VERTEX
{
  VEC P, N;
  VEC2 T;
  VEC4 C;
} tk3VERTEX; /*3d Vector for primitives*/
typedef enum tagtk3PRIM_TYPE
{
  TK3_RND_PRIM_TRIMESH,  /* Triangle mesh - array of triangles */
  TK3_RND_PRIM_TRISTRIP, /* Triangle strip - array of stripped triangles */
  TK3_RND_PRIM_LINES,    /* Line segments (by 2 points) */
  TK3_RND_PRIM_POINTS,   /* Arrauy of points */
} tk3PRIM_TYPE;


/* Primitive representation type */
typedef struct tagtk3PRIM
{
  tk3PRIM_TYPE Type; /* Primitive type */
  INT
    VA,              /* Vertex array Id */
    VBuf,            /* Vertex buffer Id */
    IBuf;            /* Index buffer Id (if 0 - use only vertex buffer) */
  INT NumOfElements; /* Number of indices/vecrtices */

  MATR Trans;   /* Additional transformation matrix */
} tk3PRIM;
typedef struct tagtk3SHADER
{
  INT ProgId;
  CHAR Name[TK3_MAX_SHADERS];
} tk3SHADER;

extern tk3SHADER TK3_RndShaders[TK3_MAX_SHADERS];
extern HWND TK3_hRndWnd;
extern HDC TK3_hRndDC;
extern HGLRC TK3_hRndGLRC;
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
VOID TK3_RndCopyFrame( VOID );
VOID TK3_RndCamSet( VEC Loc, VEC At, VEC Up );
VOID TK3_RndPrimCreate( tk3PRIM *Pr, tk3VERTEX *V, INT NumOfV, INT *I, INT NumOfI );
VOID TK3_RndPrimFree( tk3PRIM *Pr );
VOID TK3_RndPrimDraw( tk3PRIM *Prim, MATR World );
BOOL TK3_RndPrimLoad( tk3PRIM *Pr, CHAR *FileName );
VOID TK3_RndShadersInit( VOID );
VOID TK3_RndShadersClose( VOID );
VOID TK3_RndShdFree( INT ProgId );


#endif /*__rnd_h*/

/*End of 'rnd.h' file*/