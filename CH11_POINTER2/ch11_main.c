#include <stdio.h>

#define RANDOM_ARRAY_LENGTH 100
#define MAT_ROWS 4
#define MAT_COLS 4

/**************** 공통 유틸 함수들 ****************/

/*
 * 1차원 int 배열을 출력하는 함수
 *  - c      : int 배열의 시작 주소 (int* 포인터)
 *  - length : 배열의 길이(원소 개수)
 */
void print_array(int* c, int length)
{
  int i;
  for (i = 0; i < length; i++) {
    // c[i]는 *(c + i)와 같은 의미로, 포인터를 이용한 배열 접근
    printf("%d ", c[i]);
  }
  printf("\n");
}

/*
 * 2차원 배열(행렬)을 출력하는 함수
 *  - a    : 2차원 배열, 열 크기 MAT_COLS 로 고정된 형태
 *  - rows : 행 개수
 *  - cols : 열 개수
 */
void print_mat2d(int a[][MAT_COLS], int rows, int cols)
{
  int i, j;
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      printf("%3d ", a[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

/**************** exam9 (A): 포인터로 3의 배수 출력 ****************/
/*
 * 1부터 100 사이의 값이 랜덤하게 들어 있는 배열에서,
 * 포인터를 이용해 "3의 배수"인 원소만 골라 출력하는 예제.
 */

 /*
  * 배열에서 3의 배수만 출력하는 함수 (포인터 사용)
  *  - array  : int 배열의 시작 주소 (int* 포인터)
  *  - length : 배열 길이
  */
void print_multiple_of_3(int* array, int length)
{
  int i;
  int* p = array;   // 배열의 시작 주소를 가리키는 포인터

  printf("3의 배수들: ");
  for (i = 0; i < length; i++) {
    // *p 는 현재 포인터가 가리키는 원소의 값
    if (*p % 3 == 0) {     // 3으로 나누어 떨어지는지 확인
      printf("%d ", *p);
    }
    p++;                   // 다음 원소로 포인터 한 칸 이동 (p = p + 1)
  }
  printf("\n\n");
}

/**************** exam9 (B-i): add_one을 이용한 2의 배수 증가 ****************/
/*
 * B-i. 배열 안에서 2의 배수인 값만 찾아서 1씩 증가시키는 예제.
 *      이때, "해당 원소 하나의 주소"를 함수에 넘겨서 값을 수정한다.
 */

 /*
  * 하나의 int 값을 1 증가시키는 함수
  *  - value : int 값을 가리키는 포인터
  *           (호출할 때 &array[i] 처럼 특정 원소의 주소를 넘기게 됨)
  */
void add_one(int* value)
{
  // *value 는 실제 저장된 정수 값,
  // (*value)++ 로 해당 값을 1 증가시킨다.
  (*value)++;
}

/**************** exam9 (B-ii): change_array로 2의 배수 일괄 증가 ****************/
/*
 * B-ii. 배열 전체를 가리키는 포인터(int *buf)와 길이를 받아,
 *       내부에서 2의 배수인 모든 원소를 1씩 증가시키는 함수.
 */

 /*
  * 배열에서 2의 배수인 모든 원소를 1씩 증가시키는 함수
  *  - buf    : int 배열의 시작 주소
  *  - length : 배열 길이
  */
void change_array(int* buf, int length)
{
  int i;
  for (i = 0; i < length; i++) {
    // buf[i] == *(buf + i)
    if (buf[i] % 2 == 0) {
      buf[i]++;        // 2의 배수인 원소를 1 증가
    }
  }
}

/**************** exam9: 위의 A, B-i, B-ii 모두 사용하는 예제 ****************/
/*
 * 문제에서 제시된 100개의 정수를 가진 배열에 대해
 *  A. print_multiple_of_3 을 사용해서 3의 배수 출력
 *  B-i. add_one 을 사용해 2의 배수를 한 번 모두 1 증가
 *  B-ii. change_array 를 사용해 2의 배수를 다시 한 번 모두 1 증가
 */
void exam9(void)
{
  int array[RANDOM_ARRAY_LENGTH] = {
      42, 7, 89, 15, 63, 28, 94, 3, 56, 71,
      12, 100, 37, 85, 9, 64, 23, 48, 77, 31,
      5, 92, 18, 74, 60, 11, 36, 81, 25, 50,
      66, 14, 97, 8, 45, 70, 29, 53, 19, 82,
      39, 6, 95, 21, 68, 33, 80, 10, 57, 99,
      2, 27, 73, 41, 88, 16, 61, 34, 46, 20,
      76, 13, 90, 4, 55, 22, 83, 30, 65, 17,
      96, 24, 40, 78, 32, 87, 35, 59, 26, 84,
      1, 44, 75, 38, 62, 28, 93, 47, 67, 49,
      98, 19, 54, 72, 91, 36, 58, 79, 43, 100
  };
  int i;

  printf("[exam9] 원본 배열 (일부만 출력):\n");
  print_array(array, RANDOM_ARRAY_LENGTH);

  /* A. 3의 배수 출력 (포인터 사용) */
  printf("[exam9] 배열에서 3의 배수 출력\n");
  print_multiple_of_3(array, RANDOM_ARRAY_LENGTH);

  /* B-i. for문에서 2의 배수를 찾아 add_one()으로 1 증가 */
  printf("[exam9] B-i: add_one을 사용하여 2의 배수들을 1씩 증가\n");
  for (i = 0; i < RANDOM_ARRAY_LENGTH; i++) {
    if (array[i] % 2 == 0) {
      // &array[i]는 i번째 원소의 주소 → int* 타입
      // add_one의 매개변수는 int* 이므로 주소를 넘겨 줌
      add_one(&array[i]);
    }
  }

  printf("B-i 이후 배열 (일부만 출력):\n");
  print_array(array, RANDOM_ARRAY_LENGTH);

  /* B-ii. 배열 전체를 change_array로 넘겨서 2의 배수를 또 1 증가 */
  printf("[exam9] B-ii: change_array를 사용하여 2의 배수들을 다시 1씩 증가\n");
  change_array(array, RANDOM_ARRAY_LENGTH);

  printf("B-ii 이후 배열 (일부만 출력):\n");
  print_array(array, RANDOM_ARRAY_LENGTH);
}

/**************** padding_0_rows_odd_8: 2D 배열 홀수 행을 0으로 ****************/
/*
 * padding_0_rows_odd_8
 *
 *  - 2차원 배열을 1차원 포인터(int *)로 보고,
 *  - 포인터가 "열 개수(cols)"만큼씩 (정확히는 2*cols씩) 건너뛰면서
 *  - 홀수 행(1, 3, 5, ...)의 모든 원소를 0으로 만드는 함수.
 *
 * 매개변수:
 *   array : int* 형 포인터 (예: (int *)mat 처럼 2D 배열을 캐스팅해서 넘김)
 *   rows  : 행 개수
 *   cols  : 열 개수
 *
 * 아이디어:
 *   - 2D 배열을 1D 메모리 블록으로 본다면,
 *       (r, c) 의 1D 인덱스는 r * cols + c.
 *   - 1행(두 번째 행)의 첫 원소는 array + 1 * cols 위치에 있음.
 *   - 홀수 행들(1,3,...)만 0으로 만들기 위해:
 *       odd_rows = array + cols;   // 1행 시작
 *       한 행 처리 후 odd_rows += 2 * cols; 로 다음 홀수 행(3행)으로 점프
 */
void padding_0_rows_odd_8(int* array, int rows, int cols)
{
  int r, c;
  int* odd_rows;

  // 첫 번째 홀수 행은 인덱스 1번 행.
  // 1행의 첫 번째 원소는 "array + 1 * cols" 위치에 있다.
  odd_rows = array + cols;        // == &array[1 * cols]

  // r을 실제 행 인덱스(1, 3, 5, ...)로 사용
  for (r = 1; r < rows; r += 2) {
    // 현재 odd_rows는 r행의 첫 번째 원소를 가리키고 있다.
    // 그 행의 모든 열(cols 개)을 0으로 만든다.
    for (c = 0; c < cols; c++) {
      odd_rows[c] = 0;            // *(odd_rows + c) = 0; 과 동일
    }

    // 다음 홀수 행으로 이동:
    //   현재 r에서 +2 한 행의 시작 주소로 가야 하므로
    //   포인터를 2 * cols 만큼 건너뛴다.
    odd_rows += 2 * cols;
  }
}

/********** padding_0_rows_odd_8 테스트용 예제 **********/
void exam_padding_odd_rows(void)
{
  int mat[MAT_ROWS][MAT_COLS] = {
      {  1,  2,  3,  4 },
      {  5,  6,  7,  8 },
      {  9, 10, 11, 12 },
      { 13, 14, 15, 16 }
  };

  printf("[exam_padding_odd_rows] 원본 행렬:\n");
  print_mat2d(mat, MAT_ROWS, MAT_COLS);

  // 2차원 배열을 (int *)로 캐스팅해서 1차원 포인터처럼 넘겨줌
  padding_0_rows_odd_8((int*)mat, MAT_ROWS, MAT_COLS);

  printf("홀수 행(1, 3번 행)을 0으로 만든 후:\n");
  print_mat2d(mat, MAT_ROWS, MAT_COLS);
}

/**************** 실제 main: 두 예제 실행 ****************/

int main(void)
{
  //exam9(); // 1차원 배열 예제: 포인터로 3의 배수 출력 + 2의 배수 증가 (A, B-i, B-ii)
  //exam_padding_odd_rows(); // 2차원 배열 예제: 홀수 행을 0으로 만들기

  return 0;
}