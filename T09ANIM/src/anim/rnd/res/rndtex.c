/* FILE NAME: rndtex.c
 * PROGRAMMER: TK3
 * DATE: 23.06.2021
 * PURPOSE: 3D animation rendering shader handle functions module.
 */

#include <stdio.h>

#include "../rnd.h"

//#include "../def.h"
tk3TEXTURE TK3_RndTextures[TK3_MAX_TEXTURES];
INT TK3_RndTexturesSize;

VOID TK3_RndTexInit( VOID )
{
}

VOID TK3_RndTexClose( VOID )
{ 
  INT i;

  for (i = 0; i < TK3_MAX_TEXTURES; i++)
    glDeleteTextures(1, &TK3_RndTextures[i].TexId);
}

INT TK3_RndTexAddImg(CHAR *FileName, INT W, INT H )
{
  if(TK3_RndTexturesSize >= TK3_MAX_TEXTURES)
    return -1;

  glGenTextures(1, &TK3_RndTextures[TK3_RndTexturesSize].TexId);
  glBindTexture(GL_TEXTURE_2D, TK3_RndTextures[TK3_RndTexturesSize].TexId);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  strncpy(TK3_RndTextures[TK3_RndTexturesSize].Name, FileName, TK3_STR_MAX - 1);
  TK3_RndTextures[TK3_RndTexturesSize].W = W;
  TK3_RndTextures[TK3_RndTexturesSize].H = H;

  glBindTexture(GL_TEXTURE_2D, 0);

  return TK3_RndTexturesSize++;
  

}

INT TK3_RndTexAdd( CHAR *Name )//, UNIT COW )
{
  FILE *F;

  if (TK3_RndTexturesSize >= TK3_MAX_TEXTURES)
    return -1;

  if ((F = fopen(Name, "rb")) != NULL)
  {
    INT w = 0, h = 0;
    BYTE *mem;

    fread(&w, 2, 1, F);
    fread(&h, 2, 1, F);
    if ((mem = malloc(w * h * 3)) != NULL)
    {
      INT n;

      fread(mem, 3, w * h, F);

      fread(mem, 3, w * h, F);

     
      glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_BGR,
           GL_UNSIGNED_BYTE, mem); 

      n = log(w > h ? w : h) / log(2);
      n = n < 1 ? 1 : n;

      glTexStorage2D(GL_TEXTURE_2D, n, GL_RGB8, w, h);
      glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h,
                      GL_BGR, GL_UNSIGNED_BYTE, mem);

      glGenerateMipmap(GL_TEXTURE_2D);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      TK3_RndTexAddImg("X:\\PICS\\BRICK.G24", w, h);
      free(mem);
    }
    fclose(F);
  }
  return 1;
}
/* END OF 'rndtex.c' FILE */