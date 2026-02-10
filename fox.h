#ifndef FOX_H_
#define FOX_H_

#include <bits/types/struct_timeval.h>
#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

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
/// - fox_return_defer
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
///
///   Construction
///   - fox_sb_from_bytes
///   - fox_sb_from_cstr
///   - fox_sb_from_char
///   - fox_sb_from_sv
///   - fox_sb_copy
///   - fox_sb_free
///
///   - fox_sv_from_raw
///   - fox_sv_from_cstr
///   - fox_sv_from_sb
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
///
///   TODO: do something about error reporting
///   fox_get_error_message
///
/// Filesystem utils
///   Convenience functions
///   - fox_fs_read_entire_file
///   - fox_fs_write_entire_file
///   - fox_fs_read_symlink
///
///   File Attribute functions
///   - FoxFileType
///   - FoxFilePerms
///   - FoxFileStatus
///   - fox_fs_file_status
///   - fox_fs_symlink_status
///   - fox_fs_set_status
///   - fox_fs_set_symlink_status
///   - fox_fs_set_perms
///   - fox_fs_set_symlink_perms
///   - fox_fs_file_type
///   - fox_fs_file_size
///
///   File Type functions
///   - fox_fs_is_block_file
///   - fox_fs_is_character_file
///   - fox_fs_is_dir
///   - fox_fs_is_empty
///   - fox_fs_is_fifo
///   - fox_fs_is_other
///   - fox_fs_is_regular_file
///   - fox_fs_is_socket
///   - fox_fs_is_symlink
///
///   File Helper functions
///   - fox_fs_getcwd
///   - fox_fs_setcwd
///   - fox_fs_exists
///   - fox_fs_equivalent
///   - fox_fs_canonical
///
///   File operations
///   - fox_fs_create_dir
///   - fox_fs_create_dir_all
///   - fox_fs_create_symlink
///   - fox_fs_remove
///   - fox_fs_remove_all
///   - fox_fs_rename
///   - fox_fs_move
///   - FoxCopyOptions
///   - fox_fs_copy
///   - fox_fs_copy_file
///   - fox_fs_copy_symlink

#if defined(_WIN32)
#    define FOX_OS_WINDOWS /// Windows
#endif
#if defined(_WIN64)
#    define FOX_OS_WINDOWS /// Windows
#endif
#if defined(__CYGWIN__) && !defined(_WIN32)
#    define FOX_OS_WINDOWS /// Windows (Cygwin POSIX under Microsoft Windows)
#endif
#if defined(__unix__)
#    define FOX_OS_UNIX /// Unix and Unix-like systems
#endif
#if defined(__linux__) || defined(__gnu_linux__) || defined(__ANDROID__)
#    define FOX_OS_LINUX /// Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
#endif
#if defined(__APPLE__) && defined(__MACH__)
#    define FOX_OS_UNIX /// Unix and Unix-like systems
#    define FOX_OS_MAC  /// Apple OSX and iOS (Darwin)
#endif

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

#ifdef FOX_OS_WINDOWS
#    define FOX_FILE_SEPARATOR "\\"
#else
#    define FOX_FILE_SEPARATOR "/"
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

#define fox_return_defer(value)                                                                                                                      \
    do {                                                                                                                                             \
        result = (value);                                                                                                                            \
        goto defer;                                                                                                                                  \
    } while (false)
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
#define fox_da_foreach(Type, it, arr) for (Type *it = (arr)->items; it < (arr)->items + (arr)->size; ++it)
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

size_t fox__str_find_first_of__(const FoxStringView *self, const FoxStringView str);
size_t fox__str_find_first_not_of__(const FoxStringView *self, const FoxStringView str);
size_t fox__str_find_last_of__(const FoxStringView *self, const FoxStringView str);
size_t fox__str_find_last_not_of__(const FoxStringView *self, const FoxStringView str);
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
void fox_sb_copy(FoxStringBuf *dest, const FoxStringView src);
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

