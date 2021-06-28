/* FILE NAME: rndshd.c
 * PROGRAMMER: TK3
 * DATE: 23.06.2021
 * PURPOSE: 3D animation rendering shader handle functions module.
 */

#include <stdio.h>
#include <string.h>

#include "../rnd.h"


tk3SHADER TK3_RndShaders[TK3_MAX_SHADERS];
INT TK3_RndShadersSize;

/***
 * Base shaders functions
 ***/

/* Save log to file function.
 * ARGUMENTS:
 *   - shader prefix:
 *       CHAR *FileNamePrefix;
 *   - shader name:
 *       CHAR *ShaderName;
 *   - error text:
 *       CHAR *Text;
 * RETURNS: None.
 */
VOID TK3_RndShdLog( CHAR *FileNamePrefix, CHAR *ShaderName, CHAR *Text )
{
  FILE *F;

  if ((F = fopen("BIN/SHADERS/shd{30}tk3.log", "a")) == NULL)
    return;
  fprintf(F, "%s : %s\n%s\n\n", FileNamePrefix, ShaderName, Text);
  fclose(F);
} /* End of 'TK3_RndLoadTextFromFile' function */

/* Load shader text from file function.
 * ARGUMENTS:
 *   - text file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (CHAR *) load text.
 */
CHAR * TK3_RndLoadTextFromFile( CHAR *FileName )
{
  FILE *F;
  INT flen;
  CHAR *txt;

  if ((F = fopen(FileName, "rb")) == NULL)
    return NULL;

  /* Measure file length */
  fseek(F, 0, SEEK_END);
  flen = ftell(F);

  /* Allocate memory */
  if ((txt = malloc(flen + 1)) == NULL)
  {
    fclose(F);
    return NULL;
  }
  /* Load text */
  rewind(F);
  memset(txt, 0, flen + 1);
  fread(txt, 1, flen, F);

  fclose(F);
  return txt;
} /* End of 'TK3_RndLoadTextFromFile' function */

/* Load shader program function.
 * ARGUMENTS:
 *   - shader folder prefix (in 'BIN/SHADERS/***'):
 *       CHAR *FileNamePrefix;
 * RETUNS:
 *   (INT) load shader program Id.
 */
INT TK3_RndShdLoad( CHAR *FileNamePrefix )
{
  struct
  {
    CHAR *Name; /* Shader name (e.g. "VERT") */
    INT Type;   /* Shader type (e.g. GL_VERTEX_SHADER) */
    INT Id;     /* Obtained shader Id from OpenGL */
  } shd[] =
  {
    {"VERT", GL_VERTEX_SHADER, 0},
    {"FRAG", GL_FRAGMENT_SHADER, 0},
  };
  INT NoofS = sizeof(shd) / sizeof(shd[0]), i, prg, res;
  CHAR *txt;
  BOOL is_ok = TRUE;
  static CHAR Buf[1000];

  /* Load shader */
  for (i = 0; i < NoofS; i++)
  {
    /* Build shader name */
    sprintf(Buf, "BIN/SHADERS/%s/%s.glsl", FileNamePrefix, shd[i].Name);

    /* Load shader text from file */
    txt = TK3_RndLoadTextFromFile(Buf);
    if (txt == NULL)
    {
      TK3_RndShdLog(FileNamePrefix, shd[i].Name, "Error load file");
      is_ok = FALSE;
      break;
    }

    /* Create shader */
    if ((shd[i].Id = glCreateShader(shd[i].Type)) == 0)
    {
      TK3_RndShdLog(FileNamePrefix, shd[i].Name, "Error create shader");
      is_ok = FALSE;
      break;
    }

    /* Attach text to shader */
    glShaderSource(shd[i].Id, 1, &txt, NULL);
    free(txt);

    /* Compile shader */
    glCompileShader(shd[i].Id);

    /* Handle errors */
    glGetShaderiv(shd[i].Id, GL_COMPILE_STATUS, &res);
    if (res != 1)
    {
      glGetShaderInfoLog(shd[i].Id, sizeof(Buf), &res, Buf);
      TK3_RndShdLog(FileNamePrefix, shd[i].Name, Buf);
      is_ok = FALSE;
      break;
    }
  }

  /* Create program */
  if (is_ok)
    if ((prg = glCreateProgram()) == 0)
    {
      TK3_RndShdLog(FileNamePrefix, "PROG", "Error create program");
      is_ok = FALSE;
    }
    else
    {
      /* Attach shaders to program */
      for (i = 0; i < NoofS; i++)
        if (shd[i].Id != 0)
          glAttachShader(prg, shd[i].Id);
      /* Link program */
      glLinkProgram(prg);
      glGetProgramiv(prg, GL_LINK_STATUS, &res);
      if (res != 1)
      {
        glGetProgramInfoLog(prg, sizeof(Buf), &res, Buf);
        TK3_RndShdLog(FileNamePrefix, "PROG", Buf);
        is_ok = FALSE;
      }
    }

  /* Handle errors */
  if (!is_ok)
  {
    /* Delete all shaders */
    for (i = 0; i < NoofS; i++)
      if (shd[i].Id != 0)
      {
        if (prg != 0)
          glDetachShader(prg, shd[i].Id);
        glDeleteShader(shd[i].Id);
      }
    /* Delete program */
    if (prg != 0)
      glDeleteProgram(prg);
    prg = 0;
  }
  return prg;
} /* End of 'TK3_RndShdLoad' function */

