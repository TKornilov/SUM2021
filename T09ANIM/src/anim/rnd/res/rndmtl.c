/* FILE NAME: rndtex.c
 * PROGRAMMER: TK3
 * DATE: 23.06.2021
 * PURPOSE: 3D animation rendering shader handle functions module.
 */
/* Material store type */
#include "../rnd.h"

/* Material stock */

tk3MATERIAL TK3_RndMaterials[TK3_MAX_MATERIALS]; /* Array of materials */
INT TK3_RndMaterialsSize;

INT TK3_RndMtlAdd( tk3MATERIAL *Mtl )
{
  if(TK3_RndMaterialsSize >= TK3_MAX_MATERIALS)
    return -1;
  TK3_RndMaterials[TK3_RndMaterialsSize] = *Mtl;
  return TK3_RndMaterialsSize++;
}

VOID TK3_MtlInit( VOID )
{
  INT i;
  tk3MATERIAL mtl;

  TK3_RndMaterialsSize = 0;

  memset(&mtl, 0, sizeof(mtl));
  strncpy(mtl.Name, "Default", TK3_STR_MAX - 1);
  mtl.Ka = VecSet(0.2, 0.2, 0.2);
  mtl.Kd = VecSet(0.2, 0.2, 0.2);
  mtl.Ks = VecSet(0.2, 0.2, 0.2);
  mtl.Ph = 30;
  mtl.Trans = 1.0;
  for (i = 0; i < 8; i++)
    mtl.Tex[i] = -1;
  mtl.ShdNo = 0;
  TK3_RndMtlAdd(&mtl);
}
/*INT TK3_RndMtlApply( INT MtlNo )
{
  INT prg, loc;
  tk3MATERIAL *mtl;
  INT i;

  /* Set material pointer */
  /*if (MtlNo < 0 || MtlNo >= TK3_RndMaterialsSize)
    MtlNo = 0;
  mtl = &TK3_RndMaterials[MtlNo];

  /* Set shader program Id */
  /*prg = mtl->ShdNo;
  if (prg < 0 || prg >= TK3_RndShadersSize)
    prg = 0;
  prg = TK3_RndShaders[prg].ProgId;

  glUseProgram(prg);
  /* Set shading parameters */
  /*if ((loc = glGetUniformLocation(prg, "Time")) != -1)
    glUniform1f(loc, TK3_Anim.Time);
  if ((loc = glGetUniformLocation(prg, "GlobalTime")) != -1)
    glUniform1f(loc, TK3_Anim.GlobalTime);
  if ((loc = glGetUniformLocation(prg, "Ka")) != -1)
    glUniform3fv(loc, 1, &mtl->Ka.X);
  //. . .
  if ((loc = glGetUniformLocation(prg, "Ph")) != -1)
    glUniform1f(loc, mtl->Ph);

  //. . .
  /* Set textures */
  /*for (i = 0; i < 8; i++)
  {
    CHAR tname[] = "IsTexture0";  --> shader: uniform bool IsTexture2;

    tname[9] = '0' + i;
    if (mtl->Tex[i] != -1)
    {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, TK3_RndTextures[mtl->Tex[i]].TexId);
    }
    if ((loc = glGetUniformLocation(prg, tname)) != -1)
      glUniform1i(loc, mtl->Tex[i] != -1);
  }
  return prg;
} /* End of 'TK3_RndMtlApply' function */
