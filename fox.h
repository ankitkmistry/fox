#ifndef FOX_H_
#define FOX_H_

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// General helping utils
/// - i8
/// - i16
/// - i32
/// - i64
/// - u8
/// - u16
/// - u32
/// - u64
/// - FoxReallocFn
/// - fox_realloc
/// - FOX_UNUSED
/// - FOX_TODO
/// - FOX_UNREACHABLE
/// - FOX_PANIC
/// - FOX_ASSERT
/// - fox_swap
///
/// Internal functions
/// - fox__realloc__
/// - fox__rotate_left__
/// - fox__rotate_right__
/// - fox__str_find_first_of__
/// - fox__str_find_first_not_of__
/// - fox__str_find_last_of__
/// - fox__str_find_last_not_of__
/// - fox__str_compare__
/// - fox__str_equals__
/// - fox__str_starts_with__
/// - fox__str_ends_with__
/// - fox__str_contains__
/// - fox__str_slice__
/// - fox__str_split__
/// - fox__str_trim_left__
/// - fox__str_trim_right__
/// - fox__str_trim__
///
/// Dynamic array utils
/// - fox_da_foreach
/// - fox_da_front
/// - fox_da_back
/// - fox_da_reserve
/// - fox_da_resize
/// - fox_da_free
/// - fox_da_clone
/// - fox_da_copy
/// - fox_da_clear
/// - fox_da_append
/// - fox_push
/// - fox_pop
/// - fox_da_append_many
/// - fox_da_concat
/// - fox_da_rotate_left
/// - fox_da_rotate_right
/// - fox_da_insert
/// - fox_da_insert_many
/// - fox_da_remove
/// - fox_da_remove_range
/// - fox_da_remove_unordered
///
/// Sized string utils
/// - FoxStringBuf
/// - FoxStringView
/// - FoxStringViews
///   Construction
///   - fox_sb_from_bytes
///   - fox_sb_from_cstr
///   - fox_sb_from_char
///   - fox_sv_from_sb
///   - fox_sb_from_copy
///   - fox_sb_free
///
///   - fox_sv_from_raw
///   - fox_sv_from_cstr
///   - fox_sb_from_sv
///
///   Modification
///   - fox_sb_append_null
///   - fox_sb_concat
///   - fox_sb_append_bytes
///   - fox_sb_append_cstr
///   - fox_sb_insert
///   - fox_sb_replace
///   - fox_sb_tolower
///   - fox_sb_toupper
///
///   Search
///   - fox_str_find_first_of
///   - fox_str_find_first_not_of
///   - fox_str_find_last_of
///   - fox_str_find_last_not_of
///
///   Others
///   - fox_str_compare
///   - fox_str_equals
///   - fox_str_starts_with
///   - fox_str_ends_with
///   - fox_str_contains
///   - fox_str_slice
///   - fox_str_split
///   - fox_str_trim_left
///   - fox_str_trim_right
///   - fox_str_trim

#if defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
// Intel C++ Compiler (ICC and ICX)
#    define FOX_PRINTF_FORMAT(STRING_INDEX, FIRST_TO_CHECK) __attribute__((format(printf, STRING_INDEX, FIRST_TO_CHECK)))
#elif defined(__MINGW32__) || defined(__MINGW64__)
// MinGW-specific: Handles both MSVC and GNU-style stdio based on configuration
#    define FOX_PRINTF_FORMAT(STRING_INDEX, FIRST_TO_CHECK) __attribute__((format(__MINGW_PRINTF_FORMAT, STRING_INDEX, FIRST_TO_CHECK)))
#elif defined(__GNUC__) || defined(__clang__)
// For GCC and Clang
#    define FOX_PRINTF_FORMAT(STRING_INDEX, FIRST_TO_CHECK) __attribute__((format(printf, STRING_INDEX, FIRST_TO_CHECK)))
#elif defined(_MSC_VER)
// For Microsoft Visual C++ (Modern versions support __format_string)
#    include <sal.h>
#    define FOX_PRINTF_FORMAT(STRING_INDEX, FIRST_TO_CHECK) _Printf_format_string_
#else
// Fallback for other compilers that don't support format checking
#    define FOX_PRINTF_FORMAT(STRING_INDEX, FIRST_TO_CHECK)
#endif

