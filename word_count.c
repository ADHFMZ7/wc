#include "word_count.h"
#include <stdlib.h>
#include <stdio.h>

void print_help(const char *file_name) {
  printf("Usage: %s [OPTION] [FILE]\n"
         "Print newline, word, and byte counts for each FILE, and a total line "
         "if\n"
         "more than one FILE is specified.  A word is a non-zero-length "
         "sequence of\n"
         "printable characters delimited by white space.\n"
         "\n"
         "With no FILE, or when FILE is -, read standard input.\n"
         "\n"
         "The options below may be used to select which counts are printed, "
         "always in\n"
         "the following order: newline, word, character, byte, maximum line "
         "length.\n"
         "  -c, --bytes            print the byte counts\n"
         "  -l, --lines            print the newline counts\n"
         "  -L, --max-line-length  print the maximum display width\n"
         "  -w, --words            print the word counts\n"
         "      --help        display this help and exit\n"
         "\n",
         file_name);
}

long byte_count(FILE *file) {
  fseek(file, 0, SEEK_SET);
  char ch;
  long count = 0;
  while ((ch = fgetc(file)) != EOF) {
    count++;
  }
  return count;
}

long line_count(FILE *file) {
  fseek(file, 0, SEEK_SET);
  long lines = 0;
  char ch;
  do {
    ch = fgetc(file);
    if (ch == '\n')
      lines++;
  } while (ch != EOF);
  return lines;
}

int printable(int c) {
  if (c < 33 || c >= 127)
    return 0;
  return 1;
}

long wc_strlen(const char *string) {
  long count = 0;
  for (int i = 0; string[i] != '\0'; i++) {
    if (printable(string[i])) {
      count++;
    }
  }
  return count;
}

long max_line_len(FILE *file) {
  fseek(file, 0, SEEK_SET);
  long max_len = 0;
  long cur_len;
  char buffer[BUF_LEN];

  while (fgets(buffer, BUF_LEN, file)) {
    cur_len = wc_strlen(buffer);
    if (max_len < cur_len) {
      max_len = cur_len;
    }
  }
  return max_len;
}

long word_count(FILE *file) {
  fseek(file, 0, SEEK_SET);
  long count = 0;
  char prev = ' ';
  char cur;

  while ((cur = fgetc(file)) != EOF) {
    if ((prev == ' ' || prev == '\n') && (cur != ' ')) {
      count++;
    }
    prev = cur;
  }
  return count;
}

long *char_frequency(FILE *file) {
  fseek(file, 0, SEEK_SET);
  long *counts = (long *)calloc(128, sizeof(long));

  char c;
  while ((c = getc(file)) != EOF)
    counts[c]++;
  return counts;
}
