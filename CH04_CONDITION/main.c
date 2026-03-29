#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>            //ex07, ex08 헤더

/*int main(void) {
  int number = 10;
  int remain;

  remain = number % 2;
  if (remain == 0) {
    printf("even\n");
  }
  else {
    printf("odd\n");
  }
  return 0;
}
int main(void) {

  int x = 10;
  int a = 2;
  int b = 20;

  if (a < x) {
    if (x, b) {
      // printf("x는 a 와 b 사이에 있습니다\n");
      printf("x는 a 와 b 사이에 있습니다\n", x, a, b);
    }
    else { // x 가 b보다 크거나 같은 경우
      printf("%d는 %d와 %d 보다 큽니다\n", x, a, b);
    }
  }
  // &&: 그리고
  // ||: 또는
  if ((a < x) && (x < b)) {
    printf("x는 a 와 b 사이에 있습니다\n", x, a, b);
  }
  else if ((a < x) && (x > b)) {
    printf("%d는 %d와 %d 보다 큽니다\n", x, a, b);
  } */

  /*
  void ex01(void)
  {
    int a = 5;
    int b = 4;
    int c = 3;

    if (a > b) {
      if (a > c) {
        printf("%d", a);
      }
      else if (a < c) {
        printf("%d", c);
      }
      }
    else if (a < b) {
      if (b > c) {
        printf("%d", b);
      }
        else if (b < c) {
          printf("%d", c);
        }
        }
      }
      */

      /*
      void ex02(void)
      {

        int a = 1;
        int b = 4;
        int c = 3;

        if (a > b) {
          if (b > c) {
            printf("%d", c);
          }
          else if (a < c) {
            printf("%d", b);
          }
        }
        else if (a < b) {
          if (a > c) {
            printf("%d", c);
          }
          else if (a < c) {
            printf("%d", a);
          }
        }

      }
      */

      /*
      void ex03(void)
      {

        int a = 3;
        int b = 5;

        if (a > b) {
          printf("오름차순: % d % d", b, a);
        }
        else if (a < b) {
          printf("오름차순: % d % d", a, b);
        }

      }
      */

      /*
      void ex04(void)
      {

        int a = 3;
        int b = 5;

        if (a > b) {
          printf("내림차순: % d % d", a, b);
        }
        else if (a < b) {
          printf("내림차순: % d % d", b, a);
        }

      }
      */

      /*
      void ex05(void)
      {

        int a = 4;
        int b = 6;
        int c = 7;
        if (a > b) {
          if (b > c)
            printf("내림차순: %d %d %d", a, b, c);
          else if (c > a)
            printf("내림차순: %d %d %d", c, b, a);
          else
            printf("내림차순: %d %d %d", b, c, a);
        }
        else if (a < b) {
          if (c < a)
            printf("내림차순: %d %d %d", c, a, b);
          else if (b < c)
            printf("내림차순: %d %d %d", c, b, a);
          else
            printf("내림차순: %d %d %d", b, c, a);
        }

      }
      */

      /*
      void ex06(void)
      {
        int a = 15; //4비트이기에 10진수로 0~15 이여야함.

        if (a / 8 == 1) //4비트 자리
        {
          printf("1");
        }
        else
        {
          printf("0");
        }
        a = a % 8; // 나머지 7                               15 = (8*1)+7

        if (a / 4 == 1) //3비트 자리
        {
          printf("1");
        }
        else
        {
          printf("0");
        }
        a = a % 4; //나머지 3                               7 = (4*1)+3

        if (a / 2 == 1) //2비트 자리
        {
          printf("1");
        }
        else
        {
          printf("0");
        }
        a = a % 2; //나머지 1                               3 = (2*1)+1

        if (a / 1 == 1) //1비트 자리
        {
          printf("1");
        }
        else
        {
          printf("0");
        }
      }
      */

      /*
      void ex07(void)
      {
        double a, b, c, dis;

        printf("계수 a, 계수 b, 계수 c를 차례대로 입력하시오: ");
        scanf("%lf %lf %lf", &a, &b, &c);

        if (a == 0)
          printf("방정식의 근은 %f입니다.", -c / b);
        else
        {
          dis = ( b * b ) - (4.0 * a * c); //ex. x^2 - 4x + 4  ->   a=1 b=-4 c=4   ->      "" ( -b +_루트[ b^2 - 4ac ]) / 2 ""a,b,c를 대입  #sprt(루트)  #근의 공식      중근일때는 +_루트[ b^2 - 4ac ]는 0 이됨.
          if (dis > 0)
          {
            printf("방정식의 근은 %.2f입니다.\n", (-b + sqrt(dis)) / (2.0 * a));
            printf("방정식의 근은 %.2f입니다.\n", (-b - sqrt(dis)) / (2.0 * a));
          }
          else if (dis == 0)
          {
            printf("방정식의 근은 %.2f입니다.\n", (-b) / (2.0 * a));
          }
          else
            printf("실근이 존재하지 않습니다\n");
        }
      }
      */

      /*
      void ex08(void)
      {
        double a, b, c, dis;
        int sign;

        printf("계수 a, 계수 b, 계수 c를 차례대로 입력하시오: ");
        scanf("%lf %lf %lf", &a, &b, &c);
        //a = 1;
        //b = -4;
        //c = 4;

        if (a == 0)
          printf("방정식의 근은 %f입니다.", -c / b);
        else
        {
          dis = ((b * b)-(4.0*a*c));
          if (dis > 0) //switch문은 비교연산자 사용불가
            sign = 1;
          else if (dis == 0)
            sign = 0;
          else
            sign = 2;

          switch (sign)
          {
          case 0:
            printf("방정식의 근은 %.2f입니다.\n", (-b) / (2.0 * a));
            break;
          case 1:
            printf("방정식의 근은 %.2f입니다.\n", (-b + sqrt(dis)) / (2.0 * a));
            printf("방정식의 근은 %.2f입니다.\n", (-b - sqrt(dis)) / (2.0 * a));
            break;
          case 2:
            printf("실근이 존재하지 않습니다\n");
            break;
          }
        }
      }
      */

      /*
      void ex09(void)
      {
        int a = 4;
        int b = 2;
        if (a % b == 0)
          printf("약수 YES");
        else
          printf("약수 NO");
      }
      */

      /*
      void ex10(void)
      {
        int x = 10;
        int y = -2;

          if ((x > 0) && (y > 0))
          {
            printf("1사분면 입니다.");
          }
          else if ((x < 0) && (y > 0))
          {
            printf("2사분면 입니다.");
          }
          else if ((x < 0) && (y < 0))
          {
            printf("3사분면 입니다.");
          }
          else if ((x > 0) && (y < 0))
          {
            printf("4사분면 입니다.");
          }
      }
      */

      /*
      void ex11(void)
      {
        int month = 1;

        if (month <= 3)
          printf("spring");
        else if ((month > 3) && (month <= 6))
          printf("summer");
        else if ((month > 6) && (month <= 9))
          printf("fall");
        else if ((month > 9) && (month <= 12))
          printf("winter");
        else
          printf("input 1 and between 12.");
      }
      */

      /*
      void ex12(void)
      {
        int month = 1;

        switch (month)
        {
        case 1: case 2: case 3:
          printf("spring");
          break;
        case 4: case 5: case 6:
          printf("summer");
          break;
        case 7: case 8: case 9:
          printf("fall");
          break;
        case 10: case 11: case 12:
          printf("winter");
          break;
        default:
          printf("input 1 and between 12.");
          break;
        }
      }
      */

int main(void) {
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
  //ex11();
  //ex12();
  return 0;
}