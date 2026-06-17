#include <stdio.h>

// 여러 예제에서 사용할 상수 정의
#define SORTED_LENGTH 4      // 정렬된 배열 a, b 의 길이
#define RANDOM_ARRAY_LENGTH 100
#define ARRAY_LENGTH 5       // 1차원 배열 길이
#define MAT_ROWS 4           // 2차원 배열 행 수
#define MAT_COLS 4           // 2차원 배열 열 수

/**************** 공통 유틸 함수들 ****************/

// 1차원 배열을 출력하는 함수 (이름: print_array)
// - c: int 배열의 시작 주소
// - length: 배열의 길이
void print_array(int* c, int length) {
  int i;
  for (i = 0; i < length; i++) {
    printf("%d ", c[i]);   // c[i]는 *(c + i) 와 같은 의미
  }
  printf("\n");
}

// 1차원 배열을 출력하는 함수 (이름: print_array_1d)
// - 기능은 위와 동일, 이름만 다르게 둔 버전
void print_array_1d(int* array, int length) {
  int i;
  for (i = 0; i < length; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}

// 2차원 배열 출력용 (행렬 확인용)
void print_mat2d(int a[][MAT_COLS], int rows, int cols) {
  int i, j;
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      printf("%3d ", a[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

// 두 정수 값을 교환(swap)하는 함수
// - a, b: 서로 값을 바꿀 변수의 주소
void swap(int* a, int* b) {
  int temp = *a;  // temp에 *a 값(첫 번째 값) 저장
  *a = *b;        // a가 가리키는 곳에 b의 값 저장
  *b = temp;      // b가 가리키는 곳에 temp(원래 a의 값) 저장
}

/**************** ex00: 포인터 기본 연습 ****************/

int ex00(void) {
  int a = 10;
  int b = 20;
  int buf[5] = { 1, 2, 3, 4, 5 };
  int* p_buf = buf;  // 배열 이름 buf는 배열의 시작 주소 → int* 로 받기 가능
  int i;

  // a와 b의 값을 서로 교환
  swap(&a, &b);
  printf("[ex00] after swap: a=%d, b=%d\n", a, b);

  // p_buf를 이용해서 buf 배열에 있는 값들을 1씩 증가
  for (i = 0; i < 5; i++) {
    *p_buf = *p_buf + 1;   // 현재 가리키는 원소에 1 더하기
    p_buf++;               // 다음 원소를 가리키도록 포인터 한 칸 이동
  }

  // buf의 내용 출력 → 각 원소가 1씩 증가했는지 확인
  printf("[ex00] buf after ++ : ");
  print_array(buf, 5);

  return 0;
}

/**************** ex01: 두 수의 합과 차 (call by reference) ****************/

// 두 정수 x, y의 합과 차를 동시에 구하는 함수
// - sum, diff: 결과를 저장할 변수의 주소
void get_sum_diff(int x, int y, int* sum, int* diff) {
  *sum = x + y;                            // 합 = x + y
  *diff = (x >= y) ? (x - y) : (y - x);     // 차는 절댓값 형태
}

int ex01(void) {
  int s = 0;
  int d = 0;

  // 4와 3의 합과 차를 구해서 s, d에 저장
  get_sum_diff(4, 3, &s, &d);
  printf("[ex01] sum:%d, diff:%d\n", s, d);

  return 0;
}

/**************** ex02: 정렬된 두 배열 합치기(merge) ****************/

// 인덱스 방식으로 merge하는 함수
// - a, b: 오름차순으로 정렬된 배열 (길이: length)
// - merge: 결과를 저장할 배열 (길이: 2 * length)
void merge_array(int* a, int* b, int* merge, int length) {
  int i = 0; // 배열 a의 인덱스
  int j = 0; // 배열 b의 인덱스
  int k = 0; // 결과 배열 merge의 인덱스

  // a와 b 둘 다 아직 남은 요소가 있을 때까지 반복
  while (i < length && j < length) {
    if (a[i] < b[j]) {
      merge[k++] = a[i++];  // a[i]가 더 작으면 merge에 넣고 i, k 증가
    }
    else {
      merge[k++] = b[j++];  // b[j]가 더 작으면 merge에 넣고 j, k 증가
    }
  }

  // a 쪽에 남은 요소들이 있다면 전부 뒤에 붙이기
  while (i < length) {
    merge[k++] = a[i++];
  }

  // b 쪽에 남은 요소들이 있다면 전부 뒤에 붙이기
  while (j < length) {
    merge[k++] = b[j++];
  }
}

// 포인터 연산 방식으로 merge하는 함수
void merge_array2(int* a, int* b, int* merge, int length) {
  int* pa = a;              // 배열 a의 현재 위치
  int* pb = b;              // 배열 b의 현재 위치
  int* pc = merge;          // 결과 배열의 현재 위치
  int* a_end = a + length;  // 배열 a의 끝 위치(하나 뒤)
  int* b_end = b + length;  // 배열 b의 끝 위치(하나 뒤)

  // a, b 둘 다 아직 요소가 남아있는 동안 반복
  while (pa < a_end && pb < b_end) {
    if (*pa <= *pb) {
      *pc++ = *pa++;    // *pa가 더 작으면 복사 후 pa, pc 이동
    }
    else {
      *pc++ = *pb++;    // *pb가 더 작으면 복사 후 pb, pc 이동
    }
  }

  // a 쪽 남은 요소들 복사
  while (pa < a_end) {
    *pc++ = *pa++;
  }

  // b 쪽 남은 요소들 복사
  while (pb < b_end) {
    *pc++ = *pb++;
  }
}

int ex02(void) {
  int a[SORTED_LENGTH] = { 2, 5, 7, 8 };  // 정렬된 배열 a
  int b[SORTED_LENGTH] = { 1, 3, 4, 6 };  // 정렬된 배열 b
  int c[2 * SORTED_LENGTH];              // 결과 배열 (길이 8)

  // 인덱스 방식 또는 포인터 방식 중 하나 사용
  // merge_array(a, b, c, SORTED_LENGTH);
  merge_array2(a, b, c, SORTED_LENGTH);

  printf("[ex02] merged array: ");
  print_array(c, 2 * SORTED_LENGTH);
  return 0;
}

/**************** ex03: call by reference (배열 요소 1씩 증가) ****************/

// 방법 1: 인덱스 방식
void call_by_reference1(int* array, int length) {
  int i;
  for (i = 0; i < length; i++) {
    array[i] = array[i] + 1;    // i번째 원소에 1 더하기
  }
}

// 방법 2: 포인터 자체를 이동시키는 방식
void call_by_reference2(int* array, int length) {
  int i;
  for (i = 0; i < length; i++) {
    *array = *array + 1;   // 현재 가리키는 원소에 1 더하기
    array++;               // 다음 원소로 포인터 이동
  }
  // 여기서 array는 매개변수(지역 변수) 포인터라
  // 함수가 끝나면 원래 main의 배열 주소에는 영향 없음
}

// 방법 3: 포인터 + 인덱스 연산
void call_by_reference3(int* array, int length) {
  int i;
  for (i = 0; i < length; i++) {
    *(array + i) = *(array + i) + 1;  // array[i]와 같은 의미
  }
}

int ex03(void) {
  int array[ARRAY_LENGTH] = { 1, 2, 3, 4, 5 };

  printf("[ex03] 초기 배열: ");
  print_array_1d(array, ARRAY_LENGTH);

  printf("call_by_reference1\n");
  call_by_reference1(array, ARRAY_LENGTH);
  print_array_1d(array, ARRAY_LENGTH);

  printf("call_by_reference2\n");
  call_by_reference2(array, ARRAY_LENGTH);
  print_array_1d(array, ARRAY_LENGTH);

  printf("call_by_reference3\n");
  call_by_reference3(array, ARRAY_LENGTH);
  print_array_1d(array, ARRAY_LENGTH);

  return 0;
}

/**************** ex04: 2차원 배열 → 1차원 배열 변환 (4가지) ****************/

// 버전 0: int array2d[][MAT_COLS] 형식으로 받는 경우
void mat2d_to_1d_0(int array2d[][MAT_COLS], int* array1d, int rows, int cols) {
  int i, j;
  // i: 행, j: 열
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      // 2차원 인덱스 (i, j)를 1차원 인덱스 i*cols + j로 변환
      array1d[i * cols + j] = array2d[i][j];
    }
  }
}

// 버전 1: int (*array2d)[MAT_COLS] 형식 (행 포인터)
void mat2d_to_1d_1(int (*array2d)[MAT_COLS], int* array1d, int rows, int cols) {
  int i, j;
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      array1d[i * cols + j] = array2d[i][j];
    }
  }
}

