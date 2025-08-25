#pragma onc

typedef enum {
  KEY_ESC = 27,

  KEY_F1 = 0x101,
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

/*
 * waits for user keypress and returns as keycode
 */
int get_key();
