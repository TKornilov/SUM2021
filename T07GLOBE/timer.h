/*FILE NAME: timer.h
  PROGRAMMER: TK3
  DATE:15.06.2021
*/
typedef double DBL;
DBL SyncTime;

DBL GLB_Time; 
DBL GLB_DeltaTime; 
DBL GLB_FPS; 
BOOL GLB_IsPause;

LONG StartTime;
LONG OldTime;
LONG PauseTime;
LONG OldFPSTime;
LONG FrameCount;
/*End of timer.h file*/