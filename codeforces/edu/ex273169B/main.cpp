#include <cstdio>
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;
constexpr int kMaxInt = 1 << 30; // > 10^9

struct SegmentTree {
  int n_;
  int depth_;
  vector<int> data_;

  SegmentTree(const vector<int>& ls) {
    n_ = ls.size();
    depth_ = 0;
    while ((1 << depth_) < n_) {
      depth_++;
    }
    data_.resize(1 << (depth_ + 1));

    // Set leaves
    int i0 = (1 << depth_) - 1;
    for (int i = 0; i < (1 << depth_); i++) {
      data_[i0 + i] = (i < n_) ? ls[i] : kMaxInt;
    }

    // Set branches
    for (int k = depth_ - 1; k >= 0; k--) {
      int i0 = (1 << k) - 1;
      int i1 = (1 << (k + 1)) - 1;
      for (int i = i0; i < i1; i++) {
        data_[i] = min(data_[2 * i + 1], data_[2 * i + 2]);
      }
    }
  }

  void print() {
    puts("[print]");
    printf("n: %d, depth: %d\n", n_, depth_);
    for (int k = 0; k <= depth_; k++) {
      int i0 = (1 << k) - 1;
      for (int i = 0; i < (1 << k); i++) {
        printf("%d ", data_[i0 + i]);
      }
      puts("");
    }
  }

  void set(int qi, int qv) {
    int i0 = (1 << depth_) - 1 + qi;
    data_[i0] = qv;
    int i = i0;
    while (i > 0) {
      i = ((i + 1) / 2) - 1;
      data_[i] = min(data_[2 * i + 1], data_[2 * i + 2]);
    }
  }

  int minimum(int ql, int qr) {
    int result = kMaxInt;
    vector<tuple<int, int, int>> stack(depth_ + 1, {0, 0, 0}); // Use "depth + 1" for the worst case
    int ptr = 0;
    stack[ptr++] = {0, 0, 1 << depth_};
    while (ptr > 0) {
      auto [i, l, r] = stack[--ptr];
      #ifdef DEBUG
        printf("[minimum] i, l, r: %d, %d, %d\n", i, l, r);
      #endif
      if (ql <= l && r <= qr) {
        result = min(result, data_[i]);
        continue;
      }
      if (qr <= l || r <= ql) {
        continue;
      }
      stack[ptr++] = {2 * i + 1, l, (l + r) / 2};
      stack[ptr++] = {2 * i + 2, (l + r) / 2, r};
    }
    return result;
  }
};

int main() {
  int n, m;
  cin >> n >> m;

  vector<int> ls(n, 0);
  for (int i = 0; i < n; i++) {
    cin >> ls[i];
  }
  SegmentTree tree(ls);
  #ifdef DEBUG
    tree.print();
  #endif

  for (int i = 0; i < m; i++) {
    int op, a, b;
    cin >> op >> a >> b;
    if (op == 1) {
      tree.set(a, b);
      #ifdef DEBUG
        tree.print();
      #endif
    }
    if (op == 2) {
      cout << tree.minimum(a, b) << endl;
    }
  }
  return 0;
}

/*
python misc/run.py codeforces/edu/ex273169B/main.cpp --check

%%%% begin
5 5
5 4 2 3 5
2 0 3
1 2 6
2 0 3
1 3 1
2 0 5
%%%%
2
4
1
%%%% end
*/
