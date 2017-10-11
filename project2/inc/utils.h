#ifndef PROJECT2_INC_UTILS_H_
#define PROJECT2_INC_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>

#define ARB_NUMBER 1
#define ARB_FILE ".arb_file"
#define ARB_CHAR_A 'a'
#define PWD getenv("PWD")

void generate_arb_file();

char *remove_last_from_path(char* str);

#endif  // PROJECT2_INC_UTILS_H_