// 버전 2: int *로 받고, 직접 인덱스 계산
void mat2d_to_1d_2(int* array2d, int* array1d, int rows, int cols) {
  int i, j;
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      // array2d를 "연속된 int"로 보고, i*cols + j 위치에 접근
      array1d[i * cols + j] = array2d[i * cols + j];
    }
  }
}

// 버전 3: 전체를 1차원처럼 보고 복사
void mat2d_to_1d_3(int* array2d, int* array1d, int rows, int cols) {
  int i;
  int total = rows * cols;  // 전체 원소 개수
  for (i = 0; i < total; i++) {
    array1d[i] = *(array2d + i);  // array2d[i] 와 같은 의미
  }
}

int ex04(void) {
  // 4x4 2차원 배열 선언 및 초기화
  int mat2d[MAT_ROWS][MAT_COLS] = {
      { 2, 3, 0, 1 },
      { 8, 9, 1, 2 },
      { 7, 0, 5, 4 },
      { 1, 2, 3, 4 }
  };
  int mat1d[MAT_ROWS * MAT_COLS];  // 1차원으로 펼친 결과를 저장할 배열

  printf("[ex04] mat2d_to_1d_0:\n");
  mat2d_to_1d_0(mat2d, mat1d, MAT_ROWS, MAT_COLS);
  print_array_1d(mat1d, MAT_ROWS * MAT_COLS);

  printf("[ex04] mat2d_to_1d_1:\n");
  mat2d_to_1d_1(mat2d, mat1d, MAT_ROWS, MAT_COLS);
  print_array_1d(mat1d, MAT_ROWS * MAT_COLS);

  printf("[ex04] mat2d_to_1d_2:\n");
  mat2d_to_1d_2((int*)mat2d, mat1d, MAT_ROWS, MAT_COLS);
  print_array_1d(mat1d, MAT_ROWS * MAT_COLS);

  printf("[ex04] mat2d_to_1d_3:\n");
  mat2d_to_1d_3((int*)mat2d, mat1d, MAT_ROWS, MAT_COLS);
  print_array_1d(mat1d, MAT_ROWS * MAT_COLS);

  return 0;
}

