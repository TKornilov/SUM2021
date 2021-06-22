/*FILE NAME: unitsControl.c 
  PROGRAMMER: TK3
  DATE:21.06.2021
*/
#include <time.h>
#include "../def.h"
static tk3PRIM Conw;
/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       TK3UNIT *Uni;
 *   - animation context:
 *       TK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID TK3_UnitControlInit( tk3UNIT_CONTROL *Uni, tk3ANIM *Ani )
{
  Uni->CamLoc = VecSet(5, 200, 200);
  Uni->CamSet = VecSet(0, 1, 0);
  Uni->Speed = 2.0;
  Uni->AngleSpeed = 2.0;
} /* End of 'TK3_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       TK3UNIT *Uni;
 *   - animation context:
 *       TK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID TK3_UnitControlClose( tk3UNIT_CONTROL *Uni, tk3ANIM *Ani )
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
static VOID TK3_UnitControlResponse( tk3UNIT_CONTROL *Uni, tk3ANIM *Ani )
{
  //Uni->Pos.X += Ani->W * 2.5;

  Uni->CamDir = VecSet(-TK3_RndMatrView.M[0][2], -TK3_RndMatrView.M[1][2], -TK3_RndMatrView.M[2][2]);
  Uni->CamLoc =
  VecAddVec(Uni->CamLoc,
  VecMulNum(Uni->CamDir, Ani->GlobalDeltaTime * Uni->Speed * Ani->Mdz));
  /*Uni->CamLoc =
  VecAddVec(Uni->CamLoc,
  VecMulNum(Uni->CamDir, Ani->GlobalDeltaTime * Uni->Speed * Ani->Mdz));*/
} /* End of 'TK3_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       TK3UNIT *Uni;
 *   - animation context:
 *       TK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID TK3_UnitControlRender( tk3UNIT_CONTROL *Uni, tk3ANIM *Ani )
{
  TK3_RndCamSet(Uni->CamLoc, Uni->CamDir, Uni->CamSet); 
} /* End of 'TK3_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *       INT Size;
 * RETURNS:
 *   (vg4UNIT *) pointer to created unit.
 */
tk3UNIT * TK3_AnimUnitControlCreate( VOID )
{
  tk3UNIT *Uni;

  /* Memory allocation */
  if ((Uni = (tk3UNIT *)TK3_AnimUnitCreate(sizeof(tk3UNIT))) == NULL)
    return NULL;
  memset(Uni, 0, 1);

  /* Setup unit methods */
  Uni->Init = (VOID *)TK3_UnitControlInit;
  Uni->Close = (VOID *)TK3_UnitControlClose;
  Uni->Response = (VOID *)TK3_UnitControlResponse;
  Uni->Render = (VOID *)TK3_UnitControlRender;
  TK3_Anim.NumOfUnits++;

  return Uni;
} /* End of 'VG4_AnimUnitCreate' function */
/*End of "unitsControl.c" file" */