#define fox_str_find_first_of(self, str) fox__str_find_first_of__((const FoxStringView *) (self), (str))
#define fox_str_find_first_not_of(self, str) fox__str_find_first_not_of__((const FoxStringView *) (self), (str))
#define fox_str_find_last_of(self, str) fox__str_find_last_of__((const FoxStringView *) (self), (str))
#define fox_str_find_last_not_of(self, str) fox__str_find_last_not_of__((const FoxStringView *) (self), (str))

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
#define SV_Arg(sv) (int) (sv)->size, (sv)->items
/// Usage:
///   StringView sv = ...;
///   printf("sv: "SV_Arg"\n", SV_Arg(sv));

const char *fox_get_error_message(void);

bool fox_fs_read_entire_file(const char *path, FoxStringBuf *sb);
bool fox_fs_write_entire_file(const char *path, const FoxStringView *sv);
bool fox_fs_read_symlink(const char *path, FoxStringBuf *sb);

typedef enum {
    FILE_UNKNOWN,
    FILE_REGULAR,
    FILE_DIR,
    FILE_SYMLINK,
    FILE_BLOCK,
    FILE_CHARACTER,
    FILE_FIFO,
    FILE_SOCKET,
} FoxFileType;

typedef enum {
    PERM_NONE = 0,
    PERM_OWNER_READ = 0400,
    PERM_OWNER_WRITE = 0200,
    PERM_OWNER_EXEC = 0100,
    PERM_OWNER_ALL = PERM_OWNER_READ | PERM_OWNER_WRITE | PERM_OWNER_EXEC,
    PERM_GROUP_READ = 040,
    PERM_GROUP_WRITE = 020,
    PERM_GROUP_EXEC = 010,
    PERM_GROUP_ALL = PERM_GROUP_READ | PERM_GROUP_WRITE | PERM_GROUP_EXEC,
    PERM_OTHERS_READ = 04,
    PERM_OTHERS_WRITE = 02,
    PERM_OTHERS_EXEC = 01,
    PERM_OTHERS_ALL = PERM_OTHERS_READ | PERM_OTHERS_WRITE | PERM_OTHERS_EXEC,
    PERM_ALL = PERM_OWNER_ALL | PERM_GROUP_ALL | PERM_OTHERS_ALL,
    PERM_SET_UID = 04000,
    PERM_SET_GID = 02000,
    PERM_STICKY_BIT = 01000,
    PERM_MASK = PERM_ALL | PERM_SET_UID | PERM_SET_GID | PERM_STICKY_BIT,
} FoxFilePerms;

typedef struct {
    FoxFileType type;
    size_t size;
    FoxFilePerms perms;
    time_t last_modified; //< in seconds
    time_t last_accessed; //< in seconds
} FoxFileStatus;

typedef struct {
    uintmax_t capacity;
    uintmax_t free;
    uintmax_t available;
} FoxSpaceInfo;

bool fox_fs_file_status(const char *path, FoxFileStatus *status);
bool fox_fs_symlink_status(const char *path, FoxFileStatus *status);
bool fox_fs_set_status(const char *path, FoxFileStatus status);
bool fox_fs_set_symlink_status(const char *path, FoxFileStatus status);
bool fox_fs_set_perms(const char *path, FoxFilePerms perms);
bool fox_fs_set_symlink_perms(const char *path, FoxFilePerms perms);
FoxFileType fox_fs_file_type(const char *path);
uintmax_t fox_fs_file_size(const char *path);

bool fox_fs_is_block_file(const char *path);
bool fox_fs_is_character_file(const char *path);
bool fox_fs_is_dir(const char *path);
bool fox_fs_is_empty(const char *path);
bool fox_fs_is_fifo(const char *path);
bool fox_fs_is_other(const char *path);
bool fox_fs_is_regular_file(const char *path);
bool fox_fs_is_socket(const char *path);
bool fox_fs_is_symlink(const char *path);

FoxStringBuf fox_fs_getcwd(void);
bool fox_fs_setcwd(const char *path);
bool fox_fs_exists(const char *path);
bool fox_fs_equivalent(const char *path1, const char *path2);
bool fox_fs_canonical(FoxStringBuf *sb);
bool fox_fs_space(const char *path, FoxSpaceInfo *space);

