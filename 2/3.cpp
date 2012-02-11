#include <cstdio>
#include <cstdlib>
#include <cmath>

const double PI = 3.14159265358979323846264338327950288;
const double E =  2.718281828459045235360287471352;

// http://www.seijo.ac.jp/pdf/faeco/kenkyu/118/118-sekimoto.pdf
// http://ja.wikipedia.org/wiki/%E3%82%AC%E3%83%B3%E3%83%9E%E9%96%A2%E6%95%B0
double c[7] = {
    1.000000000178,
   76.180091729406,
  -86.505320327112,
   24.014098222230,
   -1.231739516140,
    0.001208580030,
   -0.000005363820
};
double A(double x) {
  double ret = c[0];
  for (int i = 1; i < 7; i++) {
    ret += c[i] / (x + i - 1);
  }
  return ret;
}
double Gamma(double x) {
  x++;
  double ret = 0.0;
  if (x < 0) {
    ret = PI / sin(PI * x) / -x / Gamma(-x - 1);
  } else {
    ret = sqrt(2 * PI) * pow(x + 4.5, x - 0.5) * pow(E, -x - 4.5) * A(x);
  }
  return ret;
}

int main() {
  double v;
  scanf("%lf", &v);
  if (v <= -2 || v > 10 || v == -1.0) {
    printf("%f is not valid input.\n", v);
    exit(1);
  }
  printf("%.8f\n", Gamma(v));
}
