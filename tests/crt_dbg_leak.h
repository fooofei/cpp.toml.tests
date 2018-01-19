
/*
  call this at the executable/library main/.cpp's file
  with a (static) global variable



  a blog http://blog.jobbole.com/95375/
  this blog say if called _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
  then _CrtDumpMemoryLeaks() will auto called, no need to manual call. On my test, it was wrong.



  this can detect malloc/calloc/realloc/new



  some way will use:
  // #ifdef _DEBUG
  // #ifndef DBG_NEW
  // #define DBG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
  // #define new DBG_NEW
  // #endif // !DBG_NEW
  // #endif
  if use this way, we cannot use new(std::nothrow), I will not accept it

*/

#pragma once 


#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#else


#endif // WIN32


struct  _crt_dbg_leak
{
    int oldflag;
};

void lock(struct _crt_dbg_leak *);
void unlock(struct _crt_dbg_leak *);






/* also we can use #pragma init_seg(compiler) at the global variable defined location
   to make sure the check is before at all static global variable init 
   NOT must
*/
#ifdef __cplusplus

#ifdef WIN32
typedef struct _crt_dbg_leak_t
{
    struct  _crt_dbg_leak ins;


    _crt_dbg_leak_t(long break_alloc = 0)
    {
        memset(&ins, 0, sizeof(ins));
        lock(&ins);
        if (break_alloc != 0)
        {
            _CrtSetBreakAlloc(break_alloc);
        }
    }
    ~_crt_dbg_leak_t()
    {
        unlock(&ins);
    }
}_crt_dbg_leak_t;

#else

typedef struct _crt_dbg_leak_t
{
    _crt_dbg_leak_t(long = 0)
    {
    }
    ~_crt_dbg_leak_t()
    {
    }
}_crt_dbg_leak_t;
#endif // WIN32

#endif //__cplusplus


