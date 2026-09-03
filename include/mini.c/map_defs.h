#ifndef MINI_C_HASH_H
#define MINI_C_HASH_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "mini.c/mini_def.h"

/*
 * Hash functions have the form:
 *
 *     usize mini_<type>_hash(const Type *value);
 *
 * Equality functions have the form:
 *
 *     bool mini_<type>_eq(const Type *a, const Type *b);
 */


/* ============================================================
 * Integer types
 * ============================================================ */
static inline usize mini_size_hash(const usize *x);

static inline usize mini_int_hash(const int *x) {
    uint32_t v = (uint32_t)*x;

    v ^= v >> 16;
    v *= UINT32_C(0x85ebca6b);
    v ^= v >> 13;
    v *= UINT32_C(0xc2b2ae35);
    v ^= v >> 16;

    return (usize)v;
}

static inline bool mini_int_eq(const int *a, const int *b) {
    return *a == *b;
}


static inline usize mini_uint_hash(const unsigned int *x) {
    uint32_t v = (uint32_t)*x;

    v ^= v >> 16;
    v *= UINT32_C(0x85ebca6b);
    v ^= v >> 13;
    v *= UINT32_C(0xc2b2ae35);
    v ^= v >> 16;

    return (usize)v;
}

static inline bool mini_uint_eq(const unsigned int *a,
                                const unsigned int *b) {
    return *a == *b;
}


static inline usize mini_long_hash(const long *x) {
    return mini_size_hash((const usize *)x);
}

static inline bool mini_long_eq(const long *a, const long *b) {
    return *a == *b;
}

static inline usize mini_ulong_hash(const unsigned long *x) {
    return mini_size_hash((const usize *)x);
}

static inline bool mini_ulong_eq(const unsigned long *a,
                                 const unsigned long *b) {
    return *a == *b;
}


static inline usize mini_llong_hash(const long long *x) {
    uint64_t v = (uint64_t)*x;

    v ^= v >> 30;
    v *= UINT64_C(0xbf58476d1ce4e5b9);
    v ^= v >> 27;
    v *= UINT64_C(0x94d049bb133111eb);
    v ^= v >> 31;

    return (usize)v;
}

static inline bool mini_llong_eq(const long long *a,
                                 const long long *b) {
    return *a == *b;
}


static inline usize mini_ullong_hash(const unsigned long long *x) {
    uint64_t v = (uint64_t)*x;

    v ^= v >> 30;
    v *= UINT64_C(0xbf58476d1ce4e5b9);
    v ^= v >> 27;
    v *= UINT64_C(0x94d049bb133111eb);
    v ^= v >> 31;

    return (usize)v;
}

static inline bool mini_ullong_eq(const unsigned long long *a,
                                  const unsigned long long *b) {
    return *a == *b;
}


/* ============================================================
 * Fixed-width integers
 * ============================================================ */

static inline usize mini_i8_hash(const int8_t *x) {
    return mini_int_hash((const int *)x);
}

static inline bool mini_i8_eq(const int8_t *a, const int8_t *b) {
    return *a == *b;
}

static inline usize mini_u8_hash(const uint8_t *x) {
    uint32_t v = *x;
    v ^= v >> 16;
    v *= UINT32_C(0x85ebca6b);
    v ^= v >> 13;
    v *= UINT32_C(0xc2b2ae35);
    v ^= v >> 16;
    return (usize)v;
}

static inline bool mini_u8_eq(const uint8_t *a, const uint8_t *b) {
    return *a == *b;
}


static inline usize mini_i16_hash(const int16_t *x) {
    uint32_t v = (uint16_t)*x;

    v ^= v >> 16;
    v *= UINT32_C(0x85ebca6b);
    v ^= v >> 13;
    v *= UINT32_C(0xc2b2ae35);
    v ^= v >> 16;

    return (usize)v;
}

static inline bool mini_i16_eq(const int16_t *a, const int16_t *b) {
    return *a == *b;
}


static inline usize mini_u16_hash(const uint16_t *x) {
    uint32_t v = *x;

    v ^= v >> 16;
    v *= UINT32_C(0x85ebca6b);
    v ^= v >> 13;
    v *= UINT32_C(0xc2b2ae35);
    v ^= v >> 16;

    return (usize)v;
}

static inline bool mini_u16_eq(const uint16_t *a, const uint16_t *b) {
    return *a == *b;
}


static inline usize mini_i32_hash(const int32_t *x) {
    uint32_t v = (uint32_t)*x;

    v ^= v >> 16;
    v *= UINT32_C(0x85ebca6b);
    v ^= v >> 13;
    v *= UINT32_C(0xc2b2ae35);
    v ^= v >> 16;

    return (usize)v;
}

