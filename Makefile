fox: fox.c fox.h
	gcc -std=c17 -Wall -Wextra -ggdb -O0 -fsanitize=address -fsanitize=undefined -o fox fox.c
