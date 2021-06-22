/*FILE NAME: units.h  
  PROGRAMMER: TK3
  DATE:21.06.2021
*/
#ifndef __units_h_
#define  __units_h_
#include "../def.h"
#include "../anim/rnd/rnd.h"
#define TK3_MAX_UNITS 3000
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
typedef struct tagtk3VERTEXEX
{
  VEC P, N;
  VEC2 T;
  VEC4 C;
} tk3VERTEXEX; /*3d Vector for primitives*/
typedef struct tagtk3PRIMEX
{
 tk3VERTEXEX *V;
 INT NumOfV;
 INT *I;
 INT NumOfI, IBuf, VBuf, VA, NumOfElements;
 MATR Trans;
} tk3PRIMEX;  /*Ptimitive and the amount of vectors and matrixes defining it*/
typedef struct tagtk3ANIM
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

}tk3ANIM;
typedef struct tagtk3UNIT_COW tk3UNIT_COW;
struct tagtk3UNIT_COW
{
  UNIT_BASE_FIELDS;
  tk3PRIMEX Cow;
  VEC Pos;
};
typedef struct tagtk3UNIT_ROMAN tk3UNIT_ROMAN;
struct tagtk3UNIT_ROMAN
{
  UNIT_BASE_FIELDS;
  tk3PRIMEX ROMAN;
  VEC Pos;
};
typedef struct tagtk3UNIT_CONTROL tk3UNIT_CONTROL;
struct tagtk3UNIT_CONTROL
{
  UNIT_BASE_FIELDS;
  DBL AngleSpeed, Speed;
  VEC Pos, CamLoc, CamDir, CamSet;
};
tk3UNIT *Units[TK3_MAX_UNITS];
INT NumOfUnits; 
tk3UNIT * TK3_AnimUnitCreate( INT Size );
tk3UNIT * TK3_AnimUnitCowCreate( VOID );
tk3UNIT * TK3_AnimUnitControlCreate( VOID );
tk3UNIT * TK3_AnimUnitRomanCreate( VOID );
static VOID TK3_UnitControlInit( tk3UNIT_CONTROL *Uni, tk3ANIM *Ani );
#endif /*__units_h_*/
/*End of "units.h" file" */

