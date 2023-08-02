#include "test.h"
int main() {
  int failed = 0;
  Suite *s21_matrix_test[] = {
      test_create_matrix(),    test_remove_matrix(),  test_eq_matrix(),
      test_sum_matrix(),       test_sub_matrix(),     test_mult_number(),
      test_mult_matrix(),      test_transpose(),      test_determinant(),
      test_calc_complements(), test_inverse_matrix(), NULL};

  for (int i = 0; s21_matrix_test[i] != NULL; i++) {
    SRunner *sr = srunner_create(s21_matrix_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);

  return 0;
}

START_TEST(create_matrix_1) {
  matrix_t matr;
  int row = 3;
  int col = 3;
  int res = s21_create_matrix(row, col, &matr);
  int res_o = 0;

  ck_assert_int_eq(res, res_o);
  ck_assert_int_eq(row, matr.rows);
  ck_assert_int_eq(col, matr.columns);
  s21_remove_matrix(&matr);
}
END_TEST

Suite *test_create_matrix(void) {
  Suite *s = suite_create("\033[45m-=create_matrix_tc=-\033[0m");
  TCase *tc = tcase_create("create_matrix_tc");

  tcase_add_test(tc, create_matrix_1);

  suite_add_tcase(s, tc);
  return s;
}

START_TEST(remove_matrix_1) {
  matrix_t matr;
  int row = 3;
  int col = 3;
  int res = s21_create_matrix(row, col, &matr);
  int res_o = 0;
  ck_assert_int_eq(res, res_o);
  s21_remove_matrix(&matr);
  ck_assert_ptr_null(matr.matrix);
}
END_TEST

Suite *test_remove_matrix(void) {
  Suite *s = suite_create("\033[45m-=remove_matrix_tc=-\033[0m");
  TCase *tc = tcase_create("remove_matrix_tc");

  tcase_add_test(tc, remove_matrix_1);

  suite_add_tcase(s, tc);
  return s;
}

START_TEST(eq_matrix_1) {
  matrix_t matr1, matr2;
  int row = 2;
  int col = 2;
  s21_create_matrix(row, col, &matr1);
  s21_create_matrix(row, col, &matr2);
  matr1.matrix[0][0] = 1.0;
  matr1.matrix[0][1] = 1.0;
  matr1.matrix[1][0] = 1.0;
  matr1.matrix[1][1] = 1.0;
  matr2.matrix[0][0] = 1.0;
  matr2.matrix[0][1] = 1.0;
  matr2.matrix[1][0] = 1.0;
  matr2.matrix[1][1] = 1.0;
  int res = s21_eq_matrix(&matr1, &matr2);
  int res_o = 1;
  ck_assert_int_eq(res, res_o);
  s21_remove_matrix(&matr1);
  s21_remove_matrix(&matr2);
}
END_TEST

Suite *test_eq_matrix(void) {
  Suite *s = suite_create("\033[45m-=eq_matrix_tc=-\033[0m");
  TCase *tc = tcase_create("eq_matrix_tc");

  tcase_add_test(tc, eq_matrix_1);

  suite_add_tcase(s, tc);
  return s;
}

START_TEST(sum_matrix_1) {
  matrix_t matr1, matr2, matr_sum;
  int row = 2;
  int col = 2;
  s21_create_matrix(row, col, &matr1);
  s21_create_matrix(row, col, &matr2);
  matr1.matrix[0][0] = 1.0;
  matr1.matrix[0][1] = 1.0;
  matr1.matrix[1][0] = 1.0;
  matr1.matrix[1][1] = 1.0;
  matr2.matrix[0][0] = 1.0;
  matr2.matrix[0][1] = 1.0;
  matr2.matrix[1][0] = 1.0;
  matr2.matrix[1][1] = 1.0;
  int res = s21_sum_matrix(&matr1, &matr2, &matr_sum);
  int res_o = 0;
  ck_assert_int_eq(res, res_o);
  ck_assert_double_eq(matr_sum.matrix[0][0], 2.0);
  ck_assert_double_eq(matr_sum.matrix[0][1], 2.0);
  ck_assert_double_eq(matr_sum.matrix[1][0], 2.0);
  ck_assert_double_eq(matr_sum.matrix[1][1], 2.0);
  s21_remove_matrix(&matr1);
  s21_remove_matrix(&matr2);
  s21_remove_matrix(&matr_sum);
}
END_TEST

START_TEST(sum_matrix_2) {
  matrix_t matr1, matr2, matr_sum;
  int row = 2;
  int col = 2;
  s21_create_matrix(row, col, &matr1);
  s21_create_matrix(row, ++col, &matr2);
  matr1.matrix[0][0] = 1.0;
  matr1.matrix[0][1] = 1.0;
  matr1.matrix[1][0] = 1.0;
  matr1.matrix[1][1] = 1.0;
  int res = s21_sum_matrix(&matr1, &matr2, &matr_sum);
  int res_o = 2;
  ck_assert_int_eq(res, res_o);
  s21_remove_matrix(&matr2);
  s21_remove_matrix(&matr1);
}
END_TEST

START_TEST(sum_matrix_3) {
  matrix_t matr1, matr2, matr_sum;
  int row = 2;
  int col = 2;
  s21_create_matrix(row, col, &matr1);
  s21_create_matrix(row, col, &matr2);
  matr1.matrix[0][0] = 1.0;
  matr1.matrix[0][1] = 1.0;
  matr1.matrix[1][0] = 1.0;
  matr1.matrix[1][1] = 1.0;
  matr2.matrix[0][0] = 1.0;
  matr2.matrix[0][1] = 1.0;
  matr2.matrix[1][0] = 1.0;
  matr2.matrix[1][1] = 0.0 / 0.0;
  int res = s21_sum_matrix(&matr1, &matr2, &matr_sum);
  int res_o = 2;
  ck_assert_int_eq(res, res_o);
  s21_remove_matrix(&matr1);
  s21_remove_matrix(&matr2);
  s21_remove_matrix(&matr_sum);
}
END_TEST

Suite *test_sum_matrix(void) {
  Suite *s = suite_create("\033[45m-=sum_matrix_tc=-\033[0m");
  TCase *tc = tcase_create("sum_matrix_tc");

  tcase_add_test(tc, sum_matrix_1);
  tcase_add_test(tc, sum_matrix_2);
  tcase_add_test(tc, sum_matrix_3);

  suite_add_tcase(s, tc);
  return s;
}

START_TEST(sub_matrix_1) {
  matrix_t matr1, matr2, matr_sub;
  int row = 2;
  int col = 2;
  s21_create_matrix(row, col, &matr1);
  s21_create_matrix(row, col, &matr2);
  matr1.matrix[0][0] = 2.0;
  matr1.matrix[0][1] = 2.0;
  matr1.matrix[1][0] = 2.0;
  matr1.matrix[1][1] = 2.0;
  matr2.matrix[0][0] = 1.0;
  matr2.matrix[0][1] = 1.0;
  matr2.matrix[1][0] = 1.0;
  matr2.matrix[1][1] = 1.0;
  int res = s21_sub_matrix(&matr1, &matr2, &matr_sub);
  int res_o = 0;
  ck_assert_int_eq(res, res_o);
  ck_assert_double_eq(matr_sub.matrix[0][0], 1.0);
  ck_assert_double_eq(matr_sub.matrix[0][1], 1.0);
  ck_assert_double_eq(matr_sub.matrix[1][0], 1.0);
  ck_assert_double_eq(matr_sub.matrix[1][1], 1.0);
  s21_remove_matrix(&matr1);
  s21_remove_matrix(&matr2);
  s21_remove_matrix(&matr_sub);
}
END_TEST

START_TEST(sub_matrix_2) {
  matrix_t matr1, matr2, matr_sub;
  int row = 2;
  int col = 2;
  s21_create_matrix(row, col, &matr1);
  s21_create_matrix(row, ++col, &matr2);
  matr1.matrix[0][0] = 1.0;
  matr1.matrix[0][1] = 1.0;
  matr1.matrix[1][0] = 1.0;
  matr1.matrix[1][1] = 1.0;
  int res = s21_sub_matrix(&matr1, &matr2, &matr_sub);
  int res_o = 2;
  ck_assert_int_eq(res, res_o);
  s21_remove_matrix(&matr2);
  s21_remove_matrix(&matr1);
}
END_TEST

START_TEST(sub_matrix_3) {
  matrix_t matr1, matr2, matr_sub;
  int row = 2;
  int col = 2;
  s21_create_matrix(row, col, &matr1);
  s21_create_matrix(row, col, &matr2);
  matr1.matrix[0][0] = 1.0;
  matr1.matrix[0][1] = 1.0;
  matr1.matrix[1][0] = 1.0;
  matr1.matrix[1][1] = 1.0;
  matr2.matrix[0][0] = 1.0;
  matr2.matrix[0][1] = 1.0;
  matr2.matrix[1][0] = 1.0;
  matr2.matrix[1][1] = 0.0 / 0.0;
  int res = s21_sub_matrix(&matr1, &matr2, &matr_sub);
  int res_o = 2;
  ck_assert_int_eq(res, res_o);
  s21_remove_matrix(&matr1);
  s21_remove_matrix(&matr2);
  s21_remove_matrix(&matr_sub);
}
END_TEST

Suite *test_sub_matrix(void) {
  Suite *s = suite_create("\033[45m-=sub_matrix_tc=-\033[0m");
  TCase *tc = tcase_create("sub_matrix_tc");

  tcase_add_test(tc, sub_matrix_1);
  tcase_add_test(tc, sub_matrix_2);
  tcase_add_test(tc, sub_matrix_3);

  suite_add_tcase(s, tc);
  return s;
}

START_TEST(mult_number_1) {
  matrix_t matr3, matr_mult;
  double num = 2.0;
  int row = 2;
  int col = 2;
  s21_create_matrix(row, col, &matr3);
  matr3.matrix[0][0] = 1.0;
  matr3.matrix[0][1] = 1.0;
  matr3.matrix[1][0] = 1.0;
  matr3.matrix[1][1] = 1.0;
  int res = s21_mult_number(&matr3, num, &matr_mult);
  int res_o = 0;
  ck_assert_int_eq(res, res_o);
  ck_assert_double_eq(matr_mult.matrix[0][0], 2.0);
  ck_assert_double_eq(matr_mult.matrix[0][1], 2.0);
  ck_assert_double_eq(matr_mult.matrix[1][0], 2.0);
  ck_assert_double_eq(matr_mult.matrix[1][1], 2.0);
  s21_remove_matrix(&matr3);
  s21_remove_matrix(&matr_mult);
}
END_TEST

START_TEST(mult_number_3) {
  matrix_t matr1, matr_mult;
  double num = 2.0;
  int row = 2;
  int col = 2;
  s21_create_matrix(row, col, &matr1);
  matr1.matrix[0][0] = 1.0;
  matr1.matrix[0][1] = 1.0;
  matr1.matrix[1][0] = 1.0;
  matr1.matrix[1][1] = 0.0 / 0.0;
  int res = s21_mult_number(&matr1, num, &matr_mult);
  int res_o = 2;
  ck_assert_int_eq(res, res_o);
  s21_remove_matrix(&matr1);
}
END_TEST

Suite *test_mult_number(void) {
  Suite *s = suite_create("\033[45m-=mult_number_tc=-\033[0m");
  TCase *tc = tcase_create("mult_number_tc");

  tcase_add_test(tc, mult_number_1);
  tcase_add_test(tc, mult_number_3);

  suite_add_tcase(s, tc);
  return s;
}

START_TEST(mult_matrix_1) {
  matrix_t matr01, matr02, matr_mult1;
  int row = 3;
  int col = 2;
  s21_create_matrix(row, col, &matr01);
  s21_create_matrix(col, row, &matr02);
  matr02.matrix[0][0] = 2.0;
  matr02.matrix[0][1] = 2.0;
  matr02.matrix[0][2] = 2.0;

  matr02.matrix[1][0] = 2.0;
  matr02.matrix[1][1] = 2.0;
  matr02.matrix[1][2] = 2.0;

  matr01.matrix[0][0] = 2.0;
  matr01.matrix[0][1] = 2.0;

  matr01.matrix[1][0] = 2.0;
  matr01.matrix[1][1] = 2.0;

  matr01.matrix[2][0] = 2.0;
  matr01.matrix[2][1] = 2.0;
  int res = s21_mult_matrix(&matr01, &matr02, &matr_mult1);
  int res_o = 0;
  double n = 8.0;
  ck_assert_int_eq(res, res_o);
  ck_assert_double_eq(matr_mult1.matrix[0][0], n);
  ck_assert_double_eq(matr_mult1.matrix[0][1], n);
  ck_assert_double_eq(matr_mult1.matrix[0][2], n);

  ck_assert_double_eq(matr_mult1.matrix[1][0], n);
  ck_assert_double_eq(matr_mult1.matrix[1][1], n);
  ck_assert_double_eq(matr_mult1.matrix[1][2], n);

  ck_assert_double_eq(matr_mult1.matrix[2][0], n);
  ck_assert_double_eq(matr_mult1.matrix[2][1], n);
  ck_assert_double_eq(matr_mult1.matrix[2][2], n);

  s21_remove_matrix(&matr01);
  s21_remove_matrix(&matr02);
  s21_remove_matrix(&matr_mult1);
}
END_TEST

START_TEST(mult_matrix_3) {
  matrix_t matr1, matr2, matr_mult;
  int row = 2;
  int col = 2;
  s21_create_matrix(row, col, &matr1);
  s21_create_matrix(row, col, &matr2);
  matr1.matrix[0][0] = 1.0;
  matr1.matrix[0][1] = 1.0;
  matr1.matrix[1][0] = 1.0;
  matr1.matrix[1][1] = 1.0;
  matr2.matrix[0][0] = 1.0;
  matr2.matrix[0][1] = 1.0;
  matr2.matrix[1][0] = 1.0;
  matr2.matrix[1][1] = 1.0 / 0.0;
  int res = s21_mult_matrix(&matr1, &matr2, &matr_mult);
  int res_o = 2;
  ck_assert_int_eq(res, res_o);
  s21_remove_matrix(&matr1);
  s21_remove_matrix(&matr2);
}
END_TEST

Suite *test_mult_matrix(void) {
  Suite *s = suite_create("\033[45m-=mult_matrix_tc=-\033[0m");
  TCase *tc = tcase_create("mult_matrix_tc");

  tcase_add_test(tc, mult_matrix_1);
  tcase_add_test(tc, mult_matrix_3);

  suite_add_tcase(s, tc);
  return s;
}

START_TEST(transpose_1) {
  matrix_t matr1, matr2;
  int row = 2;
  int col = 3;
  s21_create_matrix(row, col, &matr1);
  matr1.matrix[0][0] = 1.0;
  matr1.matrix[0][1] = 2.0;
  matr1.matrix[0][2] = 3.0;
  matr1.matrix[1][0] = 4.0;
  matr1.matrix[1][1] = 5.0;
  matr1.matrix[1][2] = 6.0;

  int res = s21_transpose(&matr1, &matr2);
  int res_o = 0;
  ck_assert_int_eq(res, res_o);
  ck_assert_double_eq(matr1.matrix[0][0], matr2.matrix[0][0]);
  ck_assert_double_eq(matr1.matrix[0][1], matr2.matrix[1][0]);
  ck_assert_double_eq(matr1.matrix[0][2], matr2.matrix[2][0]);
  ck_assert_double_eq(matr1.matrix[1][0], matr2.matrix[0][1]);
  ck_assert_double_eq(matr1.matrix[1][1], matr2.matrix[1][1]);
  ck_assert_double_eq(matr1.matrix[1][2], matr2.matrix[2][1]);
  s21_remove_matrix(&matr1);
  s21_remove_matrix(&matr2);
}
END_TEST

START_TEST(transpose_3) {
  matrix_t matr1, matr2;
  int row = 2;
  int col = 3;
  s21_create_matrix(row, col, &matr1);
  matr1.matrix[0][0] = 1.0;
  matr1.matrix[0][1] = 2.0;
  matr1.matrix[0][2] = 3.0;
  matr1.matrix[1][0] = 4.0;
  matr1.matrix[1][1] = 5.0;
  matr1.matrix[1][2] = 0.0 / 0.0;
  int res = s21_transpose(&matr1, &matr2);
  int res_o = 2;
  ck_assert_int_eq(res, res_o);
  s21_remove_matrix(&matr1);
}
END_TEST

Suite *test_transpose(void) {
  Suite *s = suite_create("\033[45m-=transpose_tc=-\033[0m");
  TCase *tc = tcase_create("transpose_tc");

  tcase_add_test(tc, transpose_1);
  tcase_add_test(tc, transpose_3);

  suite_add_tcase(s, tc);
  return s;
}

START_TEST(determinant_1) {
  matrix_t matr1;
  double det;
  int row = 2;
  int col = 2;
  s21_create_matrix(row, col, &matr1);
  matr1.matrix[0][0] = 1.0;
  matr1.matrix[0][1] = 2.0;
  matr1.matrix[1][0] = 4.0;
  matr1.matrix[1][1] = 5.0;

  int res = s21_determinant(&matr1, &det);
  int res_o = 0;
  ck_assert_int_eq(res, res_o);
  ck_assert_double_eq(det, -3.0);
  s21_remove_matrix(&matr1);
}
END_TEST

START_TEST(determinant_2) {
  matrix_t matr1;
  double det;
  int row = 2;
  int col = 3;
  s21_create_matrix(row, col, &matr1);

  int res = s21_determinant(&matr1, &det);
  int res_o = 2;
  ck_assert_int_eq(res, res_o);
  s21_remove_matrix(&matr1);
}
END_TEST

Suite *test_determinant(void) {
  Suite *s = suite_create("\033[45m-=determinant_tc=-\033[0m");
  TCase *tc = tcase_create("determinant_tc");

  tcase_add_test(tc, determinant_1);
  tcase_add_test(tc, determinant_2);

  suite_add_tcase(s, tc);
  return s;
}

START_TEST(calc_complements_1) {
  matrix_t matr1, matr2;
  int row = 1;
  int col = 1;
  s21_create_matrix(row, col, &matr1);
  matr1.matrix[0][0] = 1.0;
  int res = s21_calc_complements(&matr1, &matr2);
  int res_o = 2;
  ck_assert_int_eq(res, res_o);
  s21_remove_matrix(&matr1);
}
END_TEST

START_TEST(calc_complements_2) {
  matrix_t matr1, matr2;
  int row = 3;
  int col = 3;
  s21_create_matrix(row, col, &matr1);
  matr1.matrix[0][0] = 1.0;
  matr1.matrix[0][1] = 2.0;
  matr1.matrix[0][2] = 3.0;

  matr1.matrix[1][0] = 0.0;
  matr1.matrix[1][1] = 4.0;
  matr1.matrix[1][2] = 2.0;

  matr1.matrix[2][0] = 5.0;
  matr1.matrix[2][1] = 2.0;
  matr1.matrix[2][2] = 1.0;

  int res = s21_calc_complements(&matr1, &matr2);
  int res_o = 0;
  ck_assert_int_eq(res, res_o);
  ck_assert_double_eq(matr2.matrix[0][0], 0.0);
  ck_assert_double_eq(matr2.matrix[0][1], 10.0);
  ck_assert_double_eq(matr2.matrix[0][2], -20.0);

  ck_assert_double_eq(matr2.matrix[1][0], 4.0);
  ck_assert_double_eq(matr2.matrix[1][1], -14.0);
  ck_assert_double_eq(matr2.matrix[1][2], 8.0);

  ck_assert_double_eq(matr2.matrix[2][0], -8.0);
  ck_assert_double_eq(matr2.matrix[2][1], -2.0);
  ck_assert_double_eq(matr2.matrix[2][2], 4.0);

  s21_remove_matrix(&matr1);
  s21_remove_matrix(&matr2);
}
END_TEST

START_TEST(calc_complements_3) {
  matrix_t matr1, matr2;
  int row = 2;
  int col = 2;
  s21_create_matrix(row, col, &matr1);
  matr1.matrix[0][0] = 1.0;
  matr1.matrix[0][1] = 2.0;
  matr1.matrix[1][0] = 3.0;
  matr1.matrix[1][1] = 0.0 / 0.0;
  int res = s21_calc_complements(&matr1, &matr2);
  int res_o = 2;
  ck_assert_int_eq(res, res_o);
  s21_remove_matrix(&matr2);
  s21_remove_matrix(&matr1);
}
END_TEST

Suite *test_calc_complements(void) {
  Suite *s = suite_create("\033[45m-=calc_complements_tc=-\033[0m");
  TCase *tc = tcase_create("calc_complements_tc");

  tcase_add_test(tc, calc_complements_1);
  tcase_add_test(tc, calc_complements_2);
  tcase_add_test(tc, calc_complements_3);

  suite_add_tcase(s, tc);
  return s;
}

START_TEST(inverse_matrix_1) {
  matrix_t matr1, matr2;
  int row = 1;
  int col = 1;
  s21_create_matrix(row, col, &matr1);
  matr1.matrix[0][0] = 2.0;
  int res = s21_inverse_matrix(&matr1, &matr2);
  int res_o = 0;
  ck_assert_int_eq(res, res_o);
  ck_assert_double_eq(matr2.matrix[0][0], 0.5);
  s21_remove_matrix(&matr1);
  s21_remove_matrix(&matr2);
}
END_TEST

START_TEST(inverse_matrix_2) {
  matrix_t matr1, matr2;
  int row = 3;
  int col = 3;
  s21_create_matrix(row, col, &matr1);
  matr1.matrix[0][0] = 2.0;
  matr1.matrix[0][1] = 5.0;
  matr1.matrix[0][2] = 7.0;

  matr1.matrix[1][0] = 6.0;
  matr1.matrix[1][1] = 3.0;
  matr1.matrix[1][2] = 4.0;

  matr1.matrix[2][0] = 5.0;
  matr1.matrix[2][1] = -2.0;
  matr1.matrix[2][2] = -3.0;

  int res = s21_inverse_matrix(&matr1, &matr2);
  int res_o = 0;
  ck_assert_int_eq(res, res_o);
  ck_assert_double_eq(matr2.matrix[0][0], 1.0);
  ck_assert_double_eq(matr2.matrix[0][1], -1.0);
  ck_assert_double_eq(matr2.matrix[0][2], 1.0);

  ck_assert_double_eq(matr2.matrix[1][0], -38.0);
  ck_assert_double_eq(matr2.matrix[1][1], 41.0);
  ck_assert_double_eq(matr2.matrix[1][2], -34.0);

  ck_assert_double_eq(matr2.matrix[2][0], 27.0);
  ck_assert_double_eq(matr2.matrix[2][1], -29.0);
  ck_assert_double_eq(matr2.matrix[2][2], 24.0);

  s21_remove_matrix(&matr1);
  s21_remove_matrix(&matr2);
}
END_TEST

START_TEST(inverse_matrix_3) {
  matrix_t matr1, matr2;
  int row = 2;
  int col = 2;
  s21_create_matrix(row, col, &matr1);
  matr1.matrix[0][0] = 1.0;
  matr1.matrix[0][1] = 2.0;
  matr1.matrix[1][0] = 3.0;
  matr1.matrix[1][1] = NAN;
  int res = s21_inverse_matrix(&matr1, &matr2);
  int res_o = 2;
  ck_assert_int_eq(res, res_o);
  s21_remove_matrix(&matr1);
}
END_TEST

Suite *test_inverse_matrix(void) {
  Suite *s = suite_create("\033[45m-=inverse_matrix_tc=-\033[0m");
  TCase *tc = tcase_create("inverse_matrix_tc");

  tcase_add_test(tc, inverse_matrix_1);
  tcase_add_test(tc, inverse_matrix_2);
  tcase_add_test(tc, inverse_matrix_3);

  suite_add_tcase(s, tc);
  return s;
}