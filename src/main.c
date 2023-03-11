#include "word_count.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_LEN 1024

#define HELP 1
#define BYTES 2
#define LINES 4
#define MAX_LINE 8
#define WORDS 16
#define FREQUENCY 32

void print_help();
long byte_count(FILE *file);
long line_count(FILE *file);
long max_line_len(FILE *file);
long *char_frequency(FILE *file);
long word_count(FILE *file);

int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf("Usage: %s --help\n", argv[0]);
    return 1;
  } else if (strcmp(argv[1], "--help") == 0) {
    print_help(argv[0]);
    return 0;
  }

  uint8_t flags = 0;
  /*
    0000 0000
    bit 1: help
    bit 2: bytes
    bit 3:
    bit 4:
    bit 5: help
    bit 6:
    bit 7:
    bit 8:
  */

  for (int ix = 1; ix < argc-1; ix++) {
    if (strcmp(argv[1], "--help") == 0) {
      flags |= HELP;
    } else if (strcmp(argv[ix], "-c") == 0 || strcmp(argv[ix], "--bytes") == 0) {
      flags |= BYTES;
    } else if (strcmp(argv[ix], "-l") == 0 || strcmp(argv[ix], "--lines") == 0) {
      flags |= LINES;
    } else if (strcmp(argv[ix], "-L") == 0 || strcmp(argv[ix], "--max-line-length") == 0) {
      flags |= MAX_LINE;
    } else if (strcmp(argv[ix], "-w") == 0 || strcmp(argv[ix], "--words") == 0) {
      flags |= WORDS;
    } else if (strcmp(argv[ix], "-f") == 0 || strcmp(argv[ix], "--frequency") == 0) {
      flags |= FREQUENCY;
    } else {
      fprintf(stderr,
              "Unrecognized flag %s\n"
              "For help, use the \"--help\" flag.",
              argv[ix]);
      return 1;
    }
  }

  FILE *file = fopen(argv[argc - 1], "r");

  if (file == NULL) {
    fprintf(stderr, "Failed to open file %s\n", argv[argc-1]);
    return 1;
  }

  if (flags & LINES) {
    printf("%ld ", line_count(file));
  }
  if (flags & WORDS) {
    printf("%ld ", word_count(file));
  }
  if (flags & BYTES) {
    printf("%ld ", byte_count(file));
  }
  if (flags & MAX_LINE) {
    printf("%ld ", max_line_len(file));
  }
  if (flags & FREQUENCY) {
    long *freqs = char_frequency(file);
    for (int i = 0; i < 128; i++) {
      if (printable(i) && freqs[i]) {
        printf("%c %ld\n", i, freqs[i]);
      }
    }
    free(freqs);
  }
  printf("%s\n", argv[argc-1]);
  fclose(file);
  return 0;
  }
