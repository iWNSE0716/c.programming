#include <stdio.h>

//#define _CRT_SECURE_NO_WARNINGS

int class1(void)
{
  FILE* fp = NULL;
  int c;
  fp = fopen("sample.txt", "rt");
  if (fp == NULL)
    printf("파일 열기 실패\n");
  else
    printf("파일 열기 성공\n");
  /*
  fputc('a', fp);
  fputc('b', fp);
  fputc('c', fp);
  */

  while ((c = fgetc(fp)) != EOF) {
    putchar(c);
  }

  fclose(fp);
  return 0;
}

#include <stdio.h>
#include <stdlib.h>

  int class2(void)
  {
    FILE* fp1, * fp2;
    char file1[100] = "sample.txt";
    char file2[100] = "out.txt";
    char buffer[100];
    // 첫번째 파일을 읽기 모드로 연다.
    if ((fp1 = fopen(file1, "r")) == NULL) {
      fprintf(stderr, "원본 파일 %s을 열 수 없습니다.\n", file1);
      exit(1);
    }

    // 두번째 파일을 쓰기 모드로 연다.
    if ((fp2 = fopen(file2, "w")) == NULL) {
      fprintf(stderr, "복사 파일 %s을 열 수 없습니다.\n", file2);
      exit(1);
    }
    // 첫번째 파일을 두번째 파일로 복사한다.
    while (fgets(buffer, 100, fp1) != NULL) {
      fputs(buffer, fp2);
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
  }

#include <stdio.h>
#include <string.h>
    int class3(void)
    {
      FILE* fp;
      char fname[128] = "proverbs.txt";
      char buffer[256];
      char word[256] = "man";
      int line_num = 0;
      // 파일을 읽기 모드로 연다.
      if ((fp = fopen(fname, "r")) == NULL)
      {
        fprintf(stderr, "파일 %s을 열 수 없습니다.\n", fname);
        exit(1);
      }
      while (fgets(buffer, 256, fp)) {
        line_num++;
        if (strstr(buffer, word)) {
          printf("%s: %d 단어 %s이 발견되었습니다.\n", fname,
            line_num, word);
        }
      }
      fclose(fp);
      return 0;
    }

#define _CRT_SECURE_NO_WARNINGS   // MSVC의 보안 경고 끄기

#include <stdio.h>
#include <string.h>   // strcmp, strlen, strcpy, strcat, ...
#include <ctype.h>    // isalpha, toupper, ...
#include <windows.h>  // (현재 예제에서는 사용 안 함, 통일성을 위해 포함)

    /*
      이 파일은 fread/fwrite를 이용한 4가지 예제를 모두 포함한 예시입니다.

      ex01   : 이미지 전체를 한 번에 읽어서 복사
      ex02   : ex02_A, ex02_B를 차례로 실행하는 래퍼 함수
      ex02_A : 1바이트씩 읽고 1바이트씩 쓰면서 복사
      ex02_B : 2차원 배열로 읽어서 그대로 복사

      scanf 대신, 파일 이름과 크기를 코드 안에 직접 넣었습니다.
    */

#define WIDTH  275   // 이미지 가로 픽셀 수
#define HEIGHT 183   // 이미지 세로 픽셀 수

    /******************** ex01: 전체를 한 번에 읽고 복사 ********************/

    // ex01: fread(), fwrite()를 사용해 한 번에 전체 이미지를 복사
    int ex01(void)
    {
      // 원본 이미지 파일(바이너리 모드로 읽기)
      FILE* fp = fopen("dog_275x183_8bits.raw", "rb");
      // 복사본 이미지 파일(바이너리 모드로 쓰기)
      FILE* fout = fopen("out_ex01.raw", "wb");

      // 파일 열기 실패 여부 확인
      if (fp == NULL || fout == NULL) {
        printf("[ex01] 파일 열기 실패\n");
        if (fp != NULL) fclose(fp);
        if (fout != NULL) fclose(fout);
        return 1;
      }

      // 전체 이미지를 담을 1차원 버퍼
      unsigned char buffer[WIDTH * HEIGHT];

      // 전체 바이트 수
      size_t total_size = WIDTH * HEIGHT;

      // fread로 전체 이미지를 한 번에 읽기
      size_t byte_read = fread(buffer, sizeof(unsigned char), total_size, fp);
      if (byte_read == 0) {
        printf("[ex01] 파일 읽기 실패\n");
        fclose(fp);
        fclose(fout);
        return 1;
      }

      // 읽어온 만큼 그대로 fwrite로 쓰기
      size_t byte_write = fwrite(buffer, sizeof(unsigned char), byte_read, fout);
      if (byte_read != byte_write) {
        printf("[ex01] 파일 쓰기 실패\n");
        fclose(fp);
        fclose(fout);
        return 1;
      }

      printf("[ex01] 복사 완료 (%zu 바이트)\n", byte_write);

      fclose(fp);
      fclose(fout);

      return 0;
    }

    /******************** ex02_A: 1바이트씩 읽고 1바이트씩 쓰기 ********************/

    // ex02_A: 이미지 데이터를 1바이트씩 읽고, 1바이트씩 쓰면서 복사
    int ex02_A(void)
    {
      FILE* fp = fopen("dog_275x183_8bits.raw", "rb");   // 원본 파일
      FILE* fout = fopen("out_ex02_A.raw", "wb");        // 복사본 파일

      if (fp == NULL || fout == NULL) {
        printf("[ex02_A] 파일 열기 실패\n");
        if (fp != NULL) fclose(fp);
        if (fout != NULL) fclose(fout);
        return 1;
      }

      // 전체 이미지를 담을 1차원 버퍼
      unsigned char buffer[WIDTH * HEIGHT];

      unsigned char data;  // 1바이트씩 임시로 저장할 변수
      int i = 0;           // buffer 인덱스

      // ---------- 1바이트씩 읽어서 buffer에 저장 ----------
      while (1) {
        // data의 주소(&data)로 1바이트를 읽어온다
        size_t byte_read = fread(&data, sizeof(unsigned char), 1, fp);

        // fread가 0을 반환하면 더 이상 읽을 데이터가 없음(EOF)
        if (byte_read == 0) {
          break;
        }

        buffer[i] = data;  // 읽은 1바이트를 buffer에 넣는다
        i++;               // 인덱스를 1 증가

        // 혹시라도 파일이 예상보다 크더라도 버퍼를 넘지 않게 방어
        if (i >= WIDTH * HEIGHT) {
          break;
        }
      }

      int total_bytes = i;  // 실제로 읽은 바이트 수

      // ---------- buffer에 있는 내용을 1바이트씩 쓰기 ----------
      i = 0;
      while (i < total_bytes) {
        // buffer[i]의 주소에서 1바이트를 파일에 쓴다
        size_t byte_write = fwrite(&buffer[i], sizeof(unsigned char), 1, fout);

        if (byte_write == 0) {
          printf("[ex02_A] 파일 쓰기 중 오류 발생\n");
          break;
        }
        i++;
      }

      printf("[ex02_A] 복사 완료 (%d 바이트)\n", total_bytes);

      fclose(fp);
      fclose(fout);

      return 0;
    }

    /******************** ex02_B: 2차원 배열로 읽고 복사 ********************/

    // ex02_B: 2차원 배열(행렬)로 이미지 데이터를 읽고 그대로 복사
    int ex02_B(void)
    {
      FILE* fp = fopen("dog_275x183_8bits.raw", "rb");   // 원본 파일
      FILE* fout = fopen("out_ex02_B.raw", "wb");        // 복사본 파일

      if (fp == NULL || fout == NULL) {
        printf("[ex02_B] 파일 열기 실패\n");
        if (fp != NULL) fclose(fp);
        if (fout != NULL) fclose(fout);
        return 1;
      }

      // 2차원 배열: [세로][가로]
      // buffer[y][x] 형식으로 접근
      unsigned char buffer[HEIGHT][WIDTH];

      size_t total_size = WIDTH * HEIGHT;  // 전체 바이트 수

      // ---------- 파일에서 2차원 배열로 한 번에 읽기 ----------
      // 2차원 배열이지만 메모리 배치는 연속적이므로
      // 전체 크기만큼 fread로 한 번에 읽을 수 있다
      size_t byte_read = fread(buffer, sizeof(unsigned char), total_size, fp);

      if (byte_read != total_size) {
        printf("[ex02_B] 파일 읽기 오류 또는 크기 부족 (읽은 바이트: %zu)\n", byte_read);
        fclose(fp);
        fclose(fout);
        return 1;
      }

      // (필요하면 여기서 buffer[y][x]로 픽셀 처리 가능)

      // ---------- 2차원 배열 내용을 한 번에 파일로 쓰기 ----------
      size_t byte_write = fwrite(buffer, sizeof(unsigned char), total_size, fout);

      if (byte_write != total_size) {
        printf("[ex02_B] 파일 쓰기 오류 (쓴 바이트: %zu)\n", byte_write);
        fclose(fp);
        fclose(fout);
        return 1;
      }

      printf("[ex02_B] 복사 완료 (%zu 바이트)\n", byte_write);

      fclose(fp);
      fclose(fout);

      return 0;
    }

    /******************** ex02: ex02_A, ex02_B를 차례로 실행 ********************/

    int ex02(void)
    {
      printf("\n[ex02] ex02_A 실행\n");
      ex02_A();

      printf("\n[ex02] ex02_B 실행\n");
      ex02_B();

      return 0;
    }

    /******************** ex03: 1차원 배열로 읽어서 색 반전 후 저장 ********************/

    int ex03(void)
    {
      // 원본 이미지 파일 (바이너리 읽기 모드)
      FILE* fp = fopen("dog_275x183_8bits.raw", "rb");
      // 색 반전 결과를 저장할 파일
      FILE* fout = fopen("out_ex03_invert.raw", "wb");

      if (fp == NULL || fout == NULL) {
        printf("[ex03] 파일 열기 실패\n");
        if (fp != NULL) fclose(fp);
        if (fout != NULL) fclose(fout);
        return 1;
      }

      // 전체 이미지를 저장할 1차원 버퍼
      unsigned char buffer[WIDTH * HEIGHT];

      size_t total_size = WIDTH * HEIGHT;  // 전체 바이트 수

      // ---------- 1차원 배열로 전체 이미지 읽기 ----------
      size_t byte_read = fread(buffer, sizeof(unsigned char), total_size, fp);
      if (byte_read != total_size) {
        printf("[ex03] 파일 읽기 오류 또는 크기 부족 (읽은 바이트: %zu)\n", byte_read);
        fclose(fp);
        fclose(fout);
        return 1;
      }

      // ---------- 색 반전 처리 ----------
      /*
         8비트(1바이트) 그레이스케일이므로 값의 범위는 0~255.
         2^8 = 256이므로 unsigned char의 최대 값은 255.
         원래 값 = v 라면, 반전 값 = 255 - v
      */
      for (size_t i = 0; i < total_size; i++) {
        buffer[i] = 255 - buffer[i];
      }

      // ---------- 반전된 결과를 파일로 저장 ----------
      size_t byte_write = fwrite(buffer, sizeof(unsigned char), total_size, fout);
      if (byte_write != total_size) {
        printf("[ex03] 파일 쓰기 오류 (쓴 바이트: %zu)\n", byte_write);
        fclose(fp);
        fclose(fout);
        return 1;
      }

      printf("[ex03] 색 반전 완료 (%zu 바이트)\n", byte_write);

      fclose(fp);
      fclose(fout);

      return 0;
    }

    /*
  ex04.
  이미지 데이터를 읽고 이를 상하/좌우 flip 하는 코드입니다.

  A. 1차원 배열로 읽어서 좌우 flip
  B. 2차원 배열로 읽어서 좌우 flip
  C. 1차원 배열로 읽어서 상하 flip
  D. 2차원 배열로 읽어서 상하 flip

  8비트 그레이스케일 RAW 이미지 (WIDTH x HEIGHT)라고 가정합니다.
*/

#define WIDTH  275   // 가로 픽셀 수
#define HEIGHT 183   // 세로 픽셀 수

/******************** A. 1차원 배열로 읽어서 좌우 flip ********************/
/*
   1차원 인덱스: index = y * WIDTH + x

   좌우(수평) 플립:
     같은 y(행)에서 x 를 (WIDTH-1-x)와 교환
*/
    int ex04_A(void)
    {
      FILE* fp = fopen("dog_275x183_8bits.raw", "rb");
      FILE* fout = fopen("out_ex04_A_lr_1d.raw", "wb");

      if (fp == NULL || fout == NULL) {
        printf("[ex04_A] 파일 열기 실패\n");
        if (fp != NULL) fclose(fp);
        if (fout != NULL) fclose(fout);
        return 1;
      }

      unsigned char buffer[WIDTH * HEIGHT];
      size_t total_size = WIDTH * HEIGHT;

      // 전체 읽기
      size_t byte_read = fread(buffer, sizeof(unsigned char), total_size, fp);
      if (byte_read != total_size) {
        printf("[ex04_A] 파일 읽기 오류 또는 크기 부족 (읽은 바이트: %zu)\n", byte_read);
        fclose(fp);
        fclose(fout);
        return 1;
      }

      // 좌우 flip
      for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH / 2; x++) {
          int left_index = y * WIDTH + x;
          int right_index = y * WIDTH + (WIDTH - 1 - x);

          unsigned char temp = buffer[left_index];
          buffer[left_index] = buffer[right_index];
          buffer[right_index] = temp;
        }
      }

      // 결과 저장
      size_t byte_write = fwrite(buffer, sizeof(unsigned char), total_size, fout);
      if (byte_write != total_size) {
        printf("[ex04_A] 파일 쓰기 오류 (쓴 바이트: %zu)\n", byte_write);
        fclose(fp);
        fclose(fout);
        return 1;
      }

      printf("[ex04_A] 1D 좌우 flip 완료 (%zu 바이트)\n", byte_write);

      fclose(fp);
      fclose(fout);
      return 0;
    }

    /******************** B. 2차원 배열로 읽어서 좌우 flip ********************/
    /*
       2차원 인덱스: buffer[y][x]

       좌우(수평) 플립:
         같은 y(행)에서 x 와 (WIDTH-1-x)를 교환
    */
    int ex04_B(void)
    {
      FILE* fp = fopen("dog_275x183_8bits.raw", "rb");
      FILE* fout = fopen("out_ex04_B_lr_2d.raw", "wb");

      if (fp == NULL || fout == NULL) {
        printf("[ex04_B] 파일 열기 실패\n");
        if (fp != NULL) fclose(fp);
        if (fout != NULL) fclose(fout);
        return 1;
      }

      unsigned char buffer[HEIGHT][WIDTH];
      size_t total_size = WIDTH * HEIGHT;

      // 전체 읽기 (2D 배열이지만 메모리는 연속이라 한 번에 읽을 수 있음)
      size_t byte_read = fread(buffer, sizeof(unsigned char), total_size, fp);
      if (byte_read != total_size) {
        printf("[ex04_B] 파일 읽기 오류 또는 크기 부족 (읽은 바이트: %zu)\n", byte_read);
        fclose(fp);
        fclose(fout);
        return 1;
      }

      // 좌우 flip (행마다 좌우를 뒤집기)
      for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH / 2; x++) {
          unsigned char temp = buffer[y][x];
          buffer[y][x] = buffer[y][WIDTH - 1 - x];
          buffer[y][WIDTH - 1 - x] = temp;
        }
      }

      // 결과 저장
      size_t byte_write = fwrite(buffer, sizeof(unsigned char), total_size, fout);
      if (byte_write != total_size) {
        printf("[ex04_B] 파일 쓰기 오류 (쓴 바이트: %zu)\n", byte_write);
        fclose(fp);
        fclose(fout);
        return 1;
      }

      printf("[ex04_B] 2D 좌우 flip 완료 (%zu 바이트)\n", byte_write);

      fclose(fp);
      fclose(fout);
      return 0;
    }

    /******************** C. 1차원 배열로 읽어서 상하 flip ********************/
    /*
       1차원 인덱스: index = y * WIDTH + x

       상하(수직) 플립:
         같은 x(열)에서 y 와 (HEIGHT-1-y)를 교환
    */
    int ex04_C(void)
    {
      FILE* fp = fopen("dog_275x183_8bits.raw", "rb");
      FILE* fout = fopen("out_ex04_C_ud_1d.raw", "wb");

      if (fp == NULL || fout == NULL) {
        printf("[ex04_C] 파일 열기 실패\n");
        if (fp != NULL) fclose(fp);
        if (fout != NULL) fclose(fout);
        return 1;
      }

      unsigned char buffer[WIDTH * HEIGHT];
      size_t total_size = WIDTH * HEIGHT;

      // 전체 읽기
      size_t byte_read = fread(buffer, sizeof(unsigned char), total_size, fp);
      if (byte_read != total_size) {
        printf("[ex04_C] 파일 읽기 오류 또는 크기 부족 (읽은 바이트: %zu)\n", byte_read);
        fclose(fp);
        fclose(fout);
        return 1;
      }

      // 상하 flip
      for (int y = 0; y < HEIGHT / 2; y++) {
        int opposite_y = HEIGHT - 1 - y;  // 서로 교환할 반대쪽 행

        for (int x = 0; x < WIDTH; x++) {
          int top_index = y * WIDTH + x;
          int bottom_index = opposite_y * WIDTH + x;

          unsigned char temp = buffer[top_index];
          buffer[top_index] = buffer[bottom_index];
          buffer[bottom_index] = temp;
        }
      }

      // 결과 저장
      size_t byte_write = fwrite(buffer, sizeof(unsigned char), total_size, fout);
      if (byte_write != total_size) {
        printf("[ex04_C] 파일 쓰기 오류 (쓴 바이트: %zu)\n", byte_write);
        fclose(fp);
        fclose(fout);
        return 1;
      }

      printf("[ex04_C] 1D 상하 flip 완료 (%zu 바이트)\n", byte_write);

      fclose(fp);
      fclose(fout);
      return 0;
    }

    /******************** D. 2차원 배열로 읽어서 상하 flip ********************/
    /*
       2차원 인덱스: buffer[y][x]

       상하(수직) 플립:
         같은 x(열)에서 y 와 (HEIGHT-1-y)를 교환
    */
    int ex04_D(void)
    {
      FILE* fp = fopen("dog_275x183_8bits.raw", "rb");
      FILE* fout = fopen("out_ex04_D_ud_2d.raw", "wb");

      if (fp == NULL || fout == NULL) {
        printf("[ex04_D] 파일 열기 실패\n");
        if (fp != NULL) fclose(fp);
        if (fout != NULL) fclose(fout);
        return 1;
      }

      unsigned char buffer[HEIGHT][WIDTH];
      size_t total_size = WIDTH * HEIGHT;

      // 전체 읽기
      size_t byte_read = fread(buffer, sizeof(unsigned char), total_size, fp);
      if (byte_read != total_size) {
        printf("[ex04_D] 파일 읽기 오류 또는 크기 부족 (읽은 바이트: %zu)\n", byte_read);
        fclose(fp);
        fclose(fout);
        return 1;
      }

      // 상하 flip (위/아래 행을 서로 교환)
      for (int y = 0; y < HEIGHT / 2; y++) {
        int opposite_y = HEIGHT - 1 - y;
        for (int x = 0; x < WIDTH; x++) {
          unsigned char temp = buffer[y][x];
          buffer[y][x] = buffer[opposite_y][x];
          buffer[opposite_y][x] = temp;
        }
      }

      // 결과 저장
      size_t byte_write = fwrite(buffer, sizeof(unsigned char), total_size, fout);
      if (byte_write != total_size) {
        printf("[ex04_D] 파일 쓰기 오류 (쓴 바이트: %zu)\n", byte_write);
        fclose(fp);
        fclose(fout);
        return 1;
      }

      printf("[ex04_D] 2D 상하 flip 완료 (%zu 바이트)\n", byte_write);

      fclose(fp);
      fclose(fout);
      return 0;
    }

    /******************** ex04: 네 가지를 한 번에 호출 (선택사항) ********************/

    int ex04(void)
    {
      printf("\n[ex04] A: 1D 좌우 flip\n");
      ex04_A();

      printf("\n[ex04] B: 2D 좌우 flip\n");
      ex04_B();

      printf("\n[ex04] C: 1D 상하 flip\n");
      ex04_C();

      printf("\n[ex04] D: 2D 상하 flip\n");
      ex04_D();

      return 0;
    }

    /*
  ex05.
  CSV(comma separated values) 파일을 생성하는 예제입니다.

  - "out.csv" 파일을 생성
  - 쉼표(,)로 데이터를 구분해서 저장
  - 생성된 파일을 엑셀로 열면 자동으로 셀이 나누어져 보입니다.

  저장할 데이터 (문제에서 제시한 값):

    ID,A,B,C
    1,56,49,43
    2,7,5,36
    3,5,92,22
*/

