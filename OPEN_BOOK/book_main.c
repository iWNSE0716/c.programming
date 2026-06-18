#define _CRT_SECURE_NO_WARNINGS   // MSVC 보안 경고 끄기 (fopen 등에서 경고 제거)

#include <stdio.h>
#include <stdlib.h>   // qsort, rand, srand
#include <time.h>     // time

/************************************************************
 * [공통] 정렬에 사용할 비교 함수들
 *
 * - compare_float_asc  : float 오름차순
 * - compare_float_desc : float 내림차순
 * - compare_int_asc    : int   오름차순
 * - compare_int_desc   : int   내림차순
 *
 *  qsort()는 다음 형식의 비교 함수를 요구한다.
 *    int cmp(const void *a, const void *b);
 *
 *  이 함수는
 *    - a < b 이면 음수
 *    - a == b 이면 0
 *    - a > b 이면 양수
 *  를 반환해야 한다.
 ************************************************************/

 /*
   (1) 실수 정렬용 비교 함수: 오름차순

   매개변수:
     a, b : 배열의 원소를 가리키는 포인터 (void* 이므로 캐스팅 필요)

   동작:
     - void*를 float*로 캐스팅한 뒤, 역참조하여 값을 가져온다.
     - fa < fb 이면 음수, fa > fb 이면 양수, 같으면 0 반환.
     - 이렇게 하면 qsort가 작은 값이 앞에 오도록 정렬한다.
 */

int compare_float_asc(const void* a, const void* b)
{
  float fa = *(const float*)a;  // void* → float* 로 캐스팅 후 역참조
  float fb = *(const float*)b;

  if (fa < fb) return -1;        // fa가 더 작으면 앞으로
  if (fa > fb) return 1;         // fa가 더 크면 뒤로
  return 0;                      // 같으면 위치 유지
}

/*
  (1) 실수 정렬용 비교 함수: 내림차순

  오름차순과 반대로,
    - fa < fb 이면 양수 (자리 바꿈)
    - fa > fb 이면 음수 (그대로)
  로 반환하여 큰 값이 앞에 오도록 한다.
*/

int compare_float_desc(const void* a, const void* b)
{
  float fa = *(const float*)a;
  float fb = *(const float*)b;

  if (fa < fb) return 1;        // fa가 더 작으면 뒤로 (내림차순)
  if (fa > fb) return -1;       // fa가 더 크면 앞으로
  return 0;
}

/*
  (2) 정수 정렬용 비교 함수: 오름차순

  int 형 배열에 대해 오름차순 정렬을 수행하기 위한 비교 함수.

  방법 1: if문으로 비교 (float와 동일 방식)
  방법 2: (ia - ib)를 그대로 반환 (단, 오버플로우에 주의)

  여기서는 이해를 돕기 위해 if문 방식 사용.
*/

int compare_int_asc(const void* a, const void* b)
{
  int ia = *(const int*)a;   // void* → int* 캐스팅 후 역참조
  int ib = *(const int*)b;

  if (ia < ib) return -1;     // ia가 더 작으면 앞으로
  if (ia > ib) return 1;      // ia가 더 크면 뒤로
  return 0;
}

/*
  (2) 정수 정렬용 비교 함수: 내림차순

  오름차순일 때와 부호만 반대로 바꾸면 된다.
*/
int compare_int_desc(const void* a, const void* b)
{
  int ia = *(const int*)a;
  int ib = *(const int*)b;

  if (ia < ib) return 1;      // ia가 더 작으면 뒤로 (내림차순)
  if (ia > ib) return -1;     // ia가 더 크면 앞으로
  return 0;
}

/************************************************************
 * 도전문제 9. 실수 정렬 + 난수 100개 정렬
 *
 * (1) float arr[] = {64.1, 64.0, 25.3, 12.6, 22.8, 11.3, 90.4};
 *     배열을 각각 오름차순, 내림차순으로 정렬하여 출력한다.
 *     compare() 함수 내에서 자료형 변환을 float로 하도록 한다.
 *
 * (2) 1 ~ 10000 사이의 임의의 정수 난수 100개를 생성하여
 *     배열 arr_int[]에 저장한 뒤,
 *     qsort()로 각각 오름차순, 내림차순 정렬하여 출력한다.
 ************************************************************/

 /*
   (1) 실수 배열 정렬/출력 예제 함수

   기능:
     - 주어진 float 배열을 화면에 "정렬 전" 상태로 출력
     - qsort + compare_float_asc로 오름차순 정렬 후 출력
     - 다시 원본 배열을 준비하여 qsort + compare_float_desc로 내림차순 정렬 후 출력
 */