// Useful typedefs
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// Internal functions
void *fox__realloc__(void *p, size_t size);
void fox__rotate_left__(void *v_data, size_t item_size, size_t items_count, size_t n);
void fox__rotate_right__(void *v_data, size_t item_size, size_t items_count, size_t n);

// Configurable realloc fn
typedef void *(*FoxReallocFn)(void *p, size_t size);
FoxReallocFn fox_realloc = fox__realloc__;

#define FOX_UNUSED(value) (void) (value)
#define FOX_TODO(msg)                                                                                                                                \
    do {                                                                                                                                             \
        fprintf(stderr, "%s:%d: TODO: %s\n", __FILE__, __LINE__, msg);                                                                               \
        abort();                                                                                                                                     \
    } while (false)
#define FOX_UNREACHABLE(msg)                                                                                                                         \
    do {                                                                                                                                             \
        fprintf(stderr, "%s:%d: UNREACHABLE: %s\n", __FILE__, __LINE__, msg);                                                                        \
        abort();                                                                                                                                     \
    } while (false)
#define FOX_PANIC(msg) (fprintf(stderr, "%s:%d: PANIC: %s\n", __FILE__, __LINE__, (msg)), abort())
#define FOX_ASSERT(cond, msg) ((cond) ? (void) 0 : (fprintf(stderr, "%s:%d: ASSERT: %s\n", __FILE__, __LINE__, (msg)), abort()))
#define FOX_ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

#define fox_swap(Type, left, right)                                                                                                                  \
    do {                                                                                                                                             \
        Type fox__tmp__ = (left);                                                                                                                    \
        (left) = (right);                                                                                                                            \
        (right) = (fox__tmp__);                                                                                                                      \
    } while (false)

#ifndef FOX_ARRAY_INITIAL_CAP
#    define FOX_ARRAY_INITIAL_CAP 8
#endif // FOX_ARRAY_INITIAL_CAP

#ifndef FOX_ARRAY_GROWTH_FACTOR
#    define FOX_ARRAY_GROWTH_FACTOR 2
#endif // FOX_ARRAY_GROWTH_FACTOR

// Dynamic array utils
#define fox_da_foreach(Type, it, arr) for (Type *it = (arr)->items; it < (arr)->items + (arr)->count; ++it)
#define fox_da_front(arr) (FOX_ASSERT((arr)->size > 0, "array cannot be empty"), (arr)->items[0])
#define fox_da_back(arr) (FOX_ASSERT((arr)->size > 0, "array cannot be empty"), (arr)->items[(arr)->size - 1])

#define fox_da_reserve(arr, new_cap)                                                                                                                 \
    do {                                                                                                                                             \
        if ((new_cap) > (arr)->capacity) {                                                                                                           \
            if ((arr)->capacity == 0)                                                                                                                \
                (arr)->capacity = FOX_ARRAY_INITIAL_CAP;                                                                                             \
            while ((new_cap) > (arr)->capacity)                                                                                                      \
                (arr)->capacity *= 2;                                                                                                                \
            FOX_ASSERT(fox_realloc != NULL, "fox_realloc cannot be NULL");                                                                           \
            (arr)->items = fox_realloc((arr)->items, (arr)->capacity * sizeof((arr)->items)[0]);                                                     \
            FOX_ASSERT((arr)->items != NULL, "realloc failed");                                                                                      \
        }                                                                                                                                            \
    } while (false)

#define fox_da_resize(arr, new_size)                                                                                                                 \
    do {                                                                                                                                             \
        fox_da_reserve((arr), (new_size));                                                                                                           \
        (arr)->size = (new_size);                                                                                                                    \
    } while (false)

#define fox_da_free(arr)                                                                                                                             \
    do {                                                                                                                                             \
        (arr)->size = (arr)->capacity = 0;                                                                                                           \
        FOX_ASSERT(fox_realloc != NULL, "fox_realloc cannot be NULL");                                                                               \
        (arr)->items = fox_realloc((arr)->items, 0);                                                                                                 \
    } while (false)

