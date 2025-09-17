#include <algorithm>
#include <functional>
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

// There is one edge case to handle. What if i=0, j=1. That is the extra check
// on return.
size_t solve(vector<size_t> inp) {
  // guaranteed: inp.size() >= 2
  size_t min_so_far = inp.at(0);
  size_t sum_so_far = inp.at(0);
  for (auto it = next(inp.begin()); it != inp.end(); ++it) {
    if (min_so_far <= *it) {
      // Then we have a stagnant point, we can choose this for i.
      // This means everything after i is 0. So just account for i, and return.
      return min(sum_so_far + min_so_far, inp.at(0) + inp.at(1));
    }

    // Otherwise, we have an improvement on our min. Update our sum.
    min_so_far = *it;
    sum_so_far += min_so_far;
  }
  return min(sum_so_far, inp.at(0) + inp.at(1));
}

int main() {
  auto n = read<size_t>();

  for (; n > 0; --n) {
    // Ignore elements in array
    auto nn = read<size_t>();

    auto inp = read_line<size_t>();
    cout << solve(inp) << endl;
  }
}