bool fox_fs_create_dir(const char *path);
bool fox_fs_create_dir_all(const char *path);
bool fox_fs_create_symlink(const char *target, const char *link);
bool fox_fs_remove(const char *path);
bool fox_fs_remove_all(const char *path);
bool fox_fs_rename(const char *old_path, const char *new_path);
bool fox_fs_move(const char *old_path, const char *new_path);

typedef struct {
    unsigned existing  : 2;
    unsigned recursive : 1;
    unsigned symlink   : 2;
    unsigned other     : 2;
} FoxCopyOptions;

// FoxCopyOptions.existing
#define COPY_SKIP_EXISTING 1
#define COPY_OVERWRITE_EXISTING 2
#define COPY_UPDATE_EXISTING 3
// FoxCopyOptions.recursive = true, false
// FoxCopyOptions.symlink
#define COPY_COPY_SYMLINKS 1
#define COPY_SKIP_SYMLINKS 1
// FoxCopyOptions.other
#define COPY_DIRS_ONLY 1
#define COPY_CREATE_SYMLINKS 2
#define COPY_HARD_LINKS 3

// TODO: implement fox_fs_copy
bool fox_fs_copy_file(const char *from, const char *to, FoxCopyOptions options);
bool fox_fs_copy_symlink(const char *from, const char *to);

#endif // FOX_H_

#define FOX_IMPLEMENTATION
#ifdef FOX_IMPLEMENTATION

#ifdef FOX_OS_UNIX
#    include <unistd.h>
#endif
#ifdef _POSIX_VERSION
#    define FOX_OS_POSIX
#    include <fcntl.h>
#    include <sys/stat.h>
#    include <sys/statvfs.h>
#    include <sys/time.h>
#else
#    error "Bro are you mad? Compile this on a POSIX compliant system"
#endif

void *fox__realloc__(void *p, size_t size) {
    // If p == NULL and size > 0 then return malloc(size)
    // If p == NULL and size == 0 then return NULL
    // If size == 0 then free(p)
    // Else return realloc(p, size)
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

size_t fox__str_find_first_of__(const FoxStringView *self, const FoxStringView str) {
    if (!self)
        return self->size;

    for (size_t i = 0; i < self->size; ++i) {
        char c = self->items[i];
        // Check if current_char is present in the str set
        for (size_t j = 0; j < str.size; ++j) {
            if (c == str.items[j])
                return i; // Found the first occurrence
        }
    }
    return self->size;
}

size_t fox__str_find_first_not_of__(const FoxStringView *self, const FoxStringView str) {
    if (!self)
        return self->size;

    for (size_t i = 0; i < self->size; ++i) {
        char c = self->items[i];
        bool found = false;
        // Check if current_char is present in the str set
        for (size_t j = 0; j < str.size; ++j) {
            if (c == str.items[j]) {
                found = true;
                break; // Found the first occurrence
            }
        }
        if (!found)
            return i;
    }
    return self->size;
}

size_t fox__str_find_last_of__(const FoxStringView *self, const FoxStringView str) {
    if (!self)
        return self->size;

    for (size_t index = self->size; index > 0; index--) {
        size_t i = index - 1;
        char c = self->items[i];
        // Check if current_char is present in the str set
        for (size_t j = 0; j < str.size; ++j) {
            if (c == str.items[j])
                return i; // Found the last occurrence
        }
    }
    return self->size;
}

size_t fox__str_find_last_not_of__(const FoxStringView *self, const FoxStringView str) {
    if (!self)
        return self->size;

    for (size_t index = self->size; index > 0; index--) {
        size_t i = index - 1;
        char c = self->items[i];
        bool found = false;
        // Check if current_char is present in the str set
        for (size_t j = 0; j < str.size; ++j) {
            if (c == str.items[j]) {
                found = true;
                break; // Found the first occurrence
            }
        }
        if (!found)
            return i;
    }
    return self->size;
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
    if (str == NULL)
        return sb;

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
    if (sv.size == 0)
        return sb;

    fox_da_reserve(&sb, sv.size + 1);
    sb.size = sv.size;
    memcpy(sb.items, sv.items, sb.size);
    sb.items[sb.size] = '\0';
    return sb;
}

void fox_sb_copy(FoxStringBuf *dest, const FoxStringView src) {
    if (src.size == 0) {
        dest->size = 0;
        return;
    }

    fox_da_reserve(dest, src.size + 1);
    dest->size = src.size;
    memcpy(dest->items, src.items, src.size);
    dest->items[dest->size] = '\0';
}

FoxStringBuf fox_sb_clone(const FoxStringBuf *sb) {
    FoxStringBuf result = {0};
    fox_da_copy(&result, sb);
    return result;
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
            .size = str ? strlen(str) : 0,
    };
}