#define fox_da_copy(dest, src)                                                                                                                       \
    do {                                                                                                                                             \
        fox_da_free((dest));                                                                                                                         \
        (dest)->size = (src)->size;                                                                                                                  \
        (dest)->capacity = (src)->capacity;                                                                                                          \
        FOX_ASSERT(fox_realloc != NULL, "fox_realloc cannot be NULL");                                                                               \
        (dest)->items = fox_realloc((dest)->items, (dest)->capacity * sizeof((dest)->items[0]));                                                     \
        memcpy((dest)->items, (src)->items, (dest)->size * sizeof((dest)->items[0]));                                                                \
    } while (false)

#define fox_da_clear(arr)                                                                                                                            \
    do {                                                                                                                                             \
        (arr)->size = 0;                                                                                                                             \
    } while (false)

#define fox_da_append(arr, value)                                                                                                                    \
    do {                                                                                                                                             \
        fox_da_reserve((arr), (arr)->size + 1);                                                                                                      \
        (arr)->items[(arr)->size++] = (value);                                                                                                       \
    } while (false)

#define fox_push(arr, value) fox_da_append(arr, value)
#define fox_pop(arr) (FOX_ASSERT((arr)->size > 0, "array cannot be empty"), (arr)->items[--(arr)->size])

#define fox_da_append_many(arr, others, others_count)                                                                                                \
    do {                                                                                                                                             \
        fox_da_reserve((arr), (arr)->size + (others_count));                                                                                         \
        memcpy((arr)->items + (arr)->size, (others), (others_count) * sizeof((arr)->items[0]));                                                      \
        (arr)->size += (others_count);                                                                                                               \
    } while (false)

#define fox_da_concat(left, right) fox_da_append_many((left), (right)->items, (right)->size)
#define fox_da_rotate_left(arr, n) fox__rotate_left__((arr)->items, sizeof((arr)->items[0]), (arr)->size, (n))
#define fox_da_rotate_right(arr, n) fox__rotate_right__((arr)->items, sizeof((arr)->items[0]), (arr)->size, (n))

#define fox_da_insert(arr, index, value)                                                                                                             \
    do {                                                                                                                                             \
        FOX_ASSERT((index) <= (arr)->size, "index is invalid");                                                                                      \
        fox_da_reserve((arr), (arr)->size + 1);                                                                                                      \
        memmove(&(arr)->items[(index) + 1], &(arr)->items[(index)], ((arr)->size - (index)) * sizeof((arr)->items[0]));                              \
        (arr)->items[(index)] = (value);                                                                                                             \
        (arr)->size += 1;                                                                                                                            \
    } while (false)

#define fox_da_insert_many(arr, index, data, n)                                                                                                      \
    do {                                                                                                                                             \
        FOX_ASSERT((index) + (n) < (arr)->size, "index is invalid");                                                                                 \
        fox_da_reserve((arr), (arr)->size + (n));                                                                                                    \
        memmove(&(arr)->items[(index) + 1], &(arr)->items[(index)], ((arr)->size - (index)) * sizeof((arr)->items[0]));                              \
        memcpy(&(arr)->items[(index)], data, n * sizeof((arr)->items[0]));                                                                           \
        (arr)->size += n;                                                                                                                            \
    } while (false)

#define fox_da_remove(arr, index)                                                                                                                    \
    do {                                                                                                                                             \
        FOX_ASSERT((index) < (arr)->size, "index is invalid");                                                                                       \
        if ((index) == (arr)->size - 1) {                                                                                                            \
            fox_pop((arr));                                                                                                                          \
        } else {                                                                                                                                     \
            (arr)->size -= 1;                                                                                                                        \
            memmove(&(arr)->items[(index)], &(arr)->items[(index) + 1], ((arr)->size - (index)) * sizeof((arr)->items[0]));                          \
        }                                                                                                                                            \
    } while (false)

#define fox_da_remove_range(arr, start, end)                                                                                                         \
    do {                                                                                                                                             \
        size_t real_start = (start) < (end) ? (start) : (end);                                                                                       \
        size_t real_end = (start) < (end) ? (end) : (start);                                                                                         \
        FOX_ASSERT(real_start < (arr)->size, "start index is invalid");                                                                              \
        FOX_ASSERT(real_end <= (arr)->size, "end index is invalid");                                                                                 \
        memmove(&(arr)->items[real_start], &(arr)->items[real_end], (arr)->size - real_end);                                                         \
        (arr)->size -= (end) - (start);                                                                                                              \
    } while (false);

