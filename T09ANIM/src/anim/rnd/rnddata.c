/*FILE NAME: rnddata.c  
  PROGRAMMER: TK3
  DATE:21.06.2021
*/

#include "rnd.h"

HWND TK3_hRndWnd; 
HDC TK3_hRndDC;
HGLRC TK3_hRndGLRC;
INT TK3_RndFrameW, TK3_RndFrameH;

DBL
  TK3_RndProjSize = 0.1,  /* Project plane fit square */
  TK3_RndProjDist = 0.1,  /* Distance to project plane from viewer (near) */
  TK3_RndProjFarClip = 300; /* Distance to project far clip plane (far) */

MATR
  TK3_RndMatrView, /* View coordinate system matrix */
  TK3_RndMatrProj, /* Projection coordinate system matrix */
  TK3_RndMatrVP;   /* Stored (View * Proj) matrix */

/*End of 'rnddata.c' file*/