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

vector<size_t> solve(size_t n, size_t x) {
  vector<size_t> result(n, x);
  if (n == 1) {
    return {x};
  }

  size_t running_total = 0;
  for (int i = 0; i < n; ++i) {
    if (i == 0 | (x & i) == i) {
      result.at(i) = i;
      running_total |= i;
    }
  }
  if (running_total != x) {
    result.at(n - 1) = x;
  }

  return result;
}

int main(int argc, char *argv[]) {
  size_t n = read<size_t>();

  for (; n > 0; --n) {
    auto inp = read_line<size_t>();
    for (auto el : solve(inp.at(0), inp.at(1))) {
      cout << el << " ";
    }
    cout << endl;
  }

  return 0;
}
