#include<stdio.h>
int ex3(int x);

int main (void) {
  int i;

  printf("\nEntre um numero:\t");
  scanf("%d", &i);
  printf("\nFatorial de n = %d\n", ex3(i));

  return 0;
}
