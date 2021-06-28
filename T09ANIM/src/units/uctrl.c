/*FILE NAME: unitsControl.c 
  PROGRAMMER: TK3
  DATE:21.06.2021
*/

#include "units.h"

typedef struct tagtk3UNIT_CONTROL tk3UNIT_CONTROL;
struct tagtk3UNIT_CONTROL
{
  UNIT_BASE_FIELDS;
  tk3PRIM Diplomacy;
  DBL AngleSpeed, Speed;
  VEC Pos, CamLoc, CamDir, CamSet;
};


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
  Uni->CamLoc = VecSet(0, 50, 50);
  Uni->CamSet = VecSet(0, 1, 0);
  Uni->Speed = 10.0;
  Uni->AngleSpeed = 25.0;
  
  TK3_RndPrimLoad(&Uni->Diplomacy, "BIN/MODELS/Basic interface.obj");
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
  Uni->CamLoc =
    PointTransform(Uni->CamLoc,
      MatrRotateY(Ani->Keys[VK_LBUTTON] *
        Ani->GlobalDeltaTime * Uni->AngleSpeed * Ani->Mdx));
  /*Uni->CamLoc.X += Ani->GlobalDeltaTime * Uni->Speed *
        (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]);
  Uni->CamDir.X += Ani->GlobalDeltaTime * Uni->Speed *
        (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]);*/ 
  Uni->CamLoc =
    PointTransform(Uni->CamLoc,
      MatrTranslate(VecSet(Ani->GlobalDeltaTime * Uni->Speed *
        (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]), Ani->GlobalDeltaTime * Uni->Speed *
        (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]), Ani->GlobalDeltaTime * Uni->Speed *
        (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]))));
  /*Uni->CamDir =
    VecAddVec(Uni->CamDir,
      VecMulNum(Uni->CamDir, Ani->GlobalDeltaTime * Uni->Speed *
        (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN])));
  /*Uni->CamLoc =
    VecAddVec(Uni->CamLoc,
      VecMulNum(Uni->CamDir, Ani->GlobalDeltaTime * Uni->Speed *
        (Ani->Keys[VK_RIGHT] - Ani->Keys[VK_LEFT])));
  /*Uni->CamLoc =
  VecAddVec(Uni->CamLoc,
  VecMulNum(Uni->CamDir, Ani->GlobalDeltaTime * Uni->Speed * Ani->Mdz));*/
  TK3_RndCamSet(Uni->CamLoc, Uni->CamDir, Uni->CamSet); 
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
  TK3_RndPrimDraw(&Uni->Diplomacy, MatrMulMatr(MatrRotateX(90), MatrTranslate(VecSet(Uni->CamLoc.X + 20, Uni->CamLoc.Y - 20, Uni->CamLoc.Z - 30))));
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
  if ((Uni = TK3_AnimUnitCreate(sizeof(tk3UNIT_CONTROL))) == NULL)
    return NULL;
  memset(Uni, 0, 1);

  /* Setup unit methods */
  Uni->Init = (VOID *)TK3_UnitControlInit;
  Uni->Close = (VOID *)TK3_UnitControlClose;
  Uni->Response = (VOID *)TK3_UnitControlResponse;
  Uni->Render = (VOID *)TK3_UnitControlRender;

  return Uni;
} /* End of 'VG4_AnimUnitCreate' function */
/*End of "unitsControl.c" file" */
