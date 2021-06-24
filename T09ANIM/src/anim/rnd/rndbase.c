/*FILE NAME: rndbase.c  
  PROGRAMMER: TK3
  DATE:21.06.2021
*/

#include "rnd.h"
#include <wglew.h>
#include <gl/wglext.h>

#pragma comment(lib, "opengl32")

/*Sets the starting position for the camera*/
VOID TK3_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  TK3_RndMatrView = MatrView(Loc, At, Up);
  TK3_RndMatrVP = MatrMulMatr(TK3_RndMatrView, TK3_RndMatrProj);
}

/*Initiates the parameters of the current frame*/
VOID TK3_RndInit( HWND hWnd )
{
  INT i, nums;
  PIXELFORMATDESCRIPTOR pfd = {0};
  HGLRC hRC;
  INT PixelAttribs[] =
  {
    WGL_DRAW_TO_WINDOW_ARB, TRUE,
    WGL_SUPPORT_OPENGL_ARB, TRUE,
    WGL_DOUBLE_BUFFER_ARB, TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 32,
    0
  };
  INT ContextAttribs[] =
  {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
    WGL_CONTEXT_MINOR_VERSION_ARB, 6,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
                                  /* WGL_CONTEXT_CORE_PROFILE_BIT_ARB, */
    0
  };

  TK3_hRndWnd = hWnd;
  TK3_hRndDC = GetDC(hWnd);

  /* OpenGL init: pixel format setup */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(TK3_hRndDC, &pfd);
  DescribePixelFormat(TK3_hRndDC, i, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
  SetPixelFormat(TK3_hRndDC, i, &pfd);

  /* OpenGL init: setup rendering context */
  TK3_hRndGLRC = wglCreateContext(TK3_hRndDC);
  wglMakeCurrent(TK3_hRndDC, TK3_hRndGLRC);

  /* Initializing GLEW library */
  if (glewInit() != GLEW_OK)
  {
    MessageBox(TK3_hRndWnd, "Error extensions initializing", "Error",
      MB_ICONERROR | MB_OK);
    exit(0);
  }

  if (!(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
  {
    MessageBox(TK3_hRndWnd, "Error: no shaders support", "Error", MB_ICONERROR | MB_OK);
    exit(0);
  }

  /* Enable a new OpenGL profile support */
  wglChoosePixelFormatARB(TK3_hRndDC, PixelAttribs, NULL, 1, &i, &nums);
  hRC = wglCreateContextAttribsARB(TK3_hRndDC, NULL, ContextAttribs);

  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(TK3_hRndGLRC);

  TK3_hRndGLRC = hRC;
  wglMakeCurrent(TK3_hRndDC, TK3_hRndGLRC);
  /* Set default OpenGL parameters */
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.3, 0.47, 0.81, 1);
  TK3_RndShadersInit();
}

/*Destroys parameters of a frame*/
VOID TK3_RndClose( VOID )
{
  TK3_RndShadersClose();
  TK3_RndTexClose();
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(TK3_hRndGLRC);
  ReleaseDC(TK3_hRndWnd, TK3_hRndDC);
}

/*Starts the current frame*/
VOID TK3_RndStart( VOID )
{
  static DBL loadtime;

  if ((loadtime += TK3_Anim.GlobalDeltaTime) > 1)
  {
    loadtime = 0;
    TK3_RndShadersUpdate();
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
}

/*Summoned in the end*/
VOID TK3_RndEnd( VOID )
{
   glFinish();
}

/*Copies the frame into the main frame*/
VOID TK3_RndCopyFrame( VOID )
{
  wglSwapLayerBuffers(TK3_hRndDC, WGL_SWAP_MAIN_PLANE);

}

/*Sets the parameters of a projecting matrix*/
VOID TK3_RndProjSet( VOID )
{
  DBL rx, ry;

  rx = ry = TK3_RndProjSize;

  /* Correct aspect ratio */
  if (TK3_RndFrameW > TK3_RndFrameH)
    rx *= (DBL)TK3_RndFrameW / TK3_RndFrameH;
  else
    ry *= (DBL)TK3_RndFrameH / TK3_RndFrameW;

  TK3_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      TK3_RndProjDist, TK3_RndProjFarClip);
  TK3_RndMatrVP = MatrMulMatr(TK3_RndMatrView, TK3_RndMatrProj);
}

/*Resizes the window*/
VOID TK3_RndResize( INT W, INT H )
{
  glViewport(0, 0, W, H);
 /* HDC hDC = GetDC(TK3_hRndWnd);

  if (TK3_hRndBmFrame)
    DeleteObject(TK3_hRndBmFrame);
  TK3_hRndBmFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(TK3_hRndWnd, hDC);		
  SelectObject(TK3_hRndDCFrame, TK3_hRndBmFrame);*/

  TK3_RndFrameW = W;
  TK3_RndFrameH = H;
  TK3_RndProjSet();    
}




/*End of 'rndbase.c' file*/