#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  size_t len;
  size_t cur;
  char *start;
} string;

static inline string string_error(void) {
  string result = {0, 0, NULL};
  return result;
}

string create_string(const char *str, size_t len) {
  if (!str)
    return string_error();
  string result;
  result.len = len;
  result.cur = 0;
  result.start = (char *)malloc(sizeof(char) * (len + 1));
  if (!result.start)
    return string_error();
  memcpy(result.start, str, len);
  result.start[len] = '\0';
  return result;
}

string string_from_cstring(const char *lit) {
  string result;
  result.cur = 0;
  size_t n = 0;
  while (lit[n] != '\0')
    n++;
  result.len = n;
  result.start = (char *)malloc(sizeof(char) * (n + 1));
  if (!result.start)
    return string_error();
  memcpy(result.start, lit, n + 1);
  return result;
}

void skip_whitspc(string *str) {
  size_t n = str->cur;
  while ((n < str->len) && (str->start[n] == ' ' || str->start[n] == '\t'))
    n++;
  str->cur = n;
}

string split(string *input) {
  string result;
  size_t n = input->cur;
  while ((n < input->len) &&
         (input->start[n] != ' ' && input->start[n] != '\t'))
    n++;
  result = create_string(input->start + input->cur, n - input->cur);
  input->cur = n;
  return result;
}

int compare_strings(string O, string I) {
  if (O.len - O.cur != I.len - I.cur)
    return 0;
  for (int i = 0; i < I.len - I.cur; i++) {
    if (O.start[i + O.cur] != I.start[i + I.cur])
      return 0;
  }
  return 1;
}

int string_to_int(string str) {
  bool negative = 0;
  int result = 0;
  if (str.start[str.cur] == '-') {
    negative = 1;
    str.cur++;
  }

  for (int i = 0; i < str.len - str.cur; i++) {
    if (str.start[str.cur + i] >= '0' && str.start[str.cur + i] <= '9') {
      result = (result * 10) + (str.start[str.cur + i] - '0');
    } else {
      // printf("u fucked up lol. L bozo\n");
      printf("incorrect integer format\n");
      return NAN;
    }
  }
  if (negative)
    result *= -1;
  return result;
}

double string_to_double(string str) {
  bool negative = 0;
  bool integer = 1;
  int num_int = 0;
  int num_dec = 0;
  int point_index = 0;

  if (str.start[str.cur] == '-') {
    str.cur++;
    negative = 1;
  }

  for (int i = 0; i < str.len - str.cur; i++) {
    if (str.start[str.cur + i] >= '0' && str.start[str.cur + i] <= '9') {
      num_int++;
    } else if (str.start[str.cur + i] == '.') {
      integer = 0;
      point_index = i;
      break;
    } else {
      printf("incorrect double format\n");
      return NAN;
    }
  }

  if (integer) {
    if (negative)
      str.cur--;
    return string_to_int(str);
  }

  if ((str.len - str.cur) - point_index < 2) {
    printf("invalid dot placement in: %s\n", (str.start + str.cur));
    return NAN;
  }

  for (int i = 0; i < str.len - str.cur - (point_index + 1); i++) {
    if (str.start[str.cur + point_index + 1 + i] >= '0' &&
        str.start[str.cur + point_index + 1 + i] <= '9') {
      num_dec++;
    } else {
      printf("incorrect double format\n");
      return NAN;
    }
  }

  if (num_dec + num_int > 15) {
    printf("to many digits (up to 15 digits allowed)\n");
    return NAN;
  }

  int int_part = 0;
  double dec_part = 0;

  for (int i = 0; i < point_index; i++) {
    int_part = (int_part * 10) + (str.start[str.cur + i] - '0');
  }
  for (int i = 0; i < str.len - (str.cur + point_index + 1); i++) {
    dec_part = (dec_part / 10) + (str.start[str.len - 1 - i] - '0');
  }

  dec_part = (dec_part / 10) + int_part;
  if (negative) {
    dec_part *= -1;
  }
  return dec_part;
}
