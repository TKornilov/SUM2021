/*FILE NAME: unitsINTERFACE.c 
  PROGRAMMER: TK3
  DATE:21.06.2021
*/

#include "units.h"

typedef struct tagtk3UNIT_INTERFACE tk3UNIT_INTERFACE;
struct tagtk3UNIT_INTERFACE
{
  UNIT_BASE_FIELDS;
  tk3PRIM BASE;
  VEC Pos;
};

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       TK3UNIT *Uni;
 *   - animation context:
 *       TK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID TK3_UnitInterfaceInit( tk3UNIT_INTERFACE *Uni, tk3ANIM *Ani )
{
  //TK3_RndPrimLoad(&Uni->BASE, "BIN/MODELS/Basic interface.obj");
  /*TK3_RndPrimLoad(&Uni->BRITTANY, "BIN/MODELS/Brittany1_.obj");
  TK3_RndPrimLoad(&Uni->WALES, "BIN/MODELS/Wales2.obj");
  TK3_RndPrimLoad(&Uni->LION, "BIN/MODELS/Englishlion1obj.obj");
  TK3_RndPrimLoad(&Uni->CORNWALL, "BIN/MODELS/Cornwall.obj");
  TK3_RndPrimLoad(&Uni->LONDON, "BIN/MODELS/London.obj"); */
} /* End of 'TK3_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       TK3UNIT *Uni;
 *   - animation context:
 *       TK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID TK3_UnitInterfaceClose( tk3UNIT_INTERFACE *Uni, tk3ANIM *Ani )
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
static VOID TK3_UnitInterfaceResponse( tk3UNIT_INTERFACE *Uni, tk3ANIM *Ani )
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
static VOID TK3_UnitInterfaceRender( tk3UNIT_INTERFACE *Uni, tk3ANIM *Ani )
{
  DBL t = TK3_Anim.Time;
  TK3_RndPrimDraw(&Uni->BASE, MatrMulMatr(MatrMulMatr(MatrScale(VecSet(1, 1, 1)), MatrTranslate(VecSet(5, 5, 5))), MatrRotateY(0)));
  /*TK3_RndPrimDraw(&Uni->BRITTANY, MatrMulMatr(MatrMulMatr(MatrScale(VecSet(3, 3, 3)), MatrTranslate(VecSet(-10, 0, 0))), MatrRotateY(0)));
  TK3_RndPrimDraw(&Uni->WALES, MatrMulMatr(MatrRotateY(5), MatrMulMatr(MatrScale(VecSet(2.5, 2.5, 2.5)), MatrTranslate(VecSet(-10, 0, -9.75)))));
  TK3_RndPrimDraw(&Uni->LION, MatrMulMatr(MatrRotateX(90), MatrMulMatr(MatrScale(VecSet(3, 3, 3)), MatrTranslate(VecSet(-10, 0.6, -10)))));
  TK3_RndPrimDraw(&Uni->CORNWALL, MatrMulMatr(MatrRotateX(0), MatrMulMatr(MatrScale(VecSet(5, 5, 5)), MatrTranslate(VecSet(-11, 0, -5)))));
  TK3_RndPrimDraw(&Uni->LONDON, MatrMulMatr(MatrRotateX(0), MatrMulMatr(MatrScale(VecSet(5, 5, 5)), MatrTranslate(VecSet(-5, 0, -7)))));
*/} /* End of 'TK3_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *       INT Size;
 * RETURNS:
 *   (vg4UNIT *) pointer to created unit.
 */
tk3UNIT * TK3_AnimUnitInterfaceCreate( VOID )
{
  tk3UNIT *Uni;

  /* Memory allocation */
  if ((Uni = TK3_AnimUnitCreate(sizeof(tk3UNIT_INTERFACE))) == NULL)
    return NULL;
  memset(Uni, 0, 1);

  /* Setup unit methods */
  Uni->Init = (VOID *)TK3_UnitInterfaceInit;
  Uni->Close = (VOID *)TK3_UnitInterfaceClose;
  Uni->Response = (VOID *)TK3_UnitInterfaceResponse;
  Uni->Render = (VOID *)TK3_UnitInterfaceRender;

  return Uni;
} /* End of 'VG4_AnimUnitCreate' function */
/*End of "unitsINTERFACE.c" file" */