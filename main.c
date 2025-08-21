#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"rotmath.h"

char input[512];
char command[512];
char arg1[512];
char arg2[512];

int getlen(char* str, int maxlen){
  int n = 0;
  while((str[n] != '\n') && (n < maxlen)) n++;
  return n;
}

void strip_front(char* str, int maxlen){
  int n = 0;
  while((str[n] == ' ') || (str[n] == '\t') && (n < maxlen)) n++;

  for (int i = n; i < maxlen; i++){
    str[i-n] = str[i];
  }
}

void split(char* input, int maxlen, char* out1, char* out2){
  int n = 0;
  while((input[n] != ' ' && input[n] != '\t') && (n < maxlen)) n++;
  for (int i = 0; i < n; i++){
    out1[i] = input[i];
  }
  for (int i = n+1; i < maxlen; i++){
    out2[i-(n+1)] = input[i];
  }
}

int main(void){
  fgets(input, sizeof(input), stdin);
  int len = getlen(input, 512);
  input[len] = '\0';
  
  strip_front(input, 512);
  split(input, 512, command, input);
  strip_front(input, 512);
  split(input, 512, arg1, input);
  strip_front(input, 512);
  split(input, 512, arg2, input);
  printf("%s\n%s\n%s\n", command, arg1, arg2);
}
