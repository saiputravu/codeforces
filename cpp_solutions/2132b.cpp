#include <iostream>
#include <set>
#include <sstream>
#include <string>
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

void solve(string n) {
  // Solution
  // Track number of zeros we append
  // That is, we calculate the alternating mask of numbers
  // Then just check. The max number of times we check is strlen of n
  // Edge case:
  // - For zeros = 0, the number must be mirrored

  size_t size = n.size();
  size_t nn = stoul(n);
  vector<size_t> results;
  // Handle edge case
  // if (size % 2 == 0) {
  //   if (n.substr(0, size / 2) == n.substr(size / 2, size)) {
  //     results.insert(stoul(n.substr(0, n.size() / 2)));
  //   }
  // }

  // Handle regular cases
  for (size_t zeros = 0; zeros < n.size(); ++zeros) {
    // Ignore the digits we are zeroing
    string tmp = n.substr(0, size - zeros);
    // cout << "before: " << zeros << ":" << tmp << endl;

    int keep_count = 0;
    bool keep_side = true; // keep = true, zero = false
    for (size_t i = 0; i < tmp.size() - 1; ++i) {
      // If we are zeroing, then squash this to 0.
      if (!keep_side) {
        tmp.at(tmp.size() - 1 - i) = '0';
      }

      // Tracking whether we are zeroing or not zeroing.
      ++keep_count;
      if (keep_count >= zeros) {
        keep_count = 0;
        keep_side = !keep_side;
      }
    }

    // Add back the original zeros. Jank.
    string tmp2 = tmp;
    for (size_t i = 0; i < zeros; ++i) {
      tmp2.push_back('0');
    }

    // cout << "after: " << zeros << ":" << tmp << " == " << stol(tmp) << " vs.
    // "
    //      << stol(tmp) + stol(tmp2) << " vsvs. " << n << " |||| "
    //      << ((stol(tmp) + stol(tmp2)) == stol(n)) << endl;

    // For each number we generate, check whether x (without zeros) + y (with
    // zeros) is n
    if (stoul(tmp) + stoul(tmp2) == nn) {
      results.push_back(stoul(tmp));
    }
  }

  cout << results.size() << endl;
  if (results.size() == 0)
    return;
  for (auto it = results.rbegin(); it != results.rend(); ++it) {
    cout << *it << " ";
  }
  cout << endl;
}

int main(int argc, char *argv[]) {

  size_t n = read<size_t>();

  for (; n > 0; --n) {
    solve(std::to_string(read<size_t>()));
  }

  return 0;
}
