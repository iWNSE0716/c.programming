#include <stdio.h>
#include <string.h>
//#define ARRAY_SIZE 20
#define LENGTH 20

/*
int main(void)
{

  char hello[100] = "hello";
  int b[] = { 1,2,3 };
  int a = 0x12345678;
  int scores[ARRAY_SIZE] = { 5,4,3,2,10,11 };
  int i;
  for (i = 0; i < 10; i++)
  {
    scores[i] = i + 1;
  }
  hello[3] = '\0';
  printf("%d\n", strlen(hello));
  return 0;
}
*/

void print_array(int array[], int length)
{
  for (int i = 0; i < length; i++)
  {
    printf("%d ", array[i]);
  }
  printf("\n");
}

void print_array_2(int array[], int length) {
  for (int i = 0; i < length; i++) {
    // 배열의 모든 요소를 그대로 출력 (0이 있는지 -1이 있는지 확인용)
    printf("%d ", array[i]);
  }
  printf("\n");
}

void print_array_3(int array[], int length) {
  for (int i = 0; i < length; i++) {
    // 현재 값을 출력
    printf("%d ", array[i]);

    // 만약 방금 출력한 게 -1이라면, 그 뒤는 보지도 않고 함수 종료!
    if (array[i] == -1) {
      printf("\n");
      return; // break보다 강력하게 함수를 즉시 빠져나감
    }
  }
  printf("\n");
}

void copy_array_a2b(const int buf1[], int buf2[], int length)
{
  for (int i = 0; i < length; i++)
  {
    buf2[i] = buf1[i];
  }
}


int calc_average(int array[], int length)
{
  int sum = 0;
  int average;
  for (int i = 0; i < length; i++)
  {
    sum += array[i];
  }
  average = sum / length;
  return average;
}

int calc_std(int array[], int length)
{
  int sum = 0;
  double avr, diff_sum = 0;

  for (int i = 0; i < length; i++) {
    sum += array[i];
  }
  avr = (double)sum / length;
  for (int i = 0; i < length; i++) {
    diff_sum += pow(array[i] - avr, 2);
  }
  double std_dev = sqrt(diff_sum / length);
  return (int)std_dev;
}

void calc_divisor(int number, int array[], int length)
{
  int count = 0; // 배열의 인덱스를 관리할 변수

  // 1. 배열을 0으로 초기화 (이전 값이 남아있지 않게 함)
  for (int i = 0; i < length; i++) {
    array[i] = 0;
  }

  // 2. 1부터 number까지 나누어보며 약수를 찾음
  for (int i = 1; i <= number; i++) {
    if (number % i == 0) { // 나머지가 0이면 약수
      if (count < length) { // 배열의 크기를 넘지 않을 때만 저장
        array[count] = i;
        count++;
      }
    }
  }
}

void calc_proper_divisors(int number, int array[], int length)
{
  int count = 0;

  // 1. 배열을 0으로 초기화
  for (int i = 0; i < length; i++) {
    array[i] = 0;
  }

  // 2. 1과 자기자신을 제외하기 위해 2부터 number-1까지 검사
  for (int i = 2; i < number; i++) {
    if (number % i == 0) { // 나머지가 0이면 약수
      if (count < length) { // 배열 크기 체크
        array[count] = i;
        count++;
      }
    }
  }
}

void calc_proper_divisors_2(int number, int array[], int length)
{
  int count = 0;

  // [중요] 함수 시작하자마자 배열 전체를 -1로 싹 밀어버립니다.
  for (int i = 0; i < length; i++) {
    array[i] = -1;
  }

  // 2부터 number-1까지 검사하여 약수 채우기
  for (int i = 2; i < number; i++) {
    if (number % i == 0) {
      if (count < length) {
        array[count] = i;
        count++;
      }
    }
  }
}



void print_array_with_flag(int array[], int length) {
  for (int i = 0; i < length; i++) {
    // -1을 만나면 약수가 더 이상 없다는 뜻이므로 반복문 종료
    if (array[i] == -1) {
      break;
    }
    printf("%d ", array[i]);
  }
  printf("\n");
}

void calc_proper_divisors_3(int number, int array[], int length) {
  int count = 0;

  // 1. 혹시 모를 쓰레기 값을 위해 -1로 초기화해둘 수도 있지만, 
  // 로직상 약수 끝에만 -1을 잘 넣으면 됩니다.

  // 2. 2부터 number-1까지 진약수 찾기
  for (int i = 2; i < number; i++) {
    if (number % i == 0) {
      if (count < length - 1) { // -1을 위한 마지막 한 칸 확보
        array[count] = i;
        count++;
      }
    }
  }

}

void calc_proper_divisors_4(int number, int array[], int length) {
  int count = 0;
  // 공약수 계산을 위해 1부터 number까지 모든 약수를 찾습니다.
  for (int i = 1; i <= number; i++) {
    if (number % i == 0) {
      if (count < length - 1) {
        array[count] = i;
        count++;
      }
    }
  }
  array[count] = -1; // 데이터 끝 표시(Flag)
}

