/*FILE NAME: rndbase.c  
  PROGRAMMER: TK3
  DATE:21.06.2021
*/

#include "rnd.h"


/*Sets the starting position for the camera*/
VOID TK3_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  TK3_RndMatrView = MatrView(Loc, At, Up);
  TK3_RndMatrVP = MatrMulMatr(TK3_RndMatrView, TK3_RndMatrProj);
}

/*Initiates the parameters of the current frame*/
VOID TK3_RndInit( HWND hWnd )
{
  HDC hDC = GetDC(hWnd);
  
  TK3_hRndWnd = hWnd;
  TK3_hRndBmFrame = NULL;
  TK3_hRndDCFrame = CreateCompatibleDC(hDC);
  ReleaseDC(hWnd, hDC);
  TK3_RndCamSet(VecSet(0.5, 0, 0.5), VecSet(0, 0, 0), VecSet(0, 1, 0));

}

/*Destroys parameters of a frame*/
VOID TK3_RndClose( VOID )
{
  if (TK3_hRndBmFrame != NULL)
    DeleteObject(TK3_hRndBmFrame);
  DeleteObject(TK3_hRndDCFrame);
}

/*Starts the current frame*/
VOID TK3_RndStart( VOID )
{
  SelectObject(TK3_hRndDCFrame, GetStockObject(DC_BRUSH));
  SelectObject(TK3_hRndDCFrame, GetStockObject(NULL_PEN));
  SetDCBrushColor(TK3_hRndDCFrame, RGB(0, 0, 120));
  Rectangle(TK3_hRndDCFrame, -1, -1, TK3_RndFrameW + 1, TK3_RndFrameH + 1);

  SelectObject(TK3_hRndDCFrame, GetStockObject(NULL_BRUSH));
  SelectObject(TK3_hRndDCFrame, GetStockObject(DC_PEN));
  SetDCPenColor(TK3_hRndDCFrame, RGB(220, 220, 220));
  
}

/*Summoned in the end*/
VOID TK3_RndEnd( VOID )
{
}

/*Copies the frame into the main frame*/
VOID TK3_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, TK3_RndFrameW, TK3_RndFrameH,
    TK3_hRndDCFrame, 0, 0, SRCCOPY);
}

/*Sets the parameters of a projecting matrix*/
VOID TK3_RndProjSet( VOID )
{
  DBL rx, ry;

  rx = ry = TK3_RndProjSize;

  /* Correct aspect ratio */
  if (TK3_RndFrameW > TK3_RndFrameH)
    rx *= (DBL)TK3_RndFrameW / TK3_RndFrameH;
  else
    ry *= (DBL)TK3_RndFrameH / TK3_RndFrameW;

  TK3_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      TK3_RndProjDist, TK3_RndProjFarClip);
  TK3_RndMatrVP = MatrMulMatr(TK3_RndMatrView, TK3_RndMatrProj);
}

/*Resizes the window*/
VOID TK3_RndResize( INT W, INT H )
{
  HDC hDC = GetDC(TK3_hRndWnd);

  if (TK3_hRndBmFrame)
    DeleteObject(TK3_hRndBmFrame);
  TK3_hRndBmFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(TK3_hRndWnd, hDC);		
  SelectObject(TK3_hRndDCFrame, TK3_hRndBmFrame);

  TK3_RndFrameW = W;
  TK3_RndFrameH = H;
  TK3_RndProjSet();
}




/*End of 'rndbase.c' file*/