void challenge09_part1(void)
{
  // 교재에서 제시된 실수 배열
  float arr[] = { 64.1f, 64.0f, 25.3f, 12.6f, 22.8f, 11.3f, 90.4f };
  int n = (int)(sizeof(arr) / sizeof(arr[0]));  // 원소 개수
  int i;

  printf("=== 도전문제 9 (1) 실수 정렬 ===\n");

  // (a) 정렬 전 상태 출력
  printf("정렬 전: ");
  for (i = 0; i < n; i++) {
    printf("%.1f ", arr[i]);
  }
  printf("\n");

  // (b) 오름차순 정렬: 작은 값 → 큰 값
  //     qsort(배열, 원소 개수, 원소 크기, 비교 함수 포인터)
  qsort(arr, n, sizeof(float), compare_float_asc);

  printf("오름차순 정렬 후: ");
  for (i = 0; i < n; i++) {
    printf("%.1f ", arr[i]);
  }
  printf("\n");

  // (c) 내림차순 정렬을 위해 다시 원본 값으로 초기화
  {
    // arr2: 정렬 전 상태를 다시 담는 배열
    float arr2[] = { 64.1f, 64.0f, 25.3f, 12.6f, 22.8f, 11.3f, 90.4f };
    int j;

    // 내림차순 정렬: 큰 값 → 작은 값
    qsort(arr2, n, sizeof(float), compare_float_desc);

    printf("내림차순 정렬 후: ");
    for (j = 0; j < n; j++) {
      printf("%.1f ", arr2[j]);
    }
    printf("\n");
  }

  printf("\n");
}

/*
  (2) 난수 100개 생성 후, 정수 배열 정렬/출력 예제 함수

  기능:
    - 1 ~ 10000 범위의 난수를 100개 생성하여 arr_int[]에 저장
    - 생성한 난수들을 그대로 출력
    - qsort + compare_int_asc로 오름차순 정렬 후 출력
    - qsort + compare_int_desc로 내림차순 정렬 후 출력
*/

void challenge09_part2(void)
{
  int arr_int[100];    // 난수 100개를 저장할 배열
  int n = 100;
  int i;

  printf("=== 도전문제 9 (2) 난수 100개 정렬 ===\n");

  // (a) 난수 시드 설정
  //     time(NULL)을 이용해 현재 시간을 기준으로 시드를 주면
  //     실행할 때마다 다른 난수열을 얻게 된다.
  srand((unsigned int)time(NULL));

  // (b) 1 ~ 10000 사이 난수 생성
  for (i = 0; i < n; i++) {
    // rand() % 10000 : 0 ~ 9999
    // 여기에 +1을 해서 1 ~ 10000 범위를 만든다.
    arr_int[i] = rand() % 10000 + 1;
  }

  // (c) 생성된 난수들 출력
  printf("생성된 난수들:\n");
  for (i = 0; i < n; i++) {
    printf("%5d ", arr_int[i]);
    // 20개씩 끊어서 줄바꿈 (보기 좋게)
    if ((i + 1) % 20 == 0) printf("\n");
  }
  printf("\n\n");

  // (d) 오름차순 정렬: 작은 값 → 큰 값
  qsort(arr_int, n, sizeof(int), compare_int_asc);

  printf("오름차순 정렬 후:\n");
  for (i = 0; i < n; i++) {
    printf("%5d ", arr_int[i]);
    if ((i + 1) % 20 == 0) printf("\n");
  }
  printf("\n\n");

  // (e) 내림차순 정렬: 큰 값 → 작은 값
  qsort(arr_int, n, sizeof(int), compare_int_desc);

  printf("내림차순 정렬 후:\n");
  for (i = 0; i < n; i++) {
    printf("%5d ", arr_int[i]);
    if ((i + 1) % 20 == 0) printf("\n");
  }
  printf("\n");
}

#define _CRT_SECURE_NO_WARNINGS   // MSVC 보안 경고 끄기

#include <stdio.h>
#include <stdlib.h>   // qsort
#include <string.h>   // strcmp, strlen

/************************************************************
 * [공통] 문자열 정렬에 사용할 비교 함수들
 *
 * - compare_str_asc  : char* (문자열) 오름차순  (알파벳 사전순)
 * - compare_str_desc : char* (문자열) 내림차순 (알파벳 사전 역순)
 *
 *  qsort()는 다음 형식의 비교 함수를 사용한다.
 *    int cmp(const void *a, const void *b);
 *
 *  여기서 a, b는 "배열 원소의 주소"를 가리키므로
 *  문자열 배열일 때는 (char**) 으로 캐스팅 후 역참조하여
 *  char* 를 얻은 뒤 strcmp 로 비교한다.
 ************************************************************/

 /*
   문자열 오름차순 비교 함수 (알파벳 사전순)

   매개변수:
     a, b : 배열의 원소(char*)를 가리키는 포인터의 주소(void*)

   동작:
     - const char **로 캐스팅 후, 한 번 더 역참조해서 실제 char* 획득
     - strcmp(s1, s2)를 그대로 반환
       (s1 < s2 이면 음수, s1 == s2 이면 0, s1 > s2 이면 양수)
 */
int compare_str_asc(const void* a, const void* b)
{
  const char* s1 = *(const char**)a;   // void* → char** → char*
  const char* s2 = *(const char**)b;

  return strcmp(s1, s2);    // 사전순 정렬
}

/*
  문자열 내림차순 비교 함수 (알파벳 사전 역순)

  동작:
    - 오름차순과 반대로 비교한다.
    - strcmp(s2, s1)를 이용하면 간단히 역순을 구현할 수 있다.
*/
int compare_str_desc(const void* a, const void* b)
{
  const char* s1 = *(const char**)a;
  const char* s2 = *(const char**)b;

  // s1, s2의 순서를 바꿔서 strcmp 호출 → 결과 부호가 반대가 되어 역순
  return strcmp(s2, s1);
}

