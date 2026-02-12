#ifndef FOX_H_
#define FOX_H_

#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>

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
/// Logging system
///   Internal functions
///   - fox__init_def_log__
///
///   Definitions
///   - FoxLogLevel
///   - FoxLogHandlerFn
///   - FoxSinkWriteFn
///   - FoxSinkCloseFn
///   - FoxSink
///   - FoxSinks
///   - FoxLogger
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

#if defined(_WIN32)
#    define FOX_OS_WINDOWS /// Windows
#endif
#if defined(_WIN64)
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

#if defined(FOX_OS_LINUX) || defined(FOX_OS_UNIX) || defined(FOX_OS_MAC)
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

#define fox_sb(expr) _Generic((expr), char *: fox_sb_from_cstr, const char *: fox_sb_from_cstr, FoxStringView: fox_sb_from_sv)(expr)

FoxStringView fox_sv_from_raw(const char *str, size_t count);
FoxStringView fox_sv_from_cstr(const char *str);
FoxStringView fox_sv_from_sb(const FoxStringBuf sb);

#define fox_sv(expr) _Generic((expr), char *: fox_sv_from_cstr, const char *: fox_sv_from_cstr, FoxStringBuf: fox_sv_from_sb)(expr)

// Modification
void fox_sb_append_null(FoxStringBuf *sb);
void fox_sb_appendf(FoxStringBuf *sb, const char *fmt, ...) FOX_PRINTF_FORMAT(2, 3);
void fox_sb_vappendf(FoxStringBuf *sb, const char *fmt, va_list args);

void fox_sb_concat_sb(FoxStringBuf *sb, const FoxStringBuf *other);
void fox_sb_concat_sv(FoxStringBuf *sb, const FoxStringView other);
void fox_sb_concat_cstr(FoxStringBuf *sb, const char *str);
#define fox_sb_concat(sb, other)                                                                                                                     \
    _Generic(other,                                                                                                                                  \
            FoxStringBuf *: fox_sb_concat_sb,                                                                                                        \
            const FoxStringBuf *: fox_sb_concat_sb,                                                                                                  \
            FoxStringView: fox_sb_concat_sv,                                                                                                         \
            char *: fox_sb_concat_cstr,                                                                                                              \
            const char *: fox_sb_concat_cstr)(sb, other)
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
typedef void (*FoxSinkWriteFn)(struct FoxLogSink *sink, const FoxStringView sv);
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
void fox_default_log_write(FoxSink *sink, const FoxStringView sv);

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
bool fox_fs_write_entire_file(const char *path, const FoxStringView *sv);
bool fox_fs_read_symlink(const char *path, FoxStringBuf *sb);

