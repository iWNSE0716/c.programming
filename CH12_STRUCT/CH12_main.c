#define _CRT_SECURE_NO_WARNINGS   // MSVC의 보안 경고(예: snprintf, strtok) 끄기

#include <stdio.h>
#include <string.h>   // strcmp, strlen, strcpy, strcat, ...
#include <ctype.h>    // isalpha, toupper, ...
#include <windows.h>  // ex07: 파일 검색용 WinAPI

/*
  이 파일은 아래 7가지 예제를 모두 포함한 예시입니다.

  ex01 : 복소수 구조체 + 사칙연산 (struct 사용)
  ex02 : ex01을 typedef로 간단하게 표현
  ex03 : 점의 좌표 예시를 만들어 몇 사분면인지 판별
  ex04 : 원 구조체(Circle) 정의, 둘레/면적을 "정수"로 계산해서 반환
  ex05 : 포인터를 이용해 원 구조체 안에 둘레/면적을 저장하는 함수
  ex06 : 문자/문자열 관련 표준 라이브러리 함수(ctype.h, string.h) 사용 예시
  ex07 : 특정 디렉터리의 파일/폴더 목록 출력 (Windows 전용)

  scanf 대신, 각각 “임의의 값(예시 값)”을 코드 안에 직접 넣었습니다.
*/

/******************** ex01: struct complex와 사칙연산 ********************/

// 복소수 구조체 정의
struct complex {
  double real;  // 실수부
  double imag;  // 허수부
};

// 덧셈: (a+bi) + (c+di) = (a+c) + (b+d)i
struct complex complex_add(struct complex c1, struct complex c2) {
  struct complex r;
  r.real = c1.real + c2.real;
  r.imag = c1.imag + c2.imag;
  return r;
}

// 뺄셈: (a+bi) - (c+di) = (a-c) + (b-d)i
struct complex complex_sub(struct complex c1, struct complex c2) {
  struct complex r;
  r.real = c1.real - c2.real;
  r.imag = c1.imag - c2.imag;
  return r;
}

// 곱셈: (a+bi)(c+di) = (ac - bd) + (ad + bc)i
struct complex complex_mul(struct complex c1, struct complex c2) {
  struct complex r;
  r.real = c1.real * c2.real - c1.imag * c2.imag;
  r.imag = c1.real * c2.imag + c1.imag * c2.real;
  return r;
}

// 나눗셈: (a+bi)/(c+di) = ((ac+bd) + (bc-ad)i) / (c^2 + d^2)
struct complex complex_div(struct complex c1, struct complex c2) {
  struct complex r;
  double denom;

  denom = c2.real * c2.real + c2.imag * c2.imag; // 분모: c^2 + d^2
  r.real = (c1.real * c2.real + c1.imag * c2.imag) / denom;
  r.imag = (c1.imag * c2.real - c1.real * c2.imag) / denom;
  return r;
}

// ex01 테스트용 (예시 값 사용)
int ex01(void) {
  struct complex c1 = { 1.0, 2.0 };   // 1 + 2i
  struct complex c2 = { 3.0, -1.0 };  // 3 - 1i

  struct complex a = complex_add(c1, c2);
  struct complex s = complex_sub(c1, c2);
  struct complex m = complex_mul(c1, c2);
  struct complex d = complex_div(c1, c2);

  printf("[ex01] c1 = %.2f + %.2fi, c2 = %.2f + %.2fi\n",
    c1.real, c1.imag, c2.real, c2.imag);
  printf("[ex01] add : %.2f + %.2fi\n", a.real, a.imag);
  printf("[ex01] sub : %.2f + %.2fi\n", s.real, s.imag);
  printf("[ex01] mul : %.2f + %.2fi\n", m.real, m.imag);
  printf("[ex01] div : %.2f + %.2fi\n", d.real, d.imag);

  return 0;
}

/******************** ex02: typedef로 간결하게 변경 ********************/

