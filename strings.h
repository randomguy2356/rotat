#include<stdlib.h>
#include<string.h>

typedef struct{
  size_t len;
  size_t cur;
  char* start;
} string;

static inline string string_error(void) {
    string s = {0, 0, NULL};
    return s;
}

string create_string(const char* str, size_t len){
  if(!str) return string_error();
  string result;
  result.len = len;
  result.cur = 0;
  result.start = (char*)malloc(sizeof(char)*(len + 1));
  if(!result.start) return string_error();
  memcpy(result.start, str, len);
  result.start[len] = '\0';
  return result;
}

string string_from_cstring(const char* lit){
  string result;
  result.cur = 0;
  size_t n = 0;
  while(lit[n] != '\0') n++;
  result.len = n;
  result.start = (char*)malloc(sizeof(char) * (n + 1));
  if(!result.start) return string_error();
  memcpy(result.start, lit, n+1);
  return result;
}

void skip_whitspc(string* str){
  size_t n = str->cur;
  while((n < str->len) && (str->start[n] == ' ' || str->start[n] == '\t')) n++;
  str->cur = n;
}

string split(string* input){
  string result;
  size_t n = input->cur;
  while((n < input->len) && (input->start[n] != ' ' && input->start[n] != '\t')) n++;
  result = create_string(input->start + input->cur, n - input->cur);
  input->cur = n;
  return result;
}
