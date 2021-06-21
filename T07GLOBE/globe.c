/*FILE NAME: globe.c   
  PROGRAMMER: TK3
  DATE:15.06.2021
*/
#include <windows.h>
#include <math.h>
#include <time.h>

#include "globe.h"
#include "timer.h"
#include "MTH.h"

#define GLOBE_W 31
#define GLOBE_H 31



static VEC Geom[GLOBE_H][GLOBE_W];
static INT WinW, WinH;

/*Rotates through vector around Z axis*/
VEC RotateZ( VEC V, DBL Angle )
{
  DBL a = Angle * PI / 180.0, s = sin(a), c = cos(a);
  VEC r;
  
  r.X = V.X * c - V.Y * s;
  r.Y = V.X * s + V.Y * c;
  r.Z= V.Z;

  return r;
}

/*Rotates through vector around Y axis*/
VEC RotateY( VEC V, DBL Angle )
{
  DBL a = Angle * PI / 180.0, s = sin(a), c = cos(a);
  VEC r;
  
  r.Z = V.Z * c - V.X * s;
  r.X = V.Z * s + V.X * c;
  r.Y = V.Y;

  return r;
}

/*Sets the initial position of the globe*/
VOID GlobeSet( INT Xcenter, INT Ycenter, DOUBLE R )
{
  INT i, j;
  DOUBLE theta, phi;

  WinW = Xcenter * 2;
  WinH = Ycenter * 2;

  for (i = 0, theta = 0.0; i < GLOBE_H; i++, theta += PI / (GLOBE_H - 1))
    for (j = 0, phi = 0.0; j < GLOBE_W; j++, phi += 2 * PI / (GLOBE_W - 1))
    {
      Geom[i][j].X = R * sin(theta) * sin(phi);
      Geom[i][j].Y = R * cos(theta);
      Geom[i][j].Z = R * sin(theta) * cos(phi);
    }
}

/*Draws the globe at the current moment*/
VOID GlobeDraw( HDC hDC )
{
  INT i, j, k, minSize, s = 10;
  DBL Coef;
  HPEN hPen, hPenOld;
  LOGBRUSH lb;
  POINT pt[4];
  static POINT Pts[GLOBE_H][GLOBE_W];
  DBL t = GLB_Time;
  MATR m = MatrMulMatr(MatrRotateY(t * 30), MatrRotateZ(t * 18));

  srand(71);
  minSize = WinW < WinH ? WinW : WinH;
  m = MatrMulMatr(MatrView(VecSet(0.5, 0, 0.5), VecSet(0, 0, 0), VecSet(0, 1, 0)), m);
  lb.lbStyle = BS_SOLID;
  lb.lbHatch = HS_FDIAGONAL;
  lb.lbColor = RGB(0, 0, 0);
  hPen = ExtCreatePen(PS_GEOMETRIC | PS_SOLID, 1, &lb, 0, NULL);
  hPenOld = SelectObject(hDC, hPen);
  for (i = 0; i < GLOBE_H; i++)
    for (j = 0; j < GLOBE_W; j++)
    {
      VEC P = Geom[i][j];

      P = PointTransform(P, m);
      Pts[i][j].x = WinW / 2 + P.X * minSize * 0.47;
      Pts[i][j].y = WinH / 2 - P.Y * minSize * 0.47;
    }
  for (k = 0; k < 2; k++) 
    for (i = 0; i < GLOBE_H; i++)
      for (j = 0; j < GLOBE_W; j++)
      {
        SelectObject(hDC, GetStockObject(NULL_PEN));
        SelectObject(hDC, GetStockObject(DC_BRUSH));
        if (i < GLOBE_H / 3)
          SetDCBrushColor(hDC, RGB(255, 255, 0));
        else if (i < GLOBE_H / 3 * 2)
          SetDCBrushColor(hDC, RGB(0, 170, 100));
        else
          SetDCBrushColor(hDC, RGB(255, 0, 0));
        if(i != GLOBE_H - 1 && j != GLOBE_W - 1)
        {
          pt[0] = Pts[i][j];
          pt[1] = Pts[i][j + 1];
          pt[3] = Pts[i + 1][j];
          pt[2]= Pts[i + 1][j + 1];
          Coef = (pt[0].x - pt[1].x) * (pt[0].y + pt[1].y) + 
                 (pt[1].x - pt[2].x) * (pt[1].y + pt[2].y) +
                 (pt[2].x - pt[3].x) * (pt[2].y + pt[3].y) +
                 (pt[3].x - pt[0].x) * (pt[3].y + pt[0].y);
          if(k == 0 && Coef > 0 || k == 1 && Coef < 0)
            continue;
          Polygon(hDC, pt, 4);
        }
      }
  SelectObject(hDC, hPenOld);
  DeleteObject(hPen);
}

/*End of globe.c file*/