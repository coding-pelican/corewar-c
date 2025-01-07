/**
 * @file    str.h
 * @author  Gyeongtae Kim(dev-dasae) <codingpelican@gmail.com>
 * @date    2024-12-31 (date of creation)
 * @updated 2024-12-31 (date of last update)
 * @version v0.1
 * @ingroup corewar
 * @prefix  str
 *
 * @brief
 * @details
 */

#include "def.h"
#include <string.h>

#if PLATFORM_WINDOWS
extern char* strndup(const char* str, size_t n);
#endif

/* ========== Slices ======================================================= */

/* Slice types */

typedef struct s_sli_const_u8 {
    const u8* ptr;
    usize     len;
} t_sli_const_u8;

typedef union u_sli_u8 {
    struct {
        u8*   ptr;
        usize len;
    };
    t_sli_const_u8 as_const;
} t_sli_u8;

/* ========== Strings ====================================================== */

/* String types */
typedef t_sli_const_u8 t_str_const;
typedef t_sli_u8       t_str;

/* Optional string types */
typedef struct s_opt_str_const {
    bool        has_value;
    t_str_const value;
} t_opt_str_const;

typedef struct s_opt_str {
    bool  has_value;
    t_str value;
} t_opt_str;

#define none(T)          ((T){ .has_value = false })
#define some(T, _val_x)  ((T){ .has_value = true, .value = _val_x }) // NOLINT
#define isSome(_val_opt) ((_val_opt).has_value)
#define isNone(_val_opt) (!isSome(_val_opt))

/* Core methods */

// For string literals (read-only)
#define literal_str(_lit) ((t_str_const){ .ptr = (const u8*)"" _lit, .len = sizeof(_lit) - 1 })
// For modifiable strings (creates new array)
#define mutable_str(_lit) ((t_str){ .ptr = (u8[]){ "" _lit }, .len = sizeof(_lit) - 1 })

// Create StrConst from const u8* with explicit length
extern t_str_const str_const(const u8* ptr, usize len);
// Create Str from u8* with explicit length
extern t_str       str_from(u8 ptr[], usize len);

// Get string length in bytes
extern usize       str_len(t_str_const str);
// Compare two strings
extern bool        str_eq(t_str_const lhs, t_str_const rhs);
// Check if string is modifiable
extern bool        str_const_castable(t_str_const str);
// Convert StrConst to Str (if source is modifiable)
extern t_opt_str   str_mut(t_str_const str);
// Get substring
extern t_str_const str_slice(t_str_const str, usize start, usize end);
// Check if string contains substring
extern bool        str_contains(t_str_const haystack, t_str_const needle);

/* Sentinel-terminated slices */

typedef struct u_sli_z_const_u8 {
    const u8* ptr;
    usize     len;
    u8        sentinel;
} t_sli_z_const_u8;

typedef union u_sli_z_u8 {
    struct {
        u8*   ptr;
        usize len;
        u8    sentinel;
    };
    t_sli_z_const_u8 as_const;
} t_sli_z_u8;

/* Sentinel-terminated strings */

typedef t_sli_z_const_u8 t_str_z_const;
typedef t_sli_z_u8       t_str_z;

/* memory utils */

/*========== Memory Utilities ===============================================*/

// Memory operations
extern void mem_set(void* dest, u8 value, usize size);
extern void mem_copy(void* dest, const void* src, usize size);
extern void mem_move(void* dest, void* src, usize size);
extern i32  mem_cmp(const void* lhs, const void* rhs, usize size);

// Copy bytes between buffers with bounds checking
extern void mem_copy_bytes(u8* dest, const u8* src, usize len);
// Set bytes to value with bounds checking
extern void mem_set_bytes(u8* dest, u8 value, usize len);
// Compare two byte buffers
extern bool mem_eql_bytes(const u8* lhs, const u8* rhs, usize len);
