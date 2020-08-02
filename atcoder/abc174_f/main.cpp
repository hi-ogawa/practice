// AFTER EDITORIAL

#include <cstdio>
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <numeric>

using namespace std;

// cf. codeforces/edu/ex273169A/main.cpp
struct SegmentTree {
  int n_;
  int depth_;
  vector<int> data_;

  SegmentTree(int n) {
    n_ = n;
    depth_ = 0;
    while ((1 << depth_) < n_) {
      depth_++;
    }
    data_.assign(1 << (depth_ + 1), 0);
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
      data_[i] = data_[2 * i + 1] + data_[2 * i + 2];
    }
  }

  int sum(int ql, int qr) {
    int result = 0;
    vector<tuple<int, int, int>> stack(depth_ + 1, {0, 0, 0}); // Use "depth + 1" for the worst case
    int ptr = 0;
    stack[ptr++] = {0, 0, 1 << depth_};
    while (ptr > 0) {
      auto [i, l, r] = stack[--ptr];
      #ifdef DEBUG
        printf("[sum] i, l, r: %d, %d, %d\n", i, l, r);
      #endif
      if (ql <= l && r <= qr) {
        result += data_[i];
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
  //
  // Input
  //
  int n, m;
  cin >> n >> m;

  vector<int> ls(n, 0);
  for (int i = 0; i < n; i++) {
    cin >> ls[i];
  }

  vector<tuple<int, int>> qs(m, {0, 0});
  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    qs[i] = {l, r};
  }

  // Sort queries
  vector<int> qs_argsort(m, 0);
  iota(qs_argsort.begin(), qs_argsort.end(), 0);
  sort(qs_argsort.begin(), qs_argsort.end(), [&](auto x, auto y){ return get<1>(qs[x]) < get<1>(qs[y]); });

  #ifdef DEBUG
    puts("[qs_argsort]");
    for (auto k : qs_argsort) {
      auto [l, r] = qs[k];
      cout << l << " " << r << endl;
    }
  #endif

  vector<int> type_to_position(n + 1, -1); // Type is 1..n
  SegmentTree tree(n);
  #ifdef DEBUG
    tree.print();
  #endif

  vector<int> result(m, 0);
  int r0 = 0;
  for (int k = 0; k < m; k++) {
    auto [ql, qr] = qs[qs_argsort[k]];
    for (int i = r0; i < qr; i++) {
      int v = ls[i];
      int i0 = type_to_position[v];
      if (i0 >= 0) {
        tree.set(i0, 0);
      }
      type_to_position[v] = i;
      tree.set(i, 1);
    }
    r0 = qr;
    #ifdef DEBUG
      tree.print();
    #endif
    result[qs_argsort[k]] = tree.sum(ql - 1, qr);
  }

  for (auto x : result) {
    cout << x << endl;
  }

  return 0;
}

/*
python misc/run.py atcoder/abc174_f/main.cpp --check

%%%% begin
4 3
1 2 1 3
1 3
2 4
3 3
%%%%
2
3
1
%%%% end

%%%% begin
10 10
2 5 6 5 2 1 7 9 7 2
5 5
2 4
6 7
2 2
7 8
7 9
1 8
6 9
8 10
6 8
%%%%
1
2
2
1
2
2
6
3
3
3
%%%% end
*/
