#ifndef FOX_H_
#define FOX_H_

#ifdef __cplusplus
#    error "Bro! Just use a C compiler. Do not compile this in C++. Enough!"
#endif

#define FOX_IMPLEMENTATION
#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE

#ifndef _CRT_SECURE_NO_WARNINGS
#    define _CRT_SECURE_NO_WARNINGS
#endif // _CRT_SECURE_NO_WARNINGS

#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>

// TODO: To be implemented next
// - Implement path functions (concat, filename, rootpath and extension)
// - Implement async cmd execution
// - Implement log pattern just like spdlog
// - Log errors wherever necessary (with #ifndef FOX_NO_ECHO)
// - Document the header file
// - fox_fs_canonical does not work on Windows

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
/// - fox__sb_copy__
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
/// - fox__cmd_append__
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
/// - fox_da_push
/// - fox_da_pop
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
///   - fox_sb_pop
///   - fox_sb_append_null
///   - fox_sb_appendf
///   - fox_sb_vappendf
///   - fox_sb_concat_sb
///   - fox_sb_concat_sv
///   - fox_sb_concat_cstr
///   - fox_sb_concat_bytes
///   - fox_sb_concat
///   - fox_sb_append_bytes
///   - fox_sb_insert
///   - fox_sb_replace
///   - fox_sb_replace_char
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
///   - fox_streq
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
/// Logging system
/// - FoxLogLevel
/// - FoxLogHandlerFn
/// - FoxSinkWriteFn
/// - FoxSinkCloseFn
/// - FoxSink
/// - FoxSinks
/// - FoxLogger
///
///   Logger functions
///   - fox_logger_file_sink
///   - fox_logger_handler
///   - fox_logger_min_level
///   - fox_logger_free
///   - fox_logger_vlog_ext
///   - fox_logger_vlog
///   - fox_logger_log_ext
///   - fox_logger_log
///   - fox_logger_log_trace
///   - fox_logger_log_info
///   - fox_logger_log_warning
///   - fox_logger_log_error
///   - fox_logger_log_critical
///
///   Default logger functions
///   - fox_default_logger
///   - fox_default_log_handler
///   - fox_default_log_write
///   - fox_vlog_ext
///   - fox_vlog
///   - fox_log_ext
///   - fox_log
///   - fox_log_trace
///   - fox_log_info
///   - fox_log_warning
///   - fox_log_error
///   - fox_log_critical
///
/// Filesystem utils
///   Convenience functions
///   - fox_fs_read_entire_file
///   - fox_fs_write_entire_file
///   - fox_fs_read_symlink
///   - fox_fs_read_entire_dir
///
///   Directory visit functions
///   - FoxVisitAction
///   - FoxDirEntry
///   - FoxVisitFn
///   - FoxVisitOpt
///   - fox_fs_visit_dir_opt
///   - fox_fs_visit_dir
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
///   - fox_fs_set_file_size
///
///   File Type functions
///   - fox_fs_is_block_file
///   - fox_fs_is_character_file
///   - fox_fs_is_dir
///   - fox_fs_is_empty
///   - fox_fs_is_pipe
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
///
/// Process I/O utilities
///   Helping defs
///   - FoxProcHandle
///   - FoxFd
///   - FOX_INVALID_FD
///
///   Process managing functions
///   - FoxProc
///   - FoxProcs
///   - FoxSpawnOpt
///   - fox_cmd_spawn_opt
///   - fox_cmd_spawn
///   - fox_cmd_wait
///   - fox_cmd_kill
///   - fox_cmd_write_stdin
///   - fox_cmd_read_stdout
///   - fox_cmd_read_stderr
///
///   Process poll
///   - FoxPollResult
///   - fox_cmd_poll
///   - fox_cmd_is_running
///
///   Convenient functions
///   - FoxCmd
///   - fox_cmd_append
///   - fox_cmd_extend
///   - fox_cmd_free
///   - FoxCmdOpt
///   - fox_cmd_run_opt
///   - fox_nprocessors

#if defined(_WIN32) || defined(_WIN64)
#    define FOX_OS_WINDOWS /// Windows
#endif
#if defined(__CYGWIN__) && !defined(_WIN32)
#    define FOX_OS_WINDOWS /// Windows (Cygwin POSIX under Microsoft Windows)
#endif
#if defined(__linux__) || defined(__gnu_linux__) || defined(__ANDROID__)
#    define FOX_OS_LINUX /// Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
#endif
#if defined(__APPLE__) && defined(__MACH__)
#    define FOX_OS_MAC /// Apple OSX and iOS (Darwin)
#endif

#if defined(__MINGW32__) || defined(__MINGW64__)
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

#if defined(FOX_OS_LINUX)
#    include <sys/types.h>
#endif

#ifdef FOX_OS_WINDOWS
#    define FOX_FILE_SEPARATOR "\\"
#else
#    define FOX_FILE_SEPARATOR "/"
#endif

// #define FOX_NO_ECHO

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
#define FOX_ARRLEN(array) (sizeof(array) / sizeof(array[0]))

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

/// Any dynamic array is defined as follows:
///     typedef struct {
///         int *items;
///         size_t size;
///         size_t capacity;
///         // your other members... (I have nothing to do with it)
///     } Numbers;
///
///     // Later ...
///     Numbers numbers = {0}; // Zero-initialized value is default value
///     fox_da_append(&numbers, 1);
///     fox_da_foreach(Numbers, num, &numbers) {
///         printf("%d\n", num);
///     }
///     // Do whatever you want...

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
        (dest)->size = (src)->size;                                                                                                                  \
        (dest)->capacity = (src)->capacity;                                                                                                          \
        FOX_ASSERT(fox_realloc != NULL, "fox_realloc cannot be NULL");                                                                               \
        (dest)->items = fox_realloc((dest)->items, (dest)->capacity * sizeof((dest)->items[0]));                                                     \
        if ((src)->items)                                                                                                                            \
            memcpy((dest)->items, (src)->items, (src)->size * sizeof((src)->items[0]));                                                              \
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

#define fox_da_push(arr, value) fox_da_append(arr, value)
#define fox_da_pop(arr) (FOX_ASSERT((arr)->size > 0, "array cannot be empty"), (arr)->items[--(arr)->size])

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
            fox_da_pop((arr));                                                                                                                       \
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

// String utils

// INFO: Though StringBuf is sized, items still
// contains the null character for compatibility reasons
// but size but does not include the null character.
// INFO: StringView may or may not be null terminated.

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
    // INFO: be careful freeing up items
    FoxStringBuf *items;
    size_t size;
    size_t capacity;
} FoxStringBufs;

typedef struct {
    FoxStringView *items;
    size_t size;
    size_t capacity;
} FoxStringViews;

void fox__sb_copy__(FoxStringBuf *dest, FoxStringView src);
size_t fox__str_find_first_of__(FoxStringView self, FoxStringView str);
size_t fox__str_find_first_not_of__(FoxStringView self, FoxStringView str);
size_t fox__str_find_last_of__(FoxStringView self, FoxStringView str);
size_t fox__str_find_last_not_of__(FoxStringView self, FoxStringView str);
int fox__str_compare__(FoxStringView left, FoxStringView right);
bool fox__str_equals__(FoxStringView left, FoxStringView right);
bool fox__str_starts_with__(FoxStringView str, FoxStringView prefix);
bool fox__str_ends_with__(FoxStringView str, FoxStringView suffix);
bool fox__str_contains__(FoxStringView str, FoxStringView needle);
FoxStringView fox__str_slice__(FoxStringView str, size_t start, size_t end);
FoxStringViews fox__str_split__(FoxStringView str, char delimiter);
FoxStringView fox__str_trim_left__(FoxStringView str);
FoxStringView fox__str_trim_right__(FoxStringView str);
FoxStringView fox__str_trim__(FoxStringView str);

// Construction
FoxStringBuf fox_sb_from_chars(const char *data, size_t count);
FoxStringBuf fox_sb_from_cstr(const char *str);
FoxStringBuf fox_sb_from_char(char c, size_t count);
FoxStringBuf fox_sb_from_sv(FoxStringView sv);
FoxStringBuf fox_sb_clone(const FoxStringBuf *sb);
#define fox_sb_copy(dest, src) fox__sb_copy__((dest), fox_sv(src))
void fox_sb_free(FoxStringBuf *sb);
#define fox_str_bufs_free(str_bufs)                                                                                                                  \
    do {                                                                                                                                             \
        fox_da_foreach(FoxStringBuf, fox__sb__, (str_bufs)) { fox_sb_free(fox__sb__); }                                                              \
        fox_da_free((str_bufs));                                                                                                                     \
    } while (false)

#define fox_sb(expr) _Generic((expr), char *: fox_sb_from_cstr, const char *: fox_sb_from_cstr, FoxStringView: fox_sb_from_sv)(expr)

FoxStringView fox_sv_from_raw(const char *str, size_t count);
FoxStringView fox_sv_from_cstr(const char *str);
FoxStringView fox_sv_from_sb(const FoxStringBuf sb);
FoxStringView fox_sv_from_sv(FoxStringView sv);

#define fox_sv(expr)                                                                                                                                 \
    _Generic((expr), char *: fox_sv_from_cstr, const char *: fox_sv_from_cstr, FoxStringBuf: fox_sv_from_sb, FoxStringView: fox_sv_from_sv)(expr)

// Modification
void fox_sb_pop(FoxStringBuf *sb);
void fox_sb_append_null(FoxStringBuf *sb);
void fox_sb_appendf(FoxStringBuf *sb, const char *fmt, ...) FOX_PRINTF_FORMAT(2, 3);
void fox_sb_vappendf(FoxStringBuf *sb, const char *fmt, va_list args);

void fox_sb_concat_sb(FoxStringBuf *sb, const FoxStringBuf *other);
void fox_sb_concat_sv(FoxStringBuf *sb, FoxStringView other);
void fox_sb_concat_cstr(FoxStringBuf *sb, const char *str);
void fox_sb_concat_bytes(FoxStringBuf *sb, char *bytes, size_t count);
#define fox_sb_concat(sb, other)                                                                                                                     \
    _Generic(other,                                                                                                                                  \
            FoxStringBuf *: fox_sb_concat_sb,                                                                                                        \
            const FoxStringBuf *: fox_sb_concat_sb,                                                                                                  \
            FoxStringView: fox_sb_concat_sv,                                                                                                         \
            char *: fox_sb_concat_cstr,                                                                                                              \
            const char *: fox_sb_concat_cstr)((sb), (other))

#define fox_sb_insert(sb, index, other)                                                                                                              \
    do {                                                                                                                                             \
        fox_da_insert_many((sb), (index), (other)->items, (other)->size);                                                                            \
        fox_sb_append_null(sb);                                                                                                                      \
    } while (false);

#define fox_sb_replace(sb, start, end, other)                                                                                                        \
    do {                                                                                                                                             \
        fox_da_remove_range((sb), (start), (end));                                                                                                   \
        fox_sb_insert((sb), (start), (other));                                                                                                       \
    } while (false)
void fox_sb_replace_char(FoxStringBuf *sb, char orig, char replace);

#define fox_sb_remove_at(sb, index)                                                                                                                  \
    do {                                                                                                                                             \
        fox_da_remove((sb), (index));                                                                                                                \
        fox_sb_append_null(sb);                                                                                                                      \
    } while (false)
void fox_sb_remove_first_char(FoxStringBuf *sb, char c);
void fox_sb_remove_first_sv(FoxStringBuf *sb, FoxStringView sv);
#define fox_sb_remove_first_str(sb, mat) fox_sb_remove_first_sv((sb), fox_sv(mat))
void fox_sb_remove_all_char(FoxStringBuf *sb, char c);
void fox_sb_remove_all_sv(FoxStringBuf *sb, FoxStringView sv);
#define fox_sb_remove_all_str(sb, mat) fox_sb_remove_all_sv((sb), fox_sv(mat))

void fox_sb_tolower(FoxStringBuf *sb);
void fox_sb_toupper(FoxStringBuf *sb);

#define fox_str_find_first_of(self, str) fox__str_find_first_of__(fox_sv(self), fox_sv(str))
#define fox_str_find_first_not_of(self, str) fox__str_find_first_not_of__(fox_sv(self), fox_sv(str))
#define fox_str_find_last_of(self, str) fox__str_find_last_of__(fox_sv(self), fox_sv(str))
#define fox_str_find_last_not_of(self, str) fox__str_find_last_not_of__(fox_sv(self), fox_sv(str))

#define fox_str_compare(left, right) fox__str_compare__(fox_sv(left), fox_sv(right))
#define fox_str_equals(left, right) fox__str_equals__(fox_sv(left), fox_sv(right))
#define fox_streq(left, right) fox__str_equals__(fox_sv(left), fox_sv(right))
#define fox_str_starts_with(str, prefix) fox__str_starts_with__(fox_sv(str), fox_sv(prefix))
#define fox_str_ends_with(str, suffix) fox__str_ends_with__(fox_sv(str), fox_sv(suffix))
#define fox_str_contains(str, suffix) fox__str_contains__(fox_sv(str), fox_sv(suffix))
#define fox_str_slice(str, start, end) fox__str_slice__((str), (start), (end))
#define fox_str_split(str, delimiter) fox__str_split__(fox_sv(str), (delimiter));
#define fox_str_trim_left(str) fox__str_trim_left__(fox_sv(str))
#define fox_str_trim_right(str) fox__str_trim_right__(fox_sv(str))
#define fox_str_trim(str) fox__str_trim__(fox_sv(str))

#define SV_Fmt "%.*s"
#define SV_Arg(sv) (int) (sv)->size, (sv)->items
/// Usage:
///   StringView sv = ...;
///   printf("sv: "SV_Arg"\n", SV_Arg(sv));

void fox_get_error_message(FoxStringBuf *buf);

// Log utils

typedef enum {
    LOG_TRACE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_CRITICAL,
    LOG_NO_LOGS,
} FoxLogLevel;

struct FoxLogSink;

typedef bool (*FoxLogHandlerFn)(struct FoxLogSink *sink, FoxStringBuf *buf, FoxLogLevel level, const char *fmt, const char *path, size_t line,
                                va_list args);
typedef void (*FoxSinkWriteFn)(struct FoxLogSink *sink, FoxStringView sv);
typedef void (*FoxSinkCloseFn)(struct FoxLogSink *sink);

typedef struct FoxLogSink {
    // TODO: add support for log patterns (like in spdlog)
    void *handle;
    FoxLogLevel min_level;

    FoxLogHandlerFn log_handler;
    FoxSinkWriteFn sink_write;
    FoxSinkCloseFn sink_close;
} FoxSink;

typedef struct {
    FoxSink *items;
    size_t size;
    size_t capacity;
} FoxSinks;

