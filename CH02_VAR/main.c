//#include <stdio.h>
//
//int main(void)
//{
//	int x = 100;
//	int y = 200;
//	int avg;
//	int c = 0;
//	char ch = 'b';
//
//	avg = (x + y) / 2;
//	c = x;
//	c = c + avg;
//	printf("x = %d, y= %d\n", x, y);
//	printf("avg: %d\n", avg);
//	return 0;
//}




#include <stdio.h>

int main(void)
{
	int x;

	printf("변수의 x의 크기: %d\n", sizeof(x));
	printf("char 형의 크기 : %d\n", sizeof(char));
	printf("int 형의 x의 크기: %d\n", sizeof(int));
	printf("short 형의 x의 크기: %d\n", sizeof(short));
	printf("long 형의 x의 크기: %d\n", sizeof(long));
	printf("float 형의 x의 크기: %d\n", sizeof(float));
	printf("double 형의 x의 크기: %d\n", sizeof(double));
}