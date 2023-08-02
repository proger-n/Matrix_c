#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int ret = 0;
  if (rows > 0 && columns > 0)
    result->matrix = (double **)calloc(rows, sizeof(double *));
  else
    ret = 1;
  if (result->matrix != NULL && !ret) {
    for (int i = 0; i < rows && !ret; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      if (result->matrix[i] == NULL) {
        for (int j = 0; j < i; j++) {
          free(result->matrix[j]);
        }
        free(result->matrix);
        ret = 1;
      }
    }
    result->columns = columns;
    result->rows = rows;
  } else
    ret = 1;
  return ret;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i]) {
        free(A->matrix[i]);
        A->matrix[i] = NULL;
      }
    }
  }
  A->columns = 0;
  A->rows = 0;
  free(A->matrix);
  A->matrix = NULL;
  A = NULL;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int ret = FAILURE;
  if (A->columns == B->columns && A->rows == B->rows && A->columns > 0 &&
      A->rows > 0) {
    ret = SUCCESS;
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++) {
        if ((int)(round(A->matrix[i][j] * 1e7)) !=
            (int)(round(B->matrix[i][j] * 1e7)))
          ret = FAILURE;
      }
  }
  return ret;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = 0;
  if (!s21_matrix_exists(A) || !s21_matrix_exists(B)) ret = 1;
  if (!ret && A->rows == B->rows && A->columns == B->columns) {
    ret = s21_create_matrix(A->rows, B->columns, result);
  } else
    ret = 2;
  if (!ret) {
    for (int i = 0; i < A->rows && !ret; i++)
      for (int j = 0; j < A->columns && !ret; j++) {
        if (s21_is_matrix_member_norm(A->matrix[i][j]) &&
            s21_is_matrix_member_norm(B->matrix[i][j]) &&
            s21_is_matrix_member_norm(A->matrix[i][j] + B->matrix[i][j]))
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        else {
          s21_remove_matrix(result);
          ret = 2;
        }
      }
  }
  return ret;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = 0;
  if (!s21_matrix_exists(A) || !s21_matrix_exists(B)) ret = 1;
  if (!ret && A->rows == B->rows && A->columns == B->columns) {
    if (s21_create_matrix(A->rows, B->columns, result)) ret = 1;
  } else
    ret = 2;
  if (!ret) {
    for (int i = 0; i < A->rows && !ret; i++)
      for (int j = 0; j < A->columns && !ret; j++) {
        if (s21_is_matrix_member_norm(A->matrix[i][j]) &&
            s21_is_matrix_member_norm(B->matrix[i][j]) &&
            s21_is_matrix_member_norm(A->matrix[i][j] - B->matrix[i][j]))
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        else {
          s21_remove_matrix(result);
          ret = 2;
        }
      }
  }

  return ret;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = 0;
  if (!s21_matrix_exists(A) || !s21_matrix_exists(B)) ret = 1;
  if (!ret && A->columns == B->rows)
    ret = s21_create_matrix(A->rows, B->columns, result);
  else
    ret = 2;
  if (!ret) {
    ret = s21_check_mult(A, B, result);
    for (int i = 0; i < A->rows && !ret; i++)
      for (int j = 0; j < B->columns && !ret; j++)
        for (int k = 0; k < A->columns && !ret; k++) {
          result->matrix[i][j] += (A->matrix[i][k] * B->matrix[k][j]);
        }
  }

  return ret;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int ret = 0;
  if (!s21_matrix_exists(A)) ret = 1;
  if (!ret) ret = s21_create_matrix(A->rows, A->columns, result);
  if (!ret) {
    for (int i = 0; i < A->rows && !ret; i++)
      for (int j = 0; j < A->columns && !ret; j++) {
        if (s21_is_matrix_member_norm(A->matrix[i][j]) &&
            s21_is_matrix_member_norm(A->matrix[i][j] * number))
          result->matrix[i][j] = A->matrix[i][j] * number;
        else {
          s21_remove_matrix(result);
          ret = 2;
        }
      }
  }

  return ret;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int ret = 0;
  if (!s21_matrix_exists(A)) ret = 1;
  if (!ret && s21_create_matrix(A->columns, A->rows, result)) ret = 1;
  if (!ret) {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++) {
        if (s21_is_matrix_member_norm(A->matrix[i][j]))
          result->matrix[j][i] = A->matrix[i][j];
        else {
          s21_remove_matrix(result);
          ret = 2;
        }
      }
  }

  return ret;
}

