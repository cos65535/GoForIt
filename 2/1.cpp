#include <cstdio>
#include <cstdlib>

int fact(int v) {
  if (v == 0) { return 1; }
  return v * fact(v - 1);
}

int main() {
  int v;
  scanf("%d", &v);
  if (v < 0 || v > 10) {
    printf("%d is not valid input.\n", v);
    exit(1);
  }
  printf("%d\n", fact(v));
}
