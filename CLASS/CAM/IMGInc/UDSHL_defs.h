#ifndef UDSHL_DEFS_H_INC
#define UDSHL_DEFS_H_INC

#include "libbasedefs.h"

#pragma warning( disable : 4786 ) // too long debug info // may be ignored

#ifdef UDSHL_GENERATE_DLL_EXPORTS
	#define _UDSHL_EXP_API	__declspec(dllexport)
#else
	#define _UDSHL_EXP_API	__declspec(dllimport)
#endif

#define UDSHL_LIB_VERSION_MAJOR	3
#define UDSHL_LIB_VERSION_MINOR	4

#if !defined UDSHL_DISABLE_DEPRECATE_MESSAGES_ && defined UDSHL_GENERATE_DLL_EXPORTS
#define UDSHL_DISABLE_DEPRECATE_MESSAGES_
#endif

// use UDSHL_DEPRECATE_FUNCION_DISABLE_ to disable deprecation
#if _MSC_VER > 1500 && !defined UDSHL_DISABLE_DEPRECATE_MESSAGES_
#define UDSHL_DEPRECATE_FUNCTION_	__declspec(deprecated)
#define UDSHL_DEPRECATE_FUNCTION_TEXT_(text)	__declspec(deprecated(text))
// Text generated is: "was declared deprecated. Instead, use the <replacement>."
#define UDSHL_DEPRECATE_FUNCTION_T_(replacement)       __declspec(deprecated("was declared deprecated. Instead, use the " replacement "."))
#else
#define UDSHL_DEPRECATE_FUNCTION_
#define UDSHL_DEPRECATE_FUNCTION_TEXT_(text)
#define UDSHL_DEPRECATE_FUNCTION_T_(replacement)
#endif

#endif // UDSHL_DEFS_H_INC