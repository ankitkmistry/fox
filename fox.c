#include "fox.h"
#include <stddef.h>
#include <stdio.h>

typedef struct {
    u32 *items;
    size_t size;
    size_t capacity;
} Ages;

typedef struct {
    i8 *items;
    size_t size;
    size_t capacity;
} Numbers;

int main() {
    // Ages ages;
    //
    // for (;;) {
    //   u32 option;
    //   printf("Menu\n");
    //   printf("1. Push\n");
    //   printf("2. Pop\n");
    //   printf("3. Print\n");
    //   printf("4. Exit\n");
    //   printf("Enter option: ");
    //   scanf("%u", &option);
    //
    //   switch (option) {
    //   case 1:
    //     printf("Enter your age: ");
    //     u32 age;
    //     scanf("%u", &age);
    //     fox_arr_append(&ages, age);
    //     break;
    //   case 2: {
    //     u32 age = fox_pop(&ages);
    //     printf("Popped age: %u\n", age);
    //     break;
    //   }
    //   case 3:
    //     for (size_t i = 0; i < ages.size; i++)
    //       printf("%u\n", ages.items[i]);
    //     break;
    //   case 4:
    //     return 0;
    //   default:
    //     printf("Invalid option\n");
    //   }
    // }

    Numbers numbers = {0};
    fox_push(&numbers, 1);
    fox_push(&numbers, 3);
    fox_push(&numbers, 4);
    fox_push(&numbers, 9);
    fox_push(&numbers, 2);

    fox_da_insert(&numbers, 2, 45);
    fox_da_remove(&numbers, 3);

    printf("Numbers 1:\n");
    for (size_t i = 0; i < numbers.size; i++) {
        printf("%hhd\n", numbers.items[i]);
    }

    fox_log_trace("Log trace");
    fox_log_debug("Log debug");
    fox_log_info("Log info");
    fox_log_warning("Log warning");
    fox_log_error("Log error");
    fox_log_critical("Log critical");

    // Numbers numbers2 = {0};
    // fox_push(&numbers2, 1);
    // fox_push(&numbers2, 2);
    // fox_push(&numbers2, 4);
    // fox_push(&numbers2, 9);
    // fox_push(&numbers2, 3);
    // printf("Numbers 2:\n");
    // for (size_t i = 0; i < numbers1.size; i++) {
    //   printf("%lu\n", numbers2.items[i]);
    // }
    //
    // fox_arr_concat(&numbers1, &numbers2);
    // printf("Numbers 1:\n");
    // for (size_t i = 0; i < numbers1.size; i++) {
    //   printf("%lu\n", numbers1.items[i]);
    // }
    //
    // printf("Popping\n");
    // while (numbers2.size > 0) {
    //   printf("Popped value: %lu\n", fox_pop(&numbers2));
    // }
    fox_da_free(&numbers);
    // fox_arr_free(&numbers2);
}
