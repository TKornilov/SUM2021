/*FILE NAME: timer.h
  PROGRAMMER: TK3
  DATE:15.06.2021
*/
typedef double DBL;
DBL SyncTime;

extern DBL GLB_Time; 
extern DBL GLB_DeltaTime; 
extern DBL GLB_FPS; 
extern BOOL GLB_IsPause;
VOID Timer( VOID );
VOID GLB_TimerInit( VOID );
VOID GLB_TimerResponse( VOID );


/*End of timer.h file*/