typedef struct {
    FoxSinks sinks;
} FoxLogger;

FoxSink fox_logger_file_sink(const char *path);

void fox_logger_handler(FoxLogger *logger, FoxLogHandlerFn handler);
void fox_logger_min_level(FoxLogger *logger, FoxLogLevel level);
void fox_logger_free(FoxLogger *logger);

void fox_logger_vlog_ext(FoxLogger *logger, FoxLogLevel level, const char *fmt, const char *path, size_t line, va_list args);
#define fox_logger_vlog(logger, level, fmt, args) fox_logger_vlog_ext((logger), (level), (fmt), __FILE__, __LINE__, (args))
void fox_logger_log_ext(FoxLogger *logger, FoxLogLevel level, const char *fmt, const char *path, size_t line, ...);
#define fox_logger_log(logger, level, fmt, ...) fox_logger_log_ext((logger), (level), (fmt), __FILE__, __LINE__, ##__VA_ARGS__)
#define fox_logger_log_trace(logger, fmt, ...) fox_logger_log_ext((logger), LOG_TRACE, (fmt), __FILE__, __LINE__, ##__VA_ARGS__)
#define fox_logger_log_debug(logger, fmt, ...) fox_logger_log_ext((logger), LOG_DEBUG, (fmt), __FILE__, __LINE__, ##__VA_ARGS__)
#define fox_logger_log_info(logger, fmt, ...) fox_logger_log_ext((logger), LOG_INFO, (fmt), __FILE__, __LINE__, ##__VA_ARGS__)
#define fox_logger_log_warning(logger, fmt, ...) fox_logger_log_ext((logger), LOG_WARNING, (fmt), __FILE__, __LINE__, ##__VA_ARGS__)
#define fox_logger_log_error(logger, fmt, ...) fox_logger_log_ext((logger), LOG_ERROR, (fmt), __FILE__, __LINE__, ##__VA_ARGS__)
#define fox_logger_log_critical(logger, fmt, ...) fox_logger_log_ext((logger), LOG_CRITICAL, (fmt), __FILE__, __LINE__, ##__VA_ARGS__)

extern FoxLogger fox_default_logger;
bool fox_default_log_handler(FoxSink *sink, FoxStringBuf *buf, FoxLogLevel level, const char *fmt, const char *path, size_t line, va_list args);
void fox_default_log_write(FoxSink *sink, FoxStringView sv);

void fox_vlog_ext(FoxLogLevel level, const char *fmt, const char *path, size_t line, va_list args);
#define fox_vlog(level, fmt, args) fox_vlog_ext((level), (fmt), __FILE__, __LINE__, (args))
void fox_log_ext(FoxLogLevel level, const char *fmt, const char *path, size_t line, ...);
#define fox_log(level, fmt, ...) fox_log_ext((level), (fmt), __FILE__, __LINE__, ##__VA_ARGS__)
#define fox_log_trace(fmt, ...) fox_log(LOG_TRACE, (fmt), ##__VA_ARGS__)
#define fox_log_debug(fmt, ...) fox_log(LOG_DEBUG, (fmt), ##__VA_ARGS__)
#define fox_log_info(fmt, ...) fox_log(LOG_INFO, (fmt), ##__VA_ARGS__)
#define fox_log_warning(fmt, ...) fox_log(LOG_WARNING, (fmt), ##__VA_ARGS__)
#define fox_log_error(fmt, ...) fox_log(LOG_ERROR, (fmt), ##__VA_ARGS__)
#define fox_log_critical(fmt, ...) fox_log(LOG_CRITICAL, (fmt), ##__VA_ARGS__)

// Filesystem utils

bool fox_fs_read_entire_file(const char *path, FoxStringBuf *sb);
bool fox_fs_write_entire_file(const char *path, FoxStringView sv);
bool fox_fs_read_symlink(const char *path, FoxStringBuf *sb);
bool fox_fs_read_entire_dir(const char *path, FoxStringBufs *files);

typedef enum {
    FOX_VISIT_CONT,
    FOX_VISIT_SKIP,
    FOX_VISIT_STOP,
} FoxVisitAction;

typedef struct {
    const char *path;
    size_t level;
    void *arg;
    FoxVisitAction *action;
} FoxDirEntry;

typedef void (*FoxVisitFn)(FoxDirEntry entry);

typedef struct {
    void *arg;
    bool recursive;
    bool post_order;
    bool nofollow_dir_symlink;
} FoxVisitOpt;

bool fox_fs_visit_dir_opt(const char *path, FoxVisitFn visitor, FoxVisitOpt opt);
#define fox_fs_visit_dir(path, visitor, ...) fox_fs_visit_dir_opt(path, visitor, (FoxVisitOpt) {__VA_ARGS__})

// INFO: Only FOX_FILE_REGULAR, FOX_FILE_DIR and FOX_FILE_SYMLINK works on Windows.
// Everything else works on POSIX compliant systems.

typedef enum {
    FOX_FILE_UNKNOWN,
    FOX_FILE_REGULAR,
    FOX_FILE_DIR,
    FOX_FILE_SYMLINK,
    FOX_FILE_BLOCK,
    FOX_FILE_CHARACTER,
    FOX_FILE_PIPE,
    FOX_FILE_SOCKET,
} FoxFileType;

enum {
    FOX_PERM_NONE = 0,
    FOX_PERM_OWNER_READ = 0400,
    FOX_PERM_OWNER_WRITE = 0200,
    FOX_PERM_OWNER_EXEC = 0100,
    FOX_PERM_OWNER_ALL = FOX_PERM_OWNER_READ | FOX_PERM_OWNER_WRITE | FOX_PERM_OWNER_EXEC,
    FOX_PERM_GROUP_READ = 040,
    FOX_PERM_GROUP_WRITE = 020,
    FOX_PERM_GROUP_EXEC = 010,
    FOX_PERM_GROUP_ALL = FOX_PERM_GROUP_READ | FOX_PERM_GROUP_WRITE | FOX_PERM_GROUP_EXEC,
    FOX_PERM_OTHERS_READ = 04,
    FOX_PERM_OTHERS_WRITE = 02,
    FOX_PERM_OTHERS_EXEC = 01,
    FOX_PERM_OTHERS_ALL = FOX_PERM_OTHERS_READ | FOX_PERM_OTHERS_WRITE | FOX_PERM_OTHERS_EXEC,
    FOX_PERM_ALL = FOX_PERM_OWNER_ALL | FOX_PERM_GROUP_ALL | FOX_PERM_OTHERS_ALL,

    FOX_PERM_READONLY = FOX_PERM_OWNER_READ | FOX_PERM_GROUP_READ | FOX_PERM_OTHERS_READ,
};

typedef u32 FoxFilePerms;

typedef struct {
    FoxFileType type;
    bool read_only;
    // FoxFilePerms perms; //< Use FOX_PERM_* enum constants
    size_t size;
    time_t last_modified; //< in seconds
    time_t last_accessed; //< in seconds
} FoxFileStatus;

typedef struct {
    u64 capacity;
    u64 free;
    u64 available;
} FoxSpaceInfo;

bool fox_fs_file_status(const char *path, FoxFileStatus *status);
bool fox_fs_symlink_status(const char *path, FoxFileStatus *status);
bool fox_fs_set_status(const char *path, const FoxFileStatus status);
bool fox_fs_set_symlink_status(const char *path, const FoxFileStatus status);
bool fox_fs_get_perms(const char *path, FoxFilePerms *perms);
bool fox_fs_set_perms(const char *path, FoxFilePerms perms);
bool fox_fs_get_symlink_perms(const char *path, FoxFilePerms *perms);
bool fox_fs_set_symlink_perms(const char *path, FoxFilePerms perms);
FoxFileType fox_fs_file_type(const char *path);
u64 fox_fs_file_size(const char *path);
bool fox_fs_set_file_size(const char *path, u64 new_size);

bool fox_fs_is_block_file(const char *path);
bool fox_fs_is_character_file(const char *path);
bool fox_fs_is_dir(const char *path);
bool fox_fs_is_empty(const char *path);
bool fox_fs_is_pipe(const char *path);
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

enum {
    // FoxCopyOptions.existing
    FOX_COPY_SKIP_EXISTING = 1,
    FOX_COPY_OVERWRITE_EXISTING = 2,
    FOX_COPY_UPDATE_EXISTING = 3,
    // FoxCopyOptions.recursive = true, false
    // FoxCopyOptions.symlink
    FOX_COPY_COPY_SYMLINKS = 1,
    FOX_COPY_SKIP_SYMLINKS = 1,
    // FoxCopyOptions.other
    FOX_COPY_DIRS_ONLY = 1,
    FOX_COPY_CREATE_SYMLINKS = 2,
    FOX_COPY_HARD_LINKS = 3,
};

bool fox_fs_copy(const char *from, const char *to, FoxCopyOptions options);

bool fox_fs_copy_file(const char *from, const char *to, FoxCopyOptions options);
bool fox_fs_copy_symlink(const char *from, const char *to);

/// Process utils

typedef struct {
    void *handle;

    void *stdin_write;
    void *stdout_read;
    void *stderr_read;

    bool running;
    int exit_code;
} FoxProc;

typedef struct {
    FoxProc *items;
    size_t size;
    size_t capacity;
} FoxProcs;

typedef struct {
    FoxStringView key;
    FoxStringView value;
} FoxEnvEntry;

typedef struct {
    FoxEnvEntry *items;
    size_t size;
    size_t capacity;
} FoxEnv;

typedef struct {
    const char *stdin_path;
    const char *stdout_path;
    const char *stderr_path;
    FoxStringView working_dir;
    const FoxEnv *env;
} FoxSpawnOpt;

bool fox_cmd_spawn_opt(FoxProc *process, const char *path, const FoxStringViews argv, const FoxSpawnOpt opt);
#define fox_cmd_spawn(process, path, argv, ...) fox_cmd_spawn_opt((process), (path), (argv), (const FoxSpawnOpt) {__VA_ARGS__})
bool fox_cmd_spawn_piped_opt(FoxProc *process, const char *path, const FoxStringViews argv, const FoxSpawnOpt opt);
#define fox_cmd_spawn_piped(process, path, argv, ...) fox_cmd_spawn_piped_opt((process), (path), (argv), (const FoxSpawnOpt) {__VA_ARGS__})
bool fox_cmd_wait(FoxProc *process);
void fox_cmd_detach(FoxProc *process);
/// For Posix, @p value is the signal that you want to send to the process
/// and the process may or may not terminate depending on the signal.
/// For Windows, @p value is the exit code that will be set after the
/// process terminates and the process is forcefully terminated.
bool fox_cmd_kill(FoxProc *process, int value);

bool fox_cmd_write_stdin(FoxProc *process, FoxStringView data, size_t *written);
bool fox_cmd_read_stdout(FoxProc *process, void *buf, size_t size, size_t *bytes_read);
bool fox_cmd_read_stderr(FoxProc *process, void *buf, size_t size, size_t *bytes_read);

typedef struct {
    bool stdout_ready;
    i64 stdout_avail;
    bool stderr_ready;
    i64 stderr_avail;
} FoxPollResult;

bool fox_cmd_poll(const FoxProc *process, FoxPollResult *result, int timeout_ms);
bool fox_cmd_is_running(FoxProc *process);

typedef struct {
    const char **items;
    size_t size;
    size_t capacity;
} FoxCmd;

void fox__cmd_append__(FoxCmd *cmd, size_t n, ...);
#define fox_cmd_append(cmd, ...) fox__cmd_append__((cmd), sizeof((const char *[]) {__VA_ARGS__}) / sizeof(const char *), ##__VA_ARGS__)
void fox_cmd_extend(FoxCmd *cmd, FoxCmd *other);
#define fox_cmd_free(cmd) fox_da_free(cmd)

typedef struct {
    // TODO: implement async
    // FoxProcs *async;
    // size_t max_async;
    // size_t parallel_count;

    bool reset;
    const char *working_dir;
    const char **env;
    size_t env_size;
    const char *stdin_path;
    const char *stdout_path;
    const char *stderr_path;

    int *exit_code;
} FoxCmdOpt;

bool fox_cmd_run_opt(FoxCmd *cmd, FoxCmdOpt opt);
#define fox_cmd_run(cmd, ...) fox_cmd_run_opt((cmd), (FoxCmdOpt) {.reset = true, __VA_ARGS__})

bool fox__auto_build__(const char *src_file, int argc, char *argv[]);
#define fox_auto_build(argc, argv) fox__auto_build__(__FILE__, argc, argv);

u32 fox_nprocessors(void);

#endif // FOX_H_

#ifdef FOX_IMPLEMENTATION

#if defined(FOX_OS_LINUX)
#    include <asm/termbits.h>
#    include <dirent.h>
#    include <fcntl.h>
#    include <poll.h>
#    include <sys/ioctl.h>
#    include <sys/stat.h>
#    include <sys/statvfs.h>
#    include <sys/sysinfo.h>
#    include <sys/time.h>
#    include <sys/wait.h>
#    include <unistd.h>
#elif defined(FOX_OS_WINDOWS)
#    define WIN32_LEAN_AND_MEAN
#    include <Shlwapi.h>
#    include <windows.h>
#    include <winioctl.h>
#endif

#if defined(FOX_OS_LINUX) || defined(FOX_OS_UNIX) || defined(FOX_OS_MAC)
typedef pid_t FoxProcHandle;
typedef int FoxFd;
#    define FOX_INVALID_HANDLE (FoxProcHandle)(-1)
#    define FOX_INVALID_FD (FoxFd)(-1)

_Static_assert(sizeof(void *) >= sizeof(FoxProcHandle), "sizeof(void *) should be >= sizeof(FoxProcHandle) aka pid_t");
_Static_assert(sizeof(void *) >= sizeof(FoxFd), "sizeof(void *) should be >= sizeof(FoxFd) aka int");
#elif defined(FOX_OS_WINDOWS)
typedef HANDLE FoxProcHandle;
typedef HANDLE FoxFd;
#    define FOX_INVALID_HANDLE (FoxProcHandle) INVALID_HANDLE_VALUE
#    define FOX_INVALID_FD (FoxFd) INVALID_HANDLE_VALUE
#else
#    error "Implement this"
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

void fox__sb_copy__(FoxStringBuf *dest, FoxStringView src) {
    if (src.size == 0) {
        dest->size = 0;
        return;
    }

    fox_da_reserve(dest, src.size + 1);
    dest->size = src.size;
    memcpy(dest->items, src.items, src.size);
    dest->items[dest->size] = '\0';
}

size_t fox__str_find_first_of__(FoxStringView self, FoxStringView str) {
    for (size_t i = 0; i < self.size; ++i) {
        char c = self.items[i];
        // Check if current_char is present in the str set
        for (size_t j = 0; j < str.size; ++j) {
            if (c == str.items[j])
                return i; // Found the first occurrence
        }
    }
    return self.size;
}