/************************************************************
 * 문제 9.2
 *
 * (1) 정렬된 단어 목록을 "알파벳 사전 역순"으로 출력하기
 *     (예시 언어들: Ada, C, Fortran, Java, Pascal, Python, Swift)
 *
 * (2) 임의의 7개의 과일 이름을 영문으로 입력받아
 *     - 알파벳 사전순
 *     - 알파벳 사전 역순
 *     으로 각각 정렬하여 출력하기
 ************************************************************/

 /*
   (1) 주어진 언어 이름들을 알파벳 사전 역순으로 출력

   원래(오름차순) 예시:
     Ada
     C
     Fortran
     Java
     Pascal
     Python
     Swift

   이 함수를 통해 내림차순(역순) 결과:
     Swift
     Python
     Pascal
     Java
     Fortran
     C
     Ada
 */
void problem92_part1(void)
{
  // 문자열 리터럴로 이루어진 배열
  const char* langs[] = {
      "Ada",
      "C",
      "Fortran",
      "Java",
      "Pascal",
      "Python",
      "Swift"
  };

  int n = (int)(sizeof(langs) / sizeof(langs[0]));
  int i;

  printf("=== 문제 9.2 (1) 언어 이름을 알파벳 사전 역순으로 출력 ===\n");

  // 기존(사전순) 정렬된 목록 (문제에서 제시한 상태라고 가정)
  printf("정렬된 단어 목록(알파벳 사전순):\n");
  for (i = 0; i < n; i++) {
    printf("%s\n", langs[i]);
  }
  printf("\n");

  // qsort를 사용하기 위해, 포인터 배열을 복사해서 사용 (원본 유지용)
  const char* langs_copy[7];
  for (i = 0; i < n; i++) {
    langs_copy[i] = langs[i];
  }

  // 알파벳 사전 역순으로 정렬
  qsort(langs_copy, n, sizeof(char*), compare_str_desc);

  printf("알파벳 사전의 역순:\n");
  for (i = 0; i < n; i++) {
    printf("%s\n", langs_copy[i]);
  }
  printf("\n");
}

/*
  (2) 과일 이름 7개를 입력받아
      - 알파벳 사전순
      - 알파벳 사전 역순
      으로 각각 정렬하는 예제

  구현 방법:
    - 최대 길이 99자의 문자열 7개를 저장할 2차원 배열 선언
      char fruits[7][100];
    - 포인터 배열 char* ptrs[7]를 만들어
      각 포인터가 fruits[i]를 가리키도록 설정
    - qsort는 ptrs (char* 배열)에 대해 수행
    - 출력 시 ptrs[i]로 접근하면 정렬된 순서대로 문자열 출력
*/
void problem92_part2(void)
{
  char fruits[7][100];    // 실제 문자열 저장 공간
  char* ptrs[7];          // 각 문자열을 가리키는 포인터 배열
  int i;

  printf("=== 문제 9.2 (2) 과일 이름 7개 정렬 ===\n");

  // (a) 과일 이름 입력 받기
  printf("영문 과일 이름 7개를 입력하세요 (예: apple, banana ...):\n");
  for (i = 0; i < 7; i++) {
    // 공백 없는 단어 입력을 가정 (scanf(\"%s\"))
    // 과일 이름 길이는 최대 99자로 제한
    printf("%d번째 과일 이름: ", i + 1);
    scanf("%99s", fruits[i]);
  }

  // (b) 포인터 배열이 각 문자열을 가리키도록 설정
  for (i = 0; i < 7; i++) {
    ptrs[i] = fruits[i];     // fruits[i]는 char* 로 decay
  }

  // (c) 알파벳 사전순(오름차순) 정렬
  qsort(ptrs, 7, sizeof(char*), compare_str_asc);

  printf("\n알파벳 사전순 정렬 결과:\n");
  for (i = 0; i < 7; i++) {
    printf("%s\n", ptrs[i]);
  }

  // (d) 알파벳 사전 역순(내림차순) 정렬
  qsort(ptrs, 7, sizeof(char*), compare_str_desc);

  printf("\n알파벳 사전의 역순 정렬 결과:\n");
  for (i = 0; i < 7; i++) {
    printf("%s\n", ptrs[i]);
  }

  printf("\n");
}

#define _CRT_SECURE_NO_WARNINGS   // MSVC 보안 경고 끄기

#include <stdio.h>
#include <stdlib.h>

/************************************************************
 * 도전문제 10.1 알파벳 대문자를 만들자
 *
 * - 알파벳 소문자를 하나 입력받아
 *   해당하는 알파벳 대문자로 변환하여 출력하는 프로그램
 *
 * - 힌트:
 *   알파벳 소문자 'a' ~ 'z' 는
 *   알파벳 대문자 'A' ~ 'Z' 보다 아스키 코드 값이 32만큼 크다.
 *
 *   예)
 *     'a' (97) - 32 = 'A' (65)
 *     'b' (98) - 32 = 'B' (66)
 *     ...
 *     'z' (122) - 32 = 'Z' (90)
 ************************************************************/

void challenge10_1(void)
{
  char lower;   // 소문자 입력용 변수
  char upper;   // 대문자 결과용 변수

  // (1) 소문자 입력 안내
  printf("알파벳 소문자를 입력하세요 : ");

  // (2) 문자 하나 입력받기
  //     공백 없는 한 글자 입력을 가정
  scanf(" %c", &lower);

  // (3) 소문자 → 대문자 변환
  //     아스키 코드 기준으로 32를 빼면 대문자가 된다.
  upper = lower - 32;

  // (4) 결과 출력
  printf("%c의 대문자: %c\n", lower, upper);
}

