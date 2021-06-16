/*FILE NAME: globe.c   
  PROGRAMMER: TK3
  DATE:15.06.2021
*/
#include <windows.h>
#include <math.h>
#include <time.h>

#include "globe.h"
#include "timer.h"

#define GLOBE_W 31
#define GLOBE_H 31

#define PI 3.1415926


typedef struct
{
  DOUBLE x, y, z;
} VEC;

static VEC Geom[GLOBE_H][GLOBE_W];
static INT WinW, WinH;


VEC RotateZ( VEC V, DBL Angle )
{
  DBL a = Angle * PI / 180.0, s = sin(a), c = cos(a);
  VEC r;
  
  r.x = V.x * c - V.y * s;
  r.y = V.x * s + V.y * c;
  r.z = V.z;

  return r;
}

VEC RotateY( VEC V, DBL Angle )
{
  DBL a = Angle * PI / 180.0, s = sin(a), c = cos(a);
  VEC r;
  
  r.z = V.z * c - V.x * s;
  r.x = V.z * s + V.x * c;
  r.y = V.y;

  return r;
}

VOID GlobeSet( INT Xcenter, INT Ycenter, DOUBLE R )
{
  INT i, j;
  DOUBLE theta, phi;

  WinW = Xcenter * 2;
  WinH = Ycenter * 2;

  for (i = 0, theta = 0.0; i < GLOBE_H; i++, theta += PI / (GLOBE_H - 1))
    for (j = 0, phi = 0.0; j < GLOBE_W; j++, phi += 2 * PI / (GLOBE_W - 1))
    {
      Geom[i][j].x = R * sin(theta) * sin(phi);
      Geom[i][j].y = R * cos(theta);
      Geom[i][j].z = R * sin(theta) * cos(phi);
    }
}

VOID GlobeDraw( HDC hDC )
{
  INT i, j, k, minSize, s = 10;
  DBL Coef;
  static VEC Pts[GLOBE_H][GLOBE_W];
  HPEN hPen, hPenOld;
  LOGBRUSH lb;
  POINT pt[4];
  DBL t = GLB_Time;
  
  srand(71);
  minSize = WinW < WinH ? WinW : WinH;
  lb.lbStyle = BS_SOLID;
  lb.lbHatch = HS_FDIAGONAL;
  lb.lbColor = RGB(0, 0, 0);
  hPen = ExtCreatePen(PS_GEOMETRIC | PS_SOLID, 1, &lb, 0, NULL);
  hPenOld = SelectObject(hDC, hPen);
  for (i = 0; i < GLOBE_H; i++)
    for (j = 0; j < GLOBE_W; j++)
    {
      VEC P = Geom[i][j];

      P = RotateZ(P, 18 * sin(2 * t));
      P = RotateY(P, 30 * sin(2 * t));
      Pts[i][j].x = WinW / 2 + P.x * minSize * 0.47;
      Pts[i][j].y = WinH / 2 - P.y * minSize * 0.47;
    }
  for (k = 0; k < 2; k++) 
    for (i = 0; i < GLOBE_H; i++)
      for (j = 0; j < GLOBE_W; j++)
      {
        SelectObject(hDC, GetStockObject(NULL_PEN));
        SelectObject(hDC, GetStockObject(DC_BRUSH));
        if (i > GLOBE_H * 2 / 5 && i < GLOBE_H * 3 / 5)
          SetDCBrushColor(hDC, RGB(0, 0, 255));
        else
          SetDCBrushColor(hDC, RGB(255, 255, 255));
        if(i != GLOBE_H - 1 && j != GLOBE_W - 1)
        {
          pt[0].x = Pts[i][j].x;
          pt[0].y = Pts[i][j].y;
          pt[1].x = Pts[i][j + 1].x;
          pt[1].y = Pts[i][j + 1].y;
          pt[3].x = Pts[i + 1][j].x;
          pt[3].y = Pts[i + 1][j].y;
          pt[2].x = Pts[i + 1][j + 1].x;
          pt[2].y = Pts[i + 1][j + 1].y;
          Coef = (pt[0].x - pt[1].x) * (pt[0].y + pt[1].y) + 
                 (pt[1].x - pt[2].x) * (pt[1].y + pt[2].y) +
                 (pt[2].x - pt[3].x) * (pt[2].y + pt[3].y) +
                 (pt[3].x - pt[0].x) * (pt[3].y + pt[0].y);
          if(k == 0 && Coef < 0 || k == 1 && Coef > 0)
            continue;
          Polygon(hDC, pt, 4);
        }
      }
  SelectObject(hDC, hPenOld);
  DeleteObject(hPen);
}

/*End of globe.c file*/