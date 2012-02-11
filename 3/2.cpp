#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <string>

#include <algorithm>
#include <vector>
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
  for (int i = 2; i < (int)keyword.size(); i++) {
    int index = start + i * skip;
    if (keyword[i] != randStr[index]) { return false; }
  }
  return true;
}

// O((N / 26)^2 * len)
vector<int> indeces[256];
int main(int argc, char *argv[]) {
  // input
  if (argc != 2) { Usage(argc, argv); }
  string keyword = argv[1];
  int len = keyword.size();
  if (len <= 1) {
    printf("Invalid Keyword!\n");
    exit(1);
  }
  cin >> randStr;
  int n = randStr.size();
  if (n == 0) {
    printf("Invalid Keyword!\n");
    exit(1);
  }

  // make indeces
  for (int i = 0; i < n; i++) {
    int c = randStr[i];
    indeces[c].push_back(i);
  }
  vector<pair<int, int> > answer;
  for (int iter = 0; iter < 2; iter++) {
    const int c1 = keyword[0];
    const int c2 = keyword[1];
    for (int i = 0; i < (int)indeces[c1].size(); i++) {
      for (int j = 0; j < (int)indeces[c2].size(); j++) {
        int start = indeces[c1][i];
        int skip = indeces[c2][j] - indeces[c1][i];
        int use = 1 + (len - 1) * skip;
        if (skip < 0 || start > n - use) { continue; }
        if (OK(skip, start, keyword, randStr)) {
          answer.push_back(make_pair(skip, start));
        }
      }
    }
    // reverse keyword
    string revKeyword = keyword;
    reverse(revKeyword.begin(), revKeyword.end());
    if (keyword == revKeyword) { break; }
    keyword = revKeyword;
  }

  sort(answer.begin(), answer.end());
  for (int i = 0; i < (int)answer.size(); i++) {
    printf("%d,%d\n", answer[i].first, answer[i].second);
  }
}
