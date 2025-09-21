#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

template <typename T> T read() {
  T value;
  cin >> value;
  cin.ignore();
  return value;
}

template <typename T> vector<T> read_line(char delim = ' ', size_t len = 0) {
  vector<T> result;
  if (len != 0) {
    result.reserve(len);
  }

  string line, inline_buf;
  T t;

  getline(cin, line);
  istringstream iss(line);

  while (iss >> t)
    result.push_back(t);

  return result;
}

size_t solve(size_t n, size_t k, vector<size_t> &a) {
  // Collect counts
  // ai -> count
  unordered_map<size_t, size_t> counts;
  for (auto ai : a) {
    ++counts[ai];
  }

  // Condition 1 check.
  // All elements must be equally splittable between all multisets.
  for (auto [ai, count] : counts) {
    if (count % k != 0) {
      return 0;
    }
    counts[ai] = static_cast<size_t>(count / k);
  }

  // Condition 2 check, for each subarray.
  // Now explore l,r
  size_t l = 0, r = 0, valid = 0;
  // Track window only element counts.
  unordered_map<size_t, size_t> counts_window;

  const size_t max_window_size = static_cast<int>(a.size() / k);
  r = max_window_size - 1;

  while (l <= r && l - max_window_size < n) {
  }

  return valid;
}

int main(int argc, char *argv[]) {
  auto n = read<size_t>();

  for (; n > 0; --n) {

    auto l1 = read_line<size_t>();
    auto a = std::move(read_line<size_t>(' ', l1.at(0)));
    cout << solve(l1.at(0), l1.at(1), a) << endl;
  }

  return 0;
}
