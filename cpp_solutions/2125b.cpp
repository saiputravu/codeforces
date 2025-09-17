#include <iostream>
#include <numeric>
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

size_t solve(size_t a, size_t b, size_t k) {
  // Edge Case
  if (a <= k && b <= k)
    return 1;

  // We now need to differentiate between 2 and 1.
  // Cases:
  //  - 2: all cases except 1
  //  - 1: if the GCD(a, b) == 1, then for sure 2
  //       if the GCD(a, b) > 1:
  //         - then if max(a / gcd, b / gcd) <= k then 1
  //         - else 2

  size_t g = std::gcd(a, b);

  if (g == 1)
    return 2;
  if (max({a / g, b / g}) <= k)
    return 1;
  return 2;
}

int main(int argc, char *argv[]) {

  size_t n = read<size_t>();

  for (; n > 0; --n) {
    vector<size_t> input = read_line<size_t>();
    cout << solve(input[0], input[1], input[2]) << endl;
  }

  return 0;
}
