#include <bitset>
#include <climits>
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

void solve(vector<size_t> inp) {

  size_t n = inp.size();
  vector<size_t> min_left(n, 0), max_right(n, 0);

  // Fill the answers in tables.
  size_t min_so_far = ULONG_MAX;
  size_t max_so_far = 0;
  for (int i = 0; i < n; ++i) {
    if (i != 0) {
      min_so_far = min({min_so_far, inp.at(i - 1)});
      max_so_far = max({max_so_far, inp.at((n - 1) - (i - 1))});
    }
    min_left.at(i) = min_so_far;
    max_right.at(n - 1 - i) = max_so_far;
  }

  for (int i = 0; i < n; ++i) {
    size_t el = inp.at(i);
    if (min_left.at(i) < el && max_right.at(i) > el) {
      // No chance mate
      cout << "0";
    } else {
      cout << "1";
    }
  }

  cout << endl;
}

int main() {

  size_t n = read<size_t>();

  for (; n > 0; --n) {
    // Ignore n elements
    read<size_t>();

    auto inp = read_line<size_t>();
    solve(inp);
  }

  return 0;
}
