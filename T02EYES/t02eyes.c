/*FILE NAME: 01fwin.c   
  PrOGRAMMER: 
*/
#include <windows.h>
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

void DrawEye( HDC hDC, INT X, INT Y, INT R, INT R1, INT Mx, INT My )
{ 
  INT fl1 = 0, fl2 = 0, X1, Y1, len;
  HPEN hPen, hPenOld, hPen2, hPenOld2;
  LOGBRUSH lb;
  lb.lbStyle = BS_SOLID;
  lb.lbHatch = HS_FDIAGONAL;
  lb.lbColor = RGB(0, 0, 0);
  hPen = ExtCreatePen(PS_GEOMETRIC | PS_SOLID, 8, &lb, 0, NULL);
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(hDC, RGB(255, 255, 255));
  hPenOld = SelectObject(hDC, hPen);
  Ellipse(hDC, X, Y, X + 2 * R, Y + 2 * R);
  hPen2 = ExtCreatePen(PS_GEOMETRIC | PS_SOLID, 1, &lb, 0, NULL);
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  hPenOld2 = SelectObject(hDC, hPen2);
  SetDCBrushColor(hDC, RGB(120, 0, 255));
  len = Mx - X;
  if(Mx < X)
    fl1 = -1;
  if(Mx > X)
    fl1 = 1;
  if(My < Y)
    fl2 = -1;
  if(My > Y)
    fl2 = 1;

  Ellipse(hDC, X + R - R1 + (Mx / 70 * fl1), Y + R - R1 + (My / 70 * fl2), X + R + R1 + (Mx / 70 * fl1), Y + R + R1 + (My / 70 * fl2));
  SelectObject(hDC, hPenOld2);
  SelectObject(hDC, hPenOld);
  DeleteObject(hPen2);
  DeleteObject(hPen);
}

/*Reaction to windows messages*/
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam )
{
  PAINTSTRUCT ps;
  HDC hDC, hMemDC = NULL;
  HBITMAP hBm = NULL;
  INT x = 0, y = 0, i;
  POINT pt;
  static INT w = 2000, h = 3000;
  srand(30);
  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 100, NULL);
    return 0;
  case WM_TIMER:
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    hDC = GetDC(hWnd);
    hMemDC  = CreateCompatibleDC(hDC);
    hBm = CreateCompatibleBitmap(hDC, w, h);
    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    for(i = 0; i < 102; i++)
      DrawEye(hDC, rand() % w, rand() % h, 50 + rand() % 47, 18 + rand() % 8, pt.x, pt.y);
    ReleaseDC(hWnd, hDC); 
    return 0;
  case WM_SIZE:
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, w, h); 
    ReleaseDC(hWnd, hDC); 
    SelectObject(hMemDC, hBm);
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  /*case WM_LBUTTONDOWN:
    x = LOWORD(lParam);
    y = HIWORD(lParam); 
    /*hDC = GetDC(hWnd);
    Ellipse(hDC, 635, 485, 575, 425);
    Ellipse(hDC, 1335, 485, 1275, 425);
    SetDCBrushColor(hDC, RGB(120, 0, 255));
    Ellipse(hDC, 635 + x, 485 + y, 575 + x, 425 + y);
    Ellipse(hDC, 1335, 485, 1275, 425);
    ReleaseDC(hWnd, hDC); 
    return 0;*/
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    hMemDC  = CreateCompatibleDC(hDC);
    hBm = CreateCompatibleBitmap(hDC, w, h);
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
/*End of t01fwin.c file*/