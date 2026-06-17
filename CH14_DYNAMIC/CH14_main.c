#define _CRT_SECURE_NO_WARNINGS   // MSVC 보안 경고 끄기 (fopen 등에서 경고 제거)

#include <stdio.h>
#include <string.h>   // strlen, strstr
#include <stdlib.h>   // malloc, free

/************************************************************
 * [공통 유틸] 행렬용 함수들 (ex05, ex06에서 사용)
 *
 * - alloc_matrix : int 2차원 배열(행렬) 동적 할당
 * - free_matrix  : 할당한 행렬 메모리 해제
 * - print_matrix : 행렬 내용 출력
 ************************************************************/

 /*
   rows x cols 크기의 int 행렬을 이중 포인터로 동적 할당합니다.

   예)
     int **mat = alloc_matrix(3, 5);
     mat[행][열] 로 접근 가능
 */
int** alloc_matrix(int rows, int cols)
{
  int** mat = (int**)malloc(rows * sizeof(int*));
  int i;

  if (mat == NULL) return NULL;  // 메모리 할당 실패

  // 각 행마다 int 배열 동적 할당
  for (i = 0; i < rows; i++) {
    mat[i] = (int*)malloc(cols * sizeof(int));
    if (mat[i] == NULL) {
      // 중간에 실패하면, 이미 할당한 행들 해제
      while (--i >= 0) {
        free(mat[i]);
      }
      free(mat);
      return NULL;
    }
  }
  return mat;
}

/*
  행렬 메모리를 해제하는 함수입니다.
  rows: 행 개수
*/
void free_matrix(int** mat, int rows)
{
  int i;
  if (mat == NULL) return;

  for (i = 0; i < rows; i++) {
    free(mat[i]);
  }
  free(mat);
}

/*
  행렬 내용을 보기 좋게 출력합니다.

  name: 행렬 이름(문자열)
  mat : 행렬 포인터
  rows, cols: 행, 열 개수
*/
void print_matrix(const char* name, int** mat, int rows, int cols)
{
  int i, j;
  printf("%s:\n", name);
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      printf("%4d ", mat[i][j]);
    }
    printf("\n");
  }
}

/************************************************************
 * ex01. 구조체를 함수의 매개변수 포인터 형태로 전달
 *
 * - Point 구조체 정의
 * - print_point : 값으로 구조체를 받아 출력
 * - set_point   : 포인터로 구조체를 받아 내부 값 수정
 ************************************************************/

 // 2차원 점을 표현하는 구조체
typedef struct {
  int x;
  int y;
} Point;

/*
  값으로 구조체를 받아 단순히 출력만 하는 함수입니다.
  (함수 안에서 값을 바꿔도 원본에는 영향을 주지 않음)
*/
void print_point(Point point)
{
  printf("point x=%d, y=%d\n", point.x, point.y);
}

/*
  포인터로 구조체를 받아 멤버 값을 수정하는 함수입니다.
  (원본 구조체의 x, y 값이 실제로 바뀜)
*/
void set_point(Point* point, int x, int y)
{
  point->x = x;
  point->y = y;
}

void ex01(void)
{
  /*
    ex01.
    - Point 구조체 변수 하나를 만든다.
    - set_point에 주소를 넘겨 (3,5)로 설정한다.
    - print_point로 값이 잘 설정됐는지 확인한다.
  */
  Point point;

  set_point(&point, 3, 5);   // 구조체 주소(&point)를 넘김 → 원본 수정
  print_point(point);        // 수정된 값 출력
}

/************************************************************
 * ex02. 0~9를 binary 형태로 저장하고 다시 읽어 출력
 *
 * - write_out_dat : out.dat에 0~9를 short 형식 binary로 저장
 * - read_out_dat  : out.dat에서 값을 읽어 화면에 출력
 ************************************************************/

 /*
   0부터 9까지를 short 형식으로 out.dat 파일에 이진(binary) 저장합니다.

   fopen 모드 "wb" : write, binary
 */
void write_out_dat(void)
{
  FILE* fout = fopen("out.dat", "wb");  // binary 쓰기 모드
  if (fout == NULL) {
    printf("[ex02] out.dat 파일 열기 실패(쓰기)\n");
    return;
  }

  short i;
  for (i = 0; i <= 9; i++) {
    // &i 주소에서 sizeof(short) 바이트를 파일에 1번 쓴다.
    fwrite(&i, sizeof(short), 1, fout);
  }

  fclose(fout);
  printf("[ex02] out.dat 파일에 0~9를 binary 형태로 저장 완료\n");
}

