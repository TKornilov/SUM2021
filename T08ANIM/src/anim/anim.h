/*FILE NAME: anim.h  
  PROGRAMMER: TK3
  DATE:18.06.2021
*/ 
#ifndef __anim_h_
#define  __anim_h_
#include "../def.h"
extern INT TK3_MouseWheel;
VOID TK3_AnimInit( HWND hWnd );
VOID TK3_AnimClose( VOID );
VOID TK3_AnimResize( INT W, INT H );
VOID TK3_AnimCopyFrame( HDC hDC );
VOID TK3_AnimRender( VOID );
VOID TK3_AnimAddUnit( tk3UNIT *Uni );
VOID TK3_AnimFlipFullScreen( VOID );
VOID TK3_AnimExit( VOID );
VOID TimerInit( VOID );
VOID TimerResponse( VOID );
#endif /*__anim_h_*/
/*End of "anim.h" file" */