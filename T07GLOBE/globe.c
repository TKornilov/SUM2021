/*FILE NAME: globe.c   
  PROGRAMMER: TK3
  DATE:15.06.2021
*/
#include <windows.h>
#include <math.h>

#include "globe.h"

#define GLOBE_W 9
#define GLOBE_H 7

#define PI 3.1415926

typedef struct
{
  DOUBLE x, y, z;
} VEC;

static VEC Geom[GLOBE_H][GLOBE_W];
static INT WinW, WinH;

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
  INT i, j, minSize, s = 10;
  static VEC Pts[GLOBE_H][GLOBE_W];

  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(hDC, RGB(255, 255, 255));
  minSize = WinW < WinH ? WinW : WinH;
  for (i = 0; i < GLOBE_H; i++)
    for (j = 0; j < GLOBE_W; j++)
    {
      Pts[i][j].x = WinW / 2 + Geom[i][j].x * minSize * 0.47;
      Pts[i][j].y = WinH / 2 - Geom[i][j].y * minSize * 0.47;
    }
  for (i = 0; i < GLOBE_H; i++)
    for (j = 0; j < GLOBE_W; j++)
      Ellipse(hDC, Pts[i][j].x - s, Pts[i][j].y - s, Pts[i][j].x + s, Pts[i][j].y + s);  
}

/*End of globe.c file*/