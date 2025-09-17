#include <cmath>
#include <filesystem>
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

#define NBITS 32
size_t solve(vector<size_t> &inp) {
  // Create table of bits. Max number is 2^30.
  size_t bits[NBITS] = {};

  // For each element tally the number of set bits in each position.
  // Add bits right to left.
  for (auto el : inp) {
    size_t counter = NBITS - 1;
    while (el) {
      if ((el & 1) == 1)
        ++bits[counter];
      el >>= 1;
      counter--;
    }
  }

  // Now find the best summation
  // For each element ak, for each bit (all 32), count the number of opposite
  // bits "set". Multiply this by power of 2.
  size_t best = 0;
  for (auto ak : inp) {
    size_t sum = 0;
    size_t bit_counter = 0;
    for (size_t bit_counter = 0; bit_counter < NBITS; ++bit_counter) {
      if (ak & (1 << bit_counter)) {
        // bit set, we want number of times zeros seen in that bit position.
        sum +=
            (1 << bit_counter) * (inp.size() - bits[NBITS - 1 - bit_counter]);
      } else {
        // bit unset, we want number of times ones seen in that bit position.
        // Easier.
        sum += (1 << bit_counter) * bits[NBITS - 1 - bit_counter];
      }
    }
    best = max({best, sum});
  }

  return best;
}

int main(int argc, char **argv) {
  auto t = read<size_t>();

  for (; t > 0; --t) {
    auto n = read<size_t>();
    auto inp = read_line<size_t>();
    cout << solve(inp) << endl;
  }

  return 0;
}