/**************** exam5: 2차원 → 1차원 변환 + 각 요소 제곱 ****************/
/*
   - 2차원 배열을 1차원 배열로 변환 (4번 문제의 네 가지 방식 사용)
   - 변환된 1차원 배열의 각 요소를 "제곱"
*/

// trans_mat2d_X : 2차원 → 1차원 변환 함수들
// pow_elemt_mat2d_X : 1차원 배열 요소 제곱 함수들

// 2차원 → 1차원 (버전 0) : 4번 문제의 mat2d_to_1d_0을 재사용
void trans_mat2d_0(int array2d[][MAT_COLS], int* array1d, int rows, int cols) {
  mat2d_to_1d_0(array2d, array1d, rows, cols);
}

// 2차원 → 1차원 (버전 1)
void trans_mat2d_1(int (*array2d)[MAT_COLS], int* array1d, int rows, int cols) {
  mat2d_to_1d_1(array2d, array1d, rows, cols);
}

// 2차원 → 1차원 (버전 2)
void trans_mat2d_2(int* array2d, int* array1d, int rows, int cols) {
  mat2d_to_1d_2(array2d, array1d, rows, cols);
}

// 2차원 → 1차원 (버전 3)
void trans_mat2d_3(int* array2d, int* array1d, int rows, int cols) {
  mat2d_to_1d_3(array2d, array1d, rows, cols);
}

