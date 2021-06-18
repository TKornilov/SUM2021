/*FILE NAME: t07globe.c   
  PROGRAMMER: TK3
  DATE:15.06.2021
*/
#include <stdio.h>
#include <windows.h>
#include <math.h>

#include "globe.h"
#include "MTH.h"
#include "timer.h"
#define WND_CLASS_NAME "Summer practice"

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam );

/*Window Initialization*/
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
  wc.lpfnWndProc = MyWindowFunc;
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

/*Reaction to windows messages*/
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam )
{
  PAINTSTRUCT ps;
  HDC hDC;
  static HDC hMemDC;
  static HBITMAP hBm;
  INT x = 0, y = 0;
  HFONT hFnt;
  static CHAR Buf[100], Buf1[100];
  static INT w, h;
  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 10, NULL);
    hDC = GetDC(hWnd);
    hMemDC  = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    GLB_TimerInit();
    return 0;
  case WM_KEYDOWN:
    if(VK_SPACE)
      GLB_IsPause = !GLB_IsPause;
  case WM_TIMER:
    GLB_TimerResponse();
    hDC = GetDC(hWnd);
    SelectObject(hMemDC, GetStockObject(GRAY_BRUSH));
    Rectangle(hMemDC, -1, -1, w + 3, h + 3);
    GlobeDraw(hMemDC);
    if(GLB_IsPause)
    {
      RECT rc = {0, 0, w, h};

      hFnt = CreateFont(100, 0, 0, 0, FW_BOLD, 
                      TRUE, FALSE, FALSE, RUSSIAN_CHARSET, 
                      OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
                      PROOF_QUALITY, VARIABLE_PITCH | FF_ROMAN, 
                      "TIMES");
      SelectObject(hMemDC, hFnt);
      SetTextColor(hMemDC, RGB(0, 225, 225));
      SetBkMode(hMemDC, TRANSPARENT);
      TextOut(hMemDC, w  / 5 * 2, h / 2, Buf1, sprintf(Buf1, "PAUSE", GLB_FPS));
    }
    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    SetBkMode(hDC, TRANSPARENT);
    TextOut(hDC, 8, 8, Buf, sprintf(Buf, "FPS: %.3f", GLB_FPS));
    ReleaseDC(hWnd, hDC); 
    return 0;                                                                                                 
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, w, h);
    GlobeSet(w / 2, h / 2, 1);
    ReleaseDC(hWnd, hDC); 
    SelectObject(hMemDC, hBm);
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    SelectObject(hMemDC, GetStockObject(GRAY_BRUSH));   
    Rectangle(hMemDC, -1, -1, w + 3, h + 3);
    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_DESTROY:
    if(hBm != NULL)
      DeleteObject(hBm);
    DeleteObject(hMemDC);
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}
/*End of t07globe.c file*/