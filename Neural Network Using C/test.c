#include <stdio.h>
#include <math.h>

int main() {
  printf("Hello World\n");
  int arr[5][5] = {{1, 4, 5, 2 ,5}, {2, 1, 4, 5, 5}, {1, 2, 5, 5, 5}, {1, 4, 5, 5, 2}, {1, 5, 2, 5, 2}};
  int size = sizeof(arr) / sizeof(arr[0]);
  size_t i, j;
  for(i = 0; i < size; i++) {
    for(j = 0; j < size; j++) {
      printf("%d ", arr[i][j]); 
   }    
  printf("\n");
  }
  return 0;
}
