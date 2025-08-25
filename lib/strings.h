#pragma once

#include <stddef.h>

typedef struct {
  size_t len;
  size_t cur;
  char *start;
} string;

static inline string string_error(void) {
  string result = {0, 0, NULL};
  return result;
}

/*
 * creates a string out of a string, expecting there to be either a:
 * -'\n'
 * -'\0'
 * or nothing at the end
 */
string create_string(const char *, size_t);

/*
 * creates a string out of a C string
 */
string string_from_cstring(const char *);

/*
 * moves the cursor to the first non-whitespace character
 */
void skip_whitspc(string *);

/*
 * creates a string containing all characters between the cursor and
 * the nearest whitespace, and moves the cursor in the passed string
 * past the word
 */
string split(string *);

/*
 * rompares two strings, returns one if same, zero if not
 */
int compare_strings(string, string);

/*
 * converts a string into an integer
 */
int string_to_int(string);

/*
 * converts a string into a doubleprecision float
 */
double string_to_double(string);