#define fox_da_remove_unordered(arr, index)                                                                                                          \
    do {                                                                                                                                             \
        FOX_ASSERT((index) < ((arr))->size, "index is invalid");                                                                                     \
        (arr)->items[(index)] = (arr)->items[--(arr)->count];                                                                                        \
    } while (false)

// INFO: Though StringBuf and is sized, items still
// contains the null character for compatibility reasons
// but size but does not include the null character

typedef struct {
    char *items;
    size_t size;
    size_t capacity;
} FoxStringBuf;

typedef struct {
    const char *items;
    size_t size;
} FoxStringView;

typedef struct {
    FoxStringView *items;
    size_t size;
    size_t capacity;
} FoxStringViews;

size_t fox__str_find_first_of__(const FoxStringView *self, const FoxStringView *str);
size_t fox__str_find_first_not_of__(const FoxStringView *self, const FoxStringView *str);
size_t fox__str_find_last_of__(const FoxStringView *self, const FoxStringView *str);
size_t fox__str_find_last_not_of__(const FoxStringView *self, const FoxStringView *str);
bool fox__str_compare__(const FoxStringView *left, const FoxStringView *right);
bool fox__str_equals__(const FoxStringView *left, const FoxStringView *right);
bool fox__str_starts_with__(const FoxStringView *str, const FoxStringView *prefix);
bool fox__str_ends_with__(const FoxStringView *str, const FoxStringView *suffix);
bool fox__str_contains__(const FoxStringView *str, const FoxStringView *needle);
FoxStringView fox__str_slice__(const FoxStringView *str, size_t start, size_t end);
FoxStringViews fox__str_split__(const FoxStringView *str, char delimiter);
FoxStringView fox__str_trim_left__(const FoxStringView *str);
FoxStringView fox__str_trim_right__(const FoxStringView *str);
FoxStringView fox__str_trim__(const FoxStringView *str);

// Construction
FoxStringBuf fox_sb_from_bytes(const u8 *data, size_t count);
FoxStringBuf fox_sb_from_cstr(const char *str);
FoxStringBuf fox_sb_from_char(char c, size_t count);
FoxStringBuf fox_sb_from_sv(const FoxStringView sv);
FoxStringBuf fox_sb_clone(const FoxStringBuf *sb);
void fox_sb_copy(FoxStringBuf *dest, const FoxStringBuf *src);
void fox_sb_free(FoxStringBuf *sb);

FoxStringView fox_sv_from_raw(const char *str, size_t count);
FoxStringView fox_sv_from_cstr(const char *str);
FoxStringView fox_sv_from_sb(const FoxStringBuf *sb);

// Modification
void fox_sb_append_null(FoxStringBuf *sb);
void fox_sb_appendf(FoxStringBuf *sb, const char *fmt, ...) FOX_PRINTF_FORMAT(2, 3);

#define fox_sb_concat(sb, src) fox_da_concat((sb), (src))
#define fox_sb_append_bytes(sb, bytes, count) fox_da_append_many((sb), (bytes), (count));

#define fox_sb_append_cstr(sb, str)                                                                                                                  \
    do {                                                                                                                                             \
        const char *fox__str__ = (str);                                                                                                              \
        size_t fox__count__ = strlen(str);                                                                                                           \
        fox_da_append_many((sb), fox__str__, fox__count__);                                                                                          \
    } while (false)

#define fox_sb_insert(sb, index, other) fox_da_insert_many(sb, index, other->items, other->size)

#define fox_sb_replace(sb, start, end, other)                                                                                                        \
    do {                                                                                                                                             \
        fox_da_remove_range(sb, start, end);                                                                                                         \
        fox_sb_insert(sb, start, other);                                                                                                             \
    } while (false)

void fox_sb_tolower(FoxStringBuf *sb);
void fox_sb_toupper(FoxStringBuf *sb);

