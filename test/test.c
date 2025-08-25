#include "keys.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

struct termios bckup;

int main(void) {
  int key = get_key();
  printf("got key %d\n", key);
}
