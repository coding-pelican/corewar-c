#include "str.h"

#include <assert.h>
#include <locale.h>

#if PLATFORM_WINDOWS
#include <memoryapi.h>
#include <winnt.h>

static void __attribute__((constructor)) str_utf8_init(void) {
    static bool initialized = false;
    if (initialized) { return; }
    /* Set locale for proper UTF-8 handling */
    ignore setlocale(LC_ALL, ".UTF-8"); /* Code page 65001 */
    initialized = true;
}

char* strndup(const char* str, size_t n) {
    size_t len = strnlen(str, n);
    char* new  = (char*)malloc(len + 1);

    if (new == NULL) { return NULL; }

    memcpy(new, str, len);
    new[len] = '\0';
    return new;
}
#endif /* PLATFORM_WINDOWS */

t_str_const str_const(const u8* ptr, usize len) {
    assert(ptr);
    return (t_str_const){ .ptr = ptr, .len = len };
}

t_str str_from(u8 ptr[], usize len) {
    assert(ptr);
    return (t_str){ .ptr = ptr, .len = len };
}

usize str_len(t_str_const str) {
    return str.len;
}

bool str_eq(t_str_const lhs, t_str_const rhs) {
    if (lhs.len != rhs.len) { return false; }
    return mem_eql_bytes(lhs.ptr, rhs.ptr, lhs.len);
}

bool str_const_castable(t_str_const str) {
#if PLATFORM_WINDOWS
    MEMORY_BASIC_INFORMATION mbi = { 0 };
    if (!VirtualQuery(str.ptr, &mbi, sizeof(mbi))) { return false; }
    return (mbi.Protect & (PAGE_READWRITE | PAGE_WRITECOPY)) != 0;
#else
    // POSIX systems
    return !mprotect(
        (void*)((uintptr_t)str.ptr & ~(sysconf(_SC_PAGESIZE) - 1)),
        1,
        PROT_READ | PROT_WRITE
    )
#endif
}

t_opt_str str_mut(t_str_const str) {
    if (!str_const_castable(str)) {
        return none(t_opt_str);
    }
    return some(t_opt_str, str_from((u8*)str.ptr, str.len));
}

t_str_const str_slice(t_str_const str, usize start, usize end) {
    assert(start <= end);
    assert(end <= str.len);
    return str_const(str.ptr + start, end - start);
}

bool str_contains(t_str_const haystack, t_str_const needle) {
    if (haystack.len < needle.len) { return false; }
    for (usize index = 0; index <= haystack.len - needle.len; ++index) {
        if (mem_eql_bytes(haystack.ptr + index, needle.ptr, needle.len)) {
            return true;
        }
    }
    return false;
}

void mem_set(void* dest, u8 value, usize size) {
    assert(dest);
    memset(dest, value, size);
}

void mem_copy(void* dest, const void* src, usize size) {
    assert(dest);
    assert(src);
    memcpy(dest, src, size);
}

void mem_move(void* dest, void* src, usize size) {
    assert(dest);
    assert(src);
    memmove(dest, src, size);
}

i32 mem_cmp(const void* lhs, const void* rhs, usize size) {
    assert(lhs);
    assert(rhs);
    return memcmp(lhs, rhs, size);
}

void mem_copy_bytes(u8* dest, const u8* src, usize len) {
    assert(dest);
    assert(src);
    mem_copy(dest, src, len);
}

void mem_set_bytes(u8* dest, u8 value, usize len) {
    assert(dest);
    mem_set(dest, value, len);
}

bool mem_eql_bytes(const u8* lhs, const u8* rhs, usize len) {
    assert(lhs);
    assert(rhs);
    return mem_cmp(lhs, rhs, len) == 0;
}