typedef struct {
  double real;  // 실수부
  double imag;  // 허수부
} Complex;

// 덧셈
Complex complex_add2(Complex c1, Complex c2) {
  Complex r;
  r.real = c1.real + c2.real;
  r.imag = c1.imag + c2.imag;
  return r;
}

// 뺄셈
Complex complex_sub2(Complex c1, Complex c2) {
  Complex r;
  r.real = c1.real - c2.real;
  r.imag = c1.imag - c2.imag;
  return r;
}

// 곱셈
Complex complex_mul2(Complex c1, Complex c2) {
  Complex r;
  r.real = c1.real * c2.real - c1.imag * c2.imag;
  r.imag = c1.real * c2.imag + c1.imag * c2.real;
  return r;
}

// 나눗셈
Complex complex_div2(Complex c1, Complex c2) {
  Complex r;
  double denom;

  denom = c2.real * c2.real + c2.imag * c2.imag;
  r.real = (c1.real * c2.real + c1.imag * c2.imag) / denom;
  r.imag = (c1.imag * c2.real - c1.real * c2.imag) / denom;
  return r;
}

// ex02 테스트용 (예시 값 사용)
int ex02(void) {
  Complex c1 = { 2.0, 1.0 };
  Complex c2 = { -1.0, 3.0 };

  Complex a = complex_add2(c1, c2);
  Complex s = complex_sub2(c1, c2);
  Complex m = complex_mul2(c1, c2);
  Complex d = complex_div2(c1, c2);

  printf("[ex02] c1 = %.2f + %.2fi, c2 = %.2f + %.2fi\n",
    c1.real, c1.imag, c2.real, c2.imag);
  printf("[ex02] add2 : %.2f + %.2fi\n", a.real, a.imag);
  printf("[ex02] sub2 : %.2f + %.2fi\n", s.real, s.imag);
  printf("[ex02] mul2 : %.2f + %.2fi\n", m.real, m.imag);
  printf("[ex02] div2 : %.2f + %.2fi\n", d.real, d.imag);

  return 0;
}

/******************** ex03: 사분면 판별 (예시 좌표 사용) ********************/

typedef struct {
  int x;
  int y;
} Point;

// 사분면 판별 함수
int quadrant(Point p) {
  if (p.x > 0 && p.y > 0) {
    return 1;
  }
  else if (p.x < 0 && p.y > 0) {
    return 2;
  }
  else if (p.x < 0 && p.y < 0) {
    return 3;
  }
  else if (p.x > 0 && p.y < 0) {
    return 4;
  }
  else {
    return 0;  // x==0 또는 y==0 인 경우 (축 위)
  }
}

// ex03 테스트용 (scanf 없이 여러 예시 점을 사용)
int ex03(void) {
  Point p1 = { 3,  4 }; // 1사분면
  Point p2 = { -5,  2 }; // 2사분면
  Point p3 = { -1, -7 }; // 3사분면
  Point p4 = { 6, -3 }; // 4사분면
  Point p5 = { 0,  5 }; // y축 위
  int q;

  q = quadrant(p1);
  printf("[ex03] (%d, %d) -> %d사분면\n", p1.x, p1.y, q);

  q = quadrant(p2);
  printf("[ex03] (%d, %d) -> %d사분면\n", p2.x, p2.y, q);

  q = quadrant(p3);
  printf("[ex03] (%d, %d) -> %d사분면\n", p3.x, p3.y, q);

  q = quadrant(p4);
  printf("[ex03] (%d, %d) -> %d사분면\n", p4.x, p4.y, q);

  q = quadrant(p5);
  if (q == 0) {
    printf("[ex03] (%d, %d) -> 좌표축 위\n", p5.x, p5.y);
  }

  return 0;
}

