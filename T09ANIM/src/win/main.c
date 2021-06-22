/*FILE NAME: main.c   
  PROGRAMMER: TK3
  DATE:21.06.2021
*/
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <time.h>


#include "../def.h"
#define WND_CLASS_NAME "Summer practice"

tk3ANIM TK3_Anim;

LRESULT CALLBACK TK3_WindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam );

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstansce, 
                    CHAR *CmdLine, int ShowCmd)
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);       
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = TK3_WindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;
  
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "Error", MB_OK | MB_ICONERROR);
    return 0;
  }

  hWnd = 
    CreateWindow(WND_CLASS_NAME,
      "Title",
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT,
      NULL, NULL,
      hInstance, NULL);

  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  while (TRUE)
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      DispatchMessage(&msg);
    }
    else
    {
      TK3_AnimRender();
      TK3_RndCopyFrame();
    }
  return msg.wParam;
}

/* Window handle function.
 * ARGUMENTS:
 *   - window handle:
 *      HWND hWnd;
 *   - message type (see WM_***):
 *      UINT Msg;
 *   - message 'word' parameter:
 *      WPARAM wParam;
 *   - message 'long' parameter:
 *      LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message depending on return value.
 */
LRESULT CALLBACK TK3_WindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam )
{
  INT x = 0, y = 0, i;
  static CHAR Buf[100];
  static INT w, h;


  switch (Msg)
  {
  case WM_MOUSEWHEEL:
    TK3_MouseWheel += (SHORT)HIWORD(wParam);
    return 0;
  case WM_CREATE:
   
    TK3_AnimInit(hWnd);                                                  
    TK3_Anim.Units[0] = TK3_AnimUnitCowCreate();
    TK3_Anim.Units[1] = TK3_AnimUnitControlCreate();
    TK3_Anim.Units[2] = TK3_AnimUnitRomanCreate();
    for (i = 0; i < TK3_Anim.NumOfUnits; i++)
      TK3_Anim.Units[i]->Init(TK3_Anim.Units[i], &TK3_Anim);
    TK3_RndCamSet(VecSet(5, 200, 200), VecSet(0, 0, 0), VecSet(0, 1, 0));
   
    return 0;
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    else if (wParam == VK_SPACE)
      TK3_Anim.IsPause = !TK3_Anim.IsPause;
    /*GetKeyboardState(TK3_Anim.Keys);
    for (i = 0; i < 256; i++)
    {
      TK3_Anim.Keys[i] >>= 7;
      TK3_Anim.KeysClick[i] = TK3_Anim.Keys[i] && !TK3_Anim.KeysOld[i];   
    }
    memcpy(TK3_Anim.KeysOld, TK3_Anim.Keys, 256);*/   
    return 0;
  case WM_TIMER:
    TK3_RndCopyFrame();
    return 0;
  case WM_SIZE:
    TK3_RndResize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  case WM_PAINT:
    TK3_AnimRender();
    TK3_RndCopyFrame();
    return 0;
  case WM_DESTROY:
    //TK3_AnimClose();
    KillTimer(hWnd, 30);
    TK3_RndClose();
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}
/*End of 'main.c' file*/