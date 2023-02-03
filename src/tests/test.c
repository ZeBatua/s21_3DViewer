#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Widget/c_part/parser.h"
#include "../Widget/c_part/render.h"
file_data data;

START_TEST(test_1) {
  readFile("tests/alf.obj", &data);
  ck_assert_int_eq(3618, data.count_of_vertexes);
  freeMem(&data);
}
END_TEST

START_TEST(test_2) {
  readFile("tests/alf.obj", &data);
  ck_assert_int_eq(3442, data.count_of_facets);
  freeMem(&data);
}
END_TEST

START_TEST(test_3) {
  int res = readFile("yeahbuddy", &data);
  ck_assert_int_eq(1, res);
  freeMem(&data);
}

START_TEST(test_6) {
  file_data data;
  file_data Sdata;
  char* path = "./tests/cube.obj";
  readFile(path, &data);
  readFile(path, &Sdata);
  double buf = 5;
  zoomOut(&data, buf);
  for (int i = 1; i < Sdata.matrix_3d.rows; i++) {
    Sdata.matrix_3d.matrix[i][0] /= buf;
    Sdata.matrix_3d.matrix[i][1] /= buf;
    Sdata.matrix_3d.matrix[i][2] /= buf;
  }
  int error = s21_eq_matrix(&Sdata.matrix_3d, &data.matrix_3d);
  freeMem(&data);
  freeMem(&Sdata);
  ck_assert_int_eq(1, error);
}
END_TEST


START_TEST(test_9) {
  file_data data;
  file_data Sdata;
  char *path = "./tests/cube.obj";
  readFile(path, &data);
  readFile(path, &Sdata);
  double buf = 2.5;
  zoomIn(&data, buf);
  for (int i = 1; i < Sdata.matrix_3d.rows; i++) {
    Sdata.matrix_3d.matrix[i][0] *= buf;
    Sdata.matrix_3d.matrix[i][1] *= buf;
    Sdata.matrix_3d.matrix[i][2] *= buf;
  }
  int error = s21_eq_matrix(&Sdata.matrix_3d, &data.matrix_3d);
  freeMem(&data);
  freeMem(&Sdata);
  ck_assert_int_eq(1, error);
}
END_TEST



//---------------------------------

START_TEST(s21_shift_x) {
  file_data data;
  file_data Sdata;
  char *path = "./tests/cube.obj";
  readFile(path, &data);
  readFile(path, &Sdata);
  double buf = 2.5;
  moveX(&data, buf);
  for (int i = 1; i < Sdata.matrix_3d.rows; i++) {
    Sdata.matrix_3d.matrix[i][0] += buf;
  }
  int error = s21_eq_matrix(&Sdata.matrix_3d, &data.matrix_3d);
  ck_assert_int_eq(1, error);
  freeMem(&data);
  freeMem(&Sdata);
}
END_TEST