#define fox_str_find_first_of(self, str) fox__str_find_first_of__((const FoxStringView *) (self), (const FoxStringView *) (str))
#define fox_str_find_first_not_of(self, str) fox__str_find_first_not_of__((const FoxStringView *) (self), (const FoxStringView *) (str))
#define fox_str_find_last_of(self, str) fox__str_find_last_of__((const FoxStringView *) (self), (const FoxStringView *) (str))
#define fox_str_find_last_not_of(self, str) fox__str_find_last_not_of__((const FoxStringView *) (self), (const FoxStringView *) (str))

#define fox_str_compare(left, right) fox__str_compare__((const FoxStringView *) (left), (const FoxStringView *) (right))
#define fox_str_equals(left, right) fox__str_equals__((const FoxStringView *) (left), (const FoxStringView *) (right))
#define fox_str_starts_with(str, prefix) fox__str_starts_with__((const FoxStringView *) (str), (const FoxStringView *) (prefix))
#define fox_str_ends_with(str, suffix) fox__str_ends_with__((const FoxStringView *) (str), (const FoxStringView *) (suffix))
#define fox_str_contains(str, suffix) fox__str_contains__((const FoxStringView *) (str), (const FoxStringView *) (suffix))
#define fox_str_slice(str, start, end) fox__str_slice__((const FoxStringView *) (str), (start), (end))
#define fox_str_split(str, delimiter) fox__str_split__((const FoxStringView *) (str), (delimiter));
#define fox_str_trim_left(str) fox__str_trim_left__((const FoxStringView *) (str))
#define fox_str_trim_right(str) fox__str_trim_right__((const FoxStringView *) (str))
#define fox_str_trim(str) fox__str_trim__((const FoxStringView *) (str))

#define SV_Fmt "%.*s"
#define SV_Arg(sv) (int) (sv).size, (sv).items
/// Usage:
///   StringView sv = ...;
///   printf("sv: "SV_Arg"\n", SV_Arg(sv));

#endif // FOX_H_

#define FOX_IMPLEMENTATION
#ifdef FOX_IMPLEMENTATION

void *fox__realloc__(void *p, size_t size) {
    if (size == 0) {
        free(p);
        return NULL;
    } else
        return realloc(p, size);
}

void fox__rotate_left__(void *v_data, size_t item_size, size_t items_count, size_t n) {
    if (!v_data)
        return;
    // Avoid too many rotations
    n %= items_count;
    // Operate on data as bytes
    u8 *data = v_data;
    // Allocate temporary storage
    void *tmp = malloc(n * item_size);
    FOX_ASSERT(tmp != NULL, "malloc failed");
    // Rotate left
    memcpy(tmp, data, n * item_size);
    memmove(data, data + n * item_size, (items_count - n) * item_size);
    memcpy(data + (items_count - n) * item_size, tmp, n * item_size);
    // Free temporary storage
    free(tmp);
}

void fox__rotate_right__(void *v_data, size_t item_size, size_t items_count, size_t n) {
    if (!v_data)
        return;
    // Avoid too many rotations
    n %= items_count;
    // Operate on data as bytes
    u8 *data = v_data;
    // Allocate temporary storage
    void *tmp = malloc(n * item_size);
    FOX_ASSERT(tmp != NULL, "malloc failed");
    // Rotate right
    memcpy(tmp, data + (items_count - n) * item_size, n * item_size);
    memmove(data + n * item_size, data, (items_count - n) * item_size);
    memcpy(data, tmp, n * item_size);
    // Free temporary storage
    free(tmp);
}

size_t fox__str_find_first_of__(const FoxStringView *self, const FoxStringView *str) {
    if (!self || !str)
        return (size_t) -1;

    for (size_t i = 0; i < self->size; ++i) {
        char c = self->items[i];
        // Check if current_char is present in the str set
        for (size_t j = 0; j < str->size; ++j) {
            if (c == str->items[j])
                return i; // Found the first occurrence
        }
    }
    return (size_t) -1;
}