/******************** ex04: Circle 구조체, 둘레/면적 함수 ********************/
/*
  문제에서 제시한 구조체:
  typedef struct {
      int radius; //반지름
      Point x,y;
  } Circle;

  여기서는 x만 중심 좌표로 사용하고, y는 사용하지 않습니다.
  둘레/면적은 정수 근사로 계산:
    - 둘레 ≈ 2 * 3 * r = 6r
    - 면적 ≈ 3 * r^2
*/

typedef struct {
  int radius; // 반지름
  Point x;    // 중심 좌표 (사용)
  Point y;    // (사용하지 않음, 문제 요구 때문에 존재)
} Circle;

// 둘레를 int로 근사하여 반환
int permeter_return(Circle c) {
  int per;
  per = 6 * c.radius; // 2 * 3 * r
  return per;
}

// 면적을 int로 근사하여 반환
int area_return(Circle c) {
  int area;
  area = 3 * c.radius * c.radius; // 3 * r^2
  return area;
}

// ex04 테스트용 (예시 값 사용)
int ex04(void) {
  Circle c;
  int per;
  int area;

  // 중심 좌표 예시
  c.x.x = 0;
  c.x.y = 0;
  // c.y는 사용하지 않음
  c.radius = 5;

  per = permeter_return(c);
  area = area_return(c);

  printf("[ex04] 중심=(%d, %d), r=%d\n", c.x.x, c.x.y, c.radius);
  printf("둘레(정수 근사): %d\n", per);
  printf("면적(정수 근사): %d\n", area);

  return 0;
}

/******************** ex05: 포인터로 Circle2 구조체 값 채우기 ********************/
/*
  문제에서 새로 정의한 구조체:
  typedef struct {
      int radius;   //반지름
      int permeter; // 둘레
      int area;     // 면적
      Point x,y;
  } Circle;

  여기서는 이름이 겹치지 않도록 Circle2 를 사용.
*/

typedef struct {
  int radius;   // 반지름
  int permeter; // 둘레
  int area;     // 면적
  Point x;      // 중심 좌표 (사용)
  Point y;      // (사용하지 않음)
} Circle2;

// 둘레 계산해서 구조체에 저장 후, 그 값을 반환
int calc_permeter(Circle2* c) {
  int result;
  result = 6 * (*c).radius;   // 2 * 3 * r
  (*c).permeter = result;     // 구조체 안에 저장
  return result;
}

// 면적 계산해서 구조체에 저장 후, 그 값을 반환
int calc_area(Circle2* c) {
  int result;
  result = 3 * (*c).radius * (*c).radius; // 3 * r^2
  (*c).area = result;
  return result;
}

// ex05 테스트용 (예시 값 사용)
int ex05(void) {
  Circle2 c;
  int per;
  int area;

  // 중심 좌표 예시
  c.x.x = 1;
  c.x.y = 2;
  // c.y는 사용하지 않음

  // 반지름 예시
  c.radius = 4;

  per = calc_permeter(&c); // &c : c의 주소
  area = calc_area(&c);

  printf("[ex05] 중심=(%d, %d), r=%d\n", c.x.x, c.x.y, c.radius);
  printf("둘레(구조체에 저장된 값): %d\n", c.permeter);
  printf("면적(구조체에 저장된 값): %d\n", c.area);

  return 0;
}

/******************** ex06: 문자/문자열 관련 표준 함수 예시 ********************/

