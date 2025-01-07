/**
 * @file    cfg.h
 * @author  Gyeongtae Kim(dev-dasae) <codingpelican@gmail.com>
 * @date    2024-11-22 (date of creation)
 * @updated 2024-11-22 (date of last update)
 * @version v0.1
 * @ingroup corewar/platform
 * @prefix  PLATFORM
 *
 * @brief   Platform detection configuration
 * @details Detects operating system, environment specifics, and platform features.
 *          Includes OS family, bit width, endianness, and system-specific attributes.
 */

#ifndef PLATFORM_CFG_INCLUDED
#define PLATFORM_CFG_INCLUDED (1)
#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

/*========== Operating System Detection =====================================*/
#if defined(_WIN32) || defined(_WIN64)
#define PLATFORM_WINDOWS (1)
#define PLATFORM_UNIX    (0)
#define PLATFORM_DARWIN  (0)
#define PLATFORM_LINUX   (0)
#define PLATFORM_BSD     (0)
#define PLATFORM_NAME    "Windows"
#elif defined(__APPLE__)
#define PLATFORM_WINDOWS (0)
#define PLATFORM_UNIX    (1)
#define PLATFORM_DARWIN  (1)
#define PLATFORM_LINUX   (0)
#define PLATFORM_BSD     (0)
#define PLATFORM_NAME    "Darwin"
#elif defined(__linux__)
#define PLATFORM_WINDOWS (0)
#define PLATFORM_UNIX    (1)
#define PLATFORM_DARWIN  (0)
#define PLATFORM_LINUX   (1)
#define PLATFORM_BSD     (0)
#define PLATFORM_NAME    "Linux"
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
#define PLATFORM_WINDOWS (0)
#define PLATFORM_UNIX    (1)
#define PLATFORM_DARWIN  (0)
#define PLATFORM_LINUX   (0)
#define PLATFORM_BSD     (1)
#define PLATFORM_NAME    "BSD"
#else
#define PLATFORM_WINDOWS (0)
#define PLATFORM_UNIX    (0)
#define PLATFORM_DARWIN  (0)
#define PLATFORM_LINUX   (0)
#define PLATFORM_BSD     (0)
#define PLATFORM_NAME    "Unknown"
#warning "Unknown platform detected. Some features may not work as expected."
#endif

/*========== Platform Attributes ============================================*/
/* Bit Width Detection */
#if defined(_WIN64) || defined(__x86_64__) || defined(__ppc64__) || defined(__aarch64__)
#define PLATFORM_64BIT (1)
#define PLATFORM_32BIT (0)
#define PLATFORM_BITS  (64)
#elif defined(_WIN32) || defined(__i386__) || defined(__ppc__) || defined(__arm__)
#define PLATFORM_64BIT (0)
#define PLATFORM_32BIT (1)
#define PLATFORM_BITS  (32)
#else
#define PLATFORM_64BIT (0)
#define PLATFORM_32BIT (0)
#define PLATFORM_BITS  (16) /* Default assumption */
#warning "Unknown platform bit width"
#endif

/* Endianness Detection */
#if defined(__BYTE_ORDER__)
#define PLATFORM_BYTE_ORDER               (__BYTE_ORDER__)
#define PLATFORM_BYTE_ORDER_LITTLE_ENDIAN (__ORDER_LITTLE_ENDIAN__)
#define PLATFORM_BYTE_ORDER_BIG_ENDIAN    (__ORDER_BIG_ENDIAN__)
#endif
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define PLATFORM_LITTLE_ENDIAN (1)
#define PLATFORM_BIG_ENDIAN    (0)
#elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define PLATFORM_LITTLE_ENDIAN (0)
#define PLATFORM_BIG_ENDIAN    (1)
#else
#define PLATFORM_LITTLE_ENDIAN (1) /* Default assumption */
#define PLATFORM_BIG_ENDIAN    (0)
#warning "Unknown platform endianness"
#endif

/* Dynamic/Static Library Configuration */
#if PLATFORM_WINDOWS
#define PLATFORM_EXPORT __declspec(dllexport)
#define PLATFORM_IMPORT __declspec(dllimport)
#else
#define PLATFORM_EXPORT __attribute__((visibility("default")))
#define PLATFORM_IMPORT
#endif

#if defined(__cplusplus)
} /* extern "C" */
#endif /* defined(__cplusplus) */
#endif /* PLATFORM_CFG_INCLUDED */