START_TEST(s21_shift_y) {
  file_data data;
  file_data Sdata;
  char *path = "./tests/cube.obj";
  readFile(path, &data);
  readFile(path, &Sdata);
  double buf = 2.5;
  moveY(&data, buf);
  for (int i = 1; i < Sdata.matrix_3d.rows; i++) {
    Sdata.matrix_3d.matrix[i][1] += buf;
  }
  int error = s21_eq_matrix(&Sdata.matrix_3d, &data.matrix_3d);
  freeMem(&data);
  freeMem(&Sdata);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(s21_shift_z) {
  file_data data;
  file_data Sdata;
  char *path = "./tests/cube.obj";
  readFile(path, &data);
  readFile(path, &Sdata);
  double buf = 2.5;
  moveZ(&data, buf);
  for (int i = 1; i < Sdata.matrix_3d.rows; i++) {
    Sdata.matrix_3d.matrix[i][2] += buf;
  }
  int error = s21_eq_matrix(&Sdata.matrix_3d, &data.matrix_3d);
  freeMem(&data);
  freeMem(&Sdata);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(s21_rotationX) {
  file_data data;
  matrix_t m;
  char *path = "./tests/cube.obj";
  m.matrix = calloc(9, sizeof(double **));
  double mat0[] = {0.000, 0.000, 0.000};
  double mat1[] = {-1.0, 0.675262, -1.242586};
  double mat2[] = {-1.0, -1.242586, -0.675262};
  double mat3[] = {-1.0, 1.242586, 0.675262};
  double mat4[] = {-1.0, -0.675262, 1.242586};
  double mat5[] = {1.000000, 0.675262, -1.242586};
  double mat6[] = {1.000000, -1.242586, -0.675262};
  double mat7[] = {1.000000, 1.242586, 0.675262};
  double mat8[] = {1.000000, -0.675262, 1.242586};
  m.matrix[0] = &mat0[0];
  m.matrix[1] = &mat1[0];
  m.matrix[2] = &mat2[0];
  m.matrix[3] = &mat3[0];
  m.matrix[4] = &mat4[0];
  m.matrix[5] = &mat5[0];
  m.matrix[6] = &mat6[0];
  m.matrix[7] = &mat7[0];
  m.matrix[8] = &mat8[0];
  m.rows = 9;
  m.columns = 3;

  int result = readFile(path, &data);
  rotationOX(&data, 5);
  int error = s21_eq_matrix(&data.matrix_3d, &m);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(1, error);
  freeMem(&data);
  free(m.matrix);
}
END_TEST

START_TEST(s21_rotationY) {
  file_data data;
  matrix_t m;
  char *path = "./tests/cube.obj";
  m.matrix = calloc(9, sizeof(double **));
  double mat0[] = {0.000000, 0.000000, 0.000000};
  double mat1[] = {0.675262, -1.000000, -1.242586};
  double mat2[] = {-1.242586, -1.000000, -0.675262};
  double mat3[] = {0.675262, 1.000000, -1.242586};
  double mat4[] = {-1.242586, 1.000000, -0.675262};
  double mat5[] = {1.242586, -1.000000, 0.675262};
  double mat6[] = {-0.675262, -1.000000, 1.242586};
  double mat7[] = {1.242586, 1.000000, 0.675262};
  double mat8[] = {-0.675262, 1.000000, 1.242586};
  m.matrix[0] = &mat0[0];
  m.matrix[1] = &mat1[0];
  m.matrix[2] = &mat2[0];
  m.matrix[3] = &mat3[0];
  m.matrix[4] = &mat4[0];
  m.matrix[5] = &mat5[0];
  m.matrix[6] = &mat6[0];
  m.matrix[7] = &mat7[0];
  m.matrix[8] = &mat8[0];
  m.rows = 9;
  m.columns = 3;

  int result = readFile(path, &data);
  rotationOY(&data, 5);

  int error = s21_eq_matrix(&data.matrix_3d, &m);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(1, error);
  freeMem(&data);
  free(m.matrix);
}
END_TEST

START_TEST(s21_rotationZ) {
  file_data data;
  matrix_t m;
  char *path = "./tests/cube.obj";
  m.matrix = calloc(9, sizeof(double **));
  double mat0[] = {0.000000, 0.000000, 0.000000};
  double mat1[] = {-1.242586, 0.675262, -1.000000};
  double mat2[] = {-1.242586, 0.675262, 1.000000};
  double mat3[] = {0.675262, 1.242586, -1.000000};
  double mat4[] = {0.675262, 1.242586, 1.000000};
  double mat5[] = {-0.675262, -1.242586, -1.000000};
  double mat6[] = {-0.675262, -1.242586, 1.000000};
  double mat7[] = {1.242586, -0.675262, -1.000000};
  double mat8[] = {1.242586, -0.675262, 1.000000};
  m.matrix[0] = &mat0[0];
  m.matrix[1] = &mat1[0];
  m.matrix[2] = &mat2[0];
  m.matrix[3] = &mat3[0];
  m.matrix[4] = &mat4[0];
  m.matrix[5] = &mat5[0];
  m.matrix[6] = &mat6[0];
  m.matrix[7] = &mat7[0];
  m.matrix[8] = &mat8[0];
  m.rows = 9;
  m.columns = 3;

  int result = readFile(path, &data);
  rotationOZ(&data, 5);

  int not_error = s21_eq_matrix(&data.matrix_3d, &m);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(1, not_error);
  freeMem(&data);
  free(m.matrix);
}
END_TEST



START_TEST(rewrite_m) {
  file_data data;
  char *path = "./tests/cube.obj";
  readFile(path, &data);
  float *new_matrix = rewrite_matrix(&data);
  float result[] = {-1.0,-1.0,-1.0,-1.0,-1.0,1.0,-1.0,1.0,-1.0,-1.0,1.0,1.0,1.0,-1.0,-1.0,1.0,-1.0,1.0,1.0,1.0,-1.0,1.0,1.0,1.0};

  for (int i = 0; i < 24; i++) {
    ck_assert_float_eq(new_matrix[i], result[i]);
  }

  freeMem(&data);
}
END_TEST

START_TEST(rewrite_f) {
  file_data data;
  char *path = "./tests/cube.obj";
  readFile(path, &data);
  unsigned int *new_matrix = write_facets(&data);
  unsigned int result[] = {0,6,6,4,4,0};

  for (int i = 0; i < 6; i++) {
    ck_assert_uint_eq(new_matrix[i], result[i]);
  }

  freeMem(&data);
}
END_TEST


int main(void) {
  Suite* s1 = suite_create("Core");
  TCase* tc = tcase_create("Core");
  SRunner* sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc);

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_9);

  tcase_add_test(tc, s21_shift_x);
  tcase_add_test(tc, s21_shift_z);
  tcase_add_test(tc, s21_shift_y);
  tcase_add_test(tc, s21_rotationX);
  tcase_add_test(tc, s21_rotationY);
  tcase_add_test(tc, s21_rotationZ);
  tcase_add_test(tc, rewrite_m);
  tcase_add_test(tc, rewrite_f);
  

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
