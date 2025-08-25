#pragma once

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

typedef enum {
  KEY_ESC = 27,

  KEY_NULL = 0x100,
  KEY_F1,
  KEY_F2,
  KEY_F3,
  KEY_F4,
  KEY_F5,
  KEY_F6,
  KEY_F7,
  KEY_F8,
  KEY_F9,
  KEY_F10,
  KEY_F11,
  KEY_F12,

  KEY_UP,
  KEY_DOWN,
  KEY_LEFT,
  KEY_RIGHT,

  KEY_HOME,
  KEY_END,
  KEY_PGUP,
  KEY_PGDN,
  KEY_INSERT,
  KEY_DELETE,

  KEY_BACKSPACE,
  KEY_ENTER,
  KEY_TAB,
} keycode;

struct termios bckup;

void disable_raw_mode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &bckup); }

void enable_raw_mode() {
  tcgetattr(STDIN_FILENO, &bckup);
  atexit(disable_raw_mode);

  struct termios raw = bckup;
  raw.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
/*
 * waits for user keypress and returns as keycode
 */
int get_key() {
  enable_raw_mode();
  char c = 0;
  if (!(read(STDIN_FILENO, &c, 1) == 1)) {
    disable_raw_mode();
    return KEY_NULL;
  }
  if (c == 27) {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    struct termios tmp = bckup;
    tmp.c_lflag &= ~(ICANON | ECHO);
    tmp.c_cc[VMIN] = 0;
    tmp.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tmp);
    char esc_code[4];
    if (!(read(STDIN_FILENO, &esc_code[0], 1) == 1)) {
      disable_raw_mode();
      return KEY_ESC;
    }
    if (!(esc_code[0] == '[') && !(esc_code[0] == 'O')) {
      disable_raw_mode();
      return KEY_NULL;
    }
    if (esc_code[0] == 'O') {
      if (!(read(STDIN_FILENO, &esc_code[1], 1) == 1)) {
        disable_raw_mode();
        return KEY_NULL;
      }
      switch (esc_code[1]) {
      case 'P':
        disable_raw_mode();
        return KEY_F1;
      case 'Q':
        disable_raw_mode();
        return KEY_F2;
      case 'R':
        disable_raw_mode();
        return KEY_F3;
      case 'S':
        disable_raw_mode();
        return KEY_F4;
      default:
        disable_raw_mode();
        return KEY_NULL;
      }
    }
    if (esc_code[0] == '[') {
      if (!(read(STDIN_FILENO, &esc_code[1], 1) == 1)) {
        disable_raw_mode();
        return KEY_NULL;
      }
      switch (esc_code[1]) {
      case '1':
        if (!(read(STDIN_FILENO, &esc_code[2], 2) == 2)) {
          disable_raw_mode();
          return KEY_NULL;
        }
        switch (esc_code[2]) {
        case '5':
          disable_raw_mode();
          return KEY_F5;
        case '7':
          disable_raw_mode();
          return KEY_F6;
        case '8':
          disable_raw_mode();
          return KEY_F7;
        case '9':
          disable_raw_mode();
          return KEY_F8;
        default:
          disable_raw_mode();
          return KEY_NULL;
        }
        break;
      case '2':
        if (!(read(STDIN_FILENO, &esc_code[2], 1) == 1)) {
          disable_raw_mode();
          return KEY_NULL;
        }
        switch (esc_code[2]) {
        case '~':
          disable_raw_mode();
          return KEY_INSERT;
        case '0':
          if (!(read(STDIN_FILENO, &esc_code[3], 1) == 1)) {
            disable_raw_mode();
            return KEY_NULL;
          }
          disable_raw_mode();
          return KEY_F9;
        case '1':
          if (!(read(STDIN_FILENO, &esc_code[3], 1) == 1)) {
            disable_raw_mode();
            return KEY_NULL;
          }
          disable_raw_mode();
          return KEY_F10;
        case '3':
          if (!(read(STDIN_FILENO, &esc_code[3], 1) == 1)) {
            return KEY_NULL;
          }
          disable_raw_mode();
          return KEY_F11;
        case '4':
          if (!(read(STDIN_FILENO, &esc_code[3], 1) == 1)) {
            return KEY_NULL;
            disable_raw_mode();
          }
          disable_raw_mode();
          return KEY_F12;
        default:
          disable_raw_mode();
          return KEY_NULL;
        }
      case '3':
        if (!(read(STDIN_FILENO, &esc_code[2], 1) == 1)) {
          return KEY_NULL;
          disable_raw_mode();
        }
        disable_raw_mode();
        return KEY_DELETE;
      case '5':
        if (!(read(STDIN_FILENO, &esc_code[3], 1) == 1)) {
          disable_raw_mode();
          return KEY_NULL;
        }
        disable_raw_mode();
        return KEY_PGUP;
      case '6':
        if (!(read(STDIN_FILENO, &esc_code[3], 1) == 1)) {
          disable_raw_mode();
          return KEY_NULL;
        }
        disable_raw_mode();
        return KEY_PGDN;
      case 'A':
        disable_raw_mode();
        return KEY_UP;
      case 'B':
        disable_raw_mode();
        return KEY_DOWN;
      case 'C':
        disable_raw_mode();
        return KEY_RIGHT;
      case 'D':
        disable_raw_mode();
        return KEY_LEFT;
      case 'F':
        disable_raw_mode();
        return KEY_END;
      case 'H':
        disable_raw_mode();
        return KEY_HOME;
      default:
        disable_raw_mode();
        return KEY_NULL;
      }
    }
    disable_raw_mode();
    return KEY_NULL;
  }
  return c;
}