FoxStringView fox_sv_from_sb(const FoxStringBuf *sb) {
    return (FoxStringView) {
            .items = sb->items,
            .size = sb->size,
    };
}

const char *fox_get_error_message() {
#ifdef FOX_OS_POSIX
    return strerror(errno);
#else
#    error "Implement this"
#endif
}

bool fox_fs_read_entire_file(const char *path, FoxStringBuf *sb) {
    bool result = true;
    // Open the file
    FILE *f = fopen(path, "rb");
    if (f == NULL)
        fox_return_defer(false);
    // Go to end
    if (fseek(f, 0, SEEK_END) != 0)
        fox_return_defer(false);
    // Get number of bytes
    long size = ftell(f);
    if (size < 0)
        fox_return_defer(false);
    // Go to beginning again for reading
    if (fseek(f, 0, SEEK_SET) != 0)
        fox_return_defer(false);
    // Now read into the buffer
    fox_da_clear(sb);
    fox_da_reserve(sb, (unsigned long) size + 1);
    fread(&sb->items[sb->size], sizeof(sb->items[0]), size, f);
    if (ferror(f))
        fox_return_defer(false);
    // Do not forget to set the null terminator for compat reasons
    sb->size += size;
    sb->items[sb->size] = '\0';

defer:
    // TODO: log errors
    if (f)
        fclose(f);
    return result;
}

bool fox_fs_write_entire_file(const char *path, const FoxStringView *sv) {
    bool result = true;
    // Open the file
    FILE *f = fopen(path, "wb");
    if (f == NULL)
        fox_return_defer(false);
    // Write everything
    fwrite(sv->items, sizeof(sv->items[0]), sv->size, f);
    if (ferror(f))
        fox_return_defer(false);

defer:
    // TODO: log errors
    if (f)
        fclose(f);
    return result;
}

bool fox_fs_read_symlink(const char *path, FoxStringBuf *sb) {
    if (!sb || !path || strlen(path) == 0)
        return false;

#if defined(FOX_OS_POSIX)
    bool result;
    char *buf = NULL;
    fox_da_clear(sb);

    FoxFileStatus status;
    if (!fox_fs_symlink_status(path, &status))
        fox_return_defer(false);
    if (status.type != FILE_SYMLINK)
        fox_return_defer(false);

    const size_t buf_size = status.size;
    buf = malloc(buf_size + 1);
    ssize_t len = readlink(path, buf, buf_size + 1);

    if (len == -1)
        fox_return_defer(false);
    buf[len] = '\0';
    fox_sb_copy(sb, fox_sv_from_cstr(buf));

defer:
    free(buf);
    return result;
#else
#    error "Implement this"
#endif
}

#if defined(FOX_OS_POSIX)
static FoxFileType fox__fs_file_type__posix(mode_t mode) {
    if (S_ISREG(mode))
        return FILE_REGULAR;
    else if (S_ISDIR(mode))
        return FILE_DIR;
    else if ((mode & 0170000) == 0120000)
        return FILE_SYMLINK; // This work only when lstat() is used
    else if (S_ISCHR(mode))
        return FILE_CHARACTER;
    else if (S_ISBLK(mode))
        return FILE_BLOCK;
    else if (S_ISFIFO(mode))
        return FILE_FIFO;
    else if ((mode & 0170000) == 0140000)
        return FILE_SOCKET;
    else
        return FILE_UNKNOWN;
}
#endif