// 1차원 배열의 각 요소를 제곱 (버전 0용)
void pow_elemt_mat2d_0(int* array1d, int length) {
  int i;
  for (i = 0; i < length; i++) {
    array1d[i] = array1d[i] * array1d[i];
  }
}

// 버전 1용 (동일 동작, 이름만 구분)
void pow_elemt_mat2d_1(int* array1d, int length) {
  int i;
  for (i = 0; i < length; i++) {
    array1d[i] = array1d[i] * array1d[i];
  }
}

// 버전 2용
void pow_elemt_mat2d_2(int* array1d, int length) {
  int i;
  for (i = 0; i < length; i++) {
    array1d[i] = array1d[i] * array1d[i];
  }
}

// 버전 3용
void pow_elemt_mat2d_3(int* array1d, int length) {
  int i;
  for (i = 0; i < length; i++) {
    array1d[i] = array1d[i] * array1d[i];
  }
}

void exam5(void)
{
  // 예시용 4x4 2차원 배열
  int mat2d[MAT_ROWS][MAT_COLS] = {
    { 1,  2,  3,  4 },
    { 5,  6,  7,  8 },
    { 9, 10, 11, 12 },
    {13, 14, 15, 16 }
  };

  // 1차원으로 펼친 값을 담을 배열
  int mat1d[MAT_ROWS * MAT_COLS];

  printf("[exam5] 2차원 배열을 1차원으로 변환하고, 각 요소를 제곱\n\n");

  // 1) 방법 0: trans_mat2d_0 + pow_elemt_mat2d_0
  printf("trans_mat2d_0 + pow_elemt_mat2d_0\n");
  trans_mat2d_0(mat2d, mat1d, MAT_ROWS, MAT_COLS);                  // 2D → 1D
  pow_elemt_mat2d_0(mat1d, MAT_ROWS * MAT_COLS);                    // 제곱
  print_array_1d(mat1d, MAT_ROWS * MAT_COLS);
  printf("\n");

  // 2) 방법 1: trans_mat2d_1 + pow_elemt_mat2d_1
  printf("trans_mat2d_1 + pow_elemt_mat2d_1\n");
  trans_mat2d_1(mat2d, mat1d, MAT_ROWS, MAT_COLS);
  pow_elemt_mat2d_1(mat1d, MAT_ROWS * MAT_COLS);
  print_array_1d(mat1d, MAT_ROWS * MAT_COLS);
  printf("\n");

  // 3) 방법 2: trans_mat2d_2 + pow_elemt_mat2d_2
  printf("trans_mat2d_2 + pow_elemt_mat2d_2\n");
  // mat2d를 (int*)로 캐스팅해서 "연속된 int 블록"처럼 넘김
  trans_mat2d_2((int*)mat2d, mat1d, MAT_ROWS, MAT_COLS);
  pow_elemt_mat2d_2(mat1d, MAT_ROWS * MAT_COLS);
  print_array_1d(mat1d, MAT_ROWS * MAT_COLS);
  printf("\n");

  // 4) 방법 3: trans_mat2d_3 + pow_elemt_mat2d_3
  printf("trans_mat2d_3 + pow_elemt_mat2d_3\n");
  trans_mat2d_3((int*)mat2d, mat1d, MAT_ROWS, MAT_COLS);
  pow_elemt_mat2d_3(mat1d, MAT_ROWS * MAT_COLS);
  print_array_1d(mat1d, MAT_ROWS * MAT_COLS);
  printf("\n");
}

/**************** padding_row_to_0: 특정 행을 모두 0으로 만드는 함수 (4가지) ****************/
/*
   - 2차원 배열에서 특정 행(index)만 0으로 채움
   - 배열 인자 형태를 4가지 버전으로 구현
*/

// 1) int array2d[][MAT_COLS] 형태로 받는 버전
void padding_row_to_0_0(int array2d[][MAT_COLS],
  int index, int rows, int cols)
{
  int j;

  // index가 유효한 범위(0 ~ rows-1)인지 확인
  if (index < 0 || index >= rows) {
    return;   // 잘못된 인덱스면 아무것도 하지 않음
  }

  // 해당 행(index)의 모든 열을 0으로 설정
  for (j = 0; j < cols; j++) {
    array2d[index][j] = 0;
  }
}