typedef enum {
    FILE_UNKNOWN,
    FILE_REGULAR,
    FILE_DIR,
    FILE_SYMLINK,
    FILE_BLOCK,
    FILE_CHARACTER,
    FILE_PIPE,
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

bool fox_fs_copy(const char *from, const char *to, FoxCopyOptions options);
bool fox_fs_copy_file(const char *from, const char *to, FoxCopyOptions options);
bool fox_fs_copy_symlink(const char *from, const char *to);

/// Process utils

#if defined(FOX_OS_LINUX) || defined(FOX_OS_UNIX) || defined(FOX_OS_MAC)
typedef pid_t FoxProcHandle;
typedef int FoxFd;
#    define FOX_INVALID_FD (FoxFd)(-1)
#else
#    error "Implement this"
#endif

typedef struct {
    FoxProcHandle handle;

    FoxFd stdin_fd;
    FoxFd stdout_fd;
    FoxFd stderr_fd;

    bool running;
    int exit_code;
} FoxProc;

typedef struct {
    FoxProc *items;
    size_t size;
    size_t capacity;
} FoxProcs;

typedef struct {
    const char *stdin_path;
    const char *stdout_path;
    const char *stderr_path;
    FoxStringView working_dir;
    FoxStringViews env;
} FoxSpawnOpt;

bool fox_cmd_spawn_opt(FoxProc *process, const char *path, const FoxStringViews argv, const FoxSpawnOpt opt);
#define fox_cmd_spawn(process, path, argv, ...)                                                                                                      \
    fox_cmd_spawn_opt(                                                                                                                               \
            (process), (path), (argv),                                                                                                               \
            (const FoxSpawnOpt) {                                                                                                                    \
                    .stdin_path = NULL, .stdout_path = NULL, .stderr_path = NULL, .working_dir = NULL, .working_dir = {0}, .env = {0}, __VA_ARGS__})
bool fox_cmd_spawn_piped_opt(FoxProc *process, const char *path, const FoxStringViews argv, const FoxSpawnOpt opt);
#define fox_cmd_spawn_piped(process, path, argv, ...)                                                                                                \
    fox_cmd_spawn_piped_opt(                                                                                                                         \
            (process), (path), (argv),                                                                                                               \
            (const FoxSpawnOpt) {                                                                                                                    \
                    .stdin_path = NULL, .stdout_path = NULL, .stderr_path = NULL, .working_dir = NULL, .working_dir = {0}, .env = {0}, __VA_ARGS__})
bool fox_cmd_wait(FoxProc *process);
bool fox_cmd_kill(FoxProc *process, int sig);

bool fox_cmd_write_stdin(FoxProc *process, const FoxStringView data, size_t *written);
bool fox_cmd_read_stdout(FoxProc *process, void *buf, size_t size, size_t *bytes_read);
bool fox_cmd_read_stderr(FoxProc *process, void *buf, size_t size, size_t *bytes_read);

typedef struct {
    bool stdout_ready;
    bool stderr_ready;
    bool exited;
} FoxPollResult;

bool fox_cmd_poll(FoxProc *process, FoxPollResult *result, int timeout_ms);
bool fox_cmd_is_running(FoxProc *process);

typedef struct {
    const char **items;
    size_t size;
    size_t capacity;
} FoxCmd;

void fox__cmd_append__(FoxCmd *cmd, size_t n, ...);
#define fox_cmd_append(cmd, ...) fox__cmd_append__(cmd, sizeof((const char *[]) {__VA_ARGS__}) / sizeof(const char *), ##__VA_ARGS__)
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
} FoxCmdOpt;

bool fox_cmd_run_opt(FoxCmd *cmd, FoxCmdOpt opt);
#define fox_cmd_run(cmd, ...)                                                                                                                        \
    fox_cmd_run_opt((cmd), (FoxCmdOpt) {.reset = true,                                                                                               \
                                        .working_dir = NULL,                                                                                         \
                                        .env = NULL,                                                                                                 \
                                        .env_size = 0,                                                                                               \
                                        .stdin_path = NULL,                                                                                          \
                                        .stdout_path = NULL,                                                                                         \
                                        .stderr_path = NULL,                                                                                         \
                                        __VA_ARGS__})

int fox_nprocessors(void);

#endif // FOX_H_

#define FOX_IMPLEMENTATION
#ifdef FOX_IMPLEMENTATION

#ifdef FOX_OS_LINUX
#    include <fcntl.h>
#    include <poll.h>
#    include <sys/stat.h>
#    include <sys/statvfs.h>
#    include <sys/sysinfo.h>
#    include <sys/time.h>
#    include <sys/wait.h>
#    include <unistd.h>
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

void fox_sb_concat_sb(FoxStringBuf *sb, const FoxStringBuf *other) { fox_da_concat(sb, other); }

void fox_sb_concat_sv(FoxStringBuf *sb, const FoxStringView other) { fox_da_concat(sb, &other); }

void fox_sb_concat_cstr(FoxStringBuf *sb, const char *str) { fox_da_append_many(sb, str, strlen(str)); }

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

FoxStringView fox_sv_from_sb(const FoxStringBuf sb) {
    return (FoxStringView) {
            .items = sb.items,
            .size = sb.size,
    };
}