static inline bool mini_i32_eq(const int32_t *a, const int32_t *b) {
    return *a == *b;
}


static inline usize mini_u32_hash(const uint32_t *x) {
    uint32_t v = *x;

    v ^= v >> 16;
    v *= UINT32_C(0x85ebca6b);
    v ^= v >> 13;
    v *= UINT32_C(0xc2b2ae35);
    v ^= v >> 16;

    return (usize)v;
}

static inline bool mini_u32_eq(const uint32_t *a, const uint32_t *b) {
    return *a == *b;
}


static inline usize mini_i64_hash(const int64_t *x) {
    uint64_t v = (uint64_t)*x;

    v ^= v >> 30;
    v *= UINT64_C(0xbf58476d1ce4e5b9);
    v ^= v >> 27;
    v *= UINT64_C(0x94d049bb133111eb);
    v ^= v >> 31;

    return (usize)v;
}

static inline bool mini_i64_eq(const int64_t *a, const int64_t *b) {
    return *a == *b;
}


static inline usize mini_u64_hash(const uint64_t *x) {
    uint64_t v = *x;

    v ^= v >> 30;
    v *= UINT64_C(0xbf58476d1ce4e5b9);
    v ^= v >> 27;
    v *= UINT64_C(0x94d049bb133111eb);
    v ^= v >> 31;

    return (usize)v;
}

static inline bool mini_u64_eq(const uint64_t *a, const uint64_t *b) {
    return *a == *b;
}


/* ============================================================
 * size_t
 * ============================================================ */

static inline usize mini_size_hash(const usize *x) {
#if SIZE_MAX == UINT64_MAX
    uint64_t v = (uint64_t)*x;

    v ^= v >> 30;
    v *= UINT64_C(0xbf58476d1ce4e5b9);
    v ^= v >> 27;
    v *= UINT64_C(0x94d049bb133111eb);
    v ^= v >> 31;

    return (usize)v;
#else
    uint32_t v = (uint32_t)*x;

    v ^= v >> 16;
    v *= UINT32_C(0x85ebca6b);
    v ^= v >> 13;
    v *= UINT32_C(0xc2b2ae35);
    v ^= v >> 16;

    return (usize)v;
#endif
}

static inline bool mini_size_eq(const usize *a, const usize *b) {
    return *a == *b;
}


/* ============================================================
 * bool
 * ============================================================ */

static inline usize mini_bool_hash(const bool *x) {
    return (usize)*x;
}

static inline bool mini_bool_eq(const bool *a, const bool *b) {
    return *a == *b;
}


/* ============================================================
 * char
 * ============================================================ */

static inline usize mini_char_hash(const char *x) {
    uint32_t v = (unsigned char)*x;

    v ^= v >> 16;
    v *= UINT32_C(0x85ebca6b);
    v ^= v >> 13;
    v *= UINT32_C(0xc2b2ae35);
    v ^= v >> 16;

    return (usize)v;
}

static inline bool mini_char_eq(const char *a, const char *b) {
    return *a == *b;
}


/* ============================================================
 * C strings
 *
 * Key type:
 *
 *     char *
 *
 * Hash receives:
 *
 *     char *const *
 *
 * because the map passes &key.
 * ============================================================ */

static inline usize mini_cstr_hash(char *const *str) {
    const unsigned char *p = (const unsigned char *)*str;

    /* FNV-1a */
    usize hash = (usize)1469598103934665603ULL;

    while (*p) {
        hash ^= (usize)*p++;
        hash *= (usize)1099511628211ULL;
    }

    return hash;
}

static inline bool mini_cstr_eq(char *const *a, char *const *b) {
    return strcmp(*a, *b) == 0;
}


/* ============================================================
 * const C strings
 * ============================================================ */

static inline usize mini_const_cstr_hash(const char *const *str) {
    const unsigned char *p = (const unsigned char *)*str;

    usize hash = (usize)1469598103934665603ULL;

    while (*p) {
        hash ^= (usize)*p++;
        hash *= (usize)1099511628211ULL;
    }

    return hash;
}

static inline bool mini_const_cstr_eq(const char *const *a,
                                      const char *const *b) {
    return strcmp(*a, *b) == 0;
}


/* ============================================================
 * Pointers
 * ============================================================ */

static inline usize mini_ptr_hash(void *const *ptr) {
    uintptr_t v = (uintptr_t)*ptr;

    v ^= v >> 30;
    v *= (uintptr_t)UINT64_C(0xbf58476d1ce4e5b9);
    v ^= v >> 27;
    v *= (uintptr_t)UINT64_C(0x94d049bb133111eb);
    v ^= v >> 31;

    return (usize)v;
}

static inline bool mini_ptr_eq(void *const *a, void *const *b) {
    return *a == *b;
}

#endif /* MINI_C_HASH_H */