/******************** ex05: CSV 파일 생성 ********************/

    int ex05(void)
    {
      // 쓰기 모드로 CSV 파일 열기 (텍스트 모드)
      FILE* fp = fopen("out.csv", "w");
      if (fp == NULL) {
        printf("[ex05] 파일 열기 실패\n");
        return 1;
      }

      // 1행: 헤더(열 이름)
      fprintf(fp, "ID,A,B,C\n");

      // 2행 이후: 실제 데이터(문제에서 준 값)
      fprintf(fp, "1,56,49,43\n");
      fprintf(fp, "2,7,5,36\n");
      fprintf(fp, "3,5,92,22\n");

      fclose(fp);

      printf("[ex05] CSV 파일 생성 완료: out.csv\n");
      printf("엑셀에서 out.csv 파일을 열어 보세요.\n");

      return 0;
    }

    /*
      ex06.
      fgets 함수를 이용하여 csv 파일을 읽고,
      각 줄의 점수들(A,B,C)을 읽어서

        - 정수 배열에 저장
        - 총합과 평균을 계산
        - 새 CSV 파일("out_ex06.csv")로 저장

      조건:
        - 편의를 위해, 여기서는 out.csv를 그대로 읽되
          첫 줄(헤더: ID,A,B,C)은 건너뛰고
          다음 줄들만 처리한다고 가정.
        - 한 줄의 형식: ID,A,B,C
          (예: 1,56,49,43)
        - data[0], data[1], data[2] : 각각 점수 (A, B, C)
          data[3] : 총점
          data[4] : 평균
    */

    /******************** 보조: 공백/개행 제거 함수 ********************/
    void rstrip(char* s)
    {
      int len = (int)strlen(s);
      // 문자열 끝에서부터 개행/공백 제거
      while (len > 0 &&
        (s[len - 1] == '\n' || s[len - 1] == '\r' ||
          isspace((unsigned char)s[len - 1]))) {
        s[len - 1] = '\0';
        len--;
      }
    }

    /******************** ex06: CSV 읽고 총합/평균 계산 ********************/

    int ex06(void)
    {
      // ex05에서 만든 out.csv를 읽어서 사용
      FILE* fp_in = fopen("out.csv", "r");      // 원본 점수 파일
      FILE* fp_out = fopen("out_ex06.csv", "w"); // 결과 파일

      if (fp_in == NULL || fp_out == NULL) {
        printf("[ex06] 파일 열기 실패\n");
        if (fp_in != NULL) fclose(fp_in);
        if (fp_out != NULL) fclose(fp_out);
        return 1;
      }

      char line[256];

      // 결과 파일의 헤더(첫 줄) 쓰기
      // A,B,C,Total,Average
      fprintf(fp_out, "A,B,C,Total,Average\n");

      // ---------- 1. 첫 줄(ID,A,B,C)은 읽어서 버림 ----------
      if (fgets(line, sizeof(line), fp_in) == NULL) {
        printf("[ex06] 입력 파일이 비어 있습니다.\n");
        fclose(fp_in);
        fclose(fp_out);
        return 1;
      }

      // ---------- 2. 나머지 줄(데이터 부분) 처리 ----------
      while (fgets(line, sizeof(line), fp_in)) {
        char* token;
        int data[5] = { 0 };  // 0,1,2: 점수(A,B,C), 3:총점, 4:평균
        int idx = 0;

        // 줄 끝 개행 제거
        rstrip(line);

        // 빈 줄이면 건너뛰기
        if (line[0] == '\0') {
          continue;
        }

        /*
          line 예: "1,56,49,43"
          첫 토큰: ID
          둘째~넷째 토큰: A, B, C
        */

        // ---------- A. strtok으로 토큰 분리 ----------
        token = strtok(line, ",");   // 첫 번째 토큰: ID
        if (token == NULL) continue;

        // ID는 여기서는 사용하지 않고, A,B,C만 쓸 거라서
        // 그냥 한 번 읽고 버림
        // int id = atoi(token);  // 필요하면 이렇게 저장

        // 다음 토큰부터 A,B,C 점수
        token = strtok(NULL, ",");
        while (token != NULL && idx < 3) {
          // ---------- B. 문자열을 int로 변환해서 배열에 저장 ----------
          int score = atoi(token);   // 예: "56" -> 56
          data[idx] = score;         // data[0], data[1], data[2]
          idx++;

          token = strtok(NULL, ",");
        }

        // A,B,C 점수가 3개 미만이면 잘못된 줄이므로 건너뜀
        if (idx < 3) {
          printf("[ex06] 경고: 점수가 3개 미만인 줄을 건너뜀\n");
          continue;
        }

        // ---------- C. 총점(index 3), 평균(index 4) 계산 ----------
        int sum = data[0] + data[1] + data[2];
        int avg = sum / 3;    // 정수 나눗셈으로 평균

        data[3] = sum;
        data[4] = avg;

        // ---------- D. 결과를 새 CSV 파일로 쓰기 ----------
        // 형식: A,B,C,Total,Average
        fprintf(fp_out, "%d,%d,%d,%d,%d\n",
          data[0], data[1], data[2], data[3], data[4]);
      }

      fclose(fp_in);
      fclose(fp_out);

      printf("[ex06] 처리 완료. 결과 파일: out_ex06.csv\n");

      return 0;
    }

    /******************** main: 실행할 예제 선택 ********************/

    int main(void)
    {
      // 필요할 때 주석을 조절해서 원하는 예제만 실행해도 됩니다.
      //ex01();    // 전체를 한 번에 읽고 복사
      //ex02();    // ex02_A(1바이트씩), ex02_B(2차원 배열)를 순서대로 실행
      //ex02_A();  // 개별 실행도 가능
      //ex02_B();
      //ex03();    // 색 반전 예제 실행
      //ex04();    // 네 가지 모두 실행
      //ex04_A();
      //ex04_B();
      //ex04_C();
      //ex04_D();
      //ex05();  // CSV 생성 예제 실행
      //ex06();  // CSV 읽어서 총합/평균 계산 후 새 파일로 저장
      return 0;
    }