/* Delete shader program function.
 * ARGUMENTS:
 *   - shader program Id:
 *       INT ProgId;
 * RETUNS: None.
 */
VOID TK3_RndShdFree( INT ProgId )
{
  INT shds[5], n, i;

  if (ProgId == 0 || !glIsProgram(ProgId))
    return;
  glGetAttachedShaders(ProgId, 5, &n, shds);
  for (i = 0; i < n; i++)
    if (glIsShader(shds[i]))
    {
      glDetachShader(ProgId, shds[i]);
      glDeleteShader(shds[i]);
    }
    glDeleteProgram(ProgId);
} /* End of 'TK3_RndShdLoad' function */

/***
 * Shaders stock functions
 ***/

/* Shadre stock array and it size */
//tk3SHADER TK3_RndShaders[TK3_MAX_SHADERS];
//INT TK3_RndShadersSize;

/* Shader stock initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
INT TK3_RndShaderAdd( CHAR *FileNamePrefix )
{
  INT i;

  for (i = 0; i < TK3_RndShadersSize; i++)
    if (strcmp(FileNamePrefix, TK3_RndShaders[i].Name) == 0)
      return i;
  if (TK3_RndShadersSize >= TK3_MAX_SHADERS)
    return 0;
  strncpy(TK3_RndShaders[TK3_RndShadersSize].Name, FileNamePrefix, TK3_STR_MAX - 1);
  TK3_RndShaders[TK3_RndShadersSize].ProgId = TK3_RndShdLoad(FileNamePrefix);
  return TK3_RndShadersSize++;
} /* End of 'TK3_RndShadersAdd' function */

VOID TK3_RndShadersInit( VOID )
{
  TK3_RndShadersSize = 0;
  TK3_RndShaderAdd("DEFAULT");
} /* End of 'TK3_RndShadersInit' function */

/* Shader stock deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID TK3_RndShadersClose( VOID )
{
  INT i;

  for (i = 0; i < TK3_RndShadersSize; i++)
    TK3_RndShdFree(TK3_RndShaders[i].ProgId);
  TK3_RndShadersSize = 0;
} /* End of 'TK3_RndShadersInit' function */

/* Shader add to stock function.
 * ARGUMENTS:
 *   - shader folder prefix:
 *       CHAR *FileNamePrefix;
 * RETURNS:
 *   (INT) shader number in stock.
 */


/* Shader stock update function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID TK3_RndShadersUpdate( VOID )
{
  INT i;

  for (i = 0; i < TK3_RndShadersSize; i++)
  {
    TK3_RndShdFree(TK3_RndShaders[i].ProgId);
    TK3_RndShaders[i].ProgId = TK3_RndShdLoad(TK3_RndShaders[i].Name);
  }
} /* End of 'TK3_RndShadersUpdate' function */

/* END OF 'rndshd.c' FILE */