const char *fox_get_error_message(void) {
#ifdef FOX_OS_LINUX
    return strerror(errno);
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

void fox_default_log_write(FoxSink *sink, const FoxStringView sv) {
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

defer:
    // TODO: log errors
    if (f)
        fclose(f);
    return result;
}

bool fox_fs_write_entire_file(const char *path, const FoxStringView *sv) {
    bool result;
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

#if defined(FOX_OS_LINUX)
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
    fox_sb_copy(sb, fox_sv(buf));

defer:
    free(buf);
    return result;
#else
#    error "Implement this"
#endif
}

#if defined(FOX_OS_LINUX)
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
        return FILE_PIPE;
    else if ((mode & 0170000) == 0140000)
        return FILE_SOCKET;
    else
        return FILE_UNKNOWN;
}
#endif

bool fox_fs_file_status(const char *path, FoxFileStatus *status) {
    if (!status || !path || strlen(path) == 0)
        return false;

#if defined(FOX_OS_LINUX)
    struct stat file_info;
    if (stat(path, &file_info) < 0)
        return false;

    // Get the file type
    status->type = fox__fs_file_type__posix(file_info.st_mode);
    status->size = file_info.st_size;
    status->perms = (FoxFilePerms) (file_info.st_mode & PERM_ALL);
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

#if defined(FOX_OS_LINUX)
    struct stat file_info;
    if (lstat(path, &file_info) < 0)
        return false;

    // Get the file type
    status->type = fox__fs_file_type__posix(file_info.st_mode);
    status->size = file_info.st_size;
    status->perms = (FoxFilePerms) (file_info.st_mode & PERM_ALL);
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

#if defined(FOX_OS_LINUX)
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

#if defined(FOX_OS_LINUX)
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

#if defined(FOX_OS_LINUX)
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

#if defined(FOX_OS_LINUX)
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
    case FILE_PIPE:
    case FILE_SOCKET:
    case FILE_UNKNOWN:
        break;
    }
    return false;
}

bool fox_fs_is_pipe(const char *path) { return fox_fs_file_type(path) == FILE_PIPE; }

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
    case FILE_PIPE:
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
#if defined(FOX_OS_LINUX)
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

#if defined(FOX_OS_LINUX)
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

#if defined(FOX_OS_LINUX)
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

#if defined(FOX_OS_LINUX)
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

#if defined(FOX_OS_LINUX)
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

#if defined(FOX_OS_LINUX)
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

#if defined(FOX_OS_LINUX)
    if (!fox_fs_exists(path))
        if (mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO) == 0)
            return true;
    return false;
#else
#    error "Implement this"
#endif
}

