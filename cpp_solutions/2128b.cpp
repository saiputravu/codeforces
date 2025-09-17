#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

template <typename T> T read() {
  T value;
  cin >> value;
  cin.ignore();
  return value;
}

template <typename T> vector<T> read_line(char delim = ' ') {
  vector<T> result;
  string line, inline_buf;
  T t;

  getline(cin, line);
  istringstream iss(line);

  while (iss >> t)
    result.push_back(t);

  return result;
}

void solve(vector<size_t> &inp) {
  bool lesser = true;
  size_t front = 0;
  size_t back = inp.size() - 1;

  while (front < back) {
    if (lesser) {
      if (inp.at(front) <= inp.at(back)) {
        cout << "LR";
      } else {
        cout << "RL";
      }
    } else {
      if (inp.at(front) >= inp.at(back)) {
        cout << "LR";
      } else {
        cout << "RL";
      }
    }
    front++;
    back--;
    lesser = !lesser;
  }
  if (inp.size() % 2 != 0) {
    cout << "L";
  }
  cout << endl;
}

int main() {
  size_t n = read<size_t>();

  for (; n > 0; --n) {
    read<size_t>();
    auto inp = read_line<size_t>();
    solve(inp);
  }
}