/*
  out.dat 파일에서 short 값을 순서대로 읽어 화면에 출력합니다.

  fopen 모드 "rb" : read, binary
*/
void read_out_dat(void)
{
  FILE* fin = fopen("out.dat", "rb");   // binary 읽기 모드
  if (fin == NULL) {
    printf("[ex02] out.dat 파일 열기 실패(읽기)\n");
    return;
  }

  short value;
  int index = 0;

  printf("[ex02] out.dat 파일에서 읽은 값들:\n");

  /*
    fread의 반환값:
      - 요청한 개수(여기서는 1)를 정확히 읽으면 1
      - EOF(파일 끝) 또는 에러가 나면 0
  */
  while (fread(&value, sizeof(short), 1, fin) == 1) {
    printf("index=%d, value=%d\n", index, value);
    index++;
  }

  fclose(fin);
}

/*
  ex02를 한 번에 실행하는 래퍼 함수.
*/
void ex02(void)
{
  /*
    ex02.
    1) 0~9를 out.dat에 binary로 저장
    2) out.dat을 다시 읽어서 화면에 출력
  */
  write_out_dat();  // 쓰기
  read_out_dat();   // 읽기
}

/************************************************************
 * ex03. proverbs.txt에서 "All" 이 몇 번 나오는지 카운트
 *
 * - 파일을 한 줄씩 읽고
 * - 각 줄 안에서 strstr로 "All" 부분 문자열을 계속 찾아서 개수 누적
 ************************************************************/

void ex03(void)
{
  /*
    ex03.
    proverbs.txt에서 "All"이 몇 번 나오는지 카운트합니다.

    - 대소문자를 그대로 구분 (정확히 'A'+'l'+'l' 인 경우만 셈)
    - strstr(문자열, "All") 사용
  */
  FILE* fp = fopen("proverbs.txt", "r");
  char line[512];            // 한 줄 버퍼
  const char* target = "All";
  int total_count = 0;

  if (fp == NULL) {
    printf("[ex03] proverbs.txt 파일 열기 실패\n");
    return;
  }

  // 파일 끝까지 한 줄씩 읽으면서 "All" 검색
  while (fgets(line, sizeof(line), fp) != NULL) {
    char* p = line;

    /*
      p 위치부터 "All"을 찾고,
      찾으면 total_count 증가 후,
      찾은 위치 바로 뒤부터 다시 검색.
    */
    while ((p = strstr(p, target)) != NULL) {
      total_count++;
      p += strlen(target);
    }
  }

  fclose(fp);

  printf("[ex03] \"All\" 이 등장한 횟수: %d\n", total_count);
}

/************************************************************
 * ex04. proverbs.txt -> proverbs.dat(binary) -> out.txt
 *
 * - txt_to_bin   : proverbs.txt 를 줄 단위로 읽어 (길이 + 내용) binary 기록
 * - bin_to_stdout: binary 파일을 읽어 printf로 출력
 * - bin_to_txt   : binary 파일을 다시 out.txt 텍스트로 복원
 ************************************************************/

 /*
   A. 텍스트 파일을 읽어서 binary 파일로 저장하는 함수

   저장 형식 (각 줄마다):
     [int len][char data(len bytes)]

   - len은 '\n' 을 포함한 문자열 길이
 */
void txt_to_bin(const char* txt_name, const char* bin_name)
{
  FILE* fp_in = fopen(txt_name, "r");
  FILE* fp_out = fopen(bin_name, "wb");
  char line[512];

  if (fp_in == NULL || fp_out == NULL) {
    printf("[ex04] txt_to_bin: 파일 열기 실패\n");
    if (fp_in != NULL) fclose(fp_in);
    if (fp_out != NULL) fclose(fp_out);
    return;
  }

  // 한 줄씩 읽어와서 (길이 + 내용) 형태로 저장
  while (fgets(line, sizeof(line), fp_in) != NULL) {
    int len = (int)strlen(line);      // '\n' 포함 길이
    fwrite(&len, sizeof(int), 1, fp_out);  // 길이 기록
    fwrite(line, 1, len, fp_out);          // 문자열 데이터 기록
  }

  fclose(fp_in);
  fclose(fp_out);

  printf("[ex04] %s -> %s (텍스트에서 바이너리로) 변환 완료\n",
    txt_name, bin_name);
}