void calc_common_divisors(int buf1[], int buf2[], int common_divisors[], int length) {
  int count = 0;

  // buf1의 요소를 하나씩 확인 (-1을 만나면 중단)
  for (int i = 0; i < length && buf1[i] != -1; i++) {
    // buf2에 같은 값이 있는지 확인 (-1을 만나면 중단)
    for (int j = 0; j < length && buf2[j] != -1; j++) {
      if (buf1[i] == buf2[j]) {
        if (count < length - 1) {
          common_divisors[count] = buf1[i];
          count++;
        }
        break; // 같은 값을 찾았으니 buf2 루프 탈출
      }
    }
  }
  common_divisors[count] = -1; // 결과 배열 끝에 플래그 삽입
}

void ex01(void)
{
  int array_a[LENGTH] = { 5, 7, 3, 10, 2, };
  print_array(array_a, LENGTH);
  return 0;
}

void ex02(void)
{
  int array_a[LENGTH] = { 5, 7, 3, 10, 2, };
  int array_b[LENGTH];
  copy_array_a2b(array_a, array_b, LENGTH);
  printf("array_b의 내용: ");
  print_array(array_b, LENGTH);
  return 0;
}

void ex03(void)
{
  int buf[LENGTH];
  int avr;
  for (int i = 0; i < LENGTH; i++)
  {
    buf[i] = i + 1;
  }
  avr = calc_average(buf, LENGTH);
  printf("average = %d\n", avr);
  return 0;
}

void ex04(void)
{
  int buf[LENGTH];
  int std;
  for (int i = 0; i < LENGTH; i++) {
    buf[i] = i + 1;
  }
  std = calc_std(buf, LENGTH);
  printf("std = %d\n", std);
  return 0;
}

void ex05(void)
{
  int num = 50;
  // [주의] 여기서 배열을 선언만 하세요. { ... }로 초기화하면 0이 섞일 수 있습니다.
  int proper_divisor[LENGTH];

  // 함수 호출 (이 안에서 모든 요소를 -1로 바꾼 뒤 약수를 채웁니다)
  calc_proper_divisors(num, proper_divisor, LENGTH);

  printf("%d의 결과 (0이 보이면 안 됨):\n", num);
  print_array(proper_divisor, LENGTH);

  return 0;
}
void ex06(void)
{
  int num = 50;
  int proper_divisor[LENGTH];

  // 함수 호출 (오타 수정: proper_divisor 사용)
  calc_proper_divisors(num, proper_divisor, LENGTH);

  printf("%d의 1과 자신을 제외한 약수: ", num);
  print_array(proper_divisor, LENGTH);
  return 0;
}

void ex07(void)
{
  int num = 50;
  int proper_divisor[LENGTH];

  calc_proper_divisors_2(num, proper_divisor, LENGTH);

  printf("%d의 1과 자신을 제외한 약수: ", num);
  print_array_2(proper_divisor, LENGTH);

  // 전체 배열의 상태를 확인하고 싶을 때 (0 대신 -1이 채워졌는지 확인)
  /*
  for(int i=0; i<LENGTH; i++) printf("%d ", proper_divisor[i]);
  */

  return 0;
}

void ex08(void) {
  int num = 100;
  int proper_divisor[LENGTH];

  // 약수 계산 및 끝에 -1 넣기
  calc_proper_divisors_3(num, proper_divisor, LENGTH);

  // 출력 함수 호출
  print_array_3(proper_divisor, LENGTH);

  return 0;
}

void ex09(void) {
  int num1 = 50;
  int num2 = 80;
  int divisor1[LENGTH];
  int divisor2[LENGTH];
  int common_divisor[LENGTH];

  // 1. 각 수의 약수 계산
  calc_proper_divisors_4(num1, divisor1, LENGTH);
  calc_proper_divisors_4(num2, divisor2, LENGTH);

  // 2. 공약수 계산
  calc_common_divisors(divisor1, divisor2, common_divisor, LENGTH);

  // 3. 결과 출력
  printf("%d의 약수: ", num1);
  print_array_3(divisor1, LENGTH);

  printf("%d의 약수: ", num2);
  print_array_3(divisor2, LENGTH);

  printf("공약수 결과: ");
  print_array_3(common_divisor, LENGTH);

  return 0;
}

void ex10(void) {
  int num1 = 50;
  int num2 = 80;
  int divisor1[LENGTH];
  int divisor2[LENGTH];
  int common_divisor[LENGTH];

  // 1. 각 수의 진약수(1, 자신 제외) 구하기
  calc_proper_divisors_4(num1, divisor1, LENGTH);
  calc_proper_divisors_4(num2, divisor2, LENGTH);

  // 2. 두 진약수 배열 비교하여 공통 항목 찾기
  calc_common_divisors(divisor1, divisor2, common_divisor, LENGTH);

  // 3. 결과 출력
  printf("%d의 진약수: ", num1);
  print_array_3(divisor1, LENGTH);

  printf("%d의 진약수: ", num2);
  print_array_3(divisor2, LENGTH);

  printf("공통 진약수 결과: ");
  print_array_3(common_divisor, LENGTH);

  return 0;
}

// 변수앞에 &를 붙이면 그 변수의 주소값을 뜻한다.
int main(void)
{
  //ex01();
  //ex02();
  //ex03();
  //ex04();
  //ex05();
  //ex06();
  //ex07();
  //ex08();
  //ex09();
  //ex10();
  return 0;
}