// 2) int (*array2d)[MAT_COLS] 형태(행 포인터)로 받는 버전
void padding_row_to_0_1(int (*array2d)[MAT_COLS],
  int index, int rows, int cols)
{
  int j;

  if (index < 0 || index >= rows) {
    return;
  }

  // array2d[index][j] 로 2차원 배열처럼 접근
  for (j = 0; j < cols; j++) {
    array2d[index][j] = 0;
  }
}

// 3) int* 로 받고, 직접 인덱스 계산하는 버전
//    - array2d 를 (int*)mat 로 넘겨 받는다고 가정
void padding_row_to_0_2(int* array2d,
  int index, int rows, int cols)
{
  int j;

  if (index < 0 || index >= rows) {
    return;
  }

  // index 번째 행의 시작 1차원 인덱스 = index * cols
  int start = index * cols;

  for (j = 0; j < cols; j++) {
    array2d[start + j] = 0;     // (index, j) 위치를 0으로
  }
}

// 4) int* 로 받고, 포인터 연산을 명시적으로 사용하는 버전
void padding_row_to_0_3(int* array2d,
  int index, int rows, int cols)
{
  int j;

  if (index < 0 || index >= rows) {
    return;
  }

  // index 번째 행의 첫 원소를 가리키는 포인터
  int* p_row = array2d + (index * cols);

  for (j = 0; j < cols; j++) {
    *(p_row + j) = 0;   // p_row[j] = 0; 과 동일
  }
}

/**************** padding_0_rows_even / padding_0_rows_odd ****************/
/*
   요구사항:
   - 2차원 배열의 짝수/홀수 행만 0으로 설정
   - 배열 형태 4가지로 각각 작성
*/

/*** 짝수 행을 0으로 ***/

// 1) int array2d[][MAT_COLS]
void padding_0_rows_even_0(int array2d[][MAT_COLS], int rows, int cols)
{
  int i, j;
  for (i = 0; i < rows; i++) {
    if (i % 2 == 0) {      // 짝수 행 (0, 2, 4, ...)
      for (j = 0; j < cols; j++) {
        array2d[i][j] = 0;
      }
    }
  }
}

// 2) int (*array2d)[MAT_COLS]
void padding_0_rows_even_1(int (*array2d)[MAT_COLS], int rows, int cols)
{
  int i, j;
  for (i = 0; i < rows; i++) {
    if (i % 2 == 0) {
      for (j = 0; j < cols; j++) {
        array2d[i][j] = 0;
      }
    }
  }
}

// 3) int *array2d (직접 인덱스 계산)
void padding_0_rows_even_2(int* array2d, int rows, int cols)
{
  int i, j;
  for (i = 0; i < rows; i++) {
    if (i % 2 == 0) {
      int start = i * cols;   // i번째 행의 시작 인덱스
      for (j = 0; j < cols; j++) {
        array2d[start + j] = 0;
      }
    }
  }
}

// 4) int *array2d (포인터 연산)
void padding_0_rows_even_3(int* array2d, int rows, int cols)
{
  int i, j;
  for (i = 0; i < rows; i++) {
    if (i % 2 == 0) {
      int* p_row = array2d + i * cols;  // i번째 행 시작 주소
      for (j = 0; j < cols; j++) {
        *(p_row + j) = 0;   // p_row[j] = 0;
      }
    }
  }
}

/*** 홀수 행을 0으로 ***/

// 1) int array2d[][MAT_COLS]
void padding_0_rows_odd_0(int array2d[][MAT_COLS], int rows, int cols)
{
  int i, j;
  for (i = 0; i < rows; i++) {
    if (i % 2 == 1) {      // 홀수 행 (1, 3, 5, ...)
      for (j = 0; j < cols; j++) {
        array2d[i][j] = 0;
      }
    }
  }
}

// 2) int (*array2d)[MAT_COLS]
void padding_0_rows_odd_1(int (*array2d)[MAT_COLS], int rows, int cols)
{
  int i, j;
  for (i = 0; i < rows; i++) {
    if (i % 2 == 1) {
      for (j = 0; j < cols; j++) {
        array2d[i][j] = 0;
      }
    }
  }
}