size_t fox__str_find_first_not_of__(const FoxStringView *self, const FoxStringView *str) {
    if (!self)
        return (size_t) -1;
    if (!str)
        return 0;

    for (size_t i = 0; i < self->size; ++i) {
        char c = self->items[i];
        bool found = false;
        // Check if current_char is present in the str set
        for (size_t j = 0; j < str->size; ++j) {
            if (c == str->items[j]) {
                found = true;
                break; // Found the first occurrence
            }
        }
        if (!found)
            return i;
    }
    return (size_t) -1;
}

size_t fox__str_find_last_of__(const FoxStringView *self, const FoxStringView *str) {
    if (!self || !str)
        return (size_t) -1;

    for (size_t index = self->size; index > 0; index--) {
        size_t i = index - 1;
        char c = self->items[i];
        // Check if current_char is present in the str set
        for (size_t j = 0; j < str->size; ++j) {
            if (c == str->items[j])
                return i; // Found the last occurrence
        }
    }
    return (size_t) -1;
}

size_t fox__str_find_last_not_of__(const FoxStringView *self, const FoxStringView *str) {
    if (!self)
        return (size_t) -1;
    if (!str)
        return 0;

    for (size_t index = self->size; index > 0; index--) {
        size_t i = index - 1;
        char c = self->items[i];
        bool found = false;
        // Check if current_char is present in the str set
        for (size_t j = 0; j < str->size; ++j) {
            if (c == str->items[j]) {
                found = true;
                break; // Found the first occurrence
            }
        }
        if (!found)
            return i;
    }
    return (size_t) -1;
}

bool fox__str_compare__(const FoxStringView *left, const FoxStringView *right) {
    if (!left || !right)
        return 0;
    // Find the minimum length to compare
    size_t min_size = (left->size < right->size) ? left->size : right->size;
    // Compare characters up to the shorter length
    int result = memcmp(left->items, right->items, min_size);
    if (result != 0) {
        return result; // Mismatch found within min_size
    }
    if (left->size < right->size)
        return -1;
    if (left->size > right->size)
        return 1;
    return 0; // Lengths and contents are identical
}

bool fox__str_equals__(const FoxStringView *left, const FoxStringView *right) {
    if (left->size != right->size)
        return false;
    return fox__str_compare__(left, right) == 0;
}

bool fox__str_starts_with__(const FoxStringView *str, const FoxStringView *prefix) {
    if (!str || !prefix || prefix->size > str->size)
        return false;
    return memcmp(str->items, prefix->items, prefix->size) == 0;
}

bool fox__str_ends_with__(const FoxStringView *str, const FoxStringView *suffix) {
    if (!str || !suffix || suffix->size > str->size)
        return false;
    return memcmp(&str->items[str->size - suffix->size], suffix->items, suffix->size) == 0;
}

bool fox__str_contains__(const FoxStringView *str, const FoxStringView *needle) {
    if (!str || !needle)
        return false;
    // An empty needle is technically contained in any string
    if (needle->size == 0)
        return true;
    // Needle cannot be longer than the haystack
    if (needle->size > str->size)
        return false;
    // Naive search
    size_t limit = str->size - needle->size;
    for (size_t i = 0; i <= limit; ++i)
        if (memcmp(str->items + i, needle->items, needle->size) == 0)
            return true;
    return false;
}

FoxStringView fox__str_slice__(const FoxStringView *str, size_t start, size_t end) {
    size_t real_start = start < end ? start : end;
    size_t real_end = start < end ? end : start;
    FOX_ASSERT(real_start < str->size, "start index is invalid");
    FOX_ASSERT(real_end <= str->size, "end index is invalid");

    if (!str || str->size == 0)
        return (FoxStringView) {0};
    return (FoxStringView) {
            .items = real_end == real_start ? NULL : &str->items[real_start],
            .size = real_end - real_start,
    };
}

FoxStringViews fox__str_split__(const FoxStringView *str, char delimiter) {
    FoxStringViews result = {0};
    size_t start = 0;
    size_t index = 0;
    for (; index < str->size; index++) {
        if (str->items[index] == delimiter) {
            fox_da_append(&result, fox__str_slice__(str, start, index));
            start = index;
        }
    }
    if (start < index)
        fox_da_append(&result, fox__str_slice__(str, start, index));
    return result;
}

