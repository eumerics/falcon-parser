#ifndef _COMMON_H_
#define _COMMON_H_

#include <uchar.h>
#include <stdint.h>

#define nullptr 0

#ifdef SIMD
   #include <immintrin.h>
#endif
#define wasm_export

#if defined(verbose) && !defined(debug)
   #define debug
#endif
#define suppress(x) x
#if defined(debug)
   #define if_debug(x) x
   #if defined(verbose)
      #define if_verbose(x) x
   #else
      #define if_verbose(x)
   #endif
   #define if_not_debug(x)
   #define if_else_debug(x, y) x
#else
   #define if_debug(x)
   #define if_verbose(x)
   #define if_not_debug(x) x
   #define if_else_debug(x, y) y
#endif
#if defined(profile)
   #define if_profile(x) x
#else
   #define if_profile(x)
#endif
//#define inline_spec if_else_debug(__attribute__((noinline)), static inline)
#define inline_spec if_else_debug(__attribute__((noinline)), static __attribute__((always_inline)))

#define pnot(ptr) (~(uintptr_t)(ptr))
#define pand(ptr, mask) ((uintptr_t)(ptr) & (uintptr_t)(mask))
#define por(ptr, mask)  ((uintptr_t)(ptr) | (uintptr_t)(mask))
#define pxor(ptr, mask) ((uintptr_t)(ptr) ^ (uintptr_t)(mask))
#define pcast(type, ptr) ((type)(ptr))

#if defined(__GNUC__) && !defined(__clang__)
   #if defined(__i386__)
      static __inline__ unsigned long long __rdtsc(void)
      {
         unsigned long long int x;
         __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
         return x;
      }
   #elif defined(__x86_64__)
      static __inline__ unsigned long long __rdtsc(void)
      {
         unsigned hi, lo;
         __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
         return ((unsigned long long) lo) | (((unsigned long long) hi) << 32);
      }
   #endif
#endif

size_t strlen16(char16_t const* s)
{
	uint16_t const* a = s;
	for(; *s; s++);
	return s-a;
}
int strncmp16(char16_t const* l, char16_t const* r, size_t n)
{
	if(!n--) return 0;
	for(; n && *l == *r ; ++l, ++r, --n);
	return *l - *r;
}

#if !defined(UTF16)
   typedef char char_t;
   #define stringize(x) #x
   #define strncmp_impl(x, y, z) strncmp(x, y, z)
   #define strlen_impl(x) strlen(x)
   #define format_specifier "s"
#else
   typedef char16_t char_t;
   #define stringize(x) u ## #x
   #define strncmp_impl(x, y, z) strncmp16(x, y, z)
   #define strlen_impl(x) strlen16(x)
   #define format_specifier "zu"
#endif

// red: 31, green: 32, yellow: 33, blue: 34, magenta: 35, cyan: 36, white: 37
// normal: [0;<id>m, bold: [1;<id>m, reset [0m
#define color_bold_red(x) "\033[1;31m" x "\033[0m"
#define color_bold_green(x) "\033[1;32m" x "\033[0m"
#define color_bold_magenta(x) "\033[1;35m" x "\033[0m"
#define color_bold_cyan(x) "\033[1;36m" x "\033[0m"
#define color_bold_bright_black(x) "\033[1;90m" x "\033[0m"

#ifdef SIMD
   #include "simd.h"
   typedef u08x32 unit_t;
   typedef struct {
      char const* current;
      char const* const begin;
      char const* const end;
      unit_t const* unit_ptr;
      unit_t const* const unit_begin;
      unit_t const* const unit_end;
      size_t unit_bytes_consumed;
   } scanner_status_t;
#endif

#endif //_COMMON_H_
