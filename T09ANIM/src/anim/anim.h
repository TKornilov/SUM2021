/*FILE NAME: anim.h  
  PROGRAMMER: TK3
  DATE:21.06.2021
*/ 
#ifndef __anim_h_
#define  __anim_h_
#include "../def.h"
extern INT TK3_MouseWheel;
VOID TK3_AnimInit( HWND hWnd );
VOID TK3_AnimClose( VOID );
VOID TK3_AnimResize( INT W, INT H );
VOID TK3_AnimCopyFrame( VOID );
VOID TK3_AnimRender( VOID );
VOID TK3_AnimAddUnit( tk3UNIT *Uni );
VOID TK3_AnimFlipFullScreen( VOID );
VOID TK3_AnimExit( VOID );
VOID TK3_TimerInit( VOID );
VOID TK3_TimerResponse( VOID );
VOID TK3_AnimInputInit( VOID );
VOID TK3_AnimInputResponse( VOID );
//static VOID TK3_UnitControlResponse( tk3UNIT_CONTROL *Uni, tk3ANIM *Ani );
#endif /*__anim_h_*/
/*End of "anim.h" file" */