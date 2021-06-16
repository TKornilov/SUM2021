/*FILE NAME: t03clock.c   
  PROGRAMMER: TK3
  DAY:11.06.2021
  */
#pragma warning(disable:4244)
#include <windows.h>
#include <math.h>
#include <stdio.h>
#define WND_CLASS_NAME "Summer pradctice"

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
  wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);       
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

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
}

/*Clock hand drawing through polygons*/
VOID DrawHand( HDC hDC, INT POLW, INT POLH, INT CENTX, INT CENTY )
{
  PINT *Pt;
  Polygon(hDC, *Pt, POLW + CENTX); 

}

/*Reaction to windows messages*/
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam )
{
  SYSTEMTIME st;
  PAINTSTRUCT ps;
  HPEN hPen, hPenOld, hPen2, hPenOld2;
  HDC hDC;
  HFONT hFnt;
  POINT pt;
  static HDC hMemDC, hLogoDC, hCoatDC;
  static HBITMAP hBm, hLogoBm, hCoatBm;
  INT x = 0, y = 0;
  LOGBRUSH lb;
  DOUBLE a;
  CHAR Buf[100];
  CHAR Week[7][3] = { "ÂÑ", "ÏÍ", "ÂÒ", "ÑÐ", "×Ò", "ÏÒ", "ÑÁ" };
  static INT w, h;
  switch (Msg)                  
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 100, NULL);
    hDC = GetDC(hWnd);
    hMemDC  = CreateCompatibleDC(hDC);
    hLogoDC  = CreateCompatibleDC(hDC);
    hCoatDC  = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    return 0;
  case WM_TIMER:
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    hDC = GetDC(hWnd);
    GetLocalTime(&st);
    sprintf(Buf, "%i.%i.%i, %s, %i:%i:%i, Ñàíêò-Ïåòåðáóðã", st.wDay, st.wMonth, st.wYear, Week[st.wDayOfWeek], 
                                                            st.wHour, st.wMinute, st.wSecond );
    lb.lbStyle = BS_SOLID;
    lb.lbHatch = HS_FDIAGONAL;
    lb.lbColor = RGB(30, 30, 30); 
    SelectObject(hDC, GetStockObject(DC_BRUSH));  
    SetDCBrushColor(hDC, RGB(255, 255, 255));
    Rectangle(hMemDC, -1, -1, w + 2, h + 2);
    hFnt = CreateFont(50, 0, 0, 0, FW_BOLD, 
                      TRUE, FALSE, FALSE, RUSSIAN_CHARSET, 
                      OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
                      PROOF_QUALITY, VARIABLE_PITCH | FF_ROMAN, 
                      "TIMES");
    SelectObject(hMemDC, hFnt);
    SetTextColor(hMemDC, RGB(0, 0, 0));
    TextOut(hMemDC, w / 2 - h / 4, h * 4 / 5, Buf, strlen(Buf));
    BitBlt(hMemDC, 200, 200, w, h, hCoatDC, 0, 0, SRCAND);
    BitBlt(hMemDC, w / 2 - h / 4, h / 4, w, h, hLogoDC, 0, 0, SRCCOPY);
    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    hPen = ExtCreatePen(PS_GEOMETRIC | PS_SOLID, 1, &lb, 0, NULL);
    hPenOld = SelectObject(hDC, hPen);
    MoveToEx(hDC, w / 2, h / 2, NULL);                                            
    a = st.wSecond / 60.0 * 2 * 3.1415926;
    LineTo(hDC, w / 2 + sin(a) * h / 50 * 11, h / 2 - cos(a) * h / 50 * 11);
    hPen2 = ExtCreatePen(PS_GEOMETRIC | PS_SOLID, 4, &lb, 0, NULL);
    hPenOld2 = SelectObject(hDC, hPen2);
    MoveToEx(hDC, w / 2, h / 2, NULL);
    a = (st.wMinute + st.wSecond / 75.0) / 60.0 * 2 * 3.1415926;
    LineTo(hDC, w / 2 + sin(a) * h / 5, h / 2 - cos(a) * h / 5);
    MoveToEx(hDC, w / 2, h / 2, NULL);
    a = (st.wHour % 12 + st.wMinute / 60.0) / 12.0 * 2 * 3.1415926;
    LineTo(hDC, w / 2 + sin(a) * h / 20 * 3, h / 2 - cos(a) * h / 20 * 3);
    SelectObject(hDC, hPenOld);
    SelectObject(hDC, hPenOld2);
    ReleaseDC(hWnd, hDC);
    DeleteObject(hPen);
    DeleteObject(hPen2);
    return 0;
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, w, h); 
    hLogoBm = LoadImage(NULL, "Clockface.bmp", IMAGE_BITMAP, h / 2, h / 2, LR_LOADFROMFILE);
    hCoatBm = LoadImage(NULL, "Coat_of_arms_of_Lithuania_And.bmp", IMAGE_BITMAP, h / 2, h / 2, LR_LOADFROMFILE);
    ReleaseDC(hWnd, hDC); 
    SelectObject(hMemDC, hBm);
    SelectObject(hLogoDC, hLogoBm);
    SelectObject(hCoatDC, hCoatBm);
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    Rectangle(hDC, 0, 0, w, h);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_DESTROY:
    if (hBm != NULL)
      DeleteObject(hBm);
    DeleteObject(hMemDC);
    DeleteObject(hLogoDC);
    DeleteObject(hCoatDC);
    KillTimer(hWnd, 30);
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}
/*End of t03clock.c file*/