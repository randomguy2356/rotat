#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"rotmath.h"
#include"strings.h"

char buff[1025];

int main(void){
  if(!fgets(buff, 1024, stdin)){
    printf("fgets failed. (dunno why)");
    return -1;
  }
  size_t n = 0;
  while((n < 1024) && (buff[n] != '\n' && buff[n] != '\0')) n++;
  buff[n] = '\0';

  string input = string_from_cstring(buff);
  if(!input.start){
    printf("input failed to load (null pointer passed)");
    return -1;
  }

  skip_whitspc(&input);
  string command = split(&input);
  if(!command.start){
    printf("failed to parse first token (null pointer passed)");
    return -1;
  }
  skip_whitspc(&input);
  string arg1 = split(&input);
  if(!arg1.start){
    printf("failed to parse second token (null pointer passed)");
    return -1;
  }
  skip_whitspc(&input);
  string arg2 = split(&input);
  if(!arg2.start){
    printf("failed to parse third token (null pointer passed)");
    return -1;
  }

  printf("%s\n%s\n%s\n", command.start, arg1.start, arg2.start);
  free(input.start);
  free(command.start);
  free(arg1.start);
  free(arg2.start);
}