#define _CRT_SECURE_NO_WARNINGS   // MSVC 보안 경고 끄기

#include <stdio.h>

/************************************************************
 * 도전문제 11.1
 *
 * 자동차 정보:
 *  - 모델 이름(name)
 *  - 생산 업체(company)
 *  - 생산 연도(prod_year)
 *  - 출고 가격(price)
 *  - 최대 속도(max_speed)  ← 새로 추가
 *
 * 각 자동차의 최대 속도:
 *  - IONIQ 5 : 230 km/h
 *  - X3      : 180 km/h
 *  - E250    : 220 km/h
 *
 * 세 대의 자동차 정보를 구조체로 표현하고,
 * 예시와 같이 보기 좋게 출력한다.
 ************************************************************/

 // 자동차 정보를 표현하는 구조체
typedef struct {
  const char* name;       // 모델 이름
  const char* company;    // 생산 업체
  int         prod_year;  // 생산 연도
  int         price;      // 출고 가격 (만원 단위)
  int         max_speed;  // 최대 속도 (km/h)
} Car;

/*
  자동차 한 대의 정보를 포맷에 맞게 출력하는 함수
*/
void print_car_info(const char* title, const Car* car)
{
  printf("%s\n", title);
  printf("모델 이름: %s\n", car->name);
  printf("생산 업체: %s\n", car->company);
  printf("생산 연도: %d년\n", car->prod_year);
  printf("출고 가격: %d만원\n", car->price);
  printf("최대 속도: %dkm/h\n", car->max_speed);
  printf("\n");
}

/*
  도전문제 11.1 실행 함수
*/
void challenge11_1(void)
{
  // 문제에서 주어진 세 대의 자동차 정보를 구조체로 초기화
  Car car1 = {
      "IONIQ 5",
      "Hyundai Motor Company",
      2022,
      3120,
      230          // 최대 속도 (km/h)
  };

  Car car2 = {
      "X3",
      "BMW",
      2021,
      6500,
      180          // 최대 속도 (km/h)
  };

  Car car3 = {
      "E250",
      "Mercedes Benz",
      2025,
      7450,
      220          // 최대 속도 (km/h)
  };

  // 출력
  print_car_info("자동차 1", &car1);
  print_car_info("자동차 2", &car2);
  print_car_info("자동차 3", &car3);
}

#define _CRT_SECURE_NO_WARNINGS   // MSVC 보안 경고 끄기

#include <stdio.h>

/************************************************************
 * 도전문제 11.2 point 자료형을 재정의하여 만들자
 *
 * (1) struct point를 typedef로 Point형으로 정의하고,
 *     Point 변수 p1, p2에 (10,20), (30,50)을 넣어 출력.
 *
 * (2) (1)의 구조체 정의를 활용하여 Rectangle 구조체를 정의.
 *     - typedef를 이용하여 Rectangle 형을 정의
 *     - Point 형의 멤버 p1, p2를 원소로 가진다.
 ************************************************************/

 /*
   (공통) X, Y 좌표를 가지는 구조체 point 정의
         그리고 typedef로 Point라는 새 이름 부여
 */
struct point {
  int x;
  int y;
};

// point 구조체를 Point라는 이름의 형으로 재정의
typedef struct point Point;

/*
  (공통) Rectangle 구조체 정의
        - 두 개의 Point를 멤버로 가진다 (p1, p2)
        - typedef로 Rectangle이라는 형 이름 부여
*/
typedef struct rectangle {
  Point p1;   // 직사각형의 한 꼭짓점
  Point p2;   // 반대편 꼭짓점
} Rectangle;

/*
 * (1) 문제 11.2 (1) 풀이:
 *     Point 변수 p1, p2에 값 설정 후 출력
 */
void challenge112_part1(void)
{
  Point p1;
  Point p2;

  p1.x = 10;
  p1.y = 20;

  p2.x = 30;
  p2.y = 50;

  printf("=== 도전문제 11.2 (1) ===\n");
  printf("Point 변수 p1 : (%d, %d)\n", p1.x, p1.y);
  printf("Point 변수 p2 : (%d, %d)\n", p2.x, p2.y);
  printf("\n");
}

/*
 * (2) 문제 11.2 (2) 풀이:
 *     Rectangle 구조체를 사용하여 p1, p2를 멤버로 가지는 예시
 */
void challenge112_part2(void)
{
  Point p1 = { 10, 20 };
  Point p2 = { 30, 50 };
  Rectangle rect;

  rect.p1 = p1;
  rect.p2 = p2;

  printf("=== 도전문제 11.2 (2) ===\n");
  printf("Rectangle 구조체 예시:\n");
  printf("rect.p1 = (%d, %d)\n", rect.p1.x, rect.p1.y);
  printf("rect.p2 = (%d, %d)\n", rect.p2.x, rect.p2.y);
  printf("\n");
}

#define _CRT_SECURE_NO_WARNINGS   // MSVC 보안 경고 끄기

#include <stdio.h>

