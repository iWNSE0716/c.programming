#include <stdio.h>

/* int main(void)
{
  int i;
  int a;
  i = 2;
  a = 3;
  while (1) {

  }
  for (i = 0; i < 10; i++) {    //조건식 생략시 무한 반복
    if (i > 5) {
      continue;
    }
    printf("ch05 start \n");
  }
  return 0;
  */

/*
void ex01(void) {
  for (int a = 10, i = 2; i < a; i++)
    if (a % i == 0)
    {
      printf("Is not prime.");
      break;
    }
}
*/


/*
void ex02(void)
{
  for (int n = 12, i = 1; i < n; i++)
    if (n % i == 0)
      printf("%d", i);
}
*/

/*
void ex03(void) {
  int a = 12;           //num1
  int b = 27;           //num2

  for (int i= 1; i <= b; i++)
  {
    if ((a % i == 0) && (b % i == 0))
      printf("%d\n", i);
  }
}
*/

/*
void ex04(void) {
  int a = 3482;          //num
  int place = 0;
  while (1)
  {
    a /= 10;
    place += 1;
    if (a < 1) 
    {
      printf("%d digit", place);
      break;
    }
  }
}
*/

/*
void ex05(void) {
  int a = 4;            //num1
  int b = 10;           //num2
  while (a<=b)
  {
    printf("%d", a);
    a++;
  }
}
*/

/*
void ex06(void) {
  char ch1 = 'b';
  char ch2 = 'i';
  int d = ch2 - ch1;

  if (d > 0)
    while (1)
    {
      printf("%c", ch1);
      ch1 += 1;
      if (ch1 == (ch2+1))
      {
        break;
      }
    }
  else if (d < 0)
    while (1)
    {
      printf("%c", ch2);
      ch2 += 1;
      if (ch2 == (ch1+1))
      {
        break;
      }
    }
}
*/

/*
void ex07(void) {
  int a = 4;            //num1
  int b = 10;           //num2
  while (a <= b)
  {
    if (a % 2 == 1)
      printf("%d", a);
    a++;
  }
}
*/

/*
void ex08(void) {
  int a = 4;            //num1
  int b = 10;           //num2
  while (a <= b)
  {
    if (a % 2 == 0)
      printf("%d", a);
    a++;
  }
}
*/

/*
void ex09(void) {
  int a = 4;            //num1
  int b = 10;           //num2
  while (a <= b)
  {
    int c = 0;
    for (int i = 1; i <= a; i++)
    {
      if (a % i == 0)
      {
        c++;
      }
      
    }
    if (c <= 2)
      printf("%d ", a);
    a++;
    
  }
}
*/

/*
void ex10(void) {
  int a = 1;
  int num = 10;      //num1
  int sum = 0;
  while (a<num)
  {
    a++;
    if (a % 2 == 0) {
    printf(" + %d",a);
    sum = sum + a;
    }
  }
  printf(" = %d", sum);
}
*/

/*
void ex11(void) {
  int a = 1;
  int num = 10;     //num1
  int sum = 0;
  while (a < num)
  {
    if (a % 2 == 1) {
      printf(" + %d", a);
      sum = sum + a;
    }
    a++;
  }
  printf(" = %d", sum);
}
*/

/*
void ex12(void) {
  int a = 5;     //num1
  int product = 1;
  while (a >= 1)
  {
    product = product * a;
    printf(" X %d", a);
    a--;
  }
  printf(" = %d", product);
}
*/

/*
void ex13(void) {
  int a = 5;   //num1
  int b = 3;   //num2
  int product = 1;
  while (a >= b)
  {
    product = product * a;
    printf(" X %d", a);
    a--;
  }
  printf(" = %d", product);
}
*/

/*
void ex14(void) {
  int num = 10;
  int a = 0;
  while (1)
  {
    num = num / 2;
    a++;
    if (num == 1)
    {
      printf("%d BIT", a+1);
      break;
    }
  }
}
*/

/*
void ex15(void) {
  int i, n;
  for (i = 0; i <= 5; i++) {
    for (n = 0; n < i; n++) {
      printf("*");
    }
    printf("\n");
  }
}
*/

/*
void ex16(void) {
  int i, n;
  for (i = 5; i >= 0; i--) {
    for (n = 0; n < i; n++) {
      printf("*");
    }
    printf("\n");
  }
}
*/

/*
void ex17(void) {
  int i, n, c;
  for (i = 4; i >= 0; i--) {
    for (n = 0, c = 0; n < i; n++) {
      printf(" ");                   //"_" 코드를 먼저 써야 하기 때문에 "*" 코드 위에 놓는다
      c++;
    }
    for (n = 5; n > c; n--) {
      printf("*");
    }
    printf("\n");
  }
}
*/

/*
void ex18(void) {
  int i, n, c = 0;
  for (i = 5; i >= 0; i--) {
    for (n = 0; n < c; n++) {
      printf(" ");                  //마찬가지로 "_" 코드를 먼저 써야 하기 때문에 "*" 코드 위에 놓는다
    }
    for (n = 0; n < i; n++) {
      printf("*"); 
    }
    printf("\n");
    c++;
  }
}
*/

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
  //ex11();
  //ex12();
  //ex13();
  //ex14();
  //ex15();
  //ex16();
  //ex17();
  //ex18();
  return 0;
}