int ex06(void) {
  /* ---------- 1. 문자 처리 함수들 (ctype.h) 테스트 ---------- */
  char c1 = 'A';
  char c2 = 'g';
  char c3 = '5';
  char c4 = ' ';
  char c5 = '\n';
  char c6 = '#';
  char c7 = 7;     // 벨(제어문자), 제어 문자 예시

  printf("\n=== [ex06] ctype.h 문자 판별 함수 예시 ===\n");

  printf("문자 '%c': isalpha = %d, isupper = %d, islower = %d, isdigit = %d\n",
    c1, isalpha((unsigned char)c1), isupper((unsigned char)c1),
    islower((unsigned char)c1), isdigit((unsigned char)c1));

  printf("문자 '%c': isalpha = %d, isupper = %d, islower = %d, isdigit = %d\n",
    c2, isalpha((unsigned char)c2), isupper((unsigned char)c2),
    islower((unsigned char)c2), isdigit((unsigned char)c2));

  printf("문자 '%c': isdigit = %d, isalnum = %d, isxdigit = %d\n",
    c3, isdigit((unsigned char)c3), isalnum((unsigned char)c3),
    isxdigit((unsigned char)c3));

  printf("문자 ' ' (공백): isspace = %d, isprint = %d\n",
    isspace((unsigned char)c4), isprint((unsigned char)c4));

  printf("문자 '\\n' (줄바꿈): isspace = %d, iscntrl = %d\n",
    isspace((unsigned char)c5), iscntrl((unsigned char)c5));

  printf("문자 '%c': ispunct = %d, isprint = %d\n",
    c6, ispunct((unsigned char)c6), isprint((unsigned char)c6));

  printf("문자 '\\a' (벨, 제어문자): iscntrl = %d, isascii = %d\n",
    iscntrl((unsigned char)c7), isascii((unsigned char)c7));

  /* ---------- 2. 문자 변환 함수들 (toupper, tolower, toascii) ---------- */
  char c8 = 'a';
  char c9 = 'Z';

  printf("\n=== [ex06] ctype.h 문자 변환 함수 예시 ===\n");
  printf("'%c' -> toupper -> '%c'\n", c8, (char)toupper((unsigned char)c8));
  printf("'%c' -> tolower -> '%c'\n", c9, (char)tolower((unsigned char)c9));

  // toascii: 상위 비트를 제거해서 0~127 범위의 값으로 만듦
  unsigned char c10 = 200;
  printf("문자 코드 %d -> toascii -> %d\n", c10, toascii(c10));

  /* ---------- 3. 문자열 처리 함수들 (string.h) ---------- */
  char s1[100] = "Hello";
  char s2[100] = "World";
  char s3[100];
  char s4[100] = "HelloWorld";
  char s5[100] = "Hello C programming";
  char* p;

  printf("\n=== [ex06] string.h 문자열 함수 예시 ===\n");

  // strlen
  printf("strlen(\"%s\") = %u\n", s1, (unsigned)strlen(s1));

  // strcpy: s3 <- s1
  strcpy(s3, s1);
  printf("strcpy(s3, \"%s\") -> s3 = \"%s\"\n", s1, s3);

  // strcat: s1 끝에 s2 붙이기
  strcat(s1, s2);
  printf("strcat(\"Hello\", \"World\") -> \"%s\"\n", s1);

  // strcmp: 문자열 비교
  printf("strcmp(\"%s\", \"%s\") = %d\n", s1, s4, strcmp(s1, s4));
  printf("strcmp(\"Hello\", \"Hello\") = %d\n", strcmp("Hello", "Hello"));

  // strncpy: 앞에서부터 n글자만 복사
  strncpy(s3, "ABCDEFG", 3);
  s3[3] = '\0';  // 직접 문자열 끝 표시
  printf("strncpy(s3, \"ABCDEFG\", 3) -> \"%s\"\n", s3);

  // strncat: 앞에서부터 n글자만 덧붙이기
  strcpy(s3, "Hi");
  strncat(s3, "ABCDEFG", 2);  // "HiAB"
  printf("strncat(\"Hi\", \"ABCDEFG\", 2) -> \"%s\"\n", s3);

  // strncmp: 앞에서부터 n글자만 비교
  printf("strncmp(\"Hello\", \"Helium\", 3) = %d\n", strncmp("Hello", "Helium", 3));
  printf("strncmp(\"Hello\", \"Helium\", 4) = %d\n", strncmp("Hello", "Helium", 4));

  // strchr: 문자열 안에서 문자 찾기
  p = strchr(s5, 'C');
  if (p != NULL) {
    printf("strchr(\"%s\", 'C') -> \"%s\" (처음 찾은 위치부터)\n", s5, p);
  }
  else {
    printf("문자 'C'를 찾지 못했습니다.\n");
  }

  // strstr: 문자열 안에서 부분 문자열 찾기
  p = strstr(s5, "program");
  if (p != NULL) {
    printf("strstr(\"%s\", \"program\") -> \"%s\" (처음 찾은 위치부터)\n", s5, p);
  }
  else {
    printf("부분 문자열 \"program\"을 찾지 못했습니다.\n");
  }

  /* ---------- 4. strtok: 구분자를 기준으로 문자열 자르기 ---------- */
  printf("\n=== [ex06] strtok 예시 ===\n");

  char text[100] = "one,two;three four";
  const char* delim = " ,;"; // 공백, 콤마, 세미콜론
  char* token;

  printf("원본 문자열: \"%s\"\n", text);
  printf("구분자: 공백, 콤마(,), 세미콜론(;)\n");

  token = strtok(text, delim);   // 첫 번째 토큰
  while (token != NULL) {
    printf("토큰: \"%s\"\n", token);
    token = strtok(NULL, delim); // 다음 토큰
  }

  return 0;
}

