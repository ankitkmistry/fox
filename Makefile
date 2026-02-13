# fox: fox.c fox.h
# 	cl /std:c17 /W1 /Zi /fsanitize=address /experimental:c11atomics /Fe:fox fox.c
fox: fox.c fox.h
	gcc -std=c17 -Wall -Wextra -ggdb -O0 -fsanitize=address -fsanitize=undefined -o fox fox.c
