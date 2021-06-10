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

/*Reaction to windows messages*/
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam )
{
  PAINTSTRUCT ps;
  HDC hDC;
  HPEN hPen, hPenOld;
  LOGBRUSH lb;
  INT x, y;
  static INT w = 200, h = 300;
  switch (Msg)
  {
  case WM_SIZE:
    return 0;
  case WM_LBUTTONDOWN:
    x = LOWORD(lParam);
    y = HIWORD(lParam);
    hDC = GetDC(hWnd);
    Ellipse(hDC, x - 10, y - 10, x + 10, y + 10);
    ReleaseDC(hWnd, hDC); 
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    SetBkMode(hDC, OPAQUE);
    SetBkColor(hDC, RGB(0, 255, 120));
    lb.lbStyle = BS_HATCHED;
    lb.lbHatch = HS_FDIAGONAL;
    lb.lbColor = RGB(0, 0, 255);
    hPen = ExtCreatePen(PS_GEOMETRIC | PS_SOLID, 8, &lb, 0, NULL);
    hPenOld = SelectObject(hDC, hPen);
    MoveToEx(hDC, 30, 300, NULL);
    LineTo(hDC, 330, 300);
    LineTo(hDC, 330, 400);
    SelectObject(hDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hDC, RGB(0, 120, 255));
    Rectangle(hDC, 10, 10, h - 10, w - 10);
    Ellipse(hDC, 410, 410, 300, 200);
    SelectObject(hDC, hPenOld);
    EndPaint(hWnd, &ps);
    DeleteObject(hPen);
    return 0;
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}
/*End of t01fwin.c file*/