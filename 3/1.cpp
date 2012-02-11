#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <string>

#include <algorithm>
#include <iostream>
using namespace std;

void Usage(int argc, char *argv[]) {
  printf("Usage: %s Keyword\n", argv[0]);
  exit(1);
}

const int N = 300000;
string randStr;
void MakeRandStr(unsigned int r) {
  randStr.resize(N);
  for (int i = 0; i < N; i++) {
    r =  (r * 1103515245 + 12345) & 0xFFFFFFFF;
    randStr[i] =  0x61 + (26 * (r / 0x10000)) / 0x10000;
  }
}

bool OK(int skip, int start, const string &keyword, const string &str) {
  for (int i = 0; i < (int)keyword.size(); i++) {
    int index = start + i * skip;
    if (keyword[i] != randStr[index]) { return false; }
  }
  return true;
}

int main(int argc, char *argv[]) {
  if (argc != 2) { Usage(argc, argv); }
  string keyword = argv[1];
  string revKeyword = keyword;
  reverse(revKeyword.begin(), revKeyword.end());
  int len = keyword.size();
  if (len <= 1) {
    printf("Invalid Keyword!\n");
    exit(0);
  }
  //MakeRandStr(16);
  cin >> randStr;
  int n = randStr.size();
  for (int skip = 0; skip < n; skip++) {
    int use = 1 + (len - 1) * skip;
    for (int start = 0; start <= n - use; start++) {
      if (OK(skip, start, keyword, randStr) ||
          OK(skip, start, revKeyword, randStr)) {
        printf("%d,%d\n", skip, start);
      }
    }
  }
}
