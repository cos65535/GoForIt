#include <cstdio>
#include <cassert>
#include <cstdlib>

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Input {
  int id;
  int time;
  int from;
  int to;
  Input() {;}
  Input(int id, int time, int from, int to) :
    id(id), time(time), from(from), to(to) {;}
  bool operator<(const Input &rhs) const {
    return id < rhs.id;
  }
  static Input Load(FILE *fp) {
    int id, time, from, to;
    int v = fscanf(fp, "%d,%d,%d,%d", &id, &time, &from, &to);
    if (v < 4) {
      return Input(0xdeadbeaf, 0xdeadbeaf, 0xdeadbeaf, 0xdeadbeaf);
    }
    return Input(id, time, from, to);
  }

  static vector<Input> LoadAll(const char *filename) {
    vector<Input> ret;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) { return ret; }
    while (true) {
      Input input = Load(fp);
      if (input.id == (int)0xdeadbeaf) { break; }
      ret.push_back(input);
    }
    fclose(fp);
    return ret;
  }
};

struct Output {
  int id;
  int time;
  int floor;
  char open;
  vector<int> users;
  Output() {;}
  Output(int id, int time, int floor, char open, const vector<int> &u)
    : id(id), time(time), floor(floor), open(open), users(u)
  {
    sort(users.begin(), users.end());
    while (users.size() > 0) {
      if (users[0] == 0) { users.erase(users.begin()); }
    }
  }
  void Print() {
    printf("%d,%d,%d,%c", id, time, floor, open);
    int u[5] = { 0, 0, 0, 0, 0 };
    assert(users.size() <= 5);
    for (int i = 0; i < (int)users.size(); i++) { u[i] = users[i]; }
    for (int i = 0; i < 5; i++) {
      printf(",%d", u[i]);
    }
    printf("\n");
  }
  static Output Load(FILE *fp) {
    int id, time, floor;
    char open;
    vector<int> users;
    int v = fscanf(fp, "%d,%d,%d,%c", &id, &time, &floor, &open);
    if (v < 4) { goto end; }
    for (int i = 0; i < 5; i++) {
      int user;
      int v = fscanf(fp, ",%d", &user);
      if (v > 0) { goto end; }
      users.push_back(user);
    }
    return Output(id, time, floor, open, users);
end:
    return Output(0xdeadbeaf, 0xdeadbeaf, 0xdeadbeaf, -1, vector<int>(5, 0xdeadbeaf));
  }

  static vector<Output> LoadAll(const char *filename) {
    vector<Output> ret;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) { return ret; }
    while (true) {
      Output output = Load(fp);
      if (output.id == (int)0xdeadbeaf) { break; }
      ret.push_back(output);
    }
    fclose(fp);
    return ret;
  }
};

void Usage(int argc, char *argv[]) {
  printf("Usage: %s input", argv[0]);
  exit(1);
}
int main(int argc, char *argv[]) {
  if (argc != 2) { Usage(argc, argv); }
  vector<Input> inputs = Input::LoadAll(argv[1]);
  sort(inputs.begin(), inputs.end());
  Output state(1, 0, 1, 'E', vector<int>());
  vector<Output> outputs;
  for (int i = 0; i < (int)inputs.size(); i++) {
    int from = inputs[i].from;
    int to = inputs[i].to;

    // move
    if (state.floor != from) {
      if (state.open == 'B') {
        // close
        assert(state.users.size() == 0);
        state.time += 5;
        state.users = vector<int>();
        state.open = 'E';
        outputs.push_back(state);
      }
      state.time += abs(state.floor - from) * 2;
      state.floor = from;
    }

    // open
    state.open = 'B';
    outputs.push_back(state);

    // close
    state.time = max(state.time + 5, inputs[i].time);
    state.open = 'E';
    state.users = vector<int>(1, inputs[i].id);
    outputs.push_back(state);

    // move & open
    state.time += abs(state.floor - to) * 2;
    state.floor = to;
    state.open = 'B';
    outputs.push_back(state);

    state.users.clear();
  }
  for (int i = 0; i < (int)outputs.size(); i++) {
    outputs[i].Print();
  }
}