// 3) int *array2d (직접 인덱스 계산)
void padding_0_rows_odd_2(int* array2d, int rows, int cols)
{
  int i, j;
  for (i = 0; i < rows; i++) {
    if (i % 2 == 1) {
      int start = i * cols;
      for (j = 0; j < cols; j++) {
        array2d[start + j] = 0;
      }
    }
  }
}

// 4) int *array2d (포인터 연산)
void padding_0_rows_odd_3(int* array2d, int rows, int cols)
{
  int i, j;
  for (i = 0; i < rows; i++) {
    if (i % 2 == 1) {
      int* p_row = array2d + i * cols;
      for (j = 0; j < cols; j++) {
        *(p_row + j) = 0;
      }
    }
  }
}

/**************** padding_row_to_0 테스트용 예제 ****************/
int ex_padding_row(void)
{
  int mat[MAT_ROWS][MAT_COLS] = {
    { 1,  2,  3,  4 },
    { 5,  6,  7,  8 },
    { 9, 10, 11, 12 },
    {13, 14, 15, 16 }
  };

  printf("[padding_row_to_0] 원본 행렬:\n");
  print_mat2d(mat, MAT_ROWS, MAT_COLS);

  printf("padding_row_to_0_0 (index=1):\n");
  padding_row_to_0_0(mat, 1, MAT_ROWS, MAT_COLS);
  print_mat2d(mat, MAT_ROWS, MAT_COLS);

  printf("padding_row_to_0_1 (index=2):\n");
  padding_row_to_0_1(mat, 2, MAT_ROWS, MAT_COLS);
  print_mat2d(mat, MAT_ROWS, MAT_COLS);

  printf("padding_row_to_0_2 (index=0):\n");
  padding_row_to_0_2((int*)mat, 0, MAT_ROWS, MAT_COLS);
  print_mat2d(mat, MAT_ROWS, MAT_COLS);

  printf("padding_row_to_0_3 (index=3):\n");
  padding_row_to_0_3((int*)mat, 3, MAT_ROWS, MAT_COLS);
  print_mat2d(mat, MAT_ROWS, MAT_COLS);

  return 0;
}

/**************** 짝수/홀수 행 0으로 만드는 예제 ****************/
int ex_padding_even_odd(void)
{
  int mat[MAT_ROWS][MAT_COLS] = {
    { 1,  2,  3,  4 },
    { 5,  6,  7,  8 },
    { 9, 10, 11, 12 },
    {13, 14, 15, 16 }
  };

  printf("[padding_0_rows_even/odd] 원본 행렬:\n");
  print_mat2d(mat, MAT_ROWS, MAT_COLS);

  printf("짝수 행을 0으로 (padding_0_rows_even_0)\n");
  padding_0_rows_even_0(mat, MAT_ROWS, MAT_COLS);
  print_mat2d(mat, MAT_ROWS, MAT_COLS);

  // 다시 초기화
  int mat2[MAT_ROWS][MAT_COLS] = {
    { 1,  2,  3,  4 },
    { 5,  6,  7,  8 },
    { 9, 10, 11, 12 },
    {13, 14, 15, 16 }
  };

  printf("홀수 행을 0으로 (padding_0_rows_odd_2, int* 사용)\n");
  padding_0_rows_odd_2((int*)mat2, MAT_ROWS, MAT_COLS);
  print_mat2d(mat2, MAT_ROWS, MAT_COLS);

  return 0;
}

/**************** 실제 main: 원하는 예제 하나 실행 ****************/

int main(void) {
  //ex00();              // swap + 포인터로 배열 원소 증가
  //ex01();              // 합과 차 (get_sum_diff)
  //ex02();              // 정렬된 두 배열 merge
  //ex03();              // call by reference (배열 요소 +1)
  //ex04();              // 2차원 배열 → 1차원 배열 변환 (단순 변환)
  //exam5();             // 2차원 배열 → 1차원 변환 + 각 요소 제곱
  //ex_padding_row();    // 특정 행만 0으로
  //ex_padding_even_odd();   // 짝수/홀수 행을 0으로

  return 0;
}