size_t fox__str_find_first_not_of__(FoxStringView self, FoxStringView str) {
    for (size_t i = 0; i < self.size; ++i) {
        char c = self.items[i];
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
    return self.size;
}

size_t fox__str_find_last_of__(FoxStringView self, FoxStringView str) {
    for (size_t index = self.size; index > 0; index--) {
        size_t i = index - 1;
        char c = self.items[i];
        // Check if current_char is present in the str set
        for (size_t j = 0; j < str.size; ++j) {
            if (c == str.items[j])
                return i; // Found the last occurrence
        }
    }
    return self.size;
}

size_t fox__str_find_last_not_of__(FoxStringView self, FoxStringView str) {
    for (size_t index = self.size; index > 0; index--) {
        size_t i = index - 1;
        char c = self.items[i];
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
    return self.size;
}

int fox__str_compare__(FoxStringView left, FoxStringView right) {
    // Find the minimum length to compare
    size_t min_size = (left.size < right.size) ? left.size : right.size;
    // Compare characters up to the shorter length
    int result = memcmp(left.items, right.items, min_size);
    if (result != 0) {
        return result; // Mismatch found within min_size
    }
    if (left.size < right.size)
        return -1;
    if (left.size > right.size)
        return 1;
    return 0; // Lengths and contents are identical
}

bool fox__str_equals__(FoxStringView left, FoxStringView right) {
    if (left.size != right.size)
        return false;
    return fox__str_compare__(left, right) == 0;
}

bool fox__str_starts_with__(FoxStringView str, FoxStringView prefix) {
    if (prefix.size > str.size)
        return false;
    return memcmp(str.items, prefix.items, prefix.size) == 0;
}

bool fox__str_ends_with__(FoxStringView str, FoxStringView suffix) {
    if (suffix.size > str.size)
        return false;
    return memcmp(&str.items[str.size - suffix.size], suffix.items, suffix.size) == 0;
}

bool fox__str_contains__(FoxStringView str, FoxStringView needle) {
    // An empty needle is technically contained in any string
    if (needle.size == 0)
        return true;
    // Needle cannot be longer than the haystack
    if (needle.size > str.size)
        return false;
    // Naive search
    size_t limit = str.size - needle.size;
    for (size_t i = 0; i <= limit; ++i)
        if (memcmp(str.items + i, needle.items, needle.size) == 0)
            return true;
    return false;
}

FoxStringView fox__str_slice__(FoxStringView str, size_t start, size_t end) {
    if (start >= end)
        return (FoxStringView) {0};

    FOX_ASSERT(start < str.size, "start index is invalid");
    FOX_ASSERT(end <= str.size, "end index is invalid");

    if (str.size == 0)
        return (FoxStringView) {0};
    return (FoxStringView) {
            .items = &str.items[start],
            .size = end - start,
    };
}

FoxStringViews fox__str_split__(FoxStringView str, char delimiter) {
    FoxStringViews result = {0};
    size_t start = 0;
    size_t index = 0;
    for (; index < str.size; index++) {
        if (str.items[index] == delimiter) {
            fox_da_append(&result, fox__str_slice__(str, start, index));
            start = index;
        }
    }
    if (start < index)
        fox_da_append(&result, fox__str_slice__(str, start, index));
    return result;
}

FoxStringView fox__str_trim_left__(FoxStringView str) {
    for (size_t i = 0; i < str.size; i++) {
        if (!isspace(str.items[i]))
            return fox__str_slice__(str, i, str.size);
    }
    return (FoxStringView) {0};
}

FoxStringView fox__str_trim_right__(FoxStringView str) {
    for (size_t index = str.size; index > 0; index--) {
        size_t i = index - 1;
        if (!isspace(str.items[i]))
            return fox__str_slice__(str, 0, i + 1);
    }
    return (FoxStringView) {0};
}

FoxStringView fox__str_trim__(FoxStringView str) { return fox__str_trim_right__(fox__str_trim_left__(str)); }

FoxStringBuf fox_sb_from_chars(const char *data, size_t count) {
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

FoxStringBuf fox_sb_from_sv(FoxStringView sv) {
    FoxStringBuf sb = {0};
    if (sv.size == 0)
        return sb;

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

void fox_sb_free(FoxStringBuf *sb) {
    // Aha! got ya, sb is a valid dynarray
    fox_da_free(sb);
}

void fox_sb_pop(FoxStringBuf *sb) {
    fox_da_pop(sb);
    fox_sb_append_null(sb);
}

void fox_sb_append_null(FoxStringBuf *sb) {
    fox_da_reserve(sb, sb->size + 1);
    sb->items[sb->size] = '\0';
}

void fox_sb_appendf(FoxStringBuf *sb, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fox_sb_vappendf(sb, fmt, args);
    va_end(args);
}

void fox_sb_vappendf(FoxStringBuf *sb, const char *fmt, va_list args) {
    va_list args_for_size_computation;
    va_copy(args_for_size_computation, args);
    int n = vsnprintf(NULL, 0, fmt, args_for_size_computation);
    va_end(args_for_size_computation);
    if (n == -1)
        FOX_PANIC("vsnprintf failed");

    FoxStringBuf tmp = fox_sb_clone(sb);
    fox_da_reserve(&tmp, tmp.size + n + 1);
    vsnprintf(&tmp.items[tmp.size], n + 1, fmt, args);
    tmp.size += n;
    tmp.items[tmp.size] = '\0';
    fox_sb_copy(sb, fox_sv(tmp));

    fox_sb_free(&tmp);
}

void fox_sb_concat_sb(FoxStringBuf *sb, const FoxStringBuf *other) {
    fox_da_concat(sb, other);
    fox_sb_append_null(sb);
}

void fox_sb_concat_sv(FoxStringBuf *sb, FoxStringView other) {
    fox_da_concat(sb, &other);
    fox_sb_append_null(sb);
}

void fox_sb_concat_cstr(FoxStringBuf *sb, const char *str) {
    fox_da_append_many(sb, str, strlen(str));
    fox_sb_append_null(sb);
}

void fox_sb_concat_bytes(FoxStringBuf *sb, char *bytes, size_t count) {
    fox_da_append_many(sb, bytes, count);
    fox_sb_append_null(sb);
}

void fox_sb_replace_char(FoxStringBuf *sb, char orig, char replace) {
    fox_da_foreach(char, c, sb) {
        if (*c == orig)
            *c = replace;
    }
}

void fox_sb_remove_first_char(FoxStringBuf *sb, char c) {
    size_t index = fox_str_find_first_of(*sb, fox_sv_from_raw(&c, 1));
    fox_sb_remove_at(sb, index);
}

void fox_sb_remove_first_sv(FoxStringBuf *sb, FoxStringView sv) {
    if (sb->size < sv.size)
        return;

    bool removed = false;
    FoxStringBuf tmp = {0};
    for (size_t i = 0; i < sb->size; i++) {
        size_t j = 0;
        if (!removed) {
            for (; j < sv.size; j++) {
                char main_c = sb->items[i + j];
                char mat_c = sv.items[j];
                if (main_c != mat_c)
                    goto not_found;
            }
            i += j - 1;
            removed = true;
            continue;
        }
not_found:
        fox_da_append(&tmp, sb->items[i]);
    }
    fox_sb_append_null(&tmp);
    fox_sb_copy(sb, tmp);
    fox_sb_free(&tmp);
}

void fox_sb_remove_all_char(FoxStringBuf *sb, char c) {
    FoxStringBuf tmp = {0};
    fox_da_foreach(char, ch, sb) {
        if (*ch != c)
            fox_da_append(&tmp, c);
    }
    fox_sb_append_null(&tmp);
    fox_sb_copy(sb, tmp);
    fox_sb_free(&tmp);
}

void fox_sb_remove_all_sv(FoxStringBuf *sb, FoxStringView sv) {
    if (sb->size < sv.size)
        return;

    FoxStringBuf tmp = {0};
    for (size_t i = 0; i < sb->size; i++) {
        size_t j = 0;
        for (; j < sv.size; j++) {
            char main_c = sb->items[i + j];
            char mat_c = sv.items[j];
            if (main_c != mat_c)
                goto not_found;
        }
        i += j - 1;
        continue;
not_found:
        fox_da_append(&tmp, sb->items[i]);
    }
    fox_sb_append_null(&tmp);
    fox_sb_copy(sb, tmp);
    fox_sb_free(&tmp);
}

void fox_sb_tolower(FoxStringBuf *sb) {
    fox_da_foreach(char, c, sb) { *c = tolower(*c); }
}

void fox_sb_toupper(FoxStringBuf *sb) {
    fox_da_foreach(char, c, sb) { *c = toupper(*c); }
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

FoxStringView fox_sv_from_sb(const FoxStringBuf sb) {
    return (FoxStringView) {
            .items = sb.items,
            .size = sb.size,
    };
}

FoxStringView fox_sv_from_sv(FoxStringView sv) { return sv; }

void fox_get_error_message(FoxStringBuf *buf) {
#ifdef FOX_OS_LINUX
    fox_sb_copy(buf, strerror(errno));
#elif defined(FOX_OS_WINDOWS)
    fox_da_clear(buf);
    char err_msg_buf[4096];
    DWORD size = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), 0, err_msg_buf,
                               FOX_ARRLEN(err_msg_buf), NULL);
    if (size == 0)
        fox_sb_appendf(buf, "error code: %lu", GetLastError());

    *buf = fox_sb_from_chars(err_msg_buf, size);
    FoxStringBuf sb = fox_sb(fox_str_trim(*buf));
    fox_sb_copy(buf, sb);
    fox_sb_free(&sb);
#else
#    error "Implement this"
#endif
}

static void fox__file_sink_close__(FoxSink *sink) {
    FILE *file = sink->handle;
    fclose(file);
}

FoxSink fox_logger_file_sink(const char *path) {
    FILE *file = fopen(path, "wb");
    if (file == NULL)
        return (FoxSink) {0};
    return (FoxSink) {
            .handle = file,
            .log_handler = fox_default_log_handler,
            .sink_write = fox_default_log_write,
            .sink_close = fox__file_sink_close__,
    };
}

void fox_logger_handler(FoxLogger *logger, FoxLogHandlerFn handler) {
    if (!logger)
        return;
    fox_da_foreach(FoxSink, sink, &logger->sinks) sink->log_handler = handler;
}

void fox_logger_min_level(FoxLogger *logger, FoxLogLevel level) {
    if (!logger)
        return;
    fox_da_foreach(FoxSink, sink, &logger->sinks) sink->min_level = level;
}

void fox_logger_free(FoxLogger *logger) {
    if (!logger)
        return;
    fox_da_foreach(FoxSink, sink, &logger->sinks) {
        if (sink->sink_close)
            sink->sink_close(sink->handle);
    }
    fox_da_free(&logger->sinks);
}

void fox_logger_vlog_ext(FoxLogger *logger, FoxLogLevel level, const char *fmt, const char *path, size_t line, va_list args) {
    if (!logger)
        return;

    FoxStringBuf buf = {0};
    fox_da_foreach(FoxSink, sink, &logger->sinks) {
        bool will_write = false;
        if (sink->log_handler) {
            va_list sink_args;
            va_copy(sink_args, args);
            will_write = sink->log_handler(sink, &buf, level, fmt, path, line, sink_args);
            va_end(sink_args);
        }
        if (sink->sink_write && will_write)
            sink->sink_write(sink, fox_sv(buf));

        fox_da_clear(&buf);
    }
    fox_sb_free(&buf);
}

void fox_logger_log_ext(FoxLogger *logger, FoxLogLevel level, const char *fmt, const char *path, size_t line, ...) {
    va_list args;
    va_start(args, line);
    fox_logger_vlog_ext(logger, level, fmt, path, line, args);
    va_end(args);
}

FoxLogger fox_default_logger = {0};
static bool fox__def_log_init__ = false;
static mtx_t fox__def_log_mtx__;

static void fox__free_def_log__(void) { fox_logger_free(&fox_default_logger); }

static void fox__init_def_log__(void) {
    if (!fox__def_log_init__) {
        FoxSink default_sink = {
                .handle = stderr,
                .log_handler = fox_default_log_handler,
                .sink_write = fox_default_log_write,
                .sink_close = NULL,
        };
        fox_da_append(&fox_default_logger.sinks, default_sink);
        if (mtx_init(&fox__def_log_mtx__, mtx_plain) == thrd_error) {
            perror("could not initialize mutex for fox_default_logger");
            abort();
        }
        if (atexit(fox__free_def_log__) != 0) {
            perror("could not register exit hook for fox_default_logger");
            abort();
        }
        fox__def_log_init__ = true;
    }
}

bool fox_default_log_handler(FoxSink *sink, FoxStringBuf *buf, FoxLogLevel level, const char *fmt, const char *path, size_t line, va_list args) {
    if (level < sink->min_level)
        return false;

    const char *level_str = NULL;
    switch (level) {
    case LOG_TRACE:
        level_str = "TRACE";
        break;
    case LOG_DEBUG:
        level_str = "\033[32mDEBUG\033[0m";
        break;
    case LOG_INFO:
        level_str = "\033[34mINFO\033[0m";
        break;
    case LOG_WARNING:
        level_str = "\033[93mWARNING\033[0m";
        break;
    case LOG_ERROR:
        level_str = "\033[31mERROR\033[0m";
        break;
    case LOG_CRITICAL:
        level_str = "\033[1m\033[91mCRITICAL\033[0m";
        break;
    case LOG_NO_LOGS:
        return false;
    default:
        FOX_UNREACHABLE("fox_default_log_handler");
    }

    FoxStringBuf fmt_buf = {0};
    fox_sb_vappendf(&fmt_buf, fmt, args);

    // fox_sb_appendf(buf, "%s:%zu: [%s] %s\n", path, line, level_str, fmt_buf.items);
    fox_sb_appendf(buf, "[%s] %s\n", level_str, fmt_buf.items);
    FOX_UNUSED(path);
    FOX_UNUSED(line);
    fox_sb_free(&fmt_buf);
    return true;
}

void fox_default_log_write(FoxSink *sink, FoxStringView sv) {
    if (sv.size == 0)
        return;

    FILE *file = sink->handle;
    mtx_lock(&fox__def_log_mtx__);
    fwrite(sv.items, sizeof(sv.items[0]), sv.size, file);
    mtx_unlock(&fox__def_log_mtx__);
}

void fox_vlog_ext(FoxLogLevel level, const char *fmt, const char *path, size_t line, va_list args) {
    fox__init_def_log__();
    fox_logger_vlog_ext(&fox_default_logger, level, fmt, path, line, args);
}

void fox_log_ext(FoxLogLevel level, const char *fmt, const char *path, size_t line, ...) {
    va_list args;
    va_start(args, line);
    fox_vlog_ext(level, fmt, path, line, args);
    va_end(args);
}

bool fox_fs_read_entire_file(const char *path, FoxStringBuf *sb) {
    bool result;
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
    fox_return_defer(true);

defer:
    // TODO: log errors
    if (f)
        fclose(f);
    return result;
}

bool fox_fs_write_entire_file(const char *path, FoxStringView sv) {
    bool result;
    // Open the file
    FILE *f = fopen(path, "wb");
    if (f == NULL)
        fox_return_defer(false);
    // Write everything
    fwrite(sv.items, sizeof(sv.items[0]), sv.size, f);
    if (ferror(f))
        fox_return_defer(false);
    fox_return_defer(true);

defer:
    // TODO: log errors
    if (f)
        fclose(f);
    return result;
}

#ifdef FOX_OS_WINDOWS
//  REPARSE_DATA_BUFFER related definitions are found in ntifs.h, which is part of the
//  Windows Device Driver Kit. Since that's inconvenient, the definitions are provided
//  here.
typedef struct {
    ULONG ReparseTag;
    USHORT ReparseDataLength;
    USHORT Reserved;

    union {
        /*
         * In SymbolicLink and MountPoint reparse points, there are two names.
         * SubstituteName is the effective replacement path for the reparse point.
         * This is what should be used for path traversal.
         * PrintName is intended for presentation to the user and may omit some
         * elements of the path or be absent entirely.
         *
         * Examples of substitute and print names:
         * mklink /D ldrive c:\
         * SubstituteName: "\??\c:\"
         * PrintName: "c:\"
         *
         * mklink /J ldrive c:\
         * SubstituteName: "\??\C:\"
         * PrintName: "c:\"
         *
         * junction ldrive c:\
         * SubstituteName: "\??\C:\"
         * PrintName: ""
         *
         * box.com mounted cloud storage
         * SubstituteName: "\??\Volume{<UUID>}\"
         * PrintName: ""
         */
        struct {
            USHORT SubstituteNameOffset;
            USHORT SubstituteNameLength;
            USHORT PrintNameOffset;
            USHORT PrintNameLength;
            ULONG Flags;
            WCHAR PathBuffer[1];
        } SymbolicLinkReparseBuffer;

        struct {
            USHORT SubstituteNameOffset;
            USHORT SubstituteNameLength;
            USHORT PrintNameOffset;
            USHORT PrintNameLength;
            WCHAR PathBuffer[1];
        } MountPointReparseBuffer;

        struct {
            UCHAR DataBuffer[1];
        } GenericReparseBuffer;
    };
} fox__REPARSE_DATA_BUFFER__;

// Our convenience type for allocating REPARSE_DATA_BUFFER along with sufficient space after it
typedef union {
    fox__REPARSE_DATA_BUFFER__ rdb;
    BYTE storage[MAXIMUM_REPARSE_DATA_BUFFER_SIZE];
} fox__REPARSE_DATA_BUFFER__win;

static bool fox__get_rdb__(HANDLE h, fox__REPARSE_DATA_BUFFER__ *rdb) {
    fox__REPARSE_DATA_BUFFER__win rdb_storage = {0};
    DWORD reparse_len;
    if (!DeviceIoControl(h, FSCTL_GET_REPARSE_POINT, NULL, 0, rdb_storage.storage, FOX_ARRLEN(rdb_storage.storage), &reparse_len, NULL))
        return false;

    *rdb = rdb_storage.rdb;
    return true;
}

static FILETIME fox__cvt_time_t_to_FILETIME__(time_t t) {
    // Windows FILETIME is in 100-nanosecond intervals since Jan 1 1601.
    // Unix time_t is seconds since Jan 1 1970.
    // Calculate the FILETIME value:
    // seconds -> 100-ns ticks, and add the epoch offset.
    ULARGE_INTEGER time_value;
    time_value.QuadPart = ((ULONGLONG) t * 10000000ULL) + 116444736000000000ULL;

    FILETIME ft;
    ft.dwLowDateTime = time_value.LowPart;
    ft.dwHighDateTime = time_value.HighPart;
    return ft;
}

static time_t fox__cvt_FILETIME_to_time_t__(FILETIME ft) {
    // Number of 100-nanosecond intervals between
    // Jan 1, 1601 and Jan 1, 1970
    const u64 EPOCH_DIFF = 116444736000000000ULL;
    // Pack the FILETIME value
    u64 ft_val = ((u64) ft.dwHighDateTime << 32) | (u64) ft.dwLowDateTime;
    // If earlier than UNIX epoch then return 0
    if (ft_val < EPOCH_DIFF)
        return 0;
    // Calcalute UNIX time
    return (time_t) ((ft_val - EPOCH_DIFF) / 10000000ULL);
}

static bool fox__fs_status__(const char *path, FoxFileStatus *status, bool follow_symlink) {
    bool result;

    // Normally, we only need FILE_READ_ATTRIBUTES access mode. But SMBv1 reports incorrect
    // file attributes in GetFileInformationByHandleEx in this case (e.g. it reports FILE_ATTRIBUTE_NORMAL
    // for a directory in a SMBv1 share), so we add FILE_READ_EA as a workaround.
    HANDLE h = CreateFile(path, FILE_READ_ATTRIBUTES | FILE_READ_EA, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING,
                          follow_symlink ? FILE_FLAG_BACKUP_SEMANTICS : FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT, NULL);
    DWORD attrs, reparse_tag = 0u;
    FILETIME last_acc, last_mod;
    if (h == INVALID_HANDLE_VALUE) {
        // For some system files and folders like "System Volume Information" CreateFile fails
        // with ERROR_ACCESS_DENIED. GetFileAttributes succeeds for such files, so try that.
        // Though this will only help if the file is not a reparse point (symlink or not).
        DWORD err = GetLastError();
        if (err == ERROR_ACCESS_DENIED) {
            attrs = GetFileAttributes(path);
            if (attrs == INVALID_FILE_ATTRIBUTES)
                return false;
            if ((attrs & FILE_ATTRIBUTE_REPARSE_POINT) == 0u) {
                if (!GetFileTime(h, NULL, &last_acc, &last_mod))
                    return false;
                goto main_code;
            }
        }
        return false;
    }

    FILE_ATTRIBUTE_TAG_INFO info;
    if (!GetFileInformationByHandleEx(h, FileAttributeTagInfo, &info, sizeof(info))) {
        // On FAT/exFAT filesystems requesting FILE_ATTRIBUTE_TAG_INFO returns ERROR_INVALID_PARAMETER.
        // Presumably, this is because these filesystems don't support reparse points, so ReparseTag
        // cannot be returned. Also check ERROR_NOT_SUPPORTED for good measure. Fall back to the legacy
        // code path in this case.
        DWORD err = GetLastError();
        if (err == ERROR_INVALID_PARAMETER || err == ERROR_NOT_SUPPORTED) {
            BY_HANDLE_FILE_INFORMATION fi;
            if (!GetFileInformationByHandle(h, &fi))
                fox_return_defer(false);
            attrs = fi.dwFileAttributes;
            if (attrs & FILE_ATTRIBUTE_REPARSE_POINT) {
                fox__REPARSE_DATA_BUFFER__ rdb;
                if (!fox__get_rdb__(h, &rdb))
                    fox_return_defer(false);
                reparse_tag = rdb.ReparseTag;
                last_acc = fi.ftLastAccessTime;
                last_mod = fi.ftLastWriteTime;
                goto main_code;
            }
        }
        fox_return_defer(false);
    }
    attrs = info.FileAttributes;
    reparse_tag = info.ReparseTag;
    if (!GetFileTime(h, NULL, &last_acc, &last_mod))
        fox_return_defer(false);

main_code:
    // Set type
    if (attrs & FILE_ATTRIBUTE_REPARSE_POINT) {
        if (reparse_tag == IO_REPARSE_TAG_DEDUP)
            status->type = FOX_FILE_REGULAR;
        else if (reparse_tag == IO_REPARSE_TAG_SYMLINK || reparse_tag == IO_REPARSE_TAG_MOUNT_POINT)
            status->type = FOX_FILE_SYMLINK;
        else
            status->type = FOX_FILE_UNKNOWN; // FILE_REPARSE
    } else if (attrs & FILE_ATTRIBUTE_DIRECTORY)
        status->type = FOX_FILE_DIR;
    else
        status->type = FOX_FILE_REGULAR;
    // Set perms
    // READ permissions by default
    status->read_only = attrs & FILE_ATTRIBUTE_READONLY;
    // Set file size
    LARGE_INTEGER fsz = {0};
    if (!GetFileSizeEx(h, &fsz))
        fox_return_defer(false);
    status->size = (size_t) fsz.QuadPart;
    // Now the times
    status->last_accessed = fox__cvt_FILETIME_to_time_t__(last_acc);
    status->last_modified = fox__cvt_FILETIME_to_time_t__(last_mod);
    // Gracefully return
    fox_return_defer(true);

defer:
    CloseHandle(h);
    return result;
}

#endif // FOX_OS_WINDOWS

bool fox_fs_read_symlink(const char *path, FoxStringBuf *sb) {
    if (!sb || !path || *path == '\0')
        return false;

#if defined(FOX_OS_LINUX)
    bool result;
    char *buf = NULL;
    fox_da_clear(sb);

    FoxFileStatus status;
    if (!fox_fs_symlink_status(path, &status))
        fox_return_defer(false);
    if (status.type != FOX_FILE_SYMLINK)
        fox_return_defer(false);

    const size_t buf_size = status.size;
    buf = malloc(buf_size + 1);
    ssize_t len = readlink(path, buf, buf_size + 1);

    if (len == -1)
        fox_return_defer(false);
    buf[len] = '\0';
    fox_sb_copy(sb, fox_sv(buf));

defer:
    free(buf);
    return result;
#elif defined(FOX_OS_WINDOWS)
    bool result;

    HANDLE h = CreateFile(sb->items, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING,
                          FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_BACKUP_SEMANTICS, NULL);
    if (h == INVALID_HANDLE_VALUE)
        return false;

    fox__REPARSE_DATA_BUFFER__ rdb;
    fox__get_rdb__(h, &rdb);

    const wchar_t *buffer;
    size_t offset, len;

    switch (rdb.ReparseTag) {
    case IO_REPARSE_TAG_MOUNT_POINT:
        // NTFS junctions
        buffer = rdb.MountPointReparseBuffer.PathBuffer;
        offset = rdb.MountPointReparseBuffer.SubstituteNameOffset / sizeof(wchar_t);
        len = rdb.MountPointReparseBuffer.SubstituteNameLength / sizeof(wchar_t);
        break;
    case IO_REPARSE_TAG_SYMLINK:
        // Actual symbolic links
        buffer = rdb.SymbolicLinkReparseBuffer.PathBuffer;
        offset = rdb.SymbolicLinkReparseBuffer.SubstituteNameOffset / sizeof(wchar_t);
        len = rdb.SymbolicLinkReparseBuffer.SubstituteNameLength / sizeof(wchar_t);
        break;
    default:
        // TODO: Report error
        fox_return_defer(false);
    }

    fox_sb_free(sb);
    // FIXME: fix utf16 => utf8 happening here as wchar_t* => char *
    *sb = fox_sb_from_chars((char *) buffer + offset, len);
    fox_return_defer(true);

defer:
    CloseHandle(h);
    return result;
#else
#    error "Implement this"
#endif
}

static void fox__fs_read_dir_visitor__(FoxDirEntry entry) {
    FoxStringBufs *files = (FoxStringBufs *) entry.arg;
    fox_da_append(files, fox_sb(entry.path));
}

bool fox_fs_read_entire_dir(const char *path, FoxStringBufs *files) {
    if (!files || !path || *path == '\0')
        return false;

    if (!fox_fs_visit_dir(path, fox__fs_read_dir_visitor__, .arg = files))
        return false;
    return true;
}

static bool fox__fs_visit_dir__(const char *path, FoxVisitFn visitor, size_t level, bool *stop, FoxVisitOpt opt) {
    if (!visitor || !path || *path == '\0')
        return false;
    if (opt.nofollow_dir_symlink)
        if (fox_fs_is_dir(path) && fox_fs_is_symlink(path))
            goto visit_only_one;
    if (!fox_fs_is_dir(path)) {
visit_only_one:
        FoxVisitAction action = FOX_VISIT_CONT;
        FoxDirEntry dir_entry = {
                .path = path,
                .level = level,
                .arg = opt.arg,
                .action = &action,
        };
        visitor(dir_entry);
        // Evaluate action
        if (action == FOX_VISIT_STOP && stop)
            *stop = true;
        return true;
    }

#if defined(FOX_OS_LINUX)
    bool result;
    FoxStringBuf file_path = {0};

    DIR *dir = opendir(path);
    if (dir == NULL)
        return false;

    // Visit directory
    if (!opt.post_order) {
        FoxVisitAction action = FOX_VISIT_CONT;
        FoxDirEntry dir_entry = {
                .path = path,
                .level = level,
                .arg = opt.arg,
                .action = &action,
        };
        visitor(dir_entry);
        // Evaluate action
        switch (action) {
        case FOX_VISIT_CONT:
            break; // Do nothing
        case FOX_VISIT_SKIP:
            fox_return_defer(true);
        case FOX_VISIT_STOP:
            if (stop)
                *stop = true;
            fox_return_defer(true);
        default:
            FOX_UNREACHABLE("fox__fs_visit_dir__");
        }
    }

    bool recursion_guard;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (fox_streq(entry->d_name, ".") || fox_streq(entry->d_name, ".."))
            continue;
        recursion_guard = opt.recursive;
        // Set up file path
        fox_da_clear(&file_path);
        fox_sb_appendf(&file_path, "%s" FOX_FILE_SEPARATOR "%s", path, entry->d_name);
        // Do not follow symlinks that refer to dirs (if said so)
        if (opt.nofollow_dir_symlink)
            if (fox_fs_is_dir(file_path.items) && fox_fs_is_symlink(file_path.items))
                recursive_guard = false;
        // Recursive code
        if (recursive_guard && opt.pre_order) {
            bool stop = false;
            if (!fox__fs_visit_dir__(file_path.items, visitor, level + 1, &stop, opt))
                fox_return_defer(false);
            if (stop)
                fox_return_defer(true);
        }
    }

    // Visit directory
    if (opt.post_order) {
        FoxVisitAction action = FOX_VISIT_CONT;
        FoxDirEntry dir_entry = {
                .path = path,
                .level = level,
                .arg = opt.arg,
                .action = &action,
        };
        visitor(dir_entry);
        // Evaluate action
        switch (action) {
        case FOX_VISIT_CONT:
            break; // Do nothing
        case FOX_VISIT_SKIP:
            fox_return_defer(true);
        case FOX_VISIT_STOP:
            if (stop)
                *stop = true;
            fox_return_defer(true);
        default:
            FOX_UNREACHABLE("fox__fs_visit_dir__");
        }
    }
    fox_return_defer(true);

defer:
    closedir(dir);
    fox_da_free(&file_path);
    return result;
#elif defined(FOX_OS_WINDOWS)
    bool result;
    FoxStringBuf file_path = {0};
    FoxStringBuf glob = {0};
    WIN32_FIND_DATA find_data = {0};
    HANDLE h_find = INVALID_HANDLE_VALUE;

    if (fox_str_ends_with(path, "\\"))
        fox_sb_appendf(&glob, "%s*", path);
    else
        fox_sb_appendf(&glob, "%s\\*", path);

    h_find = FindFirstFile(glob.items, &find_data);
    if (h_find == INVALID_HANDLE_VALUE) {
        if (fox_fs_exists(path) && GetLastError() == ERROR_FILE_NOT_FOUND)
            // No files inside the directory
            fox_return_defer(true);
        fox_return_defer(false);
    }

    // Visit directory
    if (!opt.post_order) {
        FoxVisitAction action = FOX_VISIT_CONT;
        FoxDirEntry dir_entry = {
                .path = path,
                .level = level,
                .arg = opt.arg,
                .action = &action,
        };
        visitor(dir_entry);
        // Evaluate action
        switch (action) {
        case FOX_VISIT_CONT:
            break; // Do nothing
        case FOX_VISIT_SKIP:
            fox_return_defer(true);
        case FOX_VISIT_STOP:
            if (stop)
                *stop = true;
            fox_return_defer(true);
        default:
            FOX_UNREACHABLE("fox__fs_visit_dir__");
        }
    }

    bool recursion_guard;
    do {
        if (fox_streq(find_data.cFileName, ".") || fox_streq(find_data.cFileName, ".."))
            continue;
        recursion_guard = opt.recursive;
        // Set up the file path
        fox_da_clear(&file_path);
        fox_sb_appendf(&file_path, "%s" FOX_FILE_SEPARATOR "%s", path, find_data.cFileName);
        // Do not follow symlinks that refer to dirs (if said so)
        if (opt.nofollow_dir_symlink)
            if (fox_fs_is_dir(file_path.items) && fox_fs_is_symlink(file_path.items))
                recursion_guard = false;
        // Recursive code
        if (recursion_guard && opt.post_order) {
            bool stop = false;
            if (!fox__fs_visit_dir__(file_path.items, visitor, level + 1, &stop, opt))
                fox_return_defer(false);
            if (stop)
                fox_return_defer(true);
        }
    } while (FindNextFile(h_find, &find_data));

    // Visit directory
    if (opt.post_order) {
        FoxVisitAction action = FOX_VISIT_CONT;
        FoxDirEntry dir_entry = {
                .path = path,
                .level = level,
                .arg = opt.arg,
                .action = &action,
        };
        visitor(dir_entry);
        // Evaluate action
        switch (action) {
        case FOX_VISIT_CONT:
            break; // Do nothing
        case FOX_VISIT_SKIP:
            fox_return_defer(true);
        case FOX_VISIT_STOP:
            if (stop)
                *stop = true;
            fox_return_defer(true);
        default:
            FOX_UNREACHABLE("fox__fs_visit_dir__");
        }
    }
    fox_return_defer(true);

defer:
    if (h_find != INVALID_HANDLE_VALUE)
        FindClose(h_find);
    fox_da_free(&glob);
    fox_da_free(&file_path);
    return result;
#else
#    error "Implement this"
#endif
}

bool fox_fs_visit_dir_opt(const char *path, FoxVisitFn visitor, FoxVisitOpt opt) { return fox__fs_visit_dir__(path, visitor, 0, NULL, opt); }

#if defined(FOX_OS_LINUX)
static FoxFileType fox__fs_file_type__(mode_t mode) {
    if (S_ISREG(mode))
        return FOX_FILE_REGULAR;
    else if (S_ISDIR(mode))
        return FOX_FILE_DIR;
    else if ((mode & 0170000) == 0120000)
        return FOX_FILE_SYMLINK; // This work only when lstat() is used
    else if (S_ISCHR(mode))
        return FOX_FILE_CHARACTER;
    else if (S_ISBLK(mode))
        return FOX_FILE_BLOCK;
    else if (S_ISFIFO(mode))
        return FOX_FILE_PIPE;
    else if ((mode & 0170000) == 0140000)
        return FOX_FILE_SOCKET;
    else
        return FOX_FILE_UNKNOWN;
}
#endif

bool fox_fs_file_status(const char *path, FoxFileStatus *status) {
    if (!status || !path || *path == '\0')
        return false;

#if defined(FOX_OS_LINUX)
    struct stat file_info;
    if (stat(path, &file_info) < 0)
        return false;

    // Get the file type
    status->type = fox__fs_file_type__(file_info.st_mode);
    status->size = file_info.st_size;
    // status->perms = (FoxFilePerms) (file_info.st_mode & FOX_PERM_ALL);
    if (file_info.st_mode & (FOX_PERM_OWNER_WRITE | FOX_PERM_GROUP_WRITE | FOX_PERM_OTHERS_WRITE))
        status->read_only = false;
    else
        status->read_only = true;
    status->last_modified = file_info.st_mtime;
    status->last_accessed = file_info.st_atime;
    return true;
#elif defined(FOX_OS_WINDOWS)
    if (!fox_fs_symlink_status(path, status))
        return false;
    if (status->type == FOX_FILE_SYMLINK)
        return fox__fs_status__(path, status, true);
    else
        return true;
#else
#    error "Implement this"
#endif
}

bool fox_fs_symlink_status(const char *path, FoxFileStatus *status) {
    if (!status || !path || *path == '\0')
        return false;

#if defined(FOX_OS_LINUX)
    struct stat file_info;
    if (lstat(path, &file_info) < 0)
        return false;

    // Get the file type
    status->type = fox__fs_file_type__(file_info.st_mode);
    status->size = file_info.st_size;
    if (file_info.st_mode & (FOX_PERM_OWNER_WRITE | FOX_PERM_GROUP_WRITE | FOX_PERM_OTHERS_WRITE))
        status->read_only = false;
    else
        status->read_only = true;
    status->last_modified = file_info.st_mtime;
    status->last_accessed = file_info.st_atime;
    return true;
#elif defined(FOX_OS_WINDOWS)
    return fox__fs_status__(path, status, false);
#else
#    error "Implement this"
#endif
}

FoxFileType fox_fs_file_type(const char *path) {
    FoxFileStatus status;
    if (fox_fs_file_status(path, &status))
        return status.type;
    return FOX_FILE_UNKNOWN;
}

u64 fox_fs_file_size(const char *path) {
    FoxFileStatus status;
    if (fox_fs_file_status(path, &status))
        return status.size;
    return 0;
}

bool fox_fs_set_file_size(const char *path, u64 new_size) {
    if (!path || *path == '\0')
        return false;
    if (!fox_fs_is_regular_file(path))
        return false;

#if defined(FOX_OS_LINUX)
    return truncate(path, new_size) == 0;
#elif defined(FOX_OS_WINDOWS)
    bool result;

    HANDLE h =
            CreateFile(path, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h == INVALID_HANDLE_VALUE)
        return false;
    // Go to the specified location
    LARGE_INTEGER sz = {0};
    sz.QuadPart = new_size;
    if (!SetFilePointerEx(h, sz, NULL, FILE_BEGIN))
        fox_return_defer(false);
    // Set this as the new end of file
    if (!SetEndOfFile(h))
        fox_return_defer(false);
    fox_return_defer(true);

defer:
    CloseHandle(h);
    return result;
#else
#    error "Implement this"
#endif
}

bool fox_fs_set_status(const char *path, const FoxFileStatus status) {
    if (!path || *path == '\0')
        return false;

#if defined(FOX_OS_LINUX)
    if (status.read_only)
        fox_fs_set_perms(path, FOX_PERM_READONLY);
    const struct timeval acc_time = {status.last_accessed, 0};
    const struct timeval mod_time = {status.last_modified, 0};
    if (utimes(path, (const struct timeval[2]) {acc_time, mod_time}) == 0)
        return true;
    return false;
#elif defined(FOX_OS_WINDOWS)
    bool result;

    // Set or reset read only
    DWORD attrs = GetFileAttributes(path);
    if (attrs == INVALID_FILE_ATTRIBUTES)
        return false;
    if (status.read_only)
        attrs |= FILE_ATTRIBUTE_READONLY;
    else
        attrs &= ~FILE_ATTRIBUTE_READONLY;
    if (!SetFileAttributes(path, attrs))
        return false;

    HANDLE h = CreateFile(path, FILE_WRITE_ATTRIBUTES, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING,
                          FILE_FLAG_BACKUP_SEMANTICS, NULL);
    if (h == INVALID_HANDLE_VALUE)
        return false;
    // Set the file time
    FILETIME last_acc = fox__cvt_time_t_to_FILETIME__(status.last_accessed);
    FILETIME last_mod = fox__cvt_time_t_to_FILETIME__(status.last_modified);
    fox_return_defer(SetFileTime(h, NULL, &last_acc, &last_mod));

defer:
    CloseHandle(h);
    return result;
#else
#    error "Implement this"
#endif
}

bool fox_fs_set_symlink_status(const char *path, const FoxFileStatus status) {
    if (!path || *path == '\0')
        return false;

#if defined(FOX_OS_LINUX)
    if (status.read_only)
        fox_fs_set_symlink_perms(path, FOX_PERM_READONLY);
    const struct timeval acc_time = {status.last_accessed, 0};
    const struct timeval mod_time = {status.last_modified, 0};
    if (lutimes(path, (const struct timeval[2]) {acc_time, mod_time}) == 0)
        return true;
    return false;
#elif defined(FOX_OS_WINDOWS)
    bool result;

    if (!fox_fs_is_symlink(path))
        fox_fs_set_status(path, status);

    // Setting symlinks readonly does not make any sense in Windows

    HANDLE h = CreateFile(path, FILE_WRITE_ATTRIBUTES, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING,
                          FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_BACKUP_SEMANTICS, NULL);
    if (h == INVALID_HANDLE_VALUE)
        return false;
    // Set the file time
    FILETIME last_acc = fox__cvt_time_t_to_FILETIME__(status.last_accessed);
    FILETIME last_mod = fox__cvt_time_t_to_FILETIME__(status.last_modified);
    fox_return_defer(SetFileTime(h, NULL, &last_acc, &last_mod));

defer:
    CloseHandle(h);
    return result;
#else
#    error "Implement this"
#endif
}

bool fox_fs_get_perms(const char *path, FoxFilePerms *perms) {
    if (!path || *path == '\0')
        return false;

#if defined(FOX_OS_LINUX)
    struct stat file_info;
    if (stat(path, &file_info) < 0)
        return false;

    *perms = (FoxFilePerms) file_info.st_mode;
    return true;
#elif defined(FOX_OS_WINDOWS)
    FOX_UNUSED(path);
    FOX_UNUSED(perms);
    return false;
#else
#    error "Implement this"
#endif
}

bool fox_fs_set_perms(const char *path, FoxFilePerms perms) {
    if (!path || *path == '\0')
        return false;

#if defined(FOX_OS_LINUX)
    if (chmod(path, (mode_t) perms) == 0)
        return true;
    return false;
#elif defined(FOX_OS_WINDOWS)
    FOX_UNUSED(path);
    FOX_UNUSED(perms);
    return false;
#else
#    error "Implement this"
#endif
}

bool fox_fs_get_symlink_perms(const char *path, FoxFilePerms *perms) {
    if (!path || *path == '\0')
        return false;

#if defined(FOX_OS_LINUX)
    struct stat file_info;
    if (lstat(path, &file_info) < 0)
        return false;

    *perms = (FoxFilePerms) file_info.st_mode;
    return true;
#elif defined(FOX_OS_WINDOWS)
    FOX_UNUSED(path);
    FOX_UNUSED(perms);
    return false;
#else
#    error "Implement this"
#endif
}

bool fox_fs_set_symlink_perms(const char *path, FoxFilePerms perms) {
    if (!path || *path == '\0')
        return false;

#if defined(FOX_OS_LINUX)
    if (fchmodat(AT_FDCWD, path, (mode_t) perms, AT_SYMLINK_NOFOLLOW))
        return true;
    return false;
#elif defined(FOX_OS_WINDOWS)
    FOX_UNUSED(path);
    FOX_UNUSED(perms);
    return false;
#else
#    error "Implement this"
#endif
}

bool fox_fs_is_block_file(const char *path) { return fox_fs_file_type(path) == FOX_FILE_BLOCK; }

bool fox_fs_is_character_file(const char *path) { return fox_fs_file_type(path) == FOX_FILE_CHARACTER; }

bool fox_fs_is_dir(const char *path) { return fox_fs_file_type(path) == FOX_FILE_DIR; }

bool fox_fs_is_empty(const char *path) {
    if (!fox_fs_exists(path))
        return false;
    switch (fox_fs_file_type(path)) {
    case FOX_FILE_REGULAR:
    case FOX_FILE_DIR:
    case FOX_FILE_SYMLINK:
        return fox_fs_file_size(path) == 0;
    case FOX_FILE_BLOCK:
    case FOX_FILE_CHARACTER:
    case FOX_FILE_PIPE:
    case FOX_FILE_SOCKET:
    case FOX_FILE_UNKNOWN:
        break;
    }
    return false;
}

bool fox_fs_is_pipe(const char *path) { return fox_fs_file_type(path) == FOX_FILE_PIPE; }

bool fox_fs_is_other(const char *path) {
    if (!fox_fs_exists(path))
        return false;

    switch (fox_fs_file_type(path)) {
    case FOX_FILE_REGULAR:
    case FOX_FILE_DIR:
    case FOX_FILE_SYMLINK:
        return false;
    case FOX_FILE_BLOCK:
    case FOX_FILE_CHARACTER:
    case FOX_FILE_PIPE:
    case FOX_FILE_SOCKET:
    case FOX_FILE_UNKNOWN:
        break;
    }
    return true;
}

bool fox_fs_is_regular_file(const char *path) { return fox_fs_file_type(path) == FOX_FILE_REGULAR; }

bool fox_fs_is_socket(const char *path) { return fox_fs_file_type(path) == FOX_FILE_SOCKET; }

bool fox_fs_is_symlink(const char *path) {
    FoxFileStatus status;
    if (fox_fs_symlink_status(path, &status))
        return status.type == FOX_FILE_SYMLINK;
    return false;
}

FoxStringBuf fox_fs_getcwd(void) {
#if defined(FOX_OS_LINUX)
    char *buf = getcwd(NULL, 0);
    FoxStringBuf sb = fox_sb(buf);
    free(buf);
    return sb;
#elif defined(FOX_OS_WINDOWS)
    DWORD size = GetCurrentDirectory(0, NULL);
    if (size == 0)
        // TODO: Report error
        return (FoxStringBuf) {0};

    FoxStringBuf sb = {0};
    fox_da_reserve(&sb, size + 1);
    GetCurrentDirectory(size + 1, sb.items);
    sb.size = size;
    sb.items[sb.size] = '\0';
    return sb;
#else
#    error "Implement this"
#endif
}

bool fox_fs_setcwd(const char *path) {
    if (!path || *path == '\0')
        return false;

#if defined(FOX_OS_LINUX)
    return chdir(path) == 0;
#elif defined(FOX_OS_WINDOWS)
    return SetCurrentDirectory(path);
#else
#    error "Implement this"
#endif
}

bool fox_fs_exists(const char *path) {
    if (!path || *path == '\0')
        return false;

#if defined(FOX_OS_LINUX)
    return access(path, F_OK) == 0;
#elif defined(FOX_OS_WINDOWS)
    DWORD attr = GetFileAttributes(path);
    if (attr == INVALID_FILE_ATTRIBUTES) {
        DWORD err = GetLastError();
        return err == ERROR_FILE_NOT_FOUND || err == ERROR_PATH_NOT_FOUND || err == ERROR_INVALID_NAME // "tools/jam/src/:sys:stat.h", "//foo"
               || err == ERROR_INVALID_DRIVE                                                           // USB card reader with no card inserted
               || err == ERROR_NOT_READY                                                               // CD/DVD drive with no disc inserted
               || err == ERROR_INVALID_PARAMETER                                                       // ":sys:stat.h"
               || err == ERROR_BAD_PATHNAME                                                            // "//no-host" on Win64
               || err == ERROR_BAD_NETPATH                                                             // "//no-host" on Win32
               || err == ERROR_BAD_NET_NAME;                                                           // "//no-host/no-share" on Win10 x64
    }
    return true;
#else
#    error "Implement this"
#endif
}

bool fox_fs_equivalent(const char *path1, const char *path2) {
    if (!path1 || *path1 == '\0')
        return false;
    if (!path2 || *path2 == '\0')
        return false;

#if defined(FOX_OS_LINUX)
    struct stat file_info1;
    struct stat file_info2;

    if (stat(path1, &file_info1) < 0)
        return false;
    if (stat(path2, &file_info2) < 0)
        return false;

    return file_info1.st_dev == file_info2.st_dev && file_info1.st_ino == file_info2.st_ino;
#elif defined(FOX_OS_WINDOWS)
    bool result;

    HANDLE h1 = CreateFile(path1,                                                  // Path of the file
                           GENERIC_READ,                                           // Sir, I want to read
                           FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, // Other people can read and write, I hv no prblm
                           NULL,                                                   // Do not really know what is this
                           OPEN_EXISTING,                                          // I will not create any file
                           FILE_FLAG_BACKUP_SEMANTICS,                             // Allow directories also pls
                           NULL);                                                  // huh?
    HANDLE h2 = CreateFile(path2, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING,
                           FILE_FLAG_BACKUP_SEMANTICS, NULL);
    if (h1 == INVALID_HANDLE_VALUE || h2 == INVALID_HANDLE_VALUE)
        fox_return_defer(false);

    BY_HANDLE_FILE_INFORMATION fi1, fi2;
    if (!GetFileInformationByHandle(h1, &fi1) || !GetFileInformationByHandle(h2, &fi2))
        fox_return_defer(false);

    fox_return_defer(fi1.dwVolumeSerialNumber == fi2.dwVolumeSerialNumber && fi1.nFileIndexHigh == fi2.nFileIndexHigh &&
                     fi1.nFileIndexLow == fi2.nFileIndexLow);

defer:
    if (h1 != INVALID_HANDLE_VALUE)
        CloseHandle(h1);
    if (h2 != INVALID_HANDLE_VALUE)
        CloseHandle(h2);
    return result;
#else
#    error "Implement this"
#endif
}

bool fox_fs_canonical(FoxStringBuf *sb) {
    if (!sb || sb->size == 0)
        return false;

#if defined(FOX_OS_LINUX)
    char *buf = realpath(sb->items, NULL);
    if (!buf)
        return false;

    fox_sb_free(sb);
    *sb = fox_sb(buf);
    free(buf);
    return true;
#elif defined(FOX_OS_WINDOWS)
    bool result;

    HANDLE h = CreateFile(sb->items, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING,
                          FILE_FLAG_BACKUP_SEMANTICS, NULL);
    if (h == INVALID_HANDLE_VALUE)
        return false;

    char tmp = 0;
    DWORD ret = GetFinalPathNameByHandle(h, &tmp, 1, FILE_NAME_NORMALIZED | VOLUME_NAME_DOS);
    if (ret == 0)
        fox_return_defer(false);

    fox_da_clear(sb);
    fox_da_reserve(sb, ret);
    ret = GetFinalPathNameByHandle(h, sb->items, ret, FILE_NAME_NORMALIZED | VOLUME_NAME_DOS);
    if (ret == 0)
        fox_return_defer(false);

    sb->size = ret;
    fox_return_defer(true);

defer:
    CloseHandle(h);
    return result;
#else
#    error "Implement this"
#endif
}

bool fox_fs_space(const char *path, FoxSpaceInfo *space) {
    if (!space || !path || *path == '\0')
        return false;

#if defined(FOX_OS_LINUX)
    struct statvfs fs_info;
    if (statvfs(path, &fs_info) == 0) {
        space->capacity = fs_info.f_blocks * fs_info.f_frsize;
        space->free = fs_info.f_bfree * fs_info.f_frsize;
        space->available = fs_info.f_bavail * fs_info.f_frsize;
        return true;
    }
    return false;
#elif defined(FOX_OS_WINDOWS)
    // TODO: parse root path
    ULARGE_INTEGER avail = {0};
    ULARGE_INTEGER cap = {0};
    ULARGE_INTEGER free = {0};
    if (!GetDiskFreeSpaceEx(path, &avail, &cap, &free))
        return false;

    space->capacity = cap.QuadPart;
    space->free = free.QuadPart;
    space->available = avail.QuadPart;
    return true;
#else
#    error "Implement this"
#endif
};

bool fox_fs_create_dir(const char *path) {
    if (!path || *path == '\0')
        return false;

#if defined(FOX_OS_LINUX)
    if (!fox_fs_exists(path))
        if (mkdir(path, FOX_PERM_ALL) == 0)
            return true;
    return false;
#elif defined(FOX_OS_WINDOWS)
    return CreateDirectory(path, NULL);
#else
#    error "Implement this"
#endif
}

bool fox_fs_create_dir_all(const char *p) {
    FoxStringView path = fox_sv(p);
    if (path.size == 0)
        return false;
    if (fox_fs_exists(p))
        return false;

    FoxStringView path_rem = {0};
    FoxStringBuf split = {0};

    for (size_t i = 0; i < path.size; i++) {
        path_rem = fox_str_slice(path, i, path.size);
        i = i + fox_str_find_first_of(path_rem, fox_sv(FOX_FILE_SEPARATOR));

        fox_sb_copy(&split, fox_str_slice(path, 0, i));
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
    if (!target || !link || *target == '\0' || *link == '\0')
        return false;

#if defined(FOX_OS_LINUX)
    if (symlink(target, link) == 0)
        return true;
    return false;
#elif defined(FOX_OS_WINDOWS)
    if (fox_fs_is_dir(target))
        return CreateSymbolicLink(link, target, SYMBOLIC_LINK_FLAG_DIRECTORY); // Link to a directory
    else if (fox_fs_exists(target))
        return CreateSymbolicLink(link, target, 0); // Link to a file
    else
        return false;
#else
#    error "Implement this"
#endif
}

bool fox_fs_remove(const char *path) {
    if (!path || *path == '\0')
        return false;
#if defined(FOX_OS_LINUX)
    // TODO: write your own remove function
    // as this has a lot of implementation-defined behaviour
    // which is not portable.
    return remove(path) == 0;
#    error "Implement this"
#elif defined(FOX_OS_WINDOWS)
    DWORD attrs = GetFileAttributes(path);
    const bool is_dir = (attrs & FILE_ATTRIBUTE_DIRECTORY) != 0;
    const bool is_read_only = (attrs & FILE_ATTRIBUTE_READONLY) != 0;
    // RemoveDirectory and DeleteFile do not allow to remove if it is read only
    // So we first remove the read only attribute
    if (is_read_only) {
        DWORD new_attrs = attrs & ~FILE_ATTRIBUTE_READONLY;
        if (!SetFileAttributes(path, new_attrs))
            return false; // Failed to set read only
    }
    // Now remove
    BOOL res = (is_dir ? RemoveDirectoryA(path) : DeleteFileA(path));
    if (!res && fox_fs_exists(path) && is_read_only)
        // Restore the read only flag
        SetFileAttributes(path, attrs);
    return res;
#else
#    error "Implement this"
#endif
}

static void fox__fs_remove_dir_visitor__(FoxDirEntry entry) {
#ifndef FOX_NO_ECHO
    if (!fox_fs_remove(entry.path))
        fox_log_error("[FS] Failed to remove: %s", entry.path);
#else
    fox_fs_remove(entry.path);
#endif
}

bool fox_fs_remove_all(const char *path) {
    if (!path || *path == '\0')
        return false;
    if (!fox_fs_is_dir(path))
        return fox_fs_remove(path);

    if (!fox_fs_visit_dir(path, fox__fs_remove_dir_visitor__, .recursive = true, .post_order = true, .nofollow_dir_symlink = true))
        return false;
    return true;
}

bool fox_fs_rename(const char *old_path, const char *new_path) {
    if (!old_path || *old_path == '\0')
        return false;
    if (!new_path || *new_path == '\0')
        return false;

    if (rename(old_path, new_path) == 0)
        return true;
    return false;
}

bool fox_fs_move(const char *old_path, const char *new_path) { return fox_fs_rename(old_path, new_path); }

static bool fox__fs_copy_file__(const char *from, const char *to) {
    bool result;

    // Copy file contents
    FoxStringBuf sb = {0};
    if (!fox_fs_read_entire_file(from, &sb))
        fox_return_defer(false);
    if (!fox_fs_write_entire_file(to, fox_sv(sb)))
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

bool fox_fs_copy(const char *from, const char *to, FoxCopyOptions options) {
    if (!from || !to || *from == '\0' || *to == '\0')
        return false;

    // TODO: implement this after completing directory visit
    FOX_UNUSED(from);
    FOX_UNUSED(to);
    FOX_UNUSED(options);
    FOX_TODO("fox_fs_copy");
    return false;
}

bool fox_fs_copy_file(const char *from, const char *to, FoxCopyOptions options) {
    if (!from || !to || *from == '\0' || *to == '\0')
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
        case FOX_COPY_SKIP_EXISTING:
            // Do nothing
            return false;
        case FOX_COPY_OVERWRITE_EXISTING:
            return fox__fs_copy_file__(from, to);
        case FOX_COPY_UPDATE_EXISTING: {
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
    if (!from || !to || *from == '\0' || *to == '\0')
        return false;

    bool result;

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

#ifdef FOX_OS_LINUX
bool fox__cmd_set_nonblocking_pipe__posix(FoxFd fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0)
        return false;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK) >= 0;
}
#endif // FOX_OS_LINUX

bool fox_cmd_spawn_opt(FoxProc *process, const char *path, const FoxStringViews argv, const FoxSpawnOpt opt) {
    if (!path || *path == '\0')
        return false;

#if defined(FOX_OS_LINUX)
    typedef struct {
        const char **items;
        size_t size;
        size_t capacity;
    } CStrs;

    mode_t create_mode = FOX_PERM_OWNER_READ | FOX_PERM_OWNER_WRITE | FOX_PERM_GROUP_READ | FOX_PERM_OTHERS_READ;

    FoxFd stdin_fd = FOX_INVALID_FD;
    FoxFd stdout_fd = FOX_INVALID_FD;
    FoxFd stderr_fd = FOX_INVALID_FD;
    if (opt.stdin_path) {
        stdin_fd = open(opt.stdin_path, O_RDONLY);
        if (stdin_fd == FOX_INVALID_FD)
            return false;
    }
    if (opt.stdout_path) {
        stdout_fd = open(opt.stdout_path, O_WRONLY, create_mode);
        if (stdout_fd == FOX_INVALID_FD)
            return false;
    }
    if (opt.stderr_path) {
        stderr_fd = open(opt.stdout_path, O_WRONLY, create_mode);
        if (stderr_fd == FOX_INVALID_FD)
            return false;
    }

    FoxProcHandle pid = fork();
    if (pid < 0)
        return false;
    if (pid == 0) {
        // Redirect stdin/stdout/stderr
        if (stdin_fd != FOX_INVALID_FD)
            dup2(stdin_fd, STDIN_FILENO);
        if (stdout_fd != FOX_INVALID_FD)
            dup2(stdout_fd, STDOUT_FILENO);
        if (stderr_fd != FOX_INVALID_FD)
            dup2(stderr_fd, STDERR_FILENO);
        // Close unused fds
        close(stdin_fd);
        close(stdout_fd);
        close(stderr_fd);
        // Change working directory
        if (opt.working_dir.size != 0) {
            FoxStringBuf tmp = fox_sb(opt.working_dir);
            if (fox_fs_setcwd(tmp.items)) {
                fox_sb_free(&tmp);
                _exit(127);
            }
            fox_sb_free(&tmp);
        }
        // The arena to store garbage
        FoxStringBufs arena;
        // Create the final args array
        CStrs final_args = {0};
        fox_da_append(&final_args, path);
        fox_da_foreach(FoxStringView, it, &argv) {
            fox_da_append(&arena, fox_sb(*it));
            fox_da_append(&final_args, fox_da_back(&arena).items);
        }
        fox_da_reserve(&final_args, final_args.size + 1);
        final_args.items[final_args.size++] = NULL;
        // Create the final env array
        CStrs final_env = {0};
        if (opt.env && opt.env->size > 0) {
            fox_da_foreach(const FoxEnvEntry, entry, opt.env) {
                fox_da_append(&arena, fox_sb(entry->key));
                fox_da_append(&final_env, fox_da_back(&arena).items);
                fox_da_append(&arena, fox_sb(entry->value));
                fox_da_append(&final_env, fox_da_back(&arena).items);
            }
            fox_da_reserve(&final_env, final_env.size + 1);
            final_env.items[final_env.size++] = NULL;
        }
        // Now run the program
        int ret;
        if (final_env.size == 0)
            ret = execvp(path, (char *const *) final_args.items);
        else
            ret = execve(path, (char *const *) final_args.items, (char *const *) final_env.items);
        if (ret == -1) {
            fox_da_free(&final_env);
            fox_da_free(&final_args);
            fox_da_foreach(FoxStringBuf, it, &arena) { fox_sb_free(it); }
            fox_da_free(&arena);
        }
        _exit(127);
    }

    FoxProcHandle *handle = malloc(sizeof(FoxProcHandle));
    FoxFd *stdin_write = NULL;
    FoxFd *stdout_read = NULL;
    FoxFd *stderr_read = NULL;
    *handle = pid;

    process->handle = handle;
    process->stdin_write = stdin_write;
    process->stdout_read = stdout_read;
    process->stderr_read = stderr_read;
    process->running = true;
    process->exit_code = 0;
    return true;
#elif defined(FOX_OS_WINDOWS)
    bool result;

    // Prepare the command line
    FoxStringBuf cmd_line = {0};
    // Append the program name
    FoxStringView program = fox_sv(path);
    if (fox_str_find_first_of(program, " ") == program.size)
        fox_sb_appendf(&cmd_line, "\"" SV_Fmt "\" ", SV_Arg(&program));
    else
        fox_sb_appendf(&cmd_line, SV_Fmt " ", SV_Arg(&program));
    // Append the command line args
    fox_da_foreach(FoxStringView, arg, &argv) {
        if (fox_str_find_first_of(*arg, " ") == arg->size)
            fox_sb_appendf(&cmd_line, "\"" SV_Fmt "\" ", SV_Arg(arg));
        else
            fox_sb_appendf(&cmd_line, SV_Fmt " ", SV_Arg(arg));
    }
    if (cmd_line.size > 0)
        fox_sb_pop(&cmd_line);
    // Prepare current directory
    FoxStringBuf cur_dir = {0};
    if (opt.working_dir.size > 0)
        cur_dir = fox_sb(opt.working_dir);
    // Prepare env block
    // TODO: Should env be inherited or not??
    FoxStringBuf env = {0};
    if (opt.env && opt.env->size > 0) {
        fox_da_foreach(const FoxEnvEntry, entry, opt.env) {
            fox_da_concat(&env, &entry->key);
            fox_da_append_many(&env, "=", 1);
            fox_da_concat(&env, &entry->value);
            fox_da_append_many(&env, "", 1);
        }
        fox_da_append_many(&env, "", 1);
    }

    STARTUPINFO si = {0};
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi = {0};

    HANDLE child_stdin = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE child_stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE child_stderr = GetStdHandle(STD_ERROR_HANDLE);
    if (opt.stdin_path) {
        child_stdin = CreateFile(opt.stdin_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
        if (child_stdin == INVALID_HANDLE_VALUE)
            fox_return_defer(false);
    }
    if (opt.stdout_path) {
        child_stdout = CreateFile(opt.stdout_path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
        if (child_stdout == INVALID_HANDLE_VALUE)
            fox_return_defer(false);
    }
    if (opt.stderr_path) {
        child_stderr = CreateFile(opt.stderr_path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
        if (child_stderr == INVALID_HANDLE_VALUE)
            fox_return_defer(false);
    }

    si.dwFlags |= STARTF_USESTDHANDLES;
    si.hStdInput = child_stdin;
    si.hStdOutput = child_stdout;
    si.hStdError = child_stderr;

    // Create the process
    if (!CreateProcess(NULL, cmd_line.items, NULL, NULL, TRUE, 0, env.items, cur_dir.items, &si, &pi))
        fox_return_defer(false);

    process->handle = (void *) pi.hProcess;
    process->stdin_write = FOX_INVALID_FD;
    process->stdout_read = FOX_INVALID_FD;
    process->stderr_read = FOX_INVALID_FD;
    process->running = true;
    process->exit_code = 0;

    CloseHandle(pi.hThread);
    fox_return_defer(true);

defer:
    fox_sb_free(&env);
    fox_sb_free(&cur_dir);
    fox_sb_free(&cmd_line);
    return result;
#else
#    error "Implement this"
#endif
}

#ifdef FOX_OS_WINDOWS
static bool fox__create_nonblocking_pipe__(HANDLE *srv_end, DWORD srv_mode, HANDLE *cli_end) {
    bool result;
    // Create unique name
    static atomic_size_t id = 0;
    FoxStringBuf name = {0};
    fox_sb_appendf(&name, "\\\\.\\pipe\\fox__pipe_%zu__", id);
    atomic_fetch_add(&id, 1);
    // Create server end pipe
    *srv_end =
            CreateNamedPipe(name.items, srv_mode | FILE_FLAG_OVERLAPPED, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_NOWAIT, 1, 4096, 4096, 0, NULL);
    if (*srv_end == INVALID_HANDLE_VALUE)
        fox_return_defer(false);
    // Create client pipe
    *cli_end = CreateFile(name.items, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
    if (*srv_end == INVALID_HANDLE_VALUE)
        fox_return_defer(false);

    fox_return_defer(true);

defer:
    fox_sb_free(&name);
    return result;
}
#endif // FOX_OS_WINDOWS

bool fox_cmd_spawn_piped_opt(FoxProc *process, const char *path, const FoxStringViews argv, const FoxSpawnOpt opt) {
    if (!path || *path == '\0')
        return false;

#if defined(FOX_OS_LINUX)
    typedef struct {
        const char **items;
        size_t size;
        size_t capacity;
    } CStrs;

    bool result;

    FoxFd in_pipe[2] = {FOX_INVALID_FD, FOX_INVALID_FD};
    FoxFd out_pipe[2] = {FOX_INVALID_FD, FOX_INVALID_FD};
    FoxFd err_pipe[2] = {FOX_INVALID_FD, FOX_INVALID_FD};
    if (pipe(in_pipe) < 0)
        fox_return_defer(false);
    if (pipe(out_pipe) < 0)
        fox_return_defer(false);
    if (pipe(err_pipe) < 0)
        fox_return_defer(false);

    FoxProcHandle pid = fork();
    if (pid < 0)
        fox_return_defer(false);
    if (pid == 0) {
        // Redirect stdin/stdout/stderr
        dup2(in_pipe[0], STDIN_FILENO);
        dup2(out_pipe[0], STDOUT_FILENO);
        dup2(err_pipe[0], STDERR_FILENO);
        // Close unused fds
        close(in_pipe[0]);
        close(in_pipe[1]);
        close(out_pipe[0]);
        close(out_pipe[1]);
        close(err_pipe[0]);
        close(err_pipe[1]);
        // Change working directory
        if (opt.working_dir.size != 0) {
            FoxStringBuf tmp = fox_sb(opt.working_dir);
            if (fox_fs_setcwd(tmp.items)) {
                fox_sb_free(&tmp);
                _exit(127);
            }
            fox_sb_free(&tmp);
        }
        // The arena to store garbage
        FoxStringBufs arena;
        // Create the final argv array
        CStrs final_argv = {0};
        fox_da_append(&final_argv, path);
        fox_da_foreach(FoxStringView, it, &argv) {
            fox_da_append(&arena, fox_sb(*it));
            fox_da_append(&final_argv, fox_da_back(&arena).items);
        }
        final_argv.items[final_argv.size++] = NULL;
        // Create the final env array
        CStrs final_env = {0};
        if (opt.env->size > 0) {
            fox_da_foreach(const FoxEnvEntry, entry, opt.env) {
                fox_da_append(&arena, fox_sb(entry->key));
                fox_da_append(&final_env, fox_da_back(&arena).items);
                fox_da_append(&arena, fox_sb(entry->value));
                fox_da_append(&final_env, fox_da_back(&arena).items);
            }
            fox_da_reserve(&final_env, final_env.size + 1);
            final_env.items[final_env.size++] = NULL;
        }
        // Now run the program
        int ret;
        if (final_env.size == 0)
            ret = execvp(path, (char *const *) final_argv.items);
        else
            ret = execve(path, (char *const *) final_argv.items, (char *const *) final_env.items);
        if (ret == -1) {
            fox_da_free(&final_env);
            fox_da_free(&final_argv);
            fox_da_foreach(FoxStringBuf, it, &arena) { fox_sb_free(it); }
            fox_da_free(&arena);
            fox_return_defer(false);
        }
        _exit(127);
    }

    FoxProcHandle *handle = malloc(sizeof(FoxProcHandle));
    FoxFd *stdin_write = malloc(sizeof(FoxFd));
    FoxFd *stdout_read = malloc(sizeof(FoxFd));
    FoxFd *stderr_read = malloc(sizeof(FoxFd));
    *handle = pid;
    *stdin_write = in_pipe[1];
    *stdout_read = out_pipe[0];
    *stderr_read = err_pipe[0];

    process->handle = handle;
    process->stdin_write = stdin_write;
    process->stdout_read = stdout_read;
    process->stderr_read = stderr_read;
    process->running = true;
    process->exit_code = 0;

    close(in_pipe[0]);
    close(out_pipe[1]);
    close(err_pipe[1]);

    if (*(FoxFd *) process->stdin_write != FOX_INVALID_FD)
        if (!fox__cmd_set_nonblocking_pipe__posix(*(FoxFd *) process->stdin_write))
            fox_return_defer(false);
    if (*(FoxFd *) process->stdout_read != FOX_INVALID_FD)
        if (!fox__cmd_set_nonblocking_pipe__posix(*(FoxFd *) process->stdout_read))
            fox_return_defer(false);
    if (*(FoxFd *) process->stderr_read != FOX_INVALID_FD)
        if (!fox__cmd_set_nonblocking_pipe__posix(*(FoxFd *) process->stderr_read))
            fox_return_defer(false);
    fox_return_defer(true);

defer:
    if (!result) {
        if (in_pipe[0] != FOX_INVALID_FD)
            close(in_pipe[0]);
        if (in_pipe[1] != FOX_INVALID_FD)
            close(in_pipe[1]);
        if (out_pipe[0] != FOX_INVALID_FD)
            close(out_pipe[0]);
        if (out_pipe[1] != FOX_INVALID_FD)
            close(out_pipe[1]);
        if (err_pipe[0] != FOX_INVALID_FD)
            close(err_pipe[0]);
        if (err_pipe[1] != FOX_INVALID_FD)
            close(err_pipe[1]);
    }
    return result;
#elif defined(FOX_OS_WINDOWS)
    bool result;

    // Prepare the command line
    FoxStringBuf cmd_line = {0};
    // Append the program name
    FoxStringView program = fox_sv(path);
    if (fox_str_find_first_of(program, " ") == program.size)
        fox_sb_appendf(&cmd_line, "\"" SV_Fmt "\" ", SV_Arg(&program));
    else
        fox_sb_appendf(&cmd_line, SV_Fmt " ", SV_Arg(&program));
    // Append the command line args
    fox_da_foreach(FoxStringView, arg, &argv) {
        if (fox_str_find_first_of(*arg, " ") == arg->size)
            fox_sb_appendf(&cmd_line, "\"" SV_Fmt "\" ", SV_Arg(arg));
        else
            fox_sb_appendf(&cmd_line, SV_Fmt " ", SV_Arg(arg));
    }
    if (cmd_line.size > 0)
        fox_sb_pop(&cmd_line);
    // Prepare current directory
    FoxStringBuf cur_dir = {0};
    if (opt.working_dir.size > 0)
        cur_dir = fox_sb(opt.working_dir);
    // Prepare env block
    // TODO: Should env be inherited or not??
    FoxStringBuf env = {0};
    if (opt.env) {
        fox_da_foreach(const FoxEnvEntry, entry, opt.env) {
            fox_da_concat(&env, &entry->key);
            fox_da_append_many(&env, "=", 1);
            fox_da_concat(&env, &entry->value);
            fox_da_append_many(&env, "", 1);
        }
        fox_da_append_many(&env, "", 1);
    }

    STARTUPINFO si = {0};
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi = {0};

    HANDLE in_srv = INVALID_HANDLE_VALUE, in_cli = INVALID_HANDLE_VALUE;
    HANDLE out_srv = INVALID_HANDLE_VALUE, out_cli = INVALID_HANDLE_VALUE;
    HANDLE err_srv = INVALID_HANDLE_VALUE, err_cli = INVALID_HANDLE_VALUE;
    if (!fox__create_nonblocking_pipe__(&in_srv, PIPE_ACCESS_INBOUND, &in_cli))
        fox_return_defer(false);
    if (!fox__create_nonblocking_pipe__(&out_srv, PIPE_ACCESS_OUTBOUND, &out_cli))
        fox_return_defer(false);
    if (!fox__create_nonblocking_pipe__(&err_srv, PIPE_ACCESS_OUTBOUND, &err_cli))
        fox_return_defer(false);

    si.dwFlags |= STARTF_USESTDHANDLES;
    si.hStdInput = in_cli;
    si.hStdOutput = out_cli;
    si.hStdError = err_cli;

    // Create the process
    if (!CreateProcess(NULL,           // Application path (not convenient)
                       cmd_line.items, // Command line args
                       NULL,           // Process attributes
                       NULL,           // Thread attributes
                       TRUE,           // Inherit handles
                       0,              // Creation flags
                       env.items,      // Environment vars
                       cur_dir.items,  // Current directory
                       &si,            // Startup info
                       &pi))           // Process info
        fox_return_defer(false);

    process->handle = (void *) pi.hProcess;
    process->stdin_write = in_srv;
    process->stdout_read = out_srv;
    process->stderr_read = err_srv;
    process->running = true;
    process->exit_code = 0;

    CloseHandle(pi.hThread);
    fox_return_defer(true);

defer:
    if (in_cli != INVALID_HANDLE_VALUE)
        CloseHandle(in_cli);
    if (out_cli != INVALID_HANDLE_VALUE)
        CloseHandle(out_cli);
    if (err_cli != INVALID_HANDLE_VALUE)
        CloseHandle(err_cli);
    fox_sb_free(&env);
    fox_sb_free(&cur_dir);
    fox_sb_free(&cmd_line);
    return result;
#else
#    error "Implement this"
#endif
}

bool fox_cmd_wait(FoxProc *process) {
    if (!process)
        return false;

#if defined(FOX_OS_LINUX)
    bool result;

    FoxProcHandle pid = *(FoxProcHandle *) process->handle;
    for (;;) {
        int status = 0;
        if (waitpid(pid, &status, 0) < 0)
            fox_return_defer(false);
        if (WIFEXITED(status)) {
            process->running = false;
            process->exit_code = WEXITSTATUS(status);
#    ifndef FOX_NO_ECHO
            fox_log_info("[CMD] Process exited with exit code %d", WEXITSTATUS(status));
#    endif // FOX_NO_ECHO
            fox_return_defer(true);
        }
        if (WIFSIGNALED(status)) {
            process->running = false;
            process->exit_code = 128 + WTERMSIG(status);
#    ifndef FOX_NO_ECHO
            fox_log_info("[CMD] Process exited with signal %d", WTERMSIG(status));
#    endif // FOX_NO_ECHO
            fox_return_defer(true);
        }
    }

defer:
    // Close pipes (child is finished)
    if (process->stdin_write) {
        close(*(FoxFd *) process->stdin_write);
        free(process->stdin_write);
        process->stdin_write = NULL;
    }
    if (process->stdout_read) {
        close(*(FoxFd *) process->stdout_read);
        free(process->stdout_read);
        process->stdout_read = NULL;
    }
    if (process->stderr_read) {
        close(*(FoxFd *) process->stderr_read);
        free(process->stderr_read);
        process->stderr_read = NULL;
    }
    free(process->handle);
    process->handle = NULL;
    return result;
#elif defined(FOX_OS_WINDOWS)
    FoxProcHandle h = process->handle;
    DWORD ret = WaitForSingleObject(h, INFINITE);
    if (ret == WAIT_FAILED)
        return false;
    // Get the error code
    DWORD code;
    if (!GetExitCodeProcess(h, &code))
        return false;
    // Set state
    process->running = false;
    process->exit_code = code;
#    ifndef FOX_NO_ECHO
    fox_log_info("[CMD] Process exited with exit code %d", process->exit_code);
#    endif // FOX_NO_ECHO

    // Cleanup
    if (process->stdin_write != FOX_INVALID_FD) {
        CloseHandle((HANDLE) process->stdin_write);
        process->stdin_write = NULL;
    }
    if (process->stdout_read != FOX_INVALID_FD) {
        CloseHandle((HANDLE) process->stdout_read);
        process->stdout_read = NULL;
    }
    if (process->stderr_read != FOX_INVALID_FD) {
        CloseHandle((HANDLE) process->stderr_read);
        process->stderr_read = NULL;
    }
    CloseHandle(process->handle);
    process->handle = NULL;
    return true;
#else
#    error "Implement this"
#endif
}

void fox_cmd_detach(FoxProc *process) {
    if (!process)
        return;

#if defined(FOX_OS_LINUX)
    // Close pipes (child is finished)
    if (process->stdin_write) {
        close(*(FoxFd *) process->stdin_write);
        free(process->stdin_write);
    }
    if (process->stdout_read) {
        close(*(FoxFd *) process->stdout_read);
        free(process->stdout_read);
    }
    if (process->stderr_read) {
        close(*(FoxFd *) process->stderr_read);
        free(process->stderr_read);
    }
    free(process->handle);
    *process = (FoxProc) {0};
#elif defined(FOX_OS_WINDOWS)
    // Cleanup
    if (process->stdin_write != FOX_INVALID_FD)
        CloseHandle((HANDLE) process->stdin_write);
    if (process->stdout_read != FOX_INVALID_FD)
        CloseHandle((HANDLE) process->stdout_read);
    if (process->stderr_read != FOX_INVALID_FD)
        CloseHandle((HANDLE) process->stderr_read);
    CloseHandle(process->handle);
    *process = (FoxProc) {0};
#else
#    error "Implement this"
#endif
}

bool fox_cmd_kill(FoxProc *process, int value) {
    if (!process)
        return false;

#if defined(FOX_OS_LINUX)
    return kill(*(FoxProcHandle *) process->handle, value) == 0;
#elif defined(FOX_OS_WINDOWS)
    FoxProcHandle h = process->handle;
    return TerminateProcess(h, (UINT) value);
#else
#    error "Implement this"
#endif
}

bool fox_cmd_write_stdin(FoxProc *process, FoxStringView data, size_t *written) {
    if (!process)
        return false;
    if (data.size == 0)
        return true;

#if defined(FOX_OS_LINUX)
    if (process->stdin_write == NULL)
        return false;

    ssize_t n = write(*(FoxFd *) process->stdin_write, data.items, data.size);
    if (n < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            n = 0;
        else
            return false;
    }
    if (written)
        *written = (size_t) n;
    return true;
#elif defined(FOX_OS_WINDOWS)
    if (process->stdin_write == FOX_INVALID_FD)
        return false;

    bool result;

    OVERLAPPED ov = {0};
    ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (ov.hEvent == INVALID_HANDLE_VALUE)
        return false;

    if (!WriteFile(process->stdin_write, data.items, data.size, NULL, &ov)) {
        DWORD err = GetLastError();
        if (err == ERROR_IO_PENDING) {
            // Operation is in progress equivalent to EWOULDBLOCK
            if (written)
                *written = 0;
            fox_return_defer(true);
        }
        fox_return_defer(false);
    }

    if (written) {
        DWORD bytes = 0;
        if (!GetOverlappedResult(process->stdin_write, &ov, &bytes, FALSE))
            // INFO: Aha!!
            *written = data.size;
        else
            *written = bytes;
    }
    fox_return_defer(true);

defer:
    CloseHandle(ov.hEvent);
    return result;
#else
#    error "Implement this"
#endif
}

static bool fox__cmd_read_fd__(FoxFd fd, void *buf, size_t size, size_t *bytes_read) {
#if defined(FOX_OS_LINUX)
    ssize_t n = read(fd, buf, size);
    if (n < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            n = 0;
        else
            return false;
    }
    if (bytes_read)
        *bytes_read = (size_t) n;
    return true;
#elif defined(FOX_OS_WINDOWS)
    if (fd == FOX_INVALID_FD)
        return false;

    bool result;

    OVERLAPPED ov = {0};
    ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (ov.hEvent == INVALID_HANDLE_VALUE)
        return false;

    if (!ReadFile(fd, buf, size, NULL, &ov)) {
        DWORD err = GetLastError();
        if (err == ERROR_IO_PENDING) {
            // Operation is in progress equivalent to EWOULDBLOCK
            if (bytes_read)
                *bytes_read = 0;
            fox_return_defer(true);
        }
        fox_return_defer(false);
    }

    if (bytes_read) {
        DWORD bytes = 0;
        if (!GetOverlappedResult(fd, &ov, &bytes, FALSE))
            // INFO: Aha!!
            *bytes_read = size;
        else
            *bytes_read = bytes;
    }
    fox_return_defer(true);

defer:
    CloseHandle(ov.hEvent);
    return result;
#else
#    error "Implement this"
#endif
}

bool fox_cmd_read_stdout(FoxProc *process, void *buf, size_t size, size_t *bytes_read) {
    if (!buf || !process)
        return false;

#if defined(FOX_OS_LINUX)
    if (!process->stdout_read)
        return false;
    return fox__cmd_read_fd__(*(FoxFd *) process->stdout_read, buf, size, bytes_read);
#elif defined(FOX_OS_WINDOWS)
    return fox__cmd_read_fd__(process->stdout_read, buf, size, bytes_read);
#else
#    error "Implement this"
#endif
}

bool fox_cmd_read_stderr(FoxProc *process, void *buf, size_t size, size_t *bytes_read) {
    if (!buf || !process)
        return false;

#if defined(FOX_OS_LINUX)
    if (!process->stderr_read)
        return false;
    return fox__cmd_read_fd__(*(FoxFd *) process->stderr_read, buf, size, bytes_read);
#elif defined(FOX_OS_WINDOWS)
    return fox__cmd_read_fd__(process->stderr_read, buf, size, bytes_read);
#else
#    error "Implement this"
#endif
}

bool fox_cmd_poll(const FoxProc *process, FoxPollResult *result, int timeout_ms) {
    if (!process || !result) {
        return false;
    }
    result->stdout_ready = false;
    result->stderr_ready = false;
    result->stdout_avail = -1;
    result->stderr_avail = -1;

#if defined(FOX_OS_LINUX)
    FoxFd stdout_read = *(FoxFd *) process->stdout_read;
    FoxFd stderr_read = *(FoxFd *) process->stderr_read;
    // Set up for poll() call
    struct pollfd fds[2];
    nfds_t nfds = 0;
    if (stdout_read != FOX_INVALID_FD) {
        fds[nfds].fd = stdout_read;
        fds[nfds].events = POLLIN;
        nfds++;
    }
    if (stderr_read != FOX_INVALID_FD) {
        fds[nfds].fd = stderr_read;
        fds[nfds].events = POLLIN;
        nfds++;
    }
    // Call poll() if input is available
    int ret = poll(fds, nfds, timeout_ms);
    if (ret < 0)
        return false;
    // Set poll result
    nfds = 0;
    if (stdout_read != FOX_INVALID_FD) {
        if (fds[nfds].revents & POLLIN) {
            result->stdout_ready = true;
            int avail;
            if (ioctl(stdout_read, FIONREAD, &avail) == 0)
                result->stdout_avail = avail;
        }
        nfds++;
    }
    if (stderr_read != FOX_INVALID_FD) {
        if (fds[nfds].revents & POLLIN) {
            result->stderr_ready = true;
            int avail;
            if (ioctl(stderr_read, FIONREAD, &avail) == 0)
                result->stderr_avail = avail;
        }
        nfds++;
    }
    return true;
#elif defined(FOX_OS_WINDOWS)
    struct timespec tmp;
    thrd_sleep(&(struct timespec) {.tv_sec = timeout_ms / 1000, .tv_nsec = (timeout_ms % 1000) * 1000 * 1000}, &tmp);

    // Check stdout
    DWORD bytes = 0;
    if (process->stdout_read != FOX_INVALID_FD) {
        if (PeekNamedPipe(process->stdout_read, NULL, 0, NULL, &bytes, NULL)) {
            if (bytes > 0) {
                result->stdout_ready = true;
                result->stdout_avail = bytes;
            }
        } else
            return false;
    }
    // Check stderr
    bytes = 0;
    if (process->stderr_read != FOX_INVALID_FD) {
        if (PeekNamedPipe(process->stderr_read, NULL, 0, NULL, &bytes, NULL)) {
            if (bytes > 0) {
                result->stderr_ready = true;
                result->stderr_avail = bytes;
            }
        } else
            return false;
    }
    return true;
#else
#    error "Implement this"
#endif
}

bool fox_cmd_is_running(FoxProc *process) {
    if (!process)
        return false;

#if defined(FOX_OS_LINUX)
    int status;
    pid_t ret = waitpid(*(FoxProcHandle *) process->handle, &status, WNOHANG);
    if (ret < 0)
        return false; // TODO: report error
    if (ret == 0) {
        // Child has not exited yet
        process->running = true;
        return true;
    }
    // Child exited but we do not reap the status
    process->running = false;
    if (WIFEXITED(status))
        process->exit_code = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        process->exit_code = 128 + WTERMSIG(status);
    else
        FOX_UNREACHABLE("fox_cmd_is_running");
    return false;
#elif defined(FOX_OS_WINDOWS)
    DWORD exit_code;
    if (!GetExitCodeProcess((HANDLE) process->handle, &exit_code))
        return false;
    return exit_code == STILL_ACTIVE;
#else
#    error "Implement this"
#endif
}

void fox__cmd_append__(FoxCmd *cmd, size_t n, ...) {
    va_list va;
    va_start(va, n);
    for (size_t i = 0; i < n; i++) {
        const char *arg = va_arg(va, const char *);
        fox_da_append(cmd, arg);
    }
    va_end(va);
}

void fox_cmd_extend(FoxCmd *cmd, FoxCmd *other) { fox_da_concat(cmd, other); }

static void fox__log_cmd__(const FoxCmd *cmd) {
    FoxStringBuf buf = fox_sb("");
    fox_da_foreach(const char *, str, cmd) { fox_sb_appendf(&buf, "%s ", *str); }
    if (buf.size > 0)
        fox_sb_pop(&buf);
    fox_log_info("[CMD] %s", buf.items);
    fox_sb_free(&buf);
}

bool fox_cmd_run_opt(FoxCmd *cmd, FoxCmdOpt opt) {
    if (!cmd)
        return false;
    if (cmd->size == 0)
        return true; // Execute nothing

    bool result;

    const char *path = fox_da_front(cmd);
    FoxStringViews args = {0};
    for (size_t i = 1; i < cmd->size; i++)
        fox_da_append(&args, fox_sv(cmd->items[i]));
    FoxEnv env = {0};
    if (opt.env)
        for (size_t i = 0; i < opt.env_size; i++) {
            if (i + 1 >= opt.env_size)
                break;
            FoxEnvEntry entry = {.key = fox_sv(opt.env[i]), .value = fox_sv(opt.env[i + 1])};
            fox_da_append(&env, entry);
        }

    FoxProc process = {0};
#ifndef FOX_NO_ECHO
    fox__log_cmd__(cmd);
#endif // FOX_NO_ECHO
    if (!fox_cmd_spawn_opt(&process, path, args,
                           (FoxSpawnOpt) {.stdin_path = opt.stdin_path,
                                          .stdout_path = opt.stdout_path,
                                          .stderr_path = opt.stderr_path,
                                          .env = &env,
                                          .working_dir = fox_sv(opt.working_dir)}))
        fox_return_defer(false);
    if (!fox_cmd_wait(&process))
        fox_return_defer(false);

    if (opt.exit_code)
        *opt.exit_code = process.exit_code;
    fox_return_defer(true);

defer:
    fox_da_free(&env);
    fox_da_free(&args);
    fox_da_free(&env);
    if (opt.reset)
        fox_da_clear(cmd);
    return result;
}

bool fox__auto_build__(const char *src_file, int argc, char *argv[]) {
    FOX_ASSERT(argc >= 1, "argc should be atleast 1");

    bool result;

    FoxFileStatus src_status = {0};
    FoxFileStatus exe_status = {0};
    if (!fox_fs_file_status(src_file, &src_status))
        fox_return_defer(false);
    if (!fox_fs_file_status(argv[0], &exe_status))
        fox_return_defer(false);

    FoxCmd cmd = {0};
    if (src_status.last_modified >= exe_status.last_modified) {
        // Rebuild
        // FIXME: Not portable
        fox_cmd_append(&cmd, "cc", "-std=c17", "-ggdb", "-fsanitize=address", "-o", "fox", src_file);
        if (!fox_cmd_run(&cmd))
            fox_return_defer(false);
        fox_cmd_append(&cmd, "./fox");
        int exit_code = 0;
        if (!fox_cmd_run(&cmd, .exit_code = &exit_code))
            fox_return_defer(false);
        exit(exit_code);
    }
    fox_return_defer(false);

defer:
    fox_cmd_free(&cmd);
    return result;
}

u32 fox_nprocessors(void) {
#if defined(FOX_OS_LINUX)
    return get_nprocs();
#elif defined(FOX_OS_WINDOWS)
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    return info.dwNumberOfProcessors;
#else
#    error "Implement this"
#endif
}

#endif // FOX_IMPLEMENTATION
