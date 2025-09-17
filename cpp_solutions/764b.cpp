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

vector<unsigned long long> solve(vector<unsigned long long> inp) {
  bool right = true;
  vector<unsigned long long> result;
  for (int i = 0; i < inp.size(); ++i) {
    // Grab right, if looking at right, else left.
    auto cur = right ? inp.size() - 1 - i : i;
    result.push_back(inp.at(cur));
    // Handle the edge case in even sized lists. Double add on the middle point
    // and then move on.
    if (inp.size() % 2 == 0 && i == (inp.size() - 1) / 2) {
      result.push_back(inp.at(right ? cur - 1 : cur + 1));
      ++i;
    }
    right = !right;
  }
  return result;
}

int main(int argc, char **argv) {
  auto _ = read<unsigned long long>();
  auto input = read_line<unsigned long long>();
  auto result = solve(input);
  for (auto el : result) {
    cout << el << " ";
  }
  cout << endl;
}
