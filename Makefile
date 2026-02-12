fox: fox.c fox.h
	gcc -std=c17 -Wall -Wextra -ggdb -O0 -fsanitize=address -fsanitize=undefined -D_DEFAULT_SOURCE -D_POSIX_C_SOURCE=200809L -o fox fox.c