int s21_determinant(matrix_t *A, double *result) {
  int ret = 0;
  if (!s21_matrix_exists(A)) ret = 1;
  if (!ret && A->columns == A->rows) {
    int size = A->columns;
    *result = (double)s21_calculate_determinant(*A, size);
  } else
    ret = ret ? 1 : 2;
  return ret;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int ret = 0;
  if (!s21_matrix_exists(A)) ret = 1;
  if (!ret && A->columns == A->rows && A->columns > 1)
    ret = s21_create_matrix(A->rows, A->columns, result);
  else
    ret = ret ? 1 : 2;
  if (!ret) {
    int size = (A->rows) - 1;
    for (int i = 0; i < result->rows && !ret; i++) {
      for (int j = 0; j < result->columns && !ret; j++) {
        if (s21_is_matrix_member_norm(A->matrix[i][j])) {
          matrix_t temp;
          s21_create_matrix(size, size, &temp);
          s21_get_minor(A->matrix, temp.matrix, i, j, size + 1);
          result->matrix[i][j] =
              pow(-1, i + j) * s21_calculate_determinant(temp, size);
          s21_remove_matrix(&temp);
        } else {
          s21_remove_matrix(result);
          ret = 2;
        }
      }
    }
  }
  return ret;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int ret = 0, step = 0;
  double det_A = 0.0;
  if (s21_matrix_exists(A))
    step = 1;
  else
    ret = 1;
  if (step == 1 && A->columns == A->rows) {
    s21_determinant(A, &det_A);
    step = 2;
  } else
    ret = 2;
  if (step == 2 && fabs(det_A))
    step = 3;
  else
    ret = 2;
  if (step == 3 && !s21_create_matrix(A->rows, A->columns, result)) step = 4;
  if (step == 4 && A->rows == A->columns && A->columns == 1)
    result->matrix[0][0] = 1 / A->matrix[0][0];
  else if (step == 4) {
    matrix_t trans = {0};
    matrix_t comp = {0};
    if (!s21_transpose(A, &trans))
      ret = s21_calc_complements(&trans, &comp);
    else
      ret = 2;
    for (int i = 0; i < comp.rows && !ret; i++) {
      for (int j = 0; j < comp.columns && !ret; j++) {
        if (s21_is_matrix_member_norm(comp.matrix[i][j]))
          result->matrix[i][j] = (1.0 / det_A) * comp.matrix[i][j];
        else {
          ret = 2;
        }
      }
    }
    if (ret) s21_remove_matrix(result);
    s21_remove_matrix(&trans);
    s21_remove_matrix(&comp);
  }

  if (ret) result->matrix = NULL;
  return ret;
}

// auxiliary functions

int s21_matrix_exists(matrix_t *matr_struct) {
  int ret = 1;
  if (matr_struct != NULL && matr_struct->matrix != NULL &&
      matr_struct->columns > 0 && matr_struct->rows > 0) {
    for (int i = 0; i < matr_struct->rows && ret; i++) {
      if (matr_struct->matrix[i] == NULL) ret = 0;
    }
  } else
    ret = 0;
  return ret;
}

int s21_is_matrix_member_norm(double matr_member) {
  int ret = 1;
  if (isinf(matr_member) || isnan(matr_member)) ret = 0;
  return ret;
}

void s21_get_minor(double **mat, double **temp, int skip_row, int skip_col,
                   int n) {
  int i = 0, j = 0;
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (row != skip_row && col != skip_col) {
        temp[i][j++] = mat[row][col];
        if (j == n - 1) {
          j = 0;
          i++;
        }
      }
    }
  }
}

double s21_calculate_determinant(matrix_t mat, int size) {
  double D = 0;

  if (size == 1)
    D = mat.matrix[0][0];
  else {
    matrix_t temp;
    s21_create_matrix(size, size, &temp);

    int sign = 1;

    for (int cur_col = 0; cur_col < size; cur_col++) {
      s21_get_minor(mat.matrix, temp.matrix, 0, cur_col, size);
      D += sign * mat.matrix[0][cur_col] *
           s21_calculate_determinant(temp, size - 1);

      sign = -sign;
    }
    s21_remove_matrix(&temp);
  }
  return D;
}

int s21_check_mult(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = 0;
  for (int i = 0; i < A->rows && !ret; i++)
    for (int j = 0; j < B->columns && !ret; j++)
      for (int k = 0; k < A->columns && !ret; k++) {
        if (s21_is_matrix_member_norm(A->matrix[i][k]) &&
            s21_is_matrix_member_norm(B->matrix[k][j]) &&
            s21_is_matrix_member_norm(result->matrix[i][j]))
          ;
        else {
          s21_remove_matrix(result);
          ret = 2;
        }
      }
  return ret;
}