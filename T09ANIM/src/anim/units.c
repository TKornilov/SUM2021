/*FILE NAME: units.c  
  PROGRAMMER: TK3
  DATE:21.06.2021
*/
//#include ""
#include "../def.h"
#include "../units/units.h"
/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       TK3UNIT *Uni;
 *   - animation context:
 *       TK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID TK3_UnitInit( tk3UNIT *Uni, tk3ANIM *Ani )
{
  //Uni->Pos = VecSet(0, 1, 0);
} /* End of 'TK3_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       TK3UNIT *Uni;
 *   - animation context:
 *       TK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID TK3_UnitClose( tk3UNIT *Uni, tk3ANIM *Ani )
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
static VOID TK3_UnitResponse( tk3UNIT *Uni, tk3ANIM *Ani )
{
} /* End of 'TK3_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       TK3UNIT *Uni;
 *   - animation context:
 *       TK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID TK3_UnitRender( tk3UNIT *Uni, tk3ANIM *Ani )
{
} /* End of 'TK3_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (vg4UNIT *) pointer to created unit.
 */
tk3UNIT * TK3_AnimUnitCreate( INT Size )
{
  tk3UNIT *Uni;


  /* Memory allocation */
  if (Size < sizeof(tk3UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);

  /* Setup unit methods */
  Uni->Init = TK3_UnitInit;
  Uni->Close = TK3_UnitClose;
  Uni->Response = TK3_UnitResponse;
  Uni->Render = TK3_UnitRender;

  return Uni;
} /* End of 'VG4_AnimUnitCreate' function */

/*End of "units.c" file" */