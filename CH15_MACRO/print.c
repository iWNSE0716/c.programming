#include <stdio.h>
#include "def.h"

void print_hello(void)
{
  printf("Hello, World!\n");
}
void print_student(Student* student)
{
  printf("id: %d, name: %s\n", student->id, student->name);
}

void print_array_1d(int* array, int length)
{
  int i;
  for (i = 0; i < length; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}