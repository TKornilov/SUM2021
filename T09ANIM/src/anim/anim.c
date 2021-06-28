/*FILE NAME: anim.c 
  PROGRAMMER: TK3
  DATE:21.06.2021
*/

#include "anim.h"

tk3ANIM TK3_Anim;

VOID TK3_AnimInit( HWND hWnd )
{
  memset(&TK3_Anim, 0, sizeof(&TK3_Anim));

  TK3_Anim.hWnd = hWnd;
  TK3_RndInit(hWnd);

  TK3_TimerInit();
  TK3_AnimInputInit();
}
VOID TK3_AnimClose( VOID )
{
  INT i;
  for (i = 0; i < TK3_Anim.NumOfUnits; i++)
  {
    TK3_Anim.Units[i]->Close(TK3_Anim.Units[i], &TK3_Anim);
    free(TK3_Anim.Units[i]);
    TK3_Anim.Units[i] = NULL;
  }
  TK3_Anim.NumOfUnits = 0;
  TK3_RndClose();
}
VOID TK3_AnimResize( INT W, INT H )
{
  TK3_Anim.W = W;
  TK3_Anim.H = H;
  TK3_RndResize(W, H);
}
VOID TK3_AnimCopyFrame( VOID )
{
  TK3_RndCopyFrame();
}
VOID TK3_AnimRender( VOID )
{
  INT i;

  TK3_TimerResponse();
  TK3_AnimInputResponse();
  
  /*for (i = 0; i < TK3_Anim.NumOfUnits; i++)
    TK3_Anim.Units[i]->Init(TK3_Anim.Units[i], &TK3_Anim);*/ 
  for (i = 0; i < TK3_Anim.NumOfUnits; i++)
    TK3_Anim.Units[i]->Response(TK3_Anim.Units[i], &TK3_Anim);               

  TK3_RndStart();
  for (i = 0; i < TK3_Anim.NumOfUnits; i++)
    TK3_Anim.Units[i]->Render(TK3_Anim.Units[i], &TK3_Anim);
  TK3_RndEnd();
}
VOID TK3_AnimAddUnit( tk3UNIT *Uni )
{
  if (TK3_Anim.NumOfUnits < TK3_MAX_UNITS)
    TK3_Anim.Units[TK3_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &TK3_Anim);
}
VOID TK3_AnimFlipFullScreen( VOID )
{
}
VOID TK3_AnimExit( VOID )
{
}
/*End of "anim.c" file" */