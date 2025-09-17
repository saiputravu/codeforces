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

const vector<vector<size_t>> poop{{2, 3, 5, 7},
                                  {2 * 3, 2 * 5, 2 * 7, 3 * 5, 3 * 7, 5 * 7},
                                  {2 * 3 * 5, 3 * 5 * 7, 5 * 7 * 2, 7 * 2 * 3},
                                  {2 * 3 * 5 * 7}};

size_t solve(size_t num) {
  unsigned long long total = 0;

  int sign = 1;
  for (auto row : poop) {
    size_t sum = 0;
    for (auto el : row) {
      sum += num / el;
    }
    total += sign * sum;
    sign *= -1;
  }
  return num - total;
}

int main() {
  size_t n = read<size_t>();

  for (; n > 0; --n) {
    auto inp = read_line<size_t>();
    cout << solve(inp[1]) - solve(inp[0] - 1) << endl;
  }
}
