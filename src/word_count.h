#ifndef WORD_COUNT_H
#define WORD_COUNT_H

#include <stdio.h>

#define BUF_LEN 1024

void print_help();
long byte_count(FILE *file);
long line_count(FILE *file);
long max_line_len(FILE *file);
long *char_frequency(FILE *file);
long word_count(FILE *file);
int printable(int c);

#endif
