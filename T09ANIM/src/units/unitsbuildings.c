/*FILE NAME: unitsBUILDINGS.c 
  PROGRAMMER: TK3
  DATE:21.06.2021
*/

#include "units.h"

typedef struct tagtk3UNIT_BUILDINGS tk3UNIT_BUILDINGS;
struct tagtk3UNIT_BUILDINGS
{
  UNIT_BASE_FIELDS;
  tk3PRIM FARM, HOUSE, CASTLE;
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
static VOID TK3_UnitBuildingsInit( tk3UNIT_BUILDINGS *Uni, tk3ANIM *Ani )
{
  TK3_RndPrimLoad(&Uni->FARM, "BIN/MODELS/building.obj");
  TK3_RndPrimLoad(&Uni->HOUSE, "BIN/MODELS/med_house_final.obj");
  TK3_RndPrimLoad(&Uni->CASTLE, "BIN/MODELS/mercenary castle.obj");
} /* End of 'TK3_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       TK3UNIT *Uni;
 *   - animation context:
 *       TK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID TK3_UnitBuildingsClose( tk3UNIT_BUILDINGS *Uni, tk3ANIM *Ani )
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
static VOID TK3_UnitBuildingsResponse( tk3UNIT_BUILDINGS *Uni, tk3ANIM *Ani )
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
static VOID TK3_UnitBuildingsRender( tk3UNIT_BUILDINGS *Uni, FLT ProvX, FLT ProvY, FLT ProvZ, INT Dev, BOOL HasCastle )
{
  INT i;
  srand(71);
  //for (i = 0; i < Dev - (Dev / 5); i++)  
    TK3_RndPrimDraw(&Uni->FARM, MatrMulMatr(MatrMulMatr(MatrScale(VecSet(0.0003, 0.0003, 0.0003)), MatrTranslate(VecSet(-10, 0, 0))), MatrRotateY(0)));
    TK3_RndPrimDraw(&Uni->FARM, MatrMulMatr(MatrMulMatr(MatrScale(VecSet(0.0003, 0.0003, 0.0003)), MatrTranslate(VecSet(-11, 0, -5))), MatrRotateY(0)));
     // TK3_RndPrimDraw(&Uni->FARM, MatrMulMatr(MatrMulMatr(MatrScale(VecSet(0.0003, 0.0003, 0.0003)), MatrTranslate(VecSet(-10, 0, 0))), MatrRotateY(0)));
    //for (i = 0; i < Dev / 5; i++)
    TK3_RndPrimDraw(&Uni->HOUSE, MatrMulMatr(MatrRotateX(-90), MatrMulMatr(MatrScale(VecSet(0.003, 0.003, 0.003)), MatrTranslate(VecSet(-5, 0, -8)))));
  //if (HasCastle == TRUE)
    TK3_RndPrimDraw(&Uni->CASTLE, MatrMulMatr(MatrMulMatr(MatrScale(VecSet(0.03, 0.03, 0.03)), MatrTranslate(VecSet(-10, 0, -10))), MatrRotateY(0)));
    TK3_RndPrimDraw(&Uni->CASTLE, MatrMulMatr(MatrMulMatr(MatrScale(VecSet(0.03, 0.03, 0.03)), MatrTranslate(VecSet(-5, 0, -7))), MatrRotateY(0)));   
} /* End of 'TK3_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *       INT Size;
 * RETURNS:
 *   (vg4UNIT *) pointer to created unit.
 */
tk3UNIT * TK3_AnimUnitBuildingsCreate( VOID )
{
  tk3UNIT *Uni;

  /* Memory allocation */
  if ((Uni = TK3_AnimUnitCreate(sizeof(tk3UNIT_BUILDINGS))) == NULL)
    return NULL;
  memset(Uni, 0, 1);

  /* Setup unit methods */
  Uni->Init = (VOID *)TK3_UnitBuildingsInit;
  Uni->Close = (VOID *)TK3_UnitBuildingsClose;
  Uni->Response = (VOID *)TK3_UnitBuildingsResponse;
  Uni->Render = (VOID *)TK3_UnitBuildingsRender;

  return Uni;
} /* End of 'VG4_AnimUnitCreate' function */
/*End of "unitsBUILDINGS.c" file" */