#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
int multy2(int a, int b)
{
  return a * b;
}

int multy3(int a, int b, int c)
{
  return a * b * c;
}

int main(void)
{
  int x = 10;
  int y = 2;
  int z = 3;
  int result = 0;
  result = multy2(x, y);
  printf("&d\n", result);

  printf("&d\n", multy3(x, y, z));

  printf("function\n");
    return 0;
}
*/

/*
  int calc_factorial(int num)
  {
    int i;
    int result = 1;
    for (i = num; i > 1; i--) {
      result = result * i;
    }
    printf("%d",result);
    return result;
  }
 */

  /*
  int clac_permutation(int n, int r) 
  {
    int permutation;
    int i;
    int d = n - r;
    int result1 = 1;
    int result2 = 1;
    
    for (i = n; i > 1; i--) {
      result1 = result1 * i;
    }
    for (i = d; i > 1; i--) {
      result2 = result2 * i;
    }
    permutation = result1 / result2;
    printf("%d", permutation);
    return permutation;
  }
  */

/*
int clac_combination(int n, int r)
{
  int combination;
  int i;
  int d = n - r;
  int resultn = 1;
  int resultd = 1;
  int resultr = 1;

  for (i = n; i > 1; i--) {
    resultn = resultn * i;
  }
  for (i = d; i > 1; i--) {
    resultd = resultd * i;
  }
  for (i = r; i > 1; i--) {
    resultr = resultr * i;
  }
  printf("n:%d d:%d r:%d\n",resultn,resultd,resultr);
  combination = (resultn / (resultr * resultd));
  printf("COMBINATION : %d", combination);
  return combination;
}
*/

/*
int get_gcd(int num1, int num2)
{
  int gcd = 1;
  int a;
  if (num1 > num2)
    a = num2;
  else if (num1 < num2)
    a = num1;
  for (int i= 1; i <= a; i++)
  {
    if ((num1 % i == 0) && (num2 % i == 0))
      gcd = i;
  }
  printf("%d", gcd);
}
*/

/*
int get_first_digit(int n)
{
  while (n >= 10)
  {
    n /= 10; 
  }
  printf("%d", n);
  return n;
}
*/

/*
int get_lcmA(int num1, int num2)
{
  int gcd = 1;
  int a;
  int lcm = 1;
  if (num1 > num2)
    a = num2;
  else if (num1 < num2)
    a = num1;
  for (int i = 1; i <= a; i++)
  {
    if ((num1 % i == 0) && (num2 % i == 0))
      gcd = i;
  }
  lcm = ((num1 * num2) / gcd);
  printf("%d", lcm);
}
*/

/*
int get_lcmB(int num1, int num2)
{
  int gcd = get_gcd(num1, num2);
  int a = num1 / gcd;
  int b = num2 / gcd;

  return a * b * gcd;
}
*/

/*
int get_number_of_digit(int number)
{
  int digit = 0;
  int i;
  for (i = 1; number > 1; i++)
  {
    digit = i + 1;
    number = number / 8;
  }


  printf("digit = %d\n", digit);
  return digit;
}
*/

/*
void print_octal_number(int number) {
    if (number == 0) {
        printf("0");
        return;
    }
    int temp = number;
    int divisor = 1;
    while (temp >= 8) {
        temp = temp / 8;
        divisor = divisor * 8;
    }
    while (divisor > 0) {
        int digit = number / divisor;
        printf("%d ", digit);
        number = number % divisor;
        divisor = divisor / 8;
    }
    printf("\n");
}
*/

/*
void print_number_system(int number, int n) {
  if (number == 0) {
    printf("0");
    return;
  }
  int temp = number;
  int divisor = 1;
  while (temp >= n) {
    temp = temp / n;
    divisor = divisor * n;
  }
  printf("%d진수 각 자리수: ", n);
  while (divisor > 0) {
    int digit = number / divisor;
    printf("%d ", digit);

    number = number % divisor;
    divisor = divisor / n;
  }
  printf("\n");
}
  return 0;
}
*/

/*
void random()
{
  int i;
  int random_number;
  for (i = 0; i < 10; i++) {
    random_number = rand();
    printf("%d\n", random_number);
  }
  return 0;
}
*/

/*
void randseed(int seed)
{
    int i;
    int random_number;

    srand(seed);

    for (i = 0; i < 10; i++) {
        random_number = rand();
        printf("%d\n", random_number);
    }

    return 0;
}
*/

/*
void randreturn()
{
  int i;
  int random_number;

  srand((unsigned int)time(NULL));

  for (i = 0; i < 10; i++) {
    random_number = rand();
    printf("%d\n", random_number);
  }

  return 0;
}
*/

/*
int generate_random_int()
{
  int random_number;
  int seed = rand();
  srand(time(NULL) + seed);
  random_number = rand();
  srand(random_number * seed);
  return rand();;
}
*/

/*
int generate_random_int()
{
  int random_number;
  int seed = rand();
  srand(time(NULL) / seed);
  random_number = rand();
  srand(clock());
  return random_number;
}
*/

/*
int generate_dice_number()
{
  int random_number = generate_random_int();
  return (random_number % 6) + 1;
}
*/

/*
void randD(void)
{
  int i;
  int dice_number;
  for (i = 0; i < 18; i++) {
    dice_number = generate_dice_number();
    printf("dice number=%d\n", dice_number);
  }
}
*/

/*
void randF(void)
{
  int mable_number1;
  int mable_number2;
  int i;
  for (i = 0; i < 10; i++) {
    do {
      mable_number1 = generate_dice_number();
      mable_number2 = generate_dice_number();
      printf("%d %d\n", mable_number1, mable_number2);
    } while (mable_number1 == mable_number2);
  }
}
*/

/*
int generate_yut_number(void)
{
  int random_number = generate_random_int();
  return (random_number % 5) + 1;
}

void randG(void)
{
  int yut_number;
  int i;

  for (i = 0; i < 10; i++) {
    do {
      yut_number = generate_yut_number();
      printf("yut number=%d\n", yut_number);
    } while (yut_number == 4 || yut_number == 5);
  }
}
*/

int main(void)
{
  //calc_factorial(4);
  //clac_permutation(3, 1);
  //clac_combination(3, 1);
  //get_gcd(30,45);
  //get_first_digit(3234);
  //get_lcmA(30, 45);
  //get_lcmB(30, 45);
  //get_number_of_digit(34567);
  //print_octal_number(34567);
  //print_number_system(1001, 2);
  //random();
  //randseed(1234);
  //randreturn();
  //randD();
  //randF();
  //randG();
}