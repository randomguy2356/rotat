#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"rotmath.h"

int main(void){
	mat2x2 M45 = new_rot_matrix(M_PI / 4);
	mat2x2 M30 = new_rot_matrix(M_PI / 6);
	mat2x2 sum = new_rot_matrix(M_PI / 4 + M_PI / 6);
	mat2x2 multiplied = new_mat2x2();
	mat2x2 Mn30 = new_rot_matrix((M_PI / 6) * -1); 
  multiply_mxm(M45, M30, &multiplied);

  vec2 vector = new_vec2();
  vec2 other_vector = new_vec2();
  vec2 other_other_vector = new_vec2();
  
	printf("45 deg:\n%f, %f\n%f, %f\n", M45[0][0], M45[0][1], M45[1][0], M45[1][1]);
	printf("30 deg:\n%f, %f\n%f, %f\n", M30[0][0], M30[0][1], M30[1][0], M30[1][1]);

  multiply_mxv(M45, vector, &vector);
  multiply_mxv(M30, vector, &vector);

  printf("rotated M45*(M30*[1, 0]) vector:\n%f\n%f\n", vector[0], vector[1]);
  
  multiply_mxv(multiplied, other_vector, &other_vector);

  printf("rotated (M45*M30)*[1, 0] other vector:\n%f\n%f\n", other_vector[0], other_vector[1]);

  multiply_mxv(sum, other_other_vector, &other_other_vector);

  printf("rotated M(45+30)*[1, 0] other other vector:\n%f\n%f\n", other_other_vector[0], other_other_vector[1]);

  reverse_matrix(&M30);
  multiply_mxv(M30, vector, &vector);

  printf("rotated M45*(M30*[1, 0]) and then back 30 vector:\n%f\n%f\n", vector[0], vector[1]);

	printf("30 deg reversed:\n%f, %f\n%f, %f\n", M30[0][0], M30[0][1], M30[1][0], M30[1][1]);
	printf("-30 deg:\n%f, %f\n%f, %f\n", Mn30[0][0], Mn30[0][1], Mn30[1][0], Mn30[1][1]);

  reverse_matrix(&M30);
  multiply_mxm(M30, Mn30, &Mn30);

	printf("30 times -30 deg:\n%f, %f\n%f, %f\n", Mn30[0][0], Mn30[0][1], Mn30[1][0], Mn30[1][1]);

	free2x2mat(M45);
	free2x2mat(M30);
	free2x2mat(Mn30);
  free2x2mat(sum);
  free2x2mat(multiplied);
	free_vec2(vector);
	free_vec2(other_vector);
	free_vec2(other_other_vector);
}