/*
  B. binary 파일 내용을 읽어서 화면에 출력하는 함수

  - txt_to_bin에서 저장한 포맷을 그대로 읽어 온다.
*/
void bin_to_stdout(const char* bin_name)
{
  FILE* fp = fopen(bin_name, "rb");
  if (fp == NULL) {
    printf("[ex04] bin_to_stdout: 파일 열기 실패\n");
    return;
  }

  printf("[ex04] %s 내용 (바이너리 → 화면 출력):\n", bin_name);

  while (1) {
    int len = 0;
    char buffer[512];
    size_t n;

    // 1) 길이(int) 읽기
    n = fread(&len, sizeof(int), 1, fp);
    if (n != 1) {
      // 더 이상 읽을 데이터가 없으면(EOF) 종료
      break;
    }

    // 비정상 길이 방어
    if (len <= 0 || len >= (int)sizeof(buffer)) {
      printf("[ex04] 비정상 길이: %d\n", len);
      break;
    }

    // 2) 실제 문자열 데이터 읽기
    n = fread(buffer, 1, len, fp);
    if (n != (size_t)len) {
      printf("[ex04] 데이터 읽기 실패\n");
      break;
    }

    buffer[len] = '\0';  // 널 문자 추가
    printf("%s", buffer);
  }

  fclose(fp);
}

/*
  C. binary 파일을 다시 텍스트 파일(out.txt)로 복원하는 함수

  - bin_to_stdout와 동일한 방식으로 읽되,
    printf 대신 fputs로 파일에 기록
*/
void bin_to_txt(const char* bin_name, const char* txt_name)
{
  FILE* fp_in = fopen(bin_name, "rb");
  FILE* fp_out = fopen(txt_name, "w");
  if (fp_in == NULL || fp_out == NULL) {
    printf("[ex04] bin_to_txt: 파일 열기 실패\n");
    if (fp_in != NULL) fclose(fp_in);
    if (fp_out != NULL) fclose(fp_out);
    return;
  }

  while (1) {
    int len = 0;
    char buffer[512];
    size_t n;

    // 1) 길이 읽기
    n = fread(&len, sizeof(int), 1, fp_in);
    if (n != 1) break;  // EOF

    // 비정상 길이 방어
    if (len <= 0 || len >= (int)sizeof(buffer)) {
      printf("[ex04] 비정상 길이: %d\n", len);
      break;
    }

    // 2) 문자열 데이터 읽기
    n = fread(buffer, 1, len, fp_in);
    if (n != (size_t)len) {
      printf("[ex04] 데이터 읽기 실패\n");
      break;
    }

    buffer[len] = '\0';
    fputs(buffer, fp_out);   // 그대로 텍스트 파일에 기록
  }

  fclose(fp_in);
  fclose(fp_out);

  printf("[ex04] %s -> %s (바이너리에서 텍스트로) 변환 완료\n",
    bin_name, txt_name);
}

/*
  ex04 전체를 실행하는 함수
*/
void ex04(void)
{
  /*
    ex04.
    proverbs.txt를 읽어서 proverbs.dat(binary)로 저장하고,
    그 내용을 화면에 출력한 뒤,
    out.txt로 복원하는 예제입니다.
  */
  const char* src_txt = "proverbs.txt";
  const char* bin_file = "proverbs.dat";
  const char* dst_txt = "out.txt";

  txt_to_bin(src_txt, bin_file);   // A. txt -> bin
  bin_to_stdout(bin_file);         // B. bin -> printf
  bin_to_txt(bin_file, dst_txt);   // C. bin -> txt
}

/************************************************************
 * ex05. 이중 포인터로 3x5 행렬을 1~15까지 채우기
 ************************************************************/

 /*
   이중 포인터(int **mat)로 주어진 rows x cols 행렬에
   1부터 시작해서 순차적으로 값을 채워 넣습니다.
 */
void set_mat(int** mat, int rows, int cols)
{
  int i, j;
  int value = 1;

  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      mat[i][j] = value++;
    }
  }
}

/*
  ex05: 3x5 행렬을 만들고 set_mat으로 1~15까지 채운 뒤 출력
*/
void ex05(void)
{
  int rows = 3;
  int cols = 5;
  int i, j;

  int** mat = alloc_matrix(rows, cols);
  if (mat == NULL) {
    printf("[ex05] 메모리 할당 실패\n");
    return;
  }

  set_mat(mat, rows, cols);

  printf("[ex05] 3x5 행렬 내용(1~15):\n");
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      printf("%3d ", mat[i][j]);
    }
    printf("\n");
  }

  free_matrix(mat, rows);
}