/************************************************************
 * 도전문제 11.3 FILE 구조체를 사용하여 파일을 생성하자
 *
 * C: 드라이브 아래에 task 라는 폴더를 만들고,
 * FILE * 포인터를 사용하여 예시와 같은 내용을 가지는
 * hello.txt 파일을 C:\task 폴더 아래에 생성한다.
 *
 * 예시 내용:
 *   Hello, world!
 ************************************************************/

void challenge113(void)
{
  // Windows 기준 경로: C:\task\hello.txt
  // 역슬래시는 이스케이프 문자이므로 "\\" 로 써야 함
  FILE* fp = fopen("C:\\task\\hello.txt", "w");

  if (fp == NULL) {
    printf("파일을 열 수 없습니다.\n");
    return;   // 실패 시 함수 종료
  }

  // 파일에 문자열 쓰기
  fprintf(fp, "Hello, world!\n");

  // 파일 닫기
  fclose(fp);

  printf("파일 저장 완료! (C:\\task\\hello.txt)\n");
}

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

/************************************************************
 * 도전문제 12.1
 *
 * - 기존 예제는 항목 필드가 하나(int data)인 단일 연결 리스트 노드.
 * - 여기에 항목 필드를 2개로 만들어
 *     float weight;
 *     float height;
 *   를 가지도록 수정한다.
 *
 * - p1 포인터를 사용하여
 *     p1->weight = 65.6, p1->height = 187.6
 *   이 되도록 값을 넣고 출력한다.
 ************************************************************/

typedef struct ListNode {
  float weight;            // 몸무게
  float height;            // 키
  struct ListNode* link;   // 다음 노드를 가리키는 포인터
} ListNode;

void challenge121(void)
{
  // (1) 노드 하나 선언 및 초기화
  //     weight, height는 0.0f, link는 NULL로 초기화
  ListNode node = { 0.0f, 0.0f, NULL };

  // (2) 포인터 p1이 node를 가리키도록 설정
  ListNode* p1 = &node;

  // (3) p1을 이용해 weight, height 값 대입
  p1->weight = 65.6f;
  p1->height = 187.6f;

  // (4) 값 출력
  printf("p1->weight = %.1f\n", p1->weight);
  printf("p1->height = %.1f\n", p1->height);
}

#define _CRT_SECURE_NO_WARNINGS   // MSVC 보안 경고 끄기

#include <stdio.h>

/************************************************************
 * 도전문제 13.1 사용자로부터 입력한 내용을 저장하자
 *
 * - 사용자로부터 파일 이름을 입력받는다.  (예: note.txt)
 * - 이어서 한 줄의 문장을 입력받는다.     (예: Hello, this is a text.)
 * - 입력받은 문장을 지정된 파일에 저장한다.
 ************************************************************/

void challenge131(void)
{
  char filename[256];   // 파일 이름 저장용
  char line[512];       // 한 줄 문장 저장용

  // (1) 파일 이름 입력
  printf("파일의 이름을 입력하시오 : ");
  scanf("%255s", filename);   // 공백 없는 파일 이름 입력 가정

  // (2) 버퍼에 남아 있는 개행 문자 제거
  //     scanf로 파일 이름을 읽은 뒤, 바로 fgets를 쓰기 위해 필요
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF) {
    ; // 비움
  }

  // (3) 한 줄 문장 입력
  printf("한 줄의 문장을 입력하시오 : ");
  // 공백을 포함한 한 줄 전체 입력
  if (fgets(line, sizeof(line), stdin) == NULL) {
    printf("입력 오류가 발생했습니다.\n");
    return;
  }

  // (4) 파일 열기 (쓰기 모드)
  FILE* fp = fopen(filename, "w");
  if (fp == NULL) {
    printf("파일을 열 수 없습니다.\n");
    return;
  }

  // (5) 파일에 문장 쓰기
  fputs(line, fp);

  // (6) 파일 닫기
  fclose(fp);

  printf("---- %s 파일에 %s 내용이 저장됨 ----\n", filename, line);
}

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

/************************************************************
 * 도전문제 13.2 사용자로부터 입력한 내용을 저장하자
 *
 * (1) 파일 이름과 여러 줄의 텍스트를 입력받아
 *     - 빈 줄(엔터만 입력)이 나오면 입력 종료
 *     - 입력된 모든 줄을 그대로 파일에 저장
 *     - 파일 생성에 성공하면
 *         "<파일이름> 파일이 성공적으로 생성되었습니다."
 *       출력
 *
 * (2) (1)의 코드를 수정하여,
 *     - 저장되는 각 줄 앞에 줄 번호를 붙인다.
 *     - 형식: "1: 내용...", "2: 내용..."
 ************************************************************/

 /****************** (1) 줄 번호 없이 그대로 저장 ******************/
void challenge132_part1(void)
{
  char filename[256];
  char line[512];

  printf("파일의 이름을 입력하시오 : ");
  scanf("%255s", filename);

  // 남아 있는 개행 문자 제거
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF) {
    ;
  }

  FILE* fp = fopen(filename, "w");
  if (fp == NULL) {
    printf("파일을 열 수 없습니다.\n");
    return;
  }

  printf("텍스트를 입력하세요 (빈 줄 입력 시 종료):\n");

  while (1) {
    if (fgets(line, sizeof(line), stdin) == NULL) {
      break;  // 입력 에러 또는 EOF
    }

    // 빈 줄(엔터만)인지 확인: "\n" 또는 "\r\n" 등 처리
    // 여기서는 단순히 첫 문자가 '\n' 이면 빈 줄로 처리
    if (line[0] == '\n') {
      break;
    }

    fputs(line, fp);
  }

  fclose(fp);

  printf("%s 파일이 성공적으로 생성되었습니다.\n", filename);
}