bool fox_fs_file_status(const char *path, FoxFileStatus *status) {
    if (!status || !path || strlen(path) == 0)
        return false;

#if defined(FOX_OS_POSIX)
    struct stat file_info;
    if (stat(path, &file_info) < 0)
        return false;

    // Get the file type
    status->type = fox__fs_file_type__posix(file_info.st_mode);
    status->size = file_info.st_size;
    status->perms = (FoxFilePerms) (file_info.st_mode & PERM_MASK);
    status->last_modified = file_info.st_mtime;
    status->last_accessed = file_info.st_atime;
    return true;
#else
#    error "Implement this"
#endif
}

bool fox_fs_symlink_status(const char *path, FoxFileStatus *status) {
    if (!status || !path || strlen(path) == 0)
        return false;

#if defined(FOX_OS_POSIX)
    struct stat file_info;
    if (lstat(path, &file_info) < 0)
        return false;

    // Get the file type
    status->type = fox__fs_file_type__posix(file_info.st_mode);
    status->size = file_info.st_size;
    status->perms = (FoxFilePerms) (file_info.st_mode & PERM_MASK);
    status->last_modified = file_info.st_mtime;
    status->last_accessed = file_info.st_atime;
    return true;
#else
#    error "Implement this"
#endif
}

FoxFileType fox_fs_file_type(const char *path) {
    FoxFileStatus status;
    if (fox_fs_file_status(path, &status))
        return status.type;
    return FILE_UNKNOWN;
}

uintmax_t fox_fs_file_size(const char *path) {
    FoxFileStatus status;
    if (fox_fs_file_status(path, &status))
        return status.size;
    return (uintmax_t) -1;
}

bool fox_fs_set_status(const char *path, FoxFileStatus status) {
    if (!path || strlen(path) == 0)
        return false;

    fox_fs_set_perms(path, status.perms);

#if defined(FOX_OS_POSIX)
    const struct timeval acc_time = {status.last_accessed, 0};
    const struct timeval mod_time = {status.last_modified, 0};
    if (utimes(path, (const struct timeval[2]) {acc_time, mod_time}) == 0)
        return true;
    return false;
#else
#    error "Implement this"
#endif
}

bool fox_fs_set_symlink_status(const char *path, FoxFileStatus status) {
    if (!path || strlen(path) == 0)
        return false;

    fox_fs_set_symlink_perms(path, status.perms);

#if defined(FOX_OS_POSIX)
    const struct timeval acc_time = {status.last_accessed, 0};
    const struct timeval mod_time = {status.last_modified, 0};
    if (lutimes(path, (const struct timeval[2]) {acc_time, mod_time}) == 0)
        return true;
    return false;
#else
#    error "Implement this"
#endif
}

bool fox_fs_set_perms(const char *path, FoxFilePerms perms) {
    if (!path || strlen(path) == 0)
        return false;

#if defined(FOX_OS_POSIX)
    if (chmod(path, (mode_t) perms) == 0)
        return true;
    return false;
#else
#    error "Implement this"
#endif
}

bool fox_fs_set_symlink_perms(const char *path, FoxFilePerms perms) {
    if (!path || strlen(path) == 0)
        return false;

#if defined(FOX_OS_POSIX)
    if (fchmodat(AT_FDCWD, path, (mode_t) perms, AT_SYMLINK_NOFOLLOW))
        return true;
    return false;
#else
#    error "Implement this"
#endif
}

bool fox_fs_is_block_file(const char *path) { return fox_fs_file_type(path) == FILE_BLOCK; }

bool fox_fs_is_character_file(const char *path) { return fox_fs_file_type(path) == FILE_CHARACTER; }

bool fox_fs_is_dir(const char *path) { return fox_fs_file_type(path) == FILE_DIR; }

bool fox_fs_is_empty(const char *path) {
    if (!fox_fs_exists(path))
        return false;
    switch (fox_fs_file_type(path)) {
    case FILE_REGULAR:
    case FILE_DIR:
    case FILE_SYMLINK:
        return fox_fs_file_size(path) == 0;
    case FILE_BLOCK:
    case FILE_CHARACTER:
    case FILE_FIFO:
    case FILE_SOCKET:
    case FILE_UNKNOWN:
        break;
    }
    return false;
}

bool fox_fs_is_fifo(const char *path) { return fox_fs_file_type(path) == FILE_FIFO; }

