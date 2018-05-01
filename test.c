#include <stdio.h>
#include <stdlib.h>

int main() {
  double * array = malloc(sizeof(double) * 20);
  printf("%lu\n", sizeof(*array));
  return 0;
}
