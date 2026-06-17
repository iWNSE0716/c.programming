#include "def.h"

void mat2d_to_1d_0(int array2d[][MAT_COLS], int* array1d, int rows, int cols)
{
  int i, j;
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      array1d[i * cols + j] = array2d[i][j];
    }
  }
}