bool fox_fs_is_other(const char *path) {
    if (!fox_fs_exists(path))
        return false;

    switch (fox_fs_file_type(path)) {
    case FILE_REGULAR:
    case FILE_DIR:
    case FILE_SYMLINK:
        return false;
    case FILE_BLOCK:
    case FILE_CHARACTER:
    case FILE_FIFO:
    case FILE_SOCKET:
    case FILE_UNKNOWN:
        break;
    }
    return true;
}

bool fox_fs_is_regular_file(const char *path) { return fox_fs_file_type(path) == FILE_REGULAR; }

bool fox_fs_is_socket(const char *path) { return fox_fs_file_type(path) == FILE_SOCKET; }

bool fox_fs_is_symlink(const char *path) {
    FoxFileStatus status;
    if (fox_fs_symlink_status(path, &status))
        return status.type == FILE_SYMLINK;
    return false;
}

FoxStringBuf fox_fs_getcwd(void) {
#if defined(FOX_OS_POSIX)
    char *buf = getcwd(NULL, 0);
    FoxStringBuf sb = fox_sb_from_cstr(buf);
    free(buf);
    return sb;
#else
#    error "Implement this"
#endif
}

bool fox_fs_setcwd(const char *path) {
    if (!path || strlen(path) == 0)
        return false;

#if defined(FOX_OS_POSIX)
    if (chdir(path) == 0)
        return true;
    return false;
#else
#    error "Implement this"
#endif
}

bool fox_fs_exists(const char *path) {
    if (!path || strlen(path) == 0)
        return false;

#if defined(FOX_OS_POSIX)
    return access(path, F_OK) == 0;
#else
#    error "Implement this"
#endif
}

bool fox_fs_equivalent(const char *path1, const char *path2) {
    if (!path1 || strlen(path1) == 0)
        return false;
    if (!path2 || strlen(path2) == 0)
        return false;

#if defined(FOX_OS_POSIX)
    struct stat file_info1;
    struct stat file_info2;

    if (stat(path1, &file_info1) < 0)
        return false;
    if (stat(path2, &file_info2) < 0)
        return false;

    return file_info1.st_dev == file_info2.st_dev && file_info1.st_ino == file_info2.st_ino;
#else
#    error "Implement this"
#endif
}

bool fox_fs_canonical(FoxStringBuf *sb) {
    if (!sb || sb->size == 0)
        return false;

#if defined(FOX_OS_POSIX)
    char *buf = realpath(sb->items, NULL);
    if (!buf)
        return false;

    fox_sb_free(sb);
    *sb = fox_sb_from_cstr(buf);
    free(buf);
    return true;
#else
#    error "Implement this"
#endif
}

bool fox_fs_space(const char *path, FoxSpaceInfo *space) {
    if (!space || !path || strlen(path) == 0)
        return false;

#if defined(FOX_OS_POSIX)
    struct statvfs fs_info;
    if (statvfs(path, &fs_info) == 0) {
        space->capacity = fs_info.f_blocks * fs_info.f_frsize;
        space->free = fs_info.f_bfree * fs_info.f_frsize;
        space->available = fs_info.f_bavail * fs_info.f_frsize;
        return true;
    }
    return false;
#else
#    error "Implement this"
#endif
}

bool fox_fs_create_dir(const char *path) {
    if (!path || strlen(path) == 0)
        return false;

#if defined(FOX_OS_POSIX)
    if (!fox_fs_exists(path))
        if (mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO) == 0)
            return true;
    return false;
#else
#    error "Implement this"
#endif
}

bool fox_fs_create_dir_all(const char *p) {
    const FoxStringView path = fox_sv_from_cstr(p);
    if (path.size == 0)
        return false;
    if (fox_fs_exists(p))
        return false;

    FoxStringView path_rem = {0};
    FoxStringBuf split = {0};

    for (size_t i = 0; i < path.size; i++) {
        path_rem = fox_str_slice(&path, i, path.size);
        i = i + fox_str_find_first_of(&path_rem, fox_sv_from_cstr(FOX_FILE_SEPARATOR));

        fox_sb_copy(&split, fox_str_slice(&path, 0, i));
        if (split.size == 0)
            continue;

        if (fox_fs_exists(split.items)) {
            continue;
        } else {
            if (!fox_fs_create_dir(split.items)) {
                fox_sb_free(&split);
                return false;
            }
        }
    }
    fox_sb_free(&split);
    return true;
}

