/*FILE NAME: unitsROMAN.c 
  PROGRAMMER: TK3
  DATE:21.06.2021
*/
#include <time.h>
#include "../def.h"
static tk3PRIM ROMAN;
/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       TK3UNIT *Uni;
 *   - animation context:
 *       TK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID TK3_UnitRomanInit( tk3UNIT_ROMAN *Uni, tk3ANIM *Ani )
{
  INT i;
  ROMAN.NumOfV = Uni->ROMAN.NumOfV;
  for(i = 0; i < ROMAN.NumOfV; i++)
  {
    ROMAN.V[i].P = Uni->ROMAN.V[i].P;
    ROMAN.V[i].T = Uni->ROMAN.V[i].T;
    ROMAN.V[i].N = Uni->ROMAN.V[i].N;
    ROMAN.V[i].C = Uni->ROMAN.V[i].C;
  }
  ROMAN.NumOfI = Uni->ROMAN.NumOfI;
  for(i = 0; i < ROMAN.NumOfI; i++)
    ROMAN.I[i] = Uni->ROMAN.I[i];
  ROMAN.Trans = Uni->ROMAN.Trans;
  ROMAN.VA = Uni->ROMAN.VA;
  ROMAN.VBuf = Uni->ROMAN.VBuf;
  ROMAN.NumOfElements = Uni->ROMAN.NumOfElements;
  TK3_RndPrimLoad(&ROMAN, "BIN/MODELS/aiji.obj");
} /* End of 'TK3_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       TK3UNIT *Uni;
 *   - animation context:
 *       TK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID TK3_UnitRomanClose( tk3UNIT_ROMAN *Uni, tk3ANIM *Ani )
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
static VOID TK3_UnitRomanResponse( tk3UNIT_ROMAN *Uni, tk3ANIM *Ani )
{
  Uni->Pos.X += Ani->W * 2.5;

  /*Uni->CamLoc =
  VecAddVec(Uni->CamLoc,
  VecMulNum(Uni->CamDir, Ani->GlobalDeltaTime * Uni->Speed * Ani->Mdz));
  Uni->CamLoc =
  VecAddVec(Uni->CamLoc,
  VecMulNum(Uni->CamDir, Ani->GlobalDeltaTime * Uni->Speed * Ani->Mdz));
  TK3_RndCamSet(Uni->CamLoc, Uni->CamDir, Uni->CamSet); */
} /* End of 'TK3_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       TK3UNIT *Uni;
 *   - animation context:
 *       TK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID TK3_UnitRomanRender( tk3UNIT_ROMAN *Uni, tk3ANIM *Ani )
{
  DBL t = TK3_Anim.Time;
  /*if(ROMAN.V == NULL)
  {
    ROMAN.NumOfV = Uni->ROMAN.NumOfV;
    for(i = 0; i < ROMAN.NumOfV; i++)
    {
      ROMAN.V[i].P = Uni->ROMAN.V[i].P;
      ROMAN.V[i].T = Uni->ROMAN.V[i].T;
      ROMAN.V[i].N = Uni->ROMAN.V[i].N;
      ROMAN.V[i].C = Uni->ROMAN.V[i].C;
    }
    ROMAN.NumOfI = Uni->ROMAN.NumOfI;
    for(i = 0; i < ROMAN.NumOfI; i++)
      ROMAN.I[i] = Uni->ROMAN.I[i];
    ROMAN.Trans = Uni->ROMAN.Trans;
    ROMAN.VA = Uni->ROMAN.VA;
    ROMAN.VBuf = Uni->ROMAN.VBuf;
    ROMAN.NumOfElements = Uni->ROMAN.NumOfElements;
  } */
  TK3_RndPrimDraw(&ROMAN,  MatrMulMatr(MatrMulMatr(MatrScale(VecSet(0.1, 0.1, 0.1)), MatrTranslate(VecSet(-30, 0, 0))), MatrRotateY(0)));
} /* End of 'TK3_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *       INT Size;
 * RETURNS:
 *   (vg4UNIT *) pointer to created unit.
 */
tk3UNIT * TK3_AnimUnitRomanCreate( VOID )
{
  tk3UNIT *Uni;

  /* Memory allocation */
  if ((Uni = (tk3UNIT *)TK3_AnimUnitCreate(sizeof(tk3UNIT))) == NULL)
    return NULL;
  memset(Uni, 0, 1);

  /* Setup unit methods */
  Uni->Init = (VOID *)TK3_UnitRomanInit;
  Uni->Close = (VOID *)TK3_UnitRomanClose;
  Uni->Response = (VOID *)TK3_UnitRomanResponse;
  Uni->Render = (VOID *)TK3_UnitRomanRender;
  TK3_Anim.NumOfUnits++;

  ROMAN = ROMAN;

  return Uni;
} /* End of 'VG4_AnimUnitCreate' function */
/*End of "unitsROMAN.c" file" */