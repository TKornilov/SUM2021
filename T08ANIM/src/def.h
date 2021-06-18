/*FILE NAME: def.h   
  PROGRAMMER: TK3
  DATE:17.06.2021
*/
#ifndef __def_h_
#define __def_h_

#pragma warning(disable: 4244)

/* Debug memory allocation support */
#ifndef NDEBUG
#  define _CRTDBG_MAP_ALLOC
#  include <crtdbg.h>
#  define SetDbgMemHooks() \
     _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
       _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#else /* _DEBUG */
#  define SetDbgMemHooks() ((void)0)
#endif /* _DEBUG */

#include <stdio.h>
#include <stdlib.h>
#include "mth/mth.h"
#include "anim/rnd/rnd.h"

#endif /* __def_h_ */

/*End of 'def.h' file*/