#include <algorithm>
#include <iostream>
#include <random>
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

struct bst {
  size_t duplicate = 0;
  size_t children = 1;
  size_t value = 0;
  bst *left = nullptr, *right = nullptr;

  bst() {}
  bst(size_t value) : value(value) {}

  void insert(size_t v) {
    // Guaranteed its going to be inserted, so we should increment the children
    // something has.
    ++children;
    if (v == value) {
      // Don't create a new node if duplicate.
      ++duplicate;
    } else if (v <= value) {
      if (left != nullptr) {
        left->insert(v);
      } else {
        left = new bst(v);
      }
    } else {
      if (right != nullptr) {
        right->insert(v);
      } else {
        right = new bst(v);
      }
    }
  }
};

void build_bst(bst &root, vector<size_t> &X) {
  root.value = *X.begin();
  for (auto it = next(X.begin()); it != X.end(); ++it) {
    root.insert(*it);
  }
}

size_t find(bst *root, size_t m, size_t total) {
  // Base case, you explored to end of tree.
  if (!root) {
    return total;
  }

  // Base case, everything below you is acceptable.
  if (root->value <= m) {
    // Then everything to the left of root & root is suitable.
    // Also check the right side, incase there are values less than m but
    // greater than this.
    total += 1 + root->duplicate;
    if (root->left) {
      total += root->left->children;
    }
    return find(root->right, m, total);
  }

  // If m < current value at root, then we go left.
  return find(root->left, m, total);
}

void solve(vector<size_t> &X, vector<size_t> &M) {

  // Random shuffle bc i cba to implement an avl tree
  std::random_device rd;
  std::mt19937 g(rd());
  shuffle(X.begin(), X.end(), g);

  bst root;
  build_bst(root, X);

  for (auto m : M) {
    cout << find(&root, m, 0) << endl;
  }
}

int main(int argc, char *argv[]) {
  size_t n = read<size_t>();
  auto X = read_line<size_t>();
  size_t q = read<size_t>();
  vector<size_t> M;
  for (; q > 0; --q) {
    M.push_back(read<size_t>());
  }
  solve(X, M);
  return 0;
}

void solve(size_t n, vector<size_t> xs, size_t q, vector<size_t> ms) {
  ranges::sort(xs);
  map<size_t, size_t> max_idxs;

  for (size_t budget : ms) {
    if (budget < xs.front()) {
      cout << 0 << "\n";
      continue;
    }
    // Already seen this budget
    if (auto it = max_idxs.find(budget); it != max_idxs.end()) {
      cout << it->second << "\n";
      continue;
    }

    // Next largest element in the map
    auto next_largest = max_idxs.upper_bound(budget);
    // We know that it cannot be more than a larger size_tber, constrain search
    // space
    auto ending_it = next_largest == max_idxs.end()
                         ? xs.end()
                         : xs.begin() + next_largest->second;

    // Get the first size_tber in xs which is greater than budget
    // in the range [begin, ending)
    auto best = upper_bound(xs.begin(), ending_it, budget);
    // Get the index of best
    size_t answ = distance(xs.begin(), best);
    max_idxs[budget] = answ;

    cout << answ << "\n";
  }
}
