#include <cstdio>
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;
constexpr int kMaxInt = 1 << 30; // > 10^9

struct SegmentTree {
  int n_;
  int depth_;
  vector<tuple<int, int>> data_;

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
      int v = (i < n_) ? ls[i] : kMaxInt;
      data_[i0 + i] = {v, 1};
    }

    // Set branches
    for (int k = depth_ - 1; k >= 0; k--) {
      int i0 = (1 << k) - 1;
      int i1 = (1 << (k + 1)) - 1;
      for (int i = i0; i < i1; i++) {
        auto [v0, c0] = data_[2 * i + 1];
        auto [v1, c1] = data_[2 * i + 2];
        data_[i] =
            v0 == v1 ? make_tuple(v0, c0 + c1) :
            v0 < v1 ? data_[2 * i + 1] : data_[2 * i + 2];
      }
    }
  }

  void print() {
    puts("[print]");
    printf("n: %d, depth: %d\n", n_, depth_);
    for (int k = 0; k <= depth_; k++) {
      int i0 = (1 << k) - 1;
      for (int i = 0; i < (1 << k); i++) {
        auto [v, c] = data_[i0 + i];
        printf("(%d %d) ", v, c);
      }
      puts("");
    }
  }

  void set(int qi, int qv) {
    int i0 = (1 << depth_) - 1 + qi;
    data_[i0] = {qv, 1};
    int i = i0;
    while (i > 0) {
      i = ((i + 1) / 2) - 1;
      auto [v0, c0] = data_[2 * i + 1];
      auto [v1, c1] = data_[2 * i + 2];
      data_[i] =
          v0 == v1 ? make_tuple(v0, c0 + c1) :
          v0 < v1 ? data_[2 * i + 1] : data_[2 * i + 2];
    }
  }

  tuple<int, int> minimum(int ql, int qr) {
    tuple<int, int> result = {kMaxInt, 0};
    int result_v = kMaxInt;
    int result_c = 0;
    vector<tuple<int, int, int>> stack(depth_ + 1, {0, 0, 0}); // Use "depth + 1" for the worst case
    int ptr = 0;
    stack[ptr++] = {0, 0, 1 << depth_};
    while (ptr > 0) {
      auto [i, l, r] = stack[--ptr];
      #ifdef DEBUG
        printf("[minimum] i, l, r: %d, %d, %d\n", i, l, r);
      #endif
      if (ql <= l && r <= qr) {
        auto [v, c] = data_[i];
        if (v <= result_v) {
          result_c = v < result_v ? c : c + result_c;
          result_v = v;
        }
        continue;
      }
      if (qr <= l || r <= ql) {
        continue;
      }
      stack[ptr++] = {2 * i + 1, l, (l + r) / 2};
      stack[ptr++] = {2 * i + 2, (l + r) / 2, r};
    }
    return {result_v, result_c};
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
      auto [v, c] = tree.minimum(a, b);
      cout << v << " " << c << endl;
    }
  }
  return 0;
}

/*
python misc/run.py codeforces/edu/ex273169C/main.cpp --check

%%%% begin
5 5
3 4 3 5 2
2 0 3
1 1 2
2 0 3
1 0 2
2 0 5
%%%%
3 2
2 1
2 3
%%%% end
*/