/****************** (2) 줄 번호를 붙여서 저장 ******************/
void challenge132_part2(void)
{
  char filename[256];
  char line[512];

  printf("파일의 이름을 입력하시오 : ");
  scanf("%255s", filename);

  // 남아 있는 개행 문자 제거
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF) {
    ;
  }

  FILE* fp = fopen(filename, "w");
  if (fp == NULL) {
    printf("파일을 열 수 없습니다.\n");
    return;
  }

  printf("텍스트를 입력하세요 (빈 줄 입력 시 종료):\n");

  int line_no = 1;  // 줄 번호 시작값

  while (1) {
    if (fgets(line, sizeof(line), stdin) == NULL) {
      break;  // 입력 에러 또는 EOF
    }

    if (line[0] == '\n') {
      break;  // 빈 줄이면 종료
    }

    // 줄 번호와 함께 파일에 기록: "1: 내용"
    fprintf(fp, "%d: %s", line_no, line);
    line_no++;
  }

  fclose(fp);

  printf("%s 파일이 성공적으로 생성되었습니다.\n", filename);
}

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>   // rand, srand
#include <time.h>     // time

/************************************************************
 * 도전문제 13.3 이진 파일을 읽어서 출력하자
 *
 * (1)
 *  - double d[10]을 정의하고 1.0에서 10.0까지 실수를 저장
 *  - C:\workspace\binary_1to10.dat 라는 이진 파일에 저장
 *  - 정상 저장 시
 *      "c:\workspace\binary_1to10.dat 이진 파일 저장 완료!"
 *    출력
 *
 * (2)
 *  - 0.0 ~ 100.0 사이의 임의의 실수 5개를 생성
 *  - C:\workspace\binary_rand.dat 에 이진 파일로 저장
 *  - 이 파일을 다시 읽어서 실수 5개를 소수점 둘째 자리까지 출력
 ************************************************************/

 /****************** (1) 1.0 ~ 10.0 저장 ******************/
void challenge133_part1(void)
{
  double d[10];
  int i;

  // (1) 배열에 1.0 ~ 10.0 저장
  for (i = 0; i < 10; i++) {
    d[i] = (double)(i + 1);   // 1.0, 2.0, ..., 10.0
  }

  // (2) 파일 열기 (이진 쓰기 모드)
  const char* filename = "C:\\workspace\\binary_1to10.dat";
  FILE* fp = fopen(filename, "wb");

  if (fp == NULL) {
    printf("파일을 열 수 없습니다: %s\n", filename);
    return;
  }

  // (3) 배열 전체를 한 번에 쓰기
  //     원소 개수: 10, 각 원소 크기: sizeof(double)
  size_t written = fwrite(d, sizeof(double), 10, fp);
  if (written != 10) {
    printf("파일 쓰기 오류가 발생했습니다.\n");
    fclose(fp);
    return;
  }

  fclose(fp);

  printf("c:\\workspace\\binary_1to10.dat 이진 파일 저장 완료!\n");
}

/****************** (2) 0.0 ~ 100.0 난수 5개 저장 & 읽어서 출력 ******************/
void challenge133_part2(void)
{
  double d[5];
  int i;

  // (1) 난수 시드 설정
  srand((unsigned int)time(NULL));

  // (2) 0.0 ~ 100.0 사이의 실수 5개 생성
  //     rand() / RAND_MAX → 0.0 ~ 1.0
  //     여기에 100.0을 곱해 0.0 ~ 100.0 범위로 조정
  for (i = 0; i < 5; i++) {
    double r = (double)rand() / (double)RAND_MAX;
    d[i] = r * 100.0;
  }

  // (3) 이진 파일로 저장
  const char* filename = "C:\\workspace\\binary_rand.dat";
  FILE* fp = fopen(filename, "wb");
  if (fp == NULL) {
    printf("파일을 열 수 없습니다: %s\n", filename);
    return;
  }

  size_t written = fwrite(d, sizeof(double), 5, fp);
  if (written != 5) {
    printf("파일 쓰기 오류가 발생했습니다.\n");
    fclose(fp);
    return;
  }
  fclose(fp);

  // (4) 파일 다시 열어서 읽기
  fp = fopen(filename, "rb");
  if (fp == NULL) {
    printf("파일을 열 수 없습니다: %s\n", filename);
    return;
  }

  double read_vals[5];
  size_t read_count = fread(read_vals, sizeof(double), 5, fp);
  fclose(fp);

  if (read_count != 5) {
    printf("파일 읽기 오류가 발생했습니다.\n");
    return;
  }

  // (5) 읽은 값들 출력 (소수점 둘째 자리까지)
  printf("binary_rand.dat 파일\n");
  for (i = 0; i < 5; i++) {
    printf("%.2f ", read_vals[i]);
  }
  printf("\n");
}

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

