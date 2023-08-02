# matrix_c
Proprietary implementation of the matrix.h library for working with matrices in C

## Implementation 
- Library functions:
    - **Matrix operations**:

      | Description | Function name <br /> |
      | --------- | ------ |
      | Creating matrices | s21_create_matrix(int rows, int columns, matrix_t *result) | 
      | Cleaning of matrices | s21_remove_matrix(matrix_t *A) | 
      | Matrix comparison | s21_eq_matrix(matrix_t *A, matrix_t *B) |
      | Adding matrices | s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) |
      | Subtracting matrices | s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) |
      | Matrix multiplication by scalar | s21_mult_number(matrix_t *A, double number, matrix_t *result) |
      | Multiplication of two matrices | s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) |
      | Matrix transpose | s21_transpose(matrix_t *A, matrix_t *result) |
      | Matrix of algebraic complements | s21_calc_complements(matrix_t *A, matrix_t *result) |
      | Matrix determinant | s21_determinant(matrix_t *A, double *result) |
      | Inverse of the matrix | s21_inverse_matrix(matrix_t *A, matrix_t *result) |
