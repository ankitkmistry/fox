#include "fox.h"
#include <stdio.h>

typedef struct {
    i8 *items;
    size_t size;
    size_t capacity;
} Numbers;

// int main(int argc, char *argv[]) {
//     fox_auto_build(argc, argv);

static void visit_dir(FoxDirEntry entry) {
    if (fox_str_starts_with(entry.name, ".")) {
        *entry.action = FOX_VISIT_SKIP;
        return;
    }
    if (fox_streq(entry.name, "build") || fox_streq(entry.name, "target")) {
        *entry.action = FOX_VISIT_SKIP;
        return;
    }

    FoxStringBuf buf = fox_sb_from_char(' ', entry.level * 2);
    if (fox_fs_is_dir(entry.path))
        printf("%10.3s  %s%s\n", "DIR", buf.items, entry.path);
    else
        printf("%10lu  %s%s\n", fox_fs_file_size(entry.path), buf.items, entry.path);
    fox_sb_free(&buf);
}

int main(void) {
    Numbers numbers = {0};
    fox_da_append(&numbers, 1);
    fox_da_append(&numbers, 3);
    fox_da_append(&numbers, 4);
    fox_da_append(&numbers, 9);
    fox_da_append(&numbers, 2);

    fox_da_insert(&numbers, 2, 45);
    fox_da_remove(&numbers, 3);

    printf("Numbers 1:\n");
    for (size_t i = 0; i < numbers.size; i++) {
        printf("%hhd\n", numbers.items[i]);
    }

    FoxStringBufs files = {0};
    fox_fs_read_entire_dir(".", &files);
    fox_da_foreach(FoxStringBuf, file_path, &files) { fox_log_info("File: %s", file_path->items); }
    fox_str_bufs_free(&files);

    fox_fs_visit_dir("..", visit_dir, .recursive = true);

    // fox_log_trace("Log trace");
    // fox_log_debug("Log debug");
    // fox_log_info("Log info");
    // fox_log_warning("Log warning");
    // fox_log_error("Log error");
    // fox_log_critical("Log critical");

    // FoxStringBuf tmp = fox_sb("abracadabra hoola hoo");
    // fox_log_info("tmp: %s", tmp.items);
    // fox_sb_remove_first_str(&tmp, "hoo");
    // fox_log_info("After first removal of hoo");
    // fox_log_info("tmp: %s", tmp.items);
    // fox_sb_free(&tmp);

    FoxCmd cmd = {0};

#ifdef FOX_OS_LINUX
    fox_cmd_append(&cmd, "ls", "--color", "-hal");
    fox_cmd_run(&cmd);
    if (!fox_cmd_run(&cmd)) {
        FoxStringBuf err = {0};
        fox_get_error_message(&err);
        fox_log_error("Process creation failed: %s", err.items);
        fox_sb_free(&err);
    }
#else
    fox_cmd_append(&cmd, "notepad");
    if (!fox_cmd_run(&cmd)) {
        FoxStringBuf err = {0};
        fox_get_error_message(&err);
        fox_log_error("Process creation failed: %s", err.items);
        fox_sb_free(&err);
    }
#endif

    fox_cmd_append(&cmd, "clang", "--version");
    if (!fox_cmd_run(&cmd)) {
        FoxStringBuf err = {0};
        fox_get_error_message(&err);
        fox_log_error("Process creation failed: %s", err.items);
        fox_sb_free(&err);
    }

    fox_cmd_free(&cmd);
    fox_da_free(&numbers);
}