/************************************************************
 * 도전문제 13.4 이진 파일을 읽어서 출력하자
 *
 * (사전 조건)
 *  - nums.bin 파일에는 다음 10개의 int가 이진 형식으로 저장되어 있다.
 *      10, 20, 30, 40, 50, 1000, 2000, 3000, 4000, 5000
 *
 * (1)
 *  - nums.bin 파일의 데이터를 순서대로 읽어서 출력:
 *      nums.bin에 저장된 데이터 :
 *      10 20 30 40 50 1000 2000 3000 4000 5000
 *
 * (2)
 *  - 사용자로부터 숫자 1 또는 2를 입력받아
 *      1 입력 시 → 첫 번째 항목: 10 20 30 40 50
 *      2 입력 시 → 두 번째 항목: 1000 2000 3000 4000 5000
 ************************************************************/

 /****************** (1) nums.bin 전체 출력 ******************/
void challenge134_part1(void)
{
  const char* filename = "nums.bin";
  FILE* fp = fopen(filename, "rb");
  if (fp == NULL) {
    printf("파일을 열 수 없습니다: %s\n", filename);
    return;
  }

  int nums[10];
  size_t read_count = fread(nums, sizeof(int), 10, fp);
  fclose(fp);

  if (read_count != 10) {
    printf("파일에서 데이터를 모두 읽지 못했습니다.\n");
    return;
  }

  printf("nums.bin에 저장된 데이터 :\n");
  for (int i = 0; i < 10; i++) {
    printf("%d ", nums[i]);
  }
  printf("\n");
}

/****************** (2) 1 또는 2를 입력받아 해당 항목 출력 ******************/
void challenge134_part2(void)
{
  const char* filename = "nums.bin";
  FILE* fp = fopen(filename, "rb");
  if (fp == NULL) {
    printf("파일을 열 수 없습니다: %s\n", filename);
    return;
  }

  int nums[10];
  size_t read_count = fread(nums, sizeof(int), 10, fp);
  fclose(fp);

  if (read_count != 10) {
    printf("파일에서 데이터를 모두 읽지 못했습니다.\n");
    return;
  }

  int choice;
  printf("1 또는 2를 입력하시오 : ");
  if (scanf("%d", &choice) != 1) {
    printf("입력 오류입니다.\n");
    return;
  }

  if (choice == 1) {
    // 첫 번째 항목: 10 20 30 40 50  (앞의 5개)
    for (int i = 0; i < 5; i++) {
      printf("%d ", nums[i]);
    }
    printf("\n");
  }
  else if (choice == 2) {
    // 두 번째 항목: 1000 2000 3000 4000 5000  (뒤의 5개)
    for (int i = 5; i < 10; i++) {
      printf("%d ", nums[i]);
    }
    printf("\n");
  }
  else {
    printf("1 또는 2만 입력 가능합니다.\n");
  }
}

#define _CRT_SECURE_NO_WARNINGS   // MSVC 보안 경고 끄기

#include <stdio.h>
#include <string.h>

/************************************************************
 * 도전문제 13.5 이미지 파일을 복사하자
 *
 * (1) 파일명이 A.jpg일 경우, 복사 파일 이름을 A_copy.jpg 로 만든다.
 *     예) 원본: A.jpg  →  사본: A_copy.jpg
 *
 * (2) 버퍼 크기를 64, 512, 1024, 4096 바이트로 바꿔가며
 *     복사 코드에서 "버퍼 읽기/쓰기 횟수"를 출력하여 비교한다.
 *
 *  - 여기서는 (1), (2)를 각각 challenge135_part1, challenge135_part2 로 분리.
 ************************************************************/

 /*
   공통 함수: 원본 파일 이름(src_name)을 받아서
   "이름.확장자" → "이름_copy.확장자" 로 바꿔 dst_name에 만든다.

   예)
     src_name = "A.jpg"       → dst_name = "A_copy.jpg"
     src_name = "photo.png"   → dst_name = "photo_copy.png"
 */
void make_copy_name(const char* src_name, char* dst_name, int dst_size)
{
  const char* dot = strrchr(src_name, '.');   // 마지막 '.' 위치

  if (dot == NULL) {
    // 확장자가 없는 경우: 그냥 "_copy"를 뒤에 붙인다.
    snprintf(dst_name, dst_size, "%s_copy", src_name);
  }
  else {
    int basename_len = (int)(dot - src_name);

    if (basename_len <= 0) {
      // 예외적인 경우(.으로 시작 등)는 단순히 copy 붙이기
      snprintf(dst_name, dst_size, "%s_copy", src_name);
    }
    else {
      char basename[256];
      char ext[256];

      strncpy(basename, src_name, basename_len);
      basename[basename_len] = '\0';
      strcpy(ext, dot);   // ".jpg" 같은 확장자

      snprintf(dst_name, dst_size, "%s_copy%s", basename, ext);
    }
  }
}

