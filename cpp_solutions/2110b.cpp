#include <cstddef>
#include <iostream>
#include <sstream>
#include <stack>
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

string solve(string inp) {
  /*
   Solution:
   Any time you have MULTIPLE top levels (i.e. rule AB) at the top level, it is
   possible to fuck up. However, if you have top level as rule (A), then it is
   not really possible? I guess the outter () replenish the inner lost (). If
   the AB rule is outermost, then it is not possible to replenish.

   To detect whether the outermost rule is (A) or AB, we have to check using
   stacks. We can't just check start and end, as it could be i.e. ()(), which
   would look like (A). Thus, we consume until stack is empty. Each time this is
   true, before consuming the entire string, we can increment a counter. Once we
   finish, if the counter is >1, then we can say we have AB outside.
  */

  stack<char> s;
  size_t empties = 0;
  for (auto c : inp) {
    if (empties > 0) {
      // If we have seen the stack empty at least once, AND there is a new
      // character to consume, this is for sure an AB situation.
      return "YES";
    }
    // As we consume each character in the input, we append to the stack and
    // note when it becomes empty. We only push to stack on openings or empty
    // stack immediately, otherwise, we check top of stack.
    if (s.empty() || c == '(') {
      s.push(c);
    } else if (s.top() == '(') {
      // Here, c == ')' -- so we pop off the stack, if an immediate match has
      // been found.
      s.pop();
    } else {
      // Otherwise, we have double )) in our input stream. So we just push.
      s.push(c);
    }

    // Now we check whether the stack became empty again. If so, we increment
    // the counter we are tracking.
    if (s.empty()) {
      ++empties;
    }
  }

  // Reaching here means the stack has been fully consumed, but not been empty
  // (in an AB situation).
  return "NO";
}

int main(int argc, char **argv) {

  size_t n = read<size_t>();

  for (; n > 0; --n) {
    auto input = read<string>();
    cout << solve(input) << endl;
  }

  return 0;
}
