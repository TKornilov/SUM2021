/*FILE NAME: timer.c 
  PROGRAMMER: TK3
  DATE:21.06.2021
*/
#include <time.h>
#include "anim.h"
#include "../def.h"
static UINT64
    StartTime,    /* Start program time */
    OldTime,      /* Previous frame time */
    OldTimeFPS,   /* Old time FPS measurement */
    PauseTime,    /* Time during pause period */
    TimePerSec,   /* Timer resolution */
    FrameCounter; /* Frames counter */
VOID TK3_TimerInit( VOID )       
{
  LARGE_INTEGER t;	

  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  FrameCounter = 0;
  TK3_Anim.IsPause = FALSE;
  TK3_Anim.FPS = 30.0;
  PauseTime = 0;
}

VOID TK3_TimerResponse( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);
  /* Global time */
  TK3_Anim.GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
  TK3_Anim.GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;
  /* Time with pause */
  if (TK3_Anim.IsPause)
  {
    TK3_Anim.DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    TK3_Anim.DeltaTime = (DBL)TK3_Anim.GlobalDeltaTime;
    TK3_Anim.Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
  }
  /* FPS */
  FrameCounter++;
  if ((t.QuadPart - OldTimeFPS) > TimePerSec)
  {
    TK3_Anim.FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
}
/*End of "timer.c" file" */