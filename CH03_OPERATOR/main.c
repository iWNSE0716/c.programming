#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
void lab_3_1(void)
{
  printf("lab 3-1\n");
  // 코드 작성
  float height_cm = 0;
  float weight = 0;
  float bmi = 0;

  printf("당신의 키는 얼마입니까(단위 cm)?");
    scanf("%f", &height_cm);

    printf("당신의 몸무게는 얼마입니까(단위 kg)?");
    scanf("%f", &weight);

    float height_m = height_cm / 100.0;
    bmi = weight / (height_m * height_m);

      printf("당신의 체질량 지수 : %.2f\n", bmi);
}
*/


/*
void ex01(void)
{
  int a = 0;
  int b = 0;


  printf("정수 2개를 입력하시오 :");r
    scanf("%d %d", &a, &b);
    int c = a / b;
    int d = a % b;
    printf("몫:%d\n", c);
    printf("나머지:%d\n", d);
}
*/


/*
void ex02(void)
{
  int a = 20; // 4bits < 20 < 5bits = 31
  printf("%d", a % 2);
  a = a / 2;
  printf("%d", a % 2);
  a = a / 2;
  printf("%d", a % 2);
  a = a / 2;
  printf("%d", a % 2);
  a = a / 2;
  printf("%d", a % 2);
  printf("%d", a / 2);

}
*/

/*
void test3_7(void)
{
  int a = 9;
  int b = 10;
  int c = a & b;
  int d = a | b;
  int e = ~a;

  a = 1;
  a = a << 1;
  a = a << 1;
  a = a << 1;

  a = a >> 1;
  a = a >> 1;
  a = a >> 1;
  printf("end text 3 - 7\n");
}
*/


void ex04(void)
{
  //가성: 총 4bits로 이루어졌다고 가정

  int a = 11;    //1011      
  int result;
  int op = 1;    //0001
  int i = 0;

  //op = op << 0;
  op = 1 << i;

  result = a & op;
  printf("%d\n", result);     // 1011 AND 0001 -> 0001
  i = i + 1; //i=1

  //op = op << 1;
  op = 1 << i;

  result = a & op;
  result = result >> i;
  printf("%d\n", result);     // 1011 AND 0010 -> 0010 -> 0001

  //i=2
  i = i + 1;

  //op = op << 1;
  op = 1 << i;

  result = a & op;
  result = result >> i;
  printf("%d\n", result);     // 1011 AND 0100 -> 0000 -> 0000

  //i=3
  i = i + 1;

  //op = op << 1;
  op = 1 << i;

  result = a & op;
  result = result >> i;
  printf("%d\n", result);     // 1011 AND 1000 -> 1000 -> 0001


  /* op = op << 1;
  result = a & op;
  result = result >> i;
  printf("%d\n", result);
  op = op << 1;
  result = a & op;
  result = result >> 3;
  printf("%d\n", result); */

  printf("end ex04\n");

}

int main(void)
{
  //lab_3_1();                //f11 입력시 위에 입력했던 lab_3_1로 이동됨.
  //ex01();
  //ex02();
  //test3_7();
  ex04();

  return 0;
}