/******************** ex07: 특정 디렉터리의 파일/폴더 나열 ********************/

void listFiles(const char* path) {
  WIN32_FIND_DATA findData;   // 파일/디렉터리 정보가 들어가는 구조체
  HANDLE hFind;               // 검색용 핸들

  char searchPath[MAX_PATH];  // "C:\\Temp\\*" 이런 식의 검색용 경로 문자열

  // 검색할 경로 문자열 만들기: 예) "C:\Temp\*"
  snprintf(searchPath, sizeof(searchPath), "%s\\*", path);

  // 첫 번째 파일(또는 디렉터리) 찾기
  hFind = FindFirstFile(searchPath, &findData);
  if (hFind == INVALID_HANDLE_VALUE) {
    // 디렉터리를 열 수 없는 경우 (경로가 없거나 권한 문제 등)
    printf("디렉토리 열기 실패: %s\n", path);
    return;
  }

  // FindFirstFile에서 찾은 것 + FindNextFile로 이어지는 모든 것 반복
  do {
    // 파일 속성에서 "디렉터리" 비트가 있는지 확인
    if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
      // 디렉터리인 경우 -> "."(현재 디렉터리), ".."(상위 디렉터리)는 제외
      if (strcmp(findData.cFileName, ".") != 0 &&
        strcmp(findData.cFileName, "..") != 0) {
        printf("[DIR ] %s\n", findData.cFileName);
      }
    }
    else {
      // 디렉터리가 아니면 일반 파일
      printf("[FILE] %s\n", findData.cFileName);
    }
  } while (FindNextFile(hFind, &findData) != 0);  // 다음 항목이 있는 동안 반복

  // 검색용 핸들 닫기
  FindClose(hFind);
}

int ex07(void) {
  char dirPath[MAX_PATH] = "C:\\Temp"; // 검색할 디렉터리 경로 (예시)

  printf("\n=== [ex07] 디렉토리 검색: %s ===\n", dirPath);
  listFiles(dirPath);

  return 0;
}

/******************** main: 실행할 예제 선택 ********************/

int main(void) {
  // 필요할 때 주석을 조절해서 원하는 예제만 실행해도 됩니다.
  //ex01(); // 복소수(struct) 사칙연산 예시
  //ex02(); // 복소수 + typedef 예시
  //ex03(); // 사분면 판별(예시 점들)
  //ex04(); // Circle(정수 근사 둘레/면적) 예시
  //ex05(); // 포인터로 Circle2 안의 둘레/면적 채우기 예시
  //ex06(); // 문자/문자열 표준 라이브러리 함수 예시
  //ex07(); // 특정 디렉터리의 파일/폴더 목록 출력 예시

  return 0;
}