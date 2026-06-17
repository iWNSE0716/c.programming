#include <stdio.h>
#include "def.h"
#include "hello.h"
#include "print.h"
#define END_CLASS


int class1(void)
{
#ifndef END_CLASS
  printf("hello\n");
#else
  printf("bye bye\n");
#endif
  return 0;
}

int class2(void)
{
#if 1     //주석 대신 #을 사용
    printf("hello\n");
    printf("hello\n");
    printf("hello\n");
    printf("hello\n");
#else
  printf("hello222222\n");
#endif
  printf("byebye\n");
    return 0;
}

int class3(void)
{
  Student students[10];

  students[0].id = 30;
  students[0].name = "chul su";

  print_hello();
  print_student(&students[0]);
  return 0;
}

int class4(void)
{
  int mat1d[MAT_ROWS * MAT_COLS];
  int mat2d[MAT_ROWS][MAT_COLS] = {
      { 2, 3, 0, 1 },
      { 8, 9, 1, 2 },
      { 7, 0, 5, 4 },
      { 1, 2, 3, 4 }
  };

  mat2d_to_1d_0(mat2d, mat1d, MAT_ROWS, MAT_COLS);
  print_array_1d(mat1d, MAT_ROWS * MAT_COLS);
}

