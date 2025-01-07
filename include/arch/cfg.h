/**
 * @file    cfg.h
 * @author  Gyeongtae Kim(dev-dasae) <codingpelican@gmail.com>
 * @date    2024-10-27 (date of creation)
 * @updated 2024-11-22 (date of last update)
 * @version v1.0.0
 * @ingroup corewar/arch
 * @prefix  ARCH
 *
 * @brief   Architecture detection configuration
 * @details Detects CPU architecture, instruction sets, and hardware capabilities.
 *          Includes CPU family, SIMD support, and architecture-specific features.
 */

#ifndef ARCH_CFG_INCLUDED
#define ARCH_CFG_INCLUDED (1)
#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

/*========== CPU Architecture Detection =====================================*/
#if defined(__x86_64__) || defined(_M_X64)
#define ARCH_X64    (1)
#define ARCH_X86    (0)
#define ARCH_ARM64  (0)
#define ARCH_ARM32  (0)
#define ARCH_NAME   "x86_64"
#define ARCH_FAMILY "x86"
#elif defined(__i386__) || defined(_M_IX86)
#define ARCH_X64    (0)
#define ARCH_X86    (1)
#define ARCH_ARM64  (0)
#define ARCH_ARM32  (0)
#define ARCH_NAME   "x86"
#define ARCH_FAMILY "x86"
#elif defined(__aarch64__) || defined(_M_ARM64)
#define ARCH_X64    (0)
#define ARCH_X86    (0)
#define ARCH_ARM64  (1)
#define ARCH_ARM32  (0)
#define ARCH_NAME   "ARM64"
#define ARCH_FAMILY "ARM"
#elif defined(__arm__) || defined(_M_ARM)
#define ARCH_X64    (0)
#define ARCH_X86    (0)
#define ARCH_ARM64  (0)
#define ARCH_ARM32  (1)
#define ARCH_NAME   "ARM"
#define ARCH_FAMILY "ARM"
#else
#define ARCH_X64    (0)
#define ARCH_X86    (0)
#define ARCH_ARM64  (0)
#define ARCH_ARM32  (0)
#define ARCH_NAME   "Unknown"
#define ARCH_FAMILY "Unknown"
#warning "Unknown architecture detected. Please check your architecture settings."
#endif

/*========== SIMD Support Detection =========================================*/
#if ARCH_X86 || ARCH_X64
#define ARCH_HAS_SSE    (defined(__SSE__))
#define ARCH_HAS_SSE2   (defined(__SSE2__))
#define ARCH_HAS_SSE3   (defined(__SSE3__))
#define ARCH_HAS_SSSE3  (defined(__SSSE3__))
#define ARCH_HAS_SSE4_1 (defined(__SSE4_1__))
#define ARCH_HAS_SSE4_2 (defined(__SSE4_2__))
#define ARCH_HAS_AVX    (defined(__AVX__))
#define ARCH_HAS_AVX2   (defined(__AVX2__))
#endif

#if ARCH_ARM32 || ARCH_ARM64
#define ARCH_HAS_NEON  (defined(__ARM_NEON))
#define ARCH_HAS_ASIMD (defined(__ARM_FEATURE_SIMD32))
#endif

/*========== Cache Line Size ================================================*/
#if ARCH_X86 || ARCH_X64
#define ARCH_CACHE_LINE (64)
#elif ARCH_ARM32 || ARCH_ARM64
#define ARCH_CACHE_LINE (32)
#else
#define ARCH_CACHE_LINE (64) /* Default assumption */
#endif

#if defined(__cplusplus)
} /* extern "C" */
#endif /* defined(__cplusplus) */
#endif /* ARCH_CFG_INCLUDED */
