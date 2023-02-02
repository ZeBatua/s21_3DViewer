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

// START_TEST(test_3) {
//   char fname[] = "tests/testFile_1.obj";
//   double V[24] = {-0.500000, -0.500000, 0.500000,  0.500000,  -0.500000,
//                   0.500000,  -0.500000, 0.500000,  0.500000,  0.500000,
//                   0.500000,  0.500000,  -0.500000, 0.500000,  -0.500000,
//                   0.500000,  0.500000,  -0.500000, -0.500000, -0.500000,
//                   -0.500000, 0.500000,  -0.500000, -0.500000};
//   data = parser(fname);
//   for (int i = 0; i < 24; i++) {
//     ck_assert_double_eq(V[i], data.dataVertexes[i]);
//   }

//   freeMem(&data);
// }
// END_TEST

// START_TEST(test_4) {
//   char fname[] = "../test_objects.obj";
//   int F[72] = {0, 1, 1, 2, 2, 0, 2, 1, 1, 3, 3, 2, 2, 3, 3, 4, 4, 2,
//                4, 3, 3, 5, 5, 4, 4, 5, 5, 6, 6, 4, 6, 5, 5, 7, 7, 6,
//                6, 7, 7, 0, 0, 6, 0, 7, 7, 1, 1, 0, 1, 7, 7, 3, 3, 1,
//                3, 7, 7, 5, 5, 3, 6, 0, 0, 4, 4, 6, 4, 0, 0, 2, 2, 4};
//   data = parser(fname);
//   for (int i = 0; i < 72; i++) {
//     ck_assert_int_eq(F[i], data.dataFacets[i]);
//   }
//   freeMem(&data);
// }
// END_TEST

// START_TEST(test_5) {
//   double* p;
//   p = (double*)calloc(3, sizeof(double));
//   p[0] = 1.1;
//   p[1] = 1.2;
//   p[2] = 3.5;
//   // double* shift;

//   affine_scale(3, &p, 75);
//   ck_assert_ldouble_eq_tol(p[0], 0.825, 1e-2);
//   ck_assert_ldouble_eq_tol(p[1], 0.9, 1e-2);
//   ck_assert_ldouble_eq_tol(p[2], 2.625, 1e-2);
//   free(p);
//   // free(shift);
// }

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

// START_TEST(test_7) {
//   double* p;
//   p = (double*)calloc(3, sizeof(double));
//   p[0] = 1.1;
//   p[1] = 1.2;
//   p[2] = 3.5;
//   double* move = (double*)calloc(3, sizeof(double));
//   move[0] = 180.0;
//   move[1] = 360.0;
//   move[2] = 0.0;

//   affine_rotate(3, &p, move);
//   ck_assert_ldouble_eq_tol(p[0], 1.1, 1e-2);
//   ck_assert_ldouble_eq_tol(p[1], -1.2, 1e-2);
//   ck_assert_ldouble_eq_tol(p[2], -3.5, 1e-2);
//   free(p);
//   free(move);
// }

int main(void) {
  Suite* s1 = suite_create("Core");
  TCase* tc = tcase_create("Core");
  SRunner* sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc);

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  //   tcase_add_test(tc, test_4);
  //   tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  //   tcase_add_test(tc, test_7);
  //   tcase_add_test(tc, test_8);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