bool fox_fs_create_symlink(const char *target, const char *link) {
    if (!target || !link || strlen(target) == 0 || strlen(link) == 0)
        return false;

#if defined(FOX_OS_POSIX)
    if (symlink(target, link) == 0)
        return true;
    return false;
#else
#    error "Implement this"
#endif
}

bool fox_fs_remove(const char *path) {
    if (!path || strlen(path) == 0)
        return false;
    if (remove(path) == 0)
        return true;
    return false;
}

bool fox_fs_remove_all(const char *path) {
    if (!path || strlen(path) == 0)
        return false;

    // TODO: implement this after completing directory visit
    FOX_UNUSED(path);
    FOX_TODO("fox_fs_remove_all");
    return false;
}

bool fox_fs_rename(const char *old_path, const char *new_path) {
    if (!old_path || strlen(old_path) == 0)
        return false;
    if (!new_path || strlen(new_path) == 0)
        return false;

    if (rename(old_path, new_path) == 0)
        return true;
    return false;
}

bool fox_fs_move(const char *old_path, const char *new_path) { return fox_fs_rename(old_path, new_path); }

bool fox__fs_copy_file__(const char *from, const char *to) {
    bool result = false;

    // Copy file contents
    FoxStringBuf sb = {0};
    if (!fox_fs_read_entire_file(from, &sb))
        fox_return_defer(false);
    if (!fox_fs_write_entire_file(to, (const FoxStringView *) (&sb)))
        fox_return_defer(false);
    // Copy file attributes
    FoxFileStatus from_status = {0};
    if (!fox_fs_file_status(from, &from_status))
        fox_return_defer(false);
    if (!fox_fs_set_status(to, from_status))
        fox_return_defer(false);
    fox_return_defer(true);

defer:
    fox_sb_free(&sb);
    return result;
}

bool fox_fs_copy_file(const char *from, const char *to, FoxCopyOptions options) {
    if (!from || !to || strlen(from) == 0 || strlen(to) == 0)
        return false;

    if (!fox_fs_is_regular_file(from))
        // TODO: report an error
        return false;

    if (!fox_fs_exists(to))
        return fox__fs_copy_file__(from, to);
    else {
        if (!fox_fs_is_regular_file(to))
            // TODO: report an error
            return false;
        if (fox_fs_equivalent(from, to))
            // TODO: report an error
            return false;
        switch (options.existing) {
        case 0:
            // TODO: Report an error
            return false;
        case COPY_SKIP_EXISTING:
            // Do nothing
            return false;
        case COPY_OVERWRITE_EXISTING:
            return fox__fs_copy_file__(from, to);
        case COPY_UPDATE_EXISTING: {
            FoxFileStatus from_status = {0};
            if (!fox_fs_file_status(from, &from_status))
                return false;
            FoxFileStatus to_status = {0};
            if (!fox_fs_file_status(to, &to_status))
                return false;
            if (from_status.last_modified > to_status.last_modified)
                return fox__fs_copy_file__(from, to);
            return false;
        }
        default:
            FOX_UNREACHABLE("fox_fs_copy_file");
        }
    }
}

bool fox_fs_copy_symlink(const char *from, const char *to) {
    if (!from || !to || strlen(from) == 0 || strlen(to) == 0)
        return false;
    bool result = false;

    // Copy symlink
    FoxStringBuf sb = {0};
    if (!fox_fs_read_symlink(from, &sb))
        fox_return_defer(false);
    if (!fox_fs_create_symlink(sb.items, to))
        fox_return_defer(false);
    // Copy symlink attributes
    FoxFileStatus from_status = {0};
    if (!fox_fs_symlink_status(from, &from_status))
        fox_return_defer(false);
    if (!fox_fs_set_symlink_status(to, from_status))
        fox_return_defer(false);
    fox_return_defer(true);

defer:
    fox_sb_free(&sb);
    return result;
}

#endif // FOX_IMPLEMENTATION
