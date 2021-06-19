/*FILE NAME: unitscow.c 
  PROGRAMMER: TK3
  DATE:19.06.2021
*/ 
#include "../def.h"
static tk3PRIM COW;
/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       TK3UNIT *Uni;
 *   - animation context:
 *       TK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID TK3_UnitCowInit( tk3UNIT_COW *Uni, tk3ANIM *Ani )
{
  INT i;
  COW.NumOfV = Uni->Cow.NumOfV;
  for(i = 0; i < COW.NumOfV; i++)
    COW.V[i].P = Uni->Cow.V[i].P;
  COW.NumOfI = Uni->Cow.NumOfI;
  for(i = 0; i < COW.NumOfI; i++)
    COW.I[i] = Uni->Cow.I[i];
  COW.Trans = Uni->Cow.Trans;   
  TK3_RndPrimLoad(&COW, "cow.obj");
} /* End of 'TK3_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       TK3UNIT *Uni;
 *   - animation context:
 *       TK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID TK3_UnitCowClose( tk3UNIT_COW *Uni, tk3ANIM *Ani )
{
} /* End of 'TK3_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       TK3UNIT *Uni;
 *   - animation context:
 *       TK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID TK3_UnitCowResponse( tk3UNIT_COW *Uni, tk3ANIM *Ani )
{
  Uni->Pos.X += Ani->W * 2.5;
} /* End of 'TK3_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       TK3UNIT *Uni;
 *   - animation context:
 *       TK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID TK3_UnitCowRender( tk3UNIT_COW *Uni, tk3ANIM *Ani )
{
  INT i;
  COW.NumOfV = Uni->Cow.NumOfV;
  for(i = 0; i < COW.NumOfV; i++)
    COW.V[i].P = Uni->Cow.V[i].P;
  COW.NumOfI = Uni->Cow.NumOfI;
  for(i = 0; i < COW.NumOfI; i++)
    COW.I[i] = Uni->Cow.I[i];
  COW.Trans = Uni->Cow.Trans;   
  TK3_RndPrimDraw(&COW, MatrRotateX(270));
} /* End of 'TK3_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *       INT Size;
 * RETURNS:
 *   (vg4UNIT *) pointer to created unit.
 */
tk3UNIT * TK3_AnimUnitCowCreate( VOID )
{
  tk3UNIT *Uni;

  /* Memory allocation */
  if ((Uni = (tk3UNIT *)TK3_AnimUnitCreate(sizeof(tk3UNIT))) == NULL)
    return NULL;
  memset(Uni, 0, 1);

  /* Setup unit methods */
  Uni->Init = (VOID *)TK3_UnitCowInit;
  Uni->Close = (VOID *)TK3_UnitCowClose;
  Uni->Response = (VOID *)TK3_UnitCowResponse;
  Uni->Render = (VOID *)TK3_UnitCowRender;
  TK3_Anim.NumOfUnits++;

  return Uni;
} /* End of 'VG4_AnimUnitCreate' function */
/*End of "unitscow.c" file" */