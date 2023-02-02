#include "matrix.h"

int inverse_matrix(matrix_t *A, matrix_t *result);

matrix_t get_matrix(int i_rows, int j_columns, matrix_t *A) {
  matrix_t tmp = {0};
  if (!s21_create_matrix(A->rows - 1, A->columns - 1, &tmp)) {
    for (int i = 0, k = 0; i < A->rows; i++) {
      if (i != i_rows) {
        for (int j = 0, l = 0; j < A->columns; j++) {
          if (j != j_columns) {
            tmp.matrix[k][l] = A->matrix[i][j];
            l++;
          }
        }
        k++;
      }
    }
  }
  return tmp;
}

int is_valid_matrix(matrix_t *A) {
  return A == NULL || A->matrix == NULL || A->columns <= 0 || A->rows <= 0;
}

void calc_complements(matrix_t *A, matrix_t *result);

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (is_valid_matrix(A)) {
    error = INVALID_MATRIX;
  } else if (A->rows != A->columns) {
    error = CALCULATION_ERROR;
  } else {
    calc_complements(A, result);
  }
  return error;
}

void calc_complements(matrix_t *A, matrix_t *result) {
  s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows; i++) {
    double determinant = 0;
    for (int j = 0; j < A->columns; j++) {
      matrix_t tmp = get_matrix(i, j, A);
      s21_determinant(&tmp, &determinant);
      result->matrix[i][j] = pow(-1, i + j) * determinant;
      determinant = 0;
      s21_remove_matrix(&tmp);
    }
  }
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = OK;
  if (rows <= 0 || columns <= 0 || result == NULL) {
    error = INVALID_MATRIX;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (!error && !result->matrix) error = CALLOC_ERROR;
    for (int i = 0; i < rows && !error; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      if (!result->matrix[i]) {
        s21_remove_matrix(result);
        error = CALLOC_ERROR;
        break;
      }
    }
  }
  return error;
}

void get_determinant(matrix_t *A, double *result);

int s21_determinant(matrix_t *A, double *result) {
  int error = 0;
  if (is_valid_matrix(A)) {
    error = INVALID_MATRIX;
  } else if (A->rows != A->columns) {
    error = CALCULATION_ERROR;
  } else {
    get_determinant(A, result);
  }
  return error;
}

void get_determinant(matrix_t *A, double *result) {
  if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result =
        (A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0]);
  } else {
    double determinant = 0;
    for (int i = 0; i < A->rows; i++) {
      matrix_t tmp = get_matrix(i, 0, A);
      s21_determinant(&tmp, &determinant);
      *result += A->matrix[i][0] * determinant * pow(-1, i);
      determinant = 0;
      s21_remove_matrix(&tmp);
    }
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int error = SUCCESS;
  if (is_valid_matrix(A) || is_valid_matrix(B)) {
    error = FAILURE;
  } else if ((A->rows == B->rows) && (A->columns == B->columns)) {
    for (int i = 0; i < A->rows && error == SUCCESS; i++) {
      for (int j = 0; j < B->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          error = FAILURE;
          break;
        }
      }
    }
  } else {
    error = FAILURE;
  }
  return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (is_valid_matrix(A)) {
    error = INVALID_MATRIX;
  } else if (A->rows != A->columns) {
    error = CALCULATION_ERROR;
  } else {
    error = inverse_matrix(A, result);
  }
  return error;
}

int inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = 0;
  double determinant = 0;
  s21_determinant(A, &determinant);
  if (fabs(determinant) > EPS) {
    matrix_t tmp_minor = {0}, tmp_trans = {0};
    s21_calc_complements(A, &tmp_minor);
    s21_transpose(&tmp_minor, &tmp_trans);
    s21_remove_matrix(&tmp_minor);
    s21_mult_number(&tmp_trans, 1 / determinant, result);
    s21_remove_matrix(&tmp_trans);
  } else {
    error = CALCULATION_ERROR;
  }
  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (is_valid_matrix(A) || is_valid_matrix(B)) {
    error = INVALID_MATRIX;
  } else if (A->columns != B->rows) {
    error = CALCULATION_ERROR;
  } else {
    error = s21_create_matrix(A->rows, B->columns, result);
    if (error == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < B->rows; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    }
  }
  return error;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = OK;
  if (is_valid_matrix(A) || result == NULL) {
    error = INVALID_MATRIX;
  } else {
    error = s21_create_matrix(A->rows, A->columns, result);
    if (error == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  }
  return error;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL && A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i] != NULL) free(A->matrix[i]);
    }
    free(A->matrix);
  }
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (is_valid_matrix(A) || is_valid_matrix(B)) {
    error = INVALID_MATRIX;
  } else {
    if (!error && (A->rows == B->rows) && (A->columns == B->columns)) {
      error = s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else {
      error = CALCULATION_ERROR;
    }
  }
  return error;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (is_valid_matrix(A) || is_valid_matrix(B)) {
    error = INVALID_MATRIX;
  } else {
    if (!error && (A->rows == B->rows) && (A->columns == B->columns)) {
      error = s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else {
      error = CALCULATION_ERROR;
    }
  }
  return error;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = OK;
  if (is_valid_matrix(A)) {
    error = INVALID_MATRIX;
  } else {
    error = s21_create_matrix(A->columns, A->rows, result);
    if (!error) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  }
  return error;
}
