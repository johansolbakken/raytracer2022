#pragma once

#include "defines.h"

#ifndef NDEBUG
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else //_MSC_VER
#define debugBreak() __builtin_trap()
#endif //_MSC_VER
#else // NDEBUG
#define debugBreak()
#endif // NDEBUG

 void reportAssertionFailure(const char* expression, const char* message, const char* file, i32 line);

#define ASSERTIONS_ENABLED 1

#if ASSERTIONS_ENABLED
#define ENGINE_ASSERT(expr) \
    {                          \
        if(expr) {                \
        }else{                    \
            reportAssertionFailure(#expr, "", __FILE__, __LINE__); \
			debugBreak();\
        }                        \
    }

#define ENGINE_ASSERT_MSG(expr, message) \
    {                          \
        if(expr) {                \
        }else{                    \
            reportAssertionFailure(#expr, message, __FILE__, __LINE__); \
			debugBreak();\
        }                        \
    }

#ifndef NDEBUG
#define ENGINE_ASSERT_DEBUG(expr) \
    {                          \
        if(expr) {                \
        }else{                    \
            reportAssertionFailure(#expr, "", __FILE__, __LINE__); \
			debugBreak();\
        }                        \
    }
#else
#define ENGINE_ASSERT_DEBUG(expr)
#endif
#else // ASSERTIONS_ENABLED
#define ENGINE_ASSERT(expr)
#define ENGINE_ASSERT_MSG(expr, message)
#define ENGINE_ASSERT_DEBUG(expr)
#endif