/************************************************************
 * ex06. 이중 포인터 2개, 덧셈/뺄셈/곱셈(한 개를 transpose로 사용)
 ************************************************************/

 /*
   A + B -> C (동일 크기 행렬 연산)
 */
void add_matrix(int** A, int** B, int** C, int rows, int cols)
{
  int i, j;
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      C[i][j] = A[i][j] + B[i][j];
    }
  }
}

/*
  A - B -> C (동일 크기 행렬 연산)
*/
void sub_matrix(int** A, int** B, int** C, int rows, int cols)
{
  int i, j;
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      C[i][j] = A[i][j] - B[i][j];
    }
  }
}

/*
  A * B^T -> C

  - A: rows x cols
  - B: rows x cols  (하지만 계산할 때 B^T: cols x rows 로 취급)
  - C: rows x rows

  C[i][j] = Σ_k ( A[i][k] * B[j][k] )
  (B의 j행 k열을 사용하는 것은 B^T의 (i,j)에 해당)
*/
void mul_matrix_with_B_transpose(int** A, int** B, int** C,
  int rows, int cols)
{
  int i, j, k;
  for (i = 0; i < rows; i++) {
    for (j = 0; j < rows; j++) {
      int sum = 0;
      for (k = 0; k < cols; k++) {
        sum += A[i][k] * B[j][k];
      }
      C[i][j] = sum;
    }
  }
}

/*
  테스트용: 행렬에 start부터 1씩 증가하며 값 채우기
*/
void set_sequential(int** mat, int rows, int cols, int start)
{
  int i, j;
  int value = start;
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      mat[i][j] = value++;
    }
  }
}

/*
  ex06:
    - A, B 두 행렬을 이중 포인터로 동적 할당
    - A, B에 예시 값 채우기
    - 덧셈, 뺄셈, 곱셈(A * B^T) 결과를 각각 C_add, C_sub, C_mul에 저장
    - 결과 출력 후 메모리 해제
*/
void ex06(void)
{
  int rows = 3;
  int cols = 5;

  int** A = alloc_matrix(rows, cols);
  int** B = alloc_matrix(rows, cols);
  int** C_add = alloc_matrix(rows, cols);
  int** C_sub = alloc_matrix(rows, cols);
  int** C_mul = alloc_matrix(rows, rows);  // 곱셈 결과는 rows x rows

  if (!A || !B || !C_add || !C_sub || !C_mul) {
    printf("[ex06] 메모리 할당 실패\n");
    free_matrix(A, rows);
    free_matrix(B, rows);
    free_matrix(C_add, rows);
    free_matrix(C_sub, rows);
    free_matrix(C_mul, rows);
    return;
  }

  // A는 1부터, B는 100부터 순차적인 값으로 채움
  set_sequential(A, rows, cols, 1);
  set_sequential(B, rows, cols, 100);

  print_matrix("A", A, rows, cols);
  print_matrix("B", B, rows, cols);

  // 덧셈, 뺄셈, 곱셈 수행
  add_matrix(A, B, C_add, rows, cols);
  sub_matrix(A, B, C_sub, rows, cols);
  mul_matrix_with_B_transpose(A, B, C_mul, rows, cols);

  print_matrix("A + B", C_add, rows, cols);
  print_matrix("A - B", C_sub, rows, cols);
  print_matrix("A * B^T", C_mul, rows, rows);

  free_matrix(A, rows);
  free_matrix(B, rows);
  free_matrix(C_add, rows);
  free_matrix(C_sub, rows);
  free_matrix(C_mul, rows);
}

/************************************************************
 * main: 여기서 실행할 예제를 직접 골라서 호출
 *
 * - 필요한 예제 함수만 주석 해제해서 사용하면 됨.
 ************************************************************/

int main(void)
{
  //ex01();   // 구조체 포인터 전달
  //ex02();   // binary 파일 쓰기/읽기
  //ex03();   // "All" 카운트
  //ex04();   // proverbs.txt <-> proverbs.dat <-> out.txt
  //ex05();   // 3x5 행렬 채우기
  //ex06();   // 행렬 연산

  return 0;
}