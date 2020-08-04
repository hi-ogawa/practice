// AFTER CONTEST

#include <cstdio>
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <numeric>
#include <set> // multiset

using namespace std;
constexpr int kMaxInt = 1 << 30; // > 10^9

// cf. codeforces/edu/ex273169A/main.cpp
struct SegmentTree {
  int n_;
  int depth_;
  vector<int> data_;

  void initialize(int n) {
    n_ = n;
    depth_ = 0;
    while ((1 << depth_) < n_) {
      depth_++;
    }
    data_.assign(1 << (depth_ + 1), kMaxInt);
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
  // Input
  int n, q;
  cin >> n >> q;
  int l = 2 * 100'000;

  vector<int> infant_rating(n + 1, 0);
  vector<int> infant_to_kindergarten(n + 1, 0);
  vector<multiset<int>> kindergarten_scores(l + 1);

  for (int i = 1; i <= n; i++) {
    int rating, kinder;
    cin >> rating >> kinder;
    infant_rating[i] = rating;
    infant_to_kindergarten[i] = kinder;
    kindergarten_scores[kinder].insert(rating);
  }

  // Min segment tree with kindergarten's max
  SegmentTree tree;
  tree.initialize(l + 1);
  for (int i = 1; i <= l; i++) {
    auto& scores = kindergarten_scores[i];
    if (!scores.empty()) {
      tree.set(i, *scores.rbegin());
    }
  }
  #ifdef DEBUG
    tree.print();
  #endif

  // Update kindergarten and tree along query
  for (int i = 0; i < q; i++) {
    int infant, new_kinder;
    cin >> infant >> new_kinder;

    // Move infant
    int old_kinder = infant_to_kindergarten[infant];
    infant_to_kindergarten[infant] = new_kinder;
    int rating = infant_rating[infant];

    // Update kindergarten score
    auto& old_kinder_scores = kindergarten_scores[old_kinder];
    auto& new_kinder_scores = kindergarten_scores[new_kinder];
    old_kinder_scores.erase(rating);
    new_kinder_scores.insert(rating);

    // Update score in segment tree
    tree.set(old_kinder, old_kinder_scores.empty() ? kMaxInt : *old_kinder_scores.rbegin());
    tree.set(new_kinder, new_kinder_scores.empty() ? kMaxInt : *new_kinder_scores.rbegin());

    #ifdef DEBUG
      printf("[AFTER (%d, %d)]\n", infant, new_kinder);
      tree.print();
    #endif

    // Query minimum
    cout << tree.minimum(1, l + 1) << endl;
  }

  return 0;
}

/*
python misc/run.py atcoder/abc170_e/main.cpp --check

%%%% begin
6 3
8 1
6 2
9 3
1 1
2 2
1 3
4 3
2 1
1 2
%%%%
6
2
6
%%%% end

%%%% begin
2 2
4208 1234
3056 5678
1 2020
2 2020
%%%%
3056
4208
%%%% end
*/
