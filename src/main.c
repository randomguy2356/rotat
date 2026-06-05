#include "rotmath.h"
#include "strings.h"
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32)
#include <io.h>

#elif defined(__unix__) || defined(__APPLE__)
#include <unistd.h>
#endif

int quit = 0;

double truncate_double(double num, int prec) {
  double n = pow(10, prec);
  return trunc(num * n) / n;
}

void exec_rotate(string arg1, string arg2, mat2x2 cur_mat, vec2 cur_vec) {
  rotate_vec(cur_mat, cur_vec, cur_vec);
}

void exec_vector(string arg1, string arg2, mat2x2 cur_mat, vec2 cur_vec) {
  double x = string_to_double(arg1);
  double y = string_to_double(arg2);
  if (isnan(x) || isnan(y)) {
    printf("no vector created.\n");
    return;
  }
  cur_vec[0] = x;
  cur_vec[1] = y;
}

void exec_polvector(string arg1, string arg2, mat2x2 cur_mat, vec2 cur_vec) {
  double r = string_to_double(arg1);
  double phi = string_to_double(arg2);
  if (isnan(r) || isnan(phi)) {
    printf("no vector created.\n");
    return;
  }
  phi = (phi * M_PI) / 180;
  cur_vec[0] = r;
  cur_vec[1] = 0;
  mat2x2 temp = new_mat2x2();
  matrix(phi, temp);
  rotate_vec(temp, cur_vec, cur_vec);
}

void exec_matrix(string arg1, string arg2, mat2x2 cur_mat, vec2 cur_vec) {
  double degrees = string_to_double(arg1);
  if (isnan(degrees)) {
    printf("no matrix created.\n");
    return;
  }
  double rad = (degrees * M_PI) / 180;
  matrix(rad, cur_mat);
}

void exec_compose(string arg1, string arg2, mat2x2 cur_mat, vec2 cur_vec) {
  double phi = (string_to_double(arg1) * M_PI) / 180;
  compose(cur_mat, phi, cur_mat);
}

void exec_inverse(string arg1, string arg2, mat2x2 cur_mat, vec2 cur_vec) {
  inverse_matrix(cur_mat);
}

void exec_pvector(string arg1, string arg2, mat2x2 cur_mat, vec2 cur_vec) {
  double length = sqrt(pow(cur_vec[0], 2) + pow(cur_vec[1], 2));
  double angle = (asin(cur_vec[1] / length) / M_PI) * 180;

  if (cur_vec[0] < 0) {
    angle = 180 - angle;
  }
  if (cur_vec[0] > 0 && cur_vec[1] <= 0) {
    angle = 360 - angle;
  }

  printf("current vector:\n"
         "X = %f\n"
         "Y = %f\n"
         "len = %f\n"
         "angle = %f\n",
         cur_vec[0], cur_vec[1], length, angle);
}

void exec_pmatrix(string arg1, string arg2, mat2x2 cur_mat, vec2 cur_vec) {

  double matOO = fabs(cur_mat[0][0]);
  double matOI = fabs(cur_mat[0][1]);
  double matIO = fabs(cur_mat[1][0]);
  double matII = fabs(cur_mat[1][1]);

  int rotmat = 1;

  double deg = acos(fabs(cur_mat[0][0]));

  deg = (deg * 180) / M_PI;

  if (cur_mat[0][0] < 0 && cur_mat[0][1] < 0) {
    deg = 180 - deg;
  }
  if (cur_mat[0][0] < 0 && cur_mat[0][1] > 0) {
    deg = 180 + deg;
  }
  if (cur_mat[0][0] > 0 && cur_mat[0][1] > 0) {
    deg = 360 - deg;
  }

  matOO = truncate_double(acos(matOO), 10);
  matOI = truncate_double(asin(matOI), 10);
  matIO = truncate_double(asin(matIO), 10);
  matII = truncate_double(acos(matII), 10);

  if (matOO != matOI || matOI != matIO || matIO != matII) {
    rotmat = 0;
  }
  printf("current matrix:\n"
         "00: %f, 01: %f\n"
         "10: %f, 11: %f\n",
         cur_mat[0][0], cur_mat[0][1], cur_mat[1][0], cur_mat[1][1]);
  if (rotmat) {
    printf("it's a rotation matrix of %.3f degrees\n", deg);
  } else {
    printf("it's not a rotation matrix.\n");
  }
}

