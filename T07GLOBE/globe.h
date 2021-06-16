/*FILE NAME: globe.h  
  PROGRAMMER: TK3
  DATE:15.06.2021
*/

#ifndef __globe_h_
#define  __globe_h_

#pragma warning(disable: 4244)

#include <windows.h>
#include <time.h>

typedef double DBL;


VOID Timer ( VOID );
VOID GLB_TimerInit( VOID );
VOID GLB_TimerResponse( VOID );
VOID GlobeSet( INT Xcenter, INT Ycenter, DOUBLE R );
VOID GlobeDraw( HDC hDC );

#endif /*  __globe_h_ */
/*End of globe.h file*/