bool fox_fs_create_dir_all(const char *p) {
    const FoxStringView path = fox_sv(p);
    if (path.size == 0)
        return false;
    if (fox_fs_exists(p))
        return false;

    FoxStringView path_rem = {0};
    FoxStringBuf split = {0};

    for (size_t i = 0; i < path.size; i++) {
        path_rem = fox_str_slice(&path, i, path.size);
        i = i + fox_str_find_first_of(&path_rem, fox_sv(FOX_FILE_SEPARATOR));

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

#if defined(FOX_OS_LINUX)
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

static bool fox__fs_copy_file__(const char *from, const char *to) {
    bool result;

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

bool fox_fs_copy(const char *from, const char *to, FoxCopyOptions options) {
    if (!from || !to || strlen(from) == 0 || strlen(to) == 0)
        return false;

    // TODO: implement this after completing directory visit
    FOX_UNUSED(from);
    FOX_UNUSED(to);
    FOX_UNUSED(options);
    FOX_TODO("fox_fs_copy");
    return false;
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
bool fox__cmd_set_nonblocking_pipe__posix(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0)
        return false;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK) >= 0;
}
#endif

bool fox_cmd_spawn_opt(FoxProc *process, const char *path, const FoxStringViews argv, const FoxSpawnOpt opt) {
    typedef struct {
        const char **items;
        size_t size;
        size_t capacity;
    } CStrs;

    if (!path || strlen(path) == 0)
        return false;

#if defined(FOX_OS_LINUX)
    mode_t create_mode = PERM_OWNER_READ | PERM_OWNER_WRITE | PERM_GROUP_READ | PERM_OTHERS_READ;

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
            FoxStringBuf tmp = fox_sb_from_sv(opt.working_dir);
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
            fox_da_append(&arena, fox_sb_from_sv(*it));
            fox_da_append(&final_args, fox_da_back(&arena).items);
        }
        fox_da_reserve(&final_args, final_args.size + 1);
        final_args.items[final_args.size++] = NULL;
        // Create the final env array
        CStrs final_env = {0};
        if (opt.env.size > 0) {
            fox_da_foreach(FoxStringView, it, &opt.env) {
                fox_da_append(&arena, fox_sb_from_sv(*it));
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
            return false;
        }
        _exit(127);
    }

    process->handle = pid;
    process->stdin_fd = FOX_INVALID_FD;
    process->stdout_fd = FOX_INVALID_FD;
    process->stderr_fd = FOX_INVALID_FD;
    process->running = true;
    process->exit_code = 0;
    return true;
#else
#    error "Implement this"
#endif
}

bool fox_cmd_spawn_piped_opt(FoxProc *process, const char *path, const FoxStringViews argv, const FoxSpawnOpt opt) {
    typedef struct {
        const char **items;
        size_t size;
        size_t capacity;
    } CStrs;

    if (!path || strlen(path) == 0)
        return false;

#if defined(FOX_OS_LINUX)
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
            FoxStringBuf tmp = fox_sb_from_sv(opt.working_dir);
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
            fox_da_append(&arena, fox_sb_from_sv(*it));
            fox_da_append(&final_argv, fox_da_back(&arena).items);
        }
        final_argv.items[final_argv.size++] = NULL;
        // Create the final env array
        CStrs final_env = {0};
        fox_da_foreach(FoxStringView, it, &opt.env) {
            fox_da_append(&arena, fox_sb_from_sv(*it));
            fox_da_append(&final_env, fox_da_back(&arena).items);
        }
        final_env.items[final_env.size++] = NULL;
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

    process->handle = pid;
    process->stdin_fd = in_pipe[1];
    process->stdout_fd = out_pipe[0];
    process->stderr_fd = err_pipe[0];
    process->running = true;
    process->exit_code = 0;

    close(in_pipe[0]);
    close(out_pipe[1]);
    close(err_pipe[1]);

    if (process->stdin_fd != FOX_INVALID_FD)
        if (!fox__cmd_set_nonblocking_pipe__posix(process->stdin_fd))
            fox_return_defer(false);
    if (process->stdout_fd != FOX_INVALID_FD)
        if (!fox__cmd_set_nonblocking_pipe__posix(process->stdout_fd))
            fox_return_defer(false);
    if (process->stderr_fd != FOX_INVALID_FD)
        if (!fox__cmd_set_nonblocking_pipe__posix(process->stderr_fd))
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
#else
#    error "Implement this"
#endif
}

bool fox_cmd_wait(FoxProc *process) {
    if (!process)
        return false;

#if defined(FOX_OS_LINUX)
    bool result;
    for (;;) {
        int status = 0;
        if (waitpid(process->handle, &status, 0) < 0)
            fox_return_defer(false);
        if (WIFEXITED(status)) {
            process->running = false;
            process->exit_code = WEXITSTATUS(status);
            fox_return_defer(true);
        }
        if (WIFSIGNALED(status)) {
            process->running = false;
            process->exit_code = 128 + WTERMSIG(status);
            fox_return_defer(true);
        }
    }

defer:
    // Close pipes (child is finished)
    if (process->stdin_fd >= 0) {
        close(process->stdin_fd);
        process->stdin_fd = FOX_INVALID_FD;
    }
    if (process->stdout_fd >= 0) {
        close(process->stdout_fd);
        process->stdout_fd = FOX_INVALID_FD;
    }
    if (process->stderr_fd >= 0) {
        close(process->stderr_fd);
        process->stderr_fd = FOX_INVALID_FD;
    }
    return result;
#else
#    error "Implement this"
#endif
}

bool fox_cmd_kill(FoxProc *process, int sig) {
    if (!process)
        return false;

#if defined(FOX_OS_LINUX)
    return kill(process->handle, sig) == 0;
#else
#    error "Implement this"
#endif
}

