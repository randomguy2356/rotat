#include<stdlib.h>
#include<math.h>

typedef double** mat2x2;
typedef double*  vec2;

mat2x2 new_mat2x2(){
  double* O = (double*)malloc(sizeof(double) * 2);
  double* I = (double*)malloc(sizeof(double) * 2);
  mat2x2 result = (mat2x2)malloc(sizeof(double*) * 2);
  result[0] = O;
  result[1] = I;
  return result;
}

vec2 vector(double x, double y){
  vec2 result = (vec2)malloc(sizeof(double) * 2);
  result[0] = x;
  result[1] = y;
  return result;
}

void delete_2x2mat(mat2x2 mat){
  free(mat[0]);
  free(mat[1]);
  free(mat);
}

void delete_vec2(vec2 vec){
  free(vec);
}

void matrix(double phi, mat2x2* target){
  (*target)[0][0] = cos(phi);
  (*target)[0][1] = sin(phi) * -1;
  (*target)[1][0] = sin(phi);
  (*target)[1][1] = cos(phi);
}

void compose(mat2x2 first, double phi, mat2x2* result){
  mat2x2 temp = new_mat2x2();
  matrix(phi, &temp);

  double OO = (first[0][0] * temp[0][0]) + (first[0][1] * temp[1][0]);
  double OI = (first[0][0] * temp[0][1]) + (first[0][1] * temp[1][1]);
  double IO = (first[1][0] * temp[0][0]) + (first[1][1] * temp[1][0]);
  double II = (first[1][0] * temp[0][1]) + (first[1][1] * temp[1][1]);
  (*result)[0][0] = OO; (*result)[1][0] = IO; (*result)[0][1] = OI; (*result)[1][1] = II;

  delete_2x2mat(temp);
}

void rotate_vec(mat2x2 first, vec2 second, vec2* result){
  double O = (first[0][0] * second[0]) + (first[0][1] * second[1]);
  double I = (first[1][0] * second[0]) + (first[1][1] * second[1]);
  (*result)[0] = O; (*result)[1] = I; 
}

void inverse_matrix(mat2x2* mat){
  (*mat)[0][1] = (*mat)[0][1] * -1;
  (*mat)[1][0] = (*mat)[1][0] * -1;
}