void exec_help(string arg1, string arg2, mat2x2 cur_mat, vec2 cur_vec) {
  printf(
      "welcome to the help menu.\n"
      "=======commands==========\n"
      "1. rotate\n"
      "rotates the current vector by the current matrix\n"
      "2. vector x y\n"
      "sets the current vector to {x, y}\n"
      "3. polvector r phi\n"
      "sets the current vector in polar coordinates to {r, phi (in degrees)}\n"
      "4. matrix phi\n"
      "sets the current matrix to the rotation matrix of the angle phi (in "
      "degrees)\n"
      "5. compose phi\n"
      "multiplies the current matrix by the rotation matrix of the andle "
      "phi (in degrees)\n"
      "6. inverse\n"
      "inverts the current matrix\n"
      "7. pvector\n"
      "prints the current vector\n"
      "8. pmatrix\n"
      "prints the current matrix\n"
      "9. help\n"
      "opens this menu\n"
      "10. exit\n"
      "exits the program\n");
}

void exec_exit(string arg1, string arg2, mat2x2 cur_mat, vec2 cur_vec) {
  quit = 1;
}

int run_line(string input, string *commands,
             void (*exec[])(string, string, mat2x2, vec2),
             mat2x2 current_matrix, vec2 current_vector) {
  string command;
  string arg1;
  string arg2;

  if (!input.start) {
    printf("input failed to load (null pointer passed)");
    return 1;
  }

  skip_whitspc(&input);
  command = split(&input);
  if (!command.start) {
    printf("failed to parse first token (null pointer passed)");
    return 1;
  }
  skip_whitspc(&input);
  arg1 = split(&input);
  if (!arg1.start) {
    printf("failed to parse second token (null pointer passed)");
    return 1;
  }
  skip_whitspc(&input);
  arg2 = split(&input);
  if (!arg2.start) {
    printf("failed to parse third token (null pointer passed)");
    return 1;
  }

  int id = -1;
  for (int i = 0; i < 10; i++) {
    if (compare_strings(commands[i], command)) {
      id = i;
      break;
    }
  }

  if (id == -1) {
    printf("wrong command:");
    fwrite(input.start, 1, input.len, stdout);
    printf("\n");
    return 1;
  }

  exec[id](arg1, arg2, current_matrix, current_vector);

  free(input.start);
  free(command.start);
  free(arg1.start);
  free(arg2.start);

  return 0;
}

int is_terminal(FILE *f) {
  if (f == NULL) {
    return 0;
  }

#if defined(_WIN32)
  return _isatty(fileno(f));
#elif defined(__unix__) || defined(__APPLE__)
  return isatty(fileno(f));
#else
  return 0;
#endif
}

int f_run_program(FILE *script) {
  char buff[1025] = {0};
  int status = 0;
  int terminal = is_terminal(script);
  vec2 current_vector = vector(1, 0);
  mat2x2 current_matrix = new_mat2x2();

  string commands[10] = {
      string_from_cstring("rotate"),    string_from_cstring("vector"),
      string_from_cstring("polvector"), string_from_cstring("matrix"),
      string_from_cstring("compose"),   string_from_cstring("inverse"),
      string_from_cstring("pvector"),   string_from_cstring("pmatrix"),
      string_from_cstring("help"),      string_from_cstring("exit"),
  };

  void (*exec[10])(string, string, mat2x2, vec2) = {
      exec_rotate,  exec_vector,  exec_polvector, exec_matrix, exec_compose,
      exec_inverse, exec_pvector, exec_pmatrix,   exec_help,   exec_exit};

  string input;
  while (!quit) {
    if (terminal) {
      printf("> ");
      fflush(stdout);
    }
    if (!fgets(buff, sizeof(buff), script)) {
      if (feof(script)) {
        printf("\n");
        status = 1;
        break;
      }
      if (ferror(script)) {
        printf("file read error: %s\n", strerror(errno));
        status = 1;
        break;
      }
      printf("fgets failed: %s\n", strerror(errno));
      continue;
    }
    size_t n = 0;
    while ((n < 1024) && (buff[n] != '\n' && buff[n] != '\0'))
      n++;
    buff[n] = '\0';

    string input = string_from_cstring(buff);
    run_line(input, commands, exec, current_matrix, current_vector);
  }

  for (int i = 0; i < 10; i++) {
    free(commands[i].start);
  }

  delete_vec2(current_vector);
  delete_2x2mat(current_matrix);

  return status;
}

int main(int argc, char *argv[]) {
  if (argc > 1) {
    FILE *script;
    if (!(script = fopen(argv[1], "ro"))) {
      printf("couldn't open file \"%s\": %s\n", argv[1], strerror(errno));
      return 1;
    }
    return f_run_program(script);
  }
  f_run_program(stdin);
}