/*
  공통 함수: 주어진 버퍼 크기로 파일을 복사하고,
  버퍼 단위 읽기/쓰기 횟수를 count에 저장한다.
*/
int copy_file_with_buffer(const char* src_name, const char* dst_name,
  int buffer_size, int* count)
{
  FILE* fp1, * fp2;
  unsigned char buffer[4096];  // 최대 4096까지 사용 (부분만 사용)
  size_t bytesRead;
  int copy_count = 0;

  if (buffer_size <= 0 || buffer_size > (int)sizeof(buffer)) {
    printf("buffer_size가 올바르지 않습니다.\n");
    return 1;
  }

  // 원본 파일 열기 (읽기, 바이너리)
  fp1 = fopen(src_name, "rb");
  if (fp1 == NULL) {
    perror("원본 파일 열기 실패");
    return 1;
  }

  // 사본 파일 열기 (쓰기, 바이너리)
  fp2 = fopen(dst_name, "wb");
  if (fp2 == NULL) {
    perror("사본 파일 열기 실패");
    fclose(fp1);
    return 1;
  }

  // 파일 복사: buffer_size만큼씩 읽어서 그대로 쓰기
  while ((bytesRead = fread(buffer, 1, buffer_size, fp1)) > 0) {
    fwrite(buffer, 1, bytesRead, fp2);
    copy_count++;
  }

  fclose(fp2);
  fclose(fp1);

  if (count != NULL) {
    *count = copy_count;
  }

  return 0;
}

/****************** (1) 기본 복사: A.jpg → A_copy.jpg ******************/
void challenge135_part1(void)
{
  char src_name[256];
  char dst_name[256];
  int copy_count = 0;
  int buffer_size = 1024;   // 예시로 1024 바이트 사용

  printf("=== 도전문제 13.5 (1) ===\n");
  printf("복사할 이미지 파일 이름을 입력하세요 (예: A.jpg): ");
  scanf("%255s", src_name);

  // 복사본 파일 이름 만들기
  make_copy_name(src_name, dst_name, sizeof(dst_name));

  if (copy_file_with_buffer(src_name, dst_name, buffer_size, &copy_count) == 0) {
    printf("파일 복사가 완료되었습니다.\n");
    printf("원본 파일 : %s\n", src_name);
    printf("사본 파일 : %s\n", dst_name);
    printf("BUFFER_SIZE = %d 일 때, 버퍼 읽기/쓰기 횟수 = %d 번\n\n",
      buffer_size, copy_count);
  }
  else {
    printf("파일 복사에 실패했습니다.\n\n");
  }
}

/****************** (2) 버퍼 크기별 복사 횟수 비교 ******************/
void challenge135_part2(void)
{
  char src_name[256];
  char dst_name[256];
  int sizes[] = { 64, 512, 1024, 4096 };
  int i;

  printf("=== 도전문제 13.5 (2) ===\n");
  printf("복사할 이미지 파일 이름을 입력하세요 (예: A.jpg): ");
  scanf("%255s", src_name);

  // A_copy.jpg 같은 형태로 사본 이름 생성 (한 번만 사용)
  make_copy_name(src_name, dst_name, sizeof(dst_name));

  // 각 버퍼 크기에 대해 복사 + 횟수 출력
  for (i = 0; i < 4; i++) {
    int buffer_size = sizes[i];
    int copy_count = 0;

    // 매번 같은 원본에서 같은 이름으로 덮어쓰게 해도 되고,
    // 필요하면 dst_name 뒤에 버퍼크기를 붙여서 다른 이름을 만들 수도 있다.
    if (copy_file_with_buffer(src_name, dst_name, buffer_size, &copy_count) == 0) {
      printf("[BUFFER_SIZE = %4d] 버퍼 읽기/쓰기 횟수 = %d 번\n",
        buffer_size, copy_count);
    }
    else {
      printf("[BUFFER_SIZE = %4d] 파일 복사 실패\n", buffer_size);
    }
  }

  printf("\n(참고) 실제로는 같은 파일을 여러 번 덮어쓴 것입니다.\n");
  printf("필요하다면 버퍼 크기별로 다른 출력 파일 이름을 사용해도 됩니다.\n\n");
}

/************************************************************
 * main: 여기서 실행할 예제를 직접 골라서 호출
 *
 * - 필요한 예제 함수만 주석 해제해서 사용하면 됨.
 ************************************************************/

int main(void)
{
  //challenge09_part1();   // (1) float 배열 실수 정렬 예제 실행
  //challenge09_part2();   // (2) 난수 100개 정렬 예제 실행
  //problem92_part1();     // (1) 언어 이름을 알파벳 사전 역순으로 출력
  //problem92_part2();     // (2) 과일 이름을 입력받아 정렬
  //challenge10_1();       // (1) 알파벳 대문자를 만들자
  //challenge11_1();       // (1) 기본 정보에 덧붙여 최대 속도를 표시하자
  //challenge112_part1();  // (1) Point 변수 출력
  //challenge112_part2();  // (2) Rectangle 구조체 예시
  //challenge113();        // (1) FILE 구조체를 사용하여 파일을 생성
  //challenge121();        // (1) 항목 필드가 두 개인 노드를 만들자
  //challenge131();        // (1) 사용자로부터 입력한 내용을 저장하자
  //challenge132_part1();  // (1) 원본 요구사항: 줄 번호 없이 그대로 저장
  //challenge132_part2();  // (2) 줄 번호를 붙여 저장하는 버전
  //challenge133_part1();  // (1) 1.0 ~ 10.0 이진 파일 저장
  //challenge133_part2();  // (2) 0.0 ~ 100.0 난수 5개 저장 후 읽어 출력
  //challenge134_part1();  // (1) nums.bin 전체 출력
  //challenge134_part2();  // (2) 1 또는 2를 입력받아 부분 출력
  //challenge135_part1();  // (1) 기본 복사 (예: A.jpg → A_copy.jpg)
  //challenge135_part2();  // (2) 버퍼 크기별 복사 횟수 비교
  return 0;
}