bool fox_cmd_write_stdin(FoxProc *process, const FoxStringView data, size_t *written) {
    if (!process || process->stdin_fd == FOX_INVALID_FD)
        return false;

#if defined(FOX_OS_LINUX)
    ssize_t n = write(process->stdin_fd, data.items, data.size);
    if (n < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            n = 0;
        else
            return false;
    }
    if (written)
        *written = (size_t) n;
    return true;
#else
#    error "Implement this"
#endif
}

bool fox_cmd_read_stdout(FoxProc *process, void *buf, size_t size, size_t *bytes_read) {
    if (!buf || !process || process->stdin_fd == FOX_INVALID_FD)
        return false;

#if defined(FOX_OS_LINUX)
    ssize_t n = read(process->stdout_fd, buf, size);
    if (n < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            n = 0;
        else
            return false;
    }
    if (bytes_read)
        *bytes_read = (size_t) n;
    return true;
#else
#    error "Implement this"
#endif
}

bool fox_cmd_read_stderr(FoxProc *process, void *buf, size_t size, size_t *bytes_read) {
    if (!buf || !process || process->stdin_fd == FOX_INVALID_FD)
        return false;

#if defined(FOX_OS_LINUX)
    ssize_t n = read(process->stderr_fd, buf, size);
    if (n < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            n = 0;
        else
            return false;
    }
    if (bytes_read)
        *bytes_read = (size_t) n;
    return true;
#else
#    error "Implement this"
#endif
}

bool fox_cmd_poll(FoxProc *process, FoxPollResult *result, int timeout_ms) {
    if (!process || !result) {
        return false;
    }

#if defined(FOX_OS_LINUX)
    result->stdout_ready = false;
    result->stderr_ready = false;
    // Set up for poll() call
    struct pollfd fds[2];
    nfds_t nfds = 0;
    if (process->stdout_fd != FOX_INVALID_FD) {
        fds[nfds].fd = process->stdout_fd;
        fds[nfds].events = POLLIN;
        nfds++;
    }
    if (process->stderr_fd != FOX_INVALID_FD) {
        fds[nfds].fd = process->stderr_fd;
        fds[nfds].events = POLLIN;
        nfds++;
    }
    // Call poll() if input is available
    int ret = poll(fds, nfds, timeout_ms);
    if (ret < 0)
        return false;
    // Set poll result
    nfds = 0;
    if (process->stdout_fd != FOX_INVALID_FD) {
        if (fds[nfds].revents & POLLIN)
            result->stdout_ready = true;
        nfds++;
    }
    if (process->stderr_fd != FOX_INVALID_FD) {
        if (fds[nfds].revents & POLLIN)
            result->stderr_ready = true;
        nfds++;
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
    pid_t ret = waitpid(process->handle, &status, WNOHANG);
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
        fox_pop(&buf);
    fox_log_info("[CMD] %s", buf.items);
    fox_sb_free(&buf);
}

bool fox_cmd_run_opt(FoxCmd *cmd, FoxCmdOpt opt) {
    if (!cmd)
        return false;

    bool result;

    const char *path = fox_da_front(cmd);
    FoxStringViews args = {0};
    for (size_t i = 1; i < cmd->size; i++)
        fox_da_append(&args, fox_sv(cmd->items[i]));
    FoxStringViews env = {0};
    if (opt.env)
        for (size_t i = 0; i < opt.env_size; i++)
            fox_da_append(&env, fox_sv(opt.env[i]));

    FoxProc process = {0};
#ifndef FOX_NO_ECHO
    fox__log_cmd__(cmd);
#endif
    bool ret = fox_cmd_spawn_opt(&process, path, args,
                                 (FoxSpawnOpt) {.stdin_path = opt.stdin_path,
                                                .stdout_path = opt.stdout_path,
                                                .stderr_path = opt.stderr_path,
                                                .env = env,
                                                .working_dir = fox_sv(opt.working_dir)});
    if (!ret)
        fox_return_defer(false);
    fox_return_defer(fox_cmd_wait(&process));

defer:
    fox_da_free(&args);
    fox_da_free(&env);
    if (opt.reset)
        fox_da_clear(cmd);
    return result;
}

int fox_nprocessors(void) {
#if defined(FOX_OS_LINUX)
    return get_nprocs();
#else
#    error "Implement this"
#endif
}

#endif // FOX_IMPLEMENTATION
