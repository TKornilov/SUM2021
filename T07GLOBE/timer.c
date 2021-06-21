/*FILE NAME: timer.c
  PROGRAMMER: TK3
  DATE:15.06.2021
*/
#include <windows.h>
#include <time.h>
#include "timer.h"


DBL GLB_Time; 
DBL GLB_DeltaTime; 
DBL GLB_FPS; 
BOOL GLB_IsPause;
LONG StartTime;
LONG OldTime;
LONG PauseTime;
LONG OldFPSTime;
LONG FrameCount;

VOID Timer( VOID )
{
  LONG t = clock();
  static LONG StartTime = -1; 

  if(StartTime == -1)
    StartTime = t;
  SyncTime = (t - StartTime) / (double)CLOCKS_PER_SEC;
}

VOID GLB_TimerInit( VOID )
{
  StartTime = OldTime = OldFPSTime = clock();
  FrameCount = 0;
  GLB_IsPause = FALSE;
}

VOID GLB_TimerResponse( VOID )
{
  LONG t = clock();

  if (!GLB_IsPause)
  {
    GLB_Time = (DOUBLE)(t - PauseTime - StartTime) / CLOCKS_PER_SEC;
    GLB_DeltaTime = (DOUBLE)(t - OldTime) / CLOCKS_PER_SEC;
  }
  else
  {
    PauseTime += t - OldTime;
    GLB_DeltaTime = 0;
  }
  FrameCount++;
  if (t - OldFPSTime > CLOCKS_PER_SEC)
  {
    GLB_FPS = FrameCount / ((DOUBLE)(t - OldFPSTime) / CLOCKS_PER_SEC);
    OldFPSTime = t;
    FrameCount = 0;
  }
  OldTime = t;
}
/*End of timer.c file*/