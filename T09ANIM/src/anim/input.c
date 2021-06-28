/*FILE NAME: timer.c 
  PROGRAMMER: TK3
  DATE:21.06.2021
*/

#include <string.h>

#include "anim.h"
#include <mmsystem.h>

INT TK3_MouseWheel = 0;

VOID TK3_AnimMouseInit( VOID )
{
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(TK3_Anim.hWnd, &pt);
}

VOID TK3_AnimMouseResponse( VOID )
{
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(TK3_Anim.hWnd, &pt);
  TK3_Anim.Mdx = pt.x - TK3_Anim.Mx;
  TK3_Anim.Mdy = pt.y - TK3_Anim.My;
  TK3_Anim.Mx = pt.x;
  TK3_Anim.My = pt.y;
  TK3_Anim.Mdz = TK3_MouseWheel;
  TK3_Anim.Mz += TK3_MouseWheel;
  TK3_MouseWheel = 0;
}

VOID TK3_AnimKeyboardInit( VOID )
{
  INT i;

  GetKeyboardState(TK3_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    TK3_Anim.Keys[i] >>= 7;
    TK3_Anim.KeysClick[i] = TK3_Anim.Keys[i] && !TK3_Anim.KeysOld[i]; 
  }

  memcpy(TK3_Anim.KeysOld, TK3_Anim.Keys, 256);
}

VOID TK3_AnimKeyboardResponse( VOID )
{
  INT i;
  GetKeyboardState(TK3_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    TK3_Anim.Keys[i] >>= 7;
    TK3_Anim.KeysClick[i] = TK3_Anim.Keys[i] && !TK3_Anim.KeysOld[i]; 
  }

  memcpy(TK3_Anim.KeysOld, TK3_Anim.Keys, 256);
}

VOID TK3_AnimJoystickInit( VOID )
{
  
}

VOID TK3_AnimJoystickResponse( VOID )
{
  
}

VOID TK3_AnimInputInit( VOID )
{
  TK3_AnimKeyboardInit();
  TK3_AnimMouseInit();
  TK3_AnimJoystickInit();
}

VOID TK3_AnimInputResponse( VOID )
{
  TK3_AnimKeyboardResponse();
  TK3_AnimMouseResponse();
  TK3_AnimJoystickResponse();
}
/*POINT pt;
  GetCursorPos(&pt);
  ScreenToClient(hWnd, &pt);
  TK3_Anim.Mdx = pt.x - TK3_Anim.Mx;
  TK3_Anim.Mdy = pt.y - TK3_Anim.My;
  TK3_Anim.Mx = pt.x;
  TK3_Anim.My = pt.y;
  TK3_Anim.Mdz = TK3_MouseWheel;
  TK3_Anim.Mz += TK3_MouseWheel;
  TK3_MouseWheel = 0;
/*End of "timer.c" file" */