/**/

/***
 * Primitive collection support
 ***/

#include "../anim.h"

/* Primitive collection data type */
typedef struct tagtk3PRIMS
{
  INT NumOfPrims; /* Number of primitives in array */  
  tk3PRIM *Prims; /* Array of primitives */
  MATR Trans;     /* Common transformation matrix */
} tk3PRIMS;

/* Create array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       tk3PRIMS *Prs;
 *   - number of primitives to be add:
 *       INT NumOfPrims;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL TK3_RndPrimsCreate( tk3PRIMS *Prs, INT NumOfPrims );

/* Delete array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       tk3PRIMS *Prs;
 * RETURNS: None.
 */
VOID TK3_RndPrimsFree( tk3PRIMS *Prs );

/* Draw array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       tk3PRIMS *Prs;
 *   - global transformation matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID TK3_RndPrimsDraw( tk3PRIMS *Prs, MATR World );

/* Load array of primitives from .G3DM file function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       tk3PRIMS *Prs;
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL TK3_RndPrimsLoad( tk3PRIMS *Prs, CHAR *FileName );

