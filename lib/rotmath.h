#pragma once

typedef double **mat2x2;
typedef double *vec2;

/*
 * creates and returns a dynamically allocated
 * pointer-to-pointer 2D 2x2 array
 * as the mat2x2 type.
 * user must later free it with delete_2x2mat()
 */
mat2x2 new_mat2x2();

/*
 * creates and returns a dynamically allocated
 * 2D vector with the contents {1, 0}
 * as the vec2 type
 * user must later free it with delete_vec2()
 */
vec2 vector(double, double);

/*
 * frees all dynamically allocated cells from
 * a mat2x2 table
 */
void delete_2x2mat(mat2x2);

/*
 * frees all dynamically allocated cells from
 * a vec2 table
 */
void delete_vec2(vec2);

/*
 * takes in an angle in radians and a target
 * mat2x2 table, and creates a rotation matrix
 * of that angle within the mat2x2 table
 */
void matrix(double, mat2x2);

/*
 * takes in a source matrix, an angle in radians,
 * and a target matrix, and multiplies the source
 * by the rotation matrix for the specified angle
 * and puts the ressult in the target matrix
 */
void compose(mat2x2, double, mat2x2);

/*
 * takes in a source matrix, source vector,
 * and target vector. multiplies the source
 * matrix and the source vector, and puts
 * the result in the target vector
 */
void rotate_vec(mat2x2, vec2, vec2);

/*
 * takes in a source matrix and inverts it.
 * can be optimized to expect the matrix to
 * be a rotation matrix.
 */
void inverse_matrix(mat2x2);