FoxStringView fox__str_trim_left__(const FoxStringView *str) {
    for (size_t i = 0; i < str->size; i++) {
        if (str->items[i] != ' ')
            return fox__str_slice__(str, i, str->size);
    }
    return (FoxStringView) {0};
}

FoxStringView fox__str_trim_right__(const FoxStringView *str) {
    for (size_t index = str->size; index > 0; index--) {
        size_t i = index - 1;
        if (str->items[i] != ' ')
            return fox__str_slice__(str, 0, i + 1);
    }
    return (FoxStringView) {0};
}

FoxStringView fox__str_trim__(const FoxStringView *str) {
    FoxStringView text = fox__str_trim_left__(str);
    text = fox__str_trim_right__(&text);
    return text;
}

FoxStringBuf fox_sb_from_bytes(const u8 *data, size_t count) {
    FoxStringBuf sb = {0};
    fox_da_reserve(&sb, count + 1);
    sb.size = count;
    memcpy(sb.items, data, sb.size);
    sb.items[sb.size] = '\0';
    return sb;
}

FoxStringBuf fox_sb_from_cstr(const char *str) {
    FoxStringBuf sb = {0};
    size_t str_size = strlen(str);
    fox_da_reserve(&sb, str_size + 1);
    sb.size = str_size;
    memcpy(sb.items, str, sb.size + 1);
    return sb;
}

FoxStringBuf fox_sb_from_char(char c, size_t count) {
    FoxStringBuf sb = {0};
    fox_da_reserve(&sb, count + 1);
    sb.size = count;
    memset(sb.items, c, sb.size);
    sb.items[sb.size] = '\0';
    return sb;
}

FoxStringBuf fox_sb_from_sv(const FoxStringView sv) {
    FoxStringBuf sb = {0};
    fox_da_reserve(&sb, sv.size + 1);
    sb.size = sv.size;
    memcpy(sb.items, sv.items, sb.size);
    sb.items[sb.size] = '\0';
    return sb;
}

FoxStringBuf fox_sb_clone(const FoxStringBuf *sb) {
    FoxStringBuf result = {0};
    fox_da_copy(&result, sb);
    return result;
}

void fox_sb_copy(FoxStringBuf *dest, const FoxStringBuf *src) {
    fox_da_reserve(dest, src->size + 1);
    dest->size = src->size;
    memcpy(dest->items, src->items, src->size);
    dest->items[dest->size] = '\0';
}

void fox_sb_free(FoxStringBuf *sb) {
    // Aha! got ya, sb is a valid dynarray
    fox_da_free(sb);
}

void fox_sb_append_null(FoxStringBuf *sb) {
    fox_da_reserve(sb, sb->size + 1);
    sb->items[sb->size] = '\0';
}

void fox_sb_appendf(FoxStringBuf *sb, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    va_list args_for_size_computation;
    va_copy(args_for_size_computation, args);
    int n = vsnprintf(NULL, 0, fmt, args_for_size_computation);
    va_end(args_for_size_computation);
    if (n == -1)
        FOX_PANIC("vsprintf failed");

    fox_da_reserve(sb, sb->size + n + 1);
    vsnprintf(&sb->items[sb->size], n + 1, fmt, args);
    va_end(args);

    sb->size += n;
    sb->items[sb->size] = '\0';
}

void fox_sb_tolower(FoxStringBuf *sb) {
    for (size_t i = 0; i < sb->size; i++)
        sb->items[i] = tolower(sb->items[i]);
}

void fox_sb_toupper(FoxStringBuf *sb) {
    for (size_t i = 0; i < sb->size; i++)
        sb->items[i] = toupper(sb->items[i]);
}

FoxStringView fox_sv_from_raw(const char *str, size_t count) {
    return (FoxStringView) {
            .items = str,
            .size = count,
    };
}

FoxStringView fox_sv_from_cstr(const char *str) {
    return (FoxStringView) {
            .items = str,
            .size = strlen(str),
    };
}

FoxStringView fox_sv_from_sb(const FoxStringBuf *sb) {
    return (FoxStringView) {
            .items = sb->items,
            .size = sb->size,
    };
}

#endif // FOX_IMPLEMENTATION
