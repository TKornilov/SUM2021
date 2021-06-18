/*FILE NAME: main.c   
  PROGRAMMER: TK3
  DATE:17.06.2021
*/
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <time.h>

#include "../def.h"
#define WND_CLASS_NAME "Summer practice"

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
      SendMessage(hWnd, WM_TIMER, 30, 0);

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
  HDC hDC;
  PAINTSTRUCT ps;
  INT x = 0, y = 0;
  static CHAR Buf[100];
  static INT w, h;
  static tk3PRIM Pr, Pr1;

  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 1, NULL);
    TK3_RndInit(hWnd);
    TK3_RndPrimLoad(&Pr, "med_house_final.obj");
    TK3_RndPrimLoad(&Pr1, "Roman_soldier.obj");
   /* TK3_RndPrimCreate(&Pr, 4, 6);
    Pr.V[0].P = VecSet(0, 0, 0);
    Pr.V[1].P = VecSet(2, 0, 0);
    Pr.V[2].P = VecSet(0, 2, 0);
    Pr.V[3].P = VecSet(2, 2, 0);
 
    Pr.I[0] = 0;
    Pr.I[1] = 1;
    Pr.I[2] = 2;

    Pr.I[3] = 2;
    Pr.I[4] = 1;
    Pr.I[5] = 3; */
    /*SetTimer(hWnd, 30, 10, NULL);
    hDC = GetDC(hWnd);
    ReleaseDC(hWnd, hDC);
    /*GLB_TimerInit();*/
    return 0;
  case WM_KEYDOWN:
    /*if(VK_SPACE)
      GLB_IsPause = !GLB_IsPause;*/
    return 0;
  case WM_TIMER:
    /*GLB_TimerResponse(); */
    TK3_RndStart();
    TK3_RndCamSet(VecSet(5, 200, 200), VecSet(0, 0, 0), VecSet(0, 1, 0));
    TK3_RndPrimDraw(&Pr, MatrRotateX(270));
    TK3_RndPrimDraw(&Pr1, MatrMulMatr(MatrScale(VecSet(1, 1, 1)), MatrRotateX(270)));
    TK3_RndEnd();

    hDC = GetDC(hWnd);
    TK3_RndCopyFrame(hDC);
    ReleaseDC(hWnd, hDC); 
    /* InvalidateRect(hWnd, NULL, FALSE); */
    return 0;
  case WM_SIZE:
   /* w = LOWORD(lParam);
    h = HIWORD(lParam);
    hDC = GetDC(hWnd);
    ReleaseDC(hWnd, hDC); */
    TK3_RndResize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    TK3_RndCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_DESTROY:
    KillTimer(hWnd, 30);
    TK3_RndPrimFree(&Pr);
    TK3_RndClose();
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}
/*End of 'main.c' file*/