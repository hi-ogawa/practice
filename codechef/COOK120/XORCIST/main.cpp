// VC, AFTER CONTEST, WA

//
// PROP:
//   a <= a^b <= b
//     iff
//   a = 0 or
//   fs(a) < fs(b) and b[fs(a)] = 1
//
//   where fs(a) = "1st set bit of a"
//
// NOTE:
//   I miss-analyzed and I count 1st-set(a) <= 2nd-set(b) in below solution, which obviously is WA.
//   But, then, I cannot concieve a way to count such pair in above PROP.
//

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (decltype(X) I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
namespace std { template<class ...Ts> ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "{"; apply([&](auto&&... ys){ ((o << ys << ", "), ...); }, x); o << "}"; return o; } }
namespace std { template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; } }
namespace std { template<class T> ostream& operator<<(ostream& o, const vector<T>& x) { o << "{"; for (auto& y : x) { o << y << ", "; } o << "}"; return o; } }
namespace std { template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x) { o << "{"; for (auto& yz : x) { o << yz << ", "; } o << "}"; return o; } }

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
    data_.assign(1 << (depth_ + 1), 0);
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

vector<int> solve(const vector<uint>& ls, const vector<tuple<int, int>>& qs) {
  int n = ls.size();

  // Find 1st/2nd set bits
  vector<int> b1s(n, -1);
  vector<int> b2s(n, -1);
  RANGE(i, 0, n) {
    uint x = ls[i];
    for (int b = 31; b >= 0; b--) {
      if ((x >> b) & 1) {
        b1s[i] = b;
        break;
      }
    }
    if (b1s[i] == -1) {
      continue;
    }
    for (int b = b1s[i] - 1; b >= 0; b--) {
      if ((x >> b) & 1) {
        b2s[i] = b;
        break;
      }
    }
  }

  // Segment tree for each bits
  vector<SegmentTree> b1trees(33, SegmentTree());
  vector<SegmentTree> b2trees(33, SegmentTree());
  RANGE(b, -1, 32) {
    b1trees[b + 1].initialize(n);
    b2trees[b + 1].initialize(n);
    RANGE(j, 0, n) {
      b1trees[b + 1].set(j, (int)(b1s[j] == b));
      b2trees[b + 1].set(j, (int)(b2s[j] == b));
    }
  }

  // Answer queries
  int nq = qs.size();
  vector<int> result(nq, 0);
  RANGE(iq, 0, nq) {
    auto [l, r] = qs[iq];

    // Count { (i, j) | bs1[i] <= bs2[j] }
    int count = 0;
    RANGE(b1, -1, 32) {
      int c1 = b1trees[b1 + 1].sum(l - 1, r);
      RANGE(b2, b1, 32) {
        int c2 = b2trees[b2 + 1].sum(l - 1, r);
        count += c1 * c2;
        #ifdef DEBUG
          if (c1 > 0 && c2 > 0) {
            DD(tie(b1, b2, c1, c2));
          }
        #endif
      }
    }
    result[iq] = count;
  }

  return result;
}

int main() {
  int t;
  cin >> t;
  RANGE(i, 0, t) {
    int n, q;
    cin >> n >> q;
    vector<uint> ls(n, 0);
    RANGE(j, 0, n) {
      cin >> ls[j];
    }
    vector<tuple<int, int>> qs(q, {0, 0});
    RANGE(j, 0, q) {
      cin >> get<0>(qs[j]) >> get<1>(qs[j]);
    }
    auto result = solve(ls, qs);
    for (auto r : result) {
      cout << r << endl;
    }
  }
  return 0;
}

/*
python misc/run.py codechef/COOK120/XORCIST/main.cpp --check

// Single test
%%%% begin
1
5 1
2 7 1 5 2
1 5
%%%%
4
%%%% end

// Test double counting
%%%% begin
1
2 1
0 0
1 2
%%%%
4
%%%% end

%%%% begin
1
10 1
123 667 232 989 0 104 305 329 567 345
1 10
%%%%
23
%%%% end

// Original test
%%%% begin
2
5 4
2 7 1 5 2
1 5
2 3
4 5
2 4
10 1
123 667 232 989 0 104 305 329 567 345
1 10
%%%%
4
1
0
2
23
%%%% end
*/
