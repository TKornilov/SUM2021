/*FILE NAME: anim.h  
  PROGRAMMER: TK3
  DATE:21.06.2021
*/ 
#ifndef __anim_h_
#define __anim_h_

#include "rnd/rnd.h"

#define TK3_MAX_UNITS 3000
#define PROVINCES_AMOUNT 2

typedef struct tagtk3ANIM tk3ANIM;
#define UNIT_BASE_FIELDS \
  VOID (*Init)( tk3UNIT *Uni, tk3ANIM *Ani );  \
  VOID (*Close)( tk3UNIT *Uni, tk3ANIM *Ani );   \
  VOID (*Response)( tk3UNIT *Uni, tk3ANIM *Ani ); \
  VOID (*Render)( tk3UNIT *Uni, tk3ANIM *Ani )

typedef struct tagtk3UNIT tk3UNIT;
struct tagtk3UNIT
{
  UNIT_BASE_FIELDS;
};

struct tagtk3ANIM
{
  HWND hWnd;                                           
  INT W, H;                      
  DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per second value */
  BOOL
    IsPause;                     /* Pause flag */
  BYTE Keys[256],     
       KeysClick[256], 
       KeysOld[256];
  INT Mx, My, Mz, Mdx, Mdy, Mdz;
  BYTE
    JBut[32], JButOld[32], JButClick[32]; /* Joystick button states */
  INT JPov;                               /* Joystick point-of-view control [-1,0..7] */
  DBL
    JX, JY, JZ, JR;                       /* Joystick axes */

  tk3UNIT *Units[TK3_MAX_UNITS]; 
  INT NumOfUnits;                

};

typedef struct tagtk3PROVINCE tk3PROVINCE;
struct tagtk3PROVINCE
{
  CHAR *ProvName;
  INT ProvDev;
  INT CastleLevel;
  CHAR *Owner;
};


extern INT TK3_MouseWheel;

extern tk3ANIM TK3_Anim;

//extern tk3PROVINCE TK3_Provinces[PROVINCES_AMOUNT]

VOID TK3_AnimInit( HWND hWnd );
VOID TK3_AnimClose( VOID );
VOID TK3_AnimResize( INT W, INT H );
VOID TK3_AnimCopyFrame( VOID );
VOID TK3_AnimRender( VOID );
VOID TK3_AnimFlipFullScreen( VOID );
VOID TK3_AnimExit( VOID );

VOID TK3_AnimAddUnit( tk3UNIT *Uni );
tk3UNIT * TK3_AnimUnitCreate( INT Size );

VOID TK3_TimerInit( VOID );
VOID TK3_TimerResponse( VOID );

VOID TK3_AnimInputInit( VOID );
VOID TK3_AnimInputResponse( VOID );

#endif /*__anim_h_*/

/* End of "anim.h" file */