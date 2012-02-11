#include <cstdio>
#include <cstdlib>

bool LeapYear(int year) {
  return year % 400 == 0 || (year % 100 != 0 && year % 4 == 0);
}

bool Before(int thisYear, int thisMonth, int thisDay, int tYear, int tMonth, int tDay) {
  if (thisYear != tYear) { return thisYear < tYear; }
  if (thisMonth != tMonth) { return thisMonth < tMonth; }
  return thisDay < tDay;
}

const int MonthDay[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int main() {
  int a, b, c, d, e, f, n;
  int v = scanf("%d %d %d %d %d %d %d", &a, &b, &c, &d, &e, &f, &n);
  if (v != 7) {
    printf("input:BirthYear BirthMonth BirthDay ThisYear ThisMonth ThisDay n\n");
    exit(1);
  }
  if (a < 1990 || 2000 < a || n != 80) {
    printf("Invalid Input!\n");
    exit(1);
  }
  int totalDay = 0;
  int today = 0;
  for (int year = a; year <= a + n + 1; year++) {
    for (int month = 0; month < 12; month++) {
      int Day = MonthDay[month];
      if (LeapYear(year) && month == 1) { Day = 29; }
      for (int day = 0; day < Day; day++) {
        if (!Before(year, month + 1, day + 1, a, b, c)) {
          if (Before(year, month + 1, day + 1, a + n + 1, b, c))  { totalDay++; }
          if (Before(year, month + 1, day + 1, d, e, f)) { today++; }
        }
      }
    }
  }
  if (totalDay <= today) {
    printf("You are Dead!\n");
    exit(1);
  }
  int sec = (long long)60 * 60 * 24 * today / totalDay;
  printf("%02d:%02d:%02d\n", sec / 3600, sec / 60 % 60, sec % 60);
}
