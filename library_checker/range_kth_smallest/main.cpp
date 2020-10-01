// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i,       tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; auto s = ""; apply([&](auto&&... y){ ((o << s << y, s = ", "), ...); }, x); return o << ")"; }
template<class T1, class T2> istream& operator>>(istream& i,       pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
istream& operator>>(istream& i,       T& x) { for (auto& y : x) { i >> y; } return i; }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
ostream& operator<<(ostream& o, const T& x) { o << "{"; auto s = ""; for (auto& y : x) { o << s << y; s = ", "; } return o << "}"; }
}

#ifdef DEBUG
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

namespace std {
template<class T> ostream& operator<<(ostream& o, const reference_wrapper<T>& x) { return o << x.get(); }
}

constexpr int kInf = 1e9 + 1;

// Segment tree for order statistics
struct SegmentTree {
  int n = 1;
  vector<vector<int>> data;

  SegmentTree(const vector<int>& ls) {
    int m = ls.size();
    while (n < m) { n *= 2; }
    data.resize(2 * n);
    FOR(i, 0, n) { data[i + n].assign(1, i < m ? ls[i] : kInf); }
    sort(0, n, 1);
  }
  friend ostream& operator<<(ostream& ostr, const SegmentTree& self) {
    FOR(j, 1, 2 * self.n) {
      if (((j - 1) & j) == 0) { ostr << "\n"; } // new line when power of two
      ostr << self.data[j] << "  ";
    }
    return ostr;
  }

  void sort(int l, int r, int j) {
    if (n <= j) { return; } // data[j] is leaf
    sort(l, (l + r) / 2, 2 * j);
    sort((l + r) / 2, r, 2 * j + 1);
    auto& d  = data[j];
    auto& dl = data[2 * j];
    auto& dr = data[2 * j + 1];
    int il = 0, ir = 0;
    int k = r - l;
    d.resize(k);
    FOR(i, 0, k) {
      if (il >= k / 2) { d[i] = dr[ir++]; continue; }
      if (ir >= k / 2) { d[i] = dl[il++]; continue; }
      d[i] = (dr[ir] < dl[il]) ? dr[ir++] : dl[il++];
    }
  }

  int query(int ql, int qr, int qk) {
    // Collect O(log(n)) segments
    vector<reference_wrapper<vector<int>>> segs; // probably it's crucial not to copy
    function<void(int, int, int)> collectSegments = [&](int l, int r, int j) {
      if (qr <= l || r <= ql) { return; }
      if (ql <= l && r <= qr) { segs.push_back(ref(data[j])); return; }
      collectSegments(l, (l + r) / 2, 2 * j);
      collectSegments((l + r) / 2, r, 2 * j + 1);
    };
    collectSegments(0, n, 1);

    // f(x) = #{ y \in segs | y <= x }
    auto evaluate = [&](int x) -> int {
      int cnt = 0;
      for (auto seg : segs) {
        cnt += distance(seg.get().begin(), upper_bound(ALL(seg.get()), x));
      }
      return cnt;
    };

    // Find min {x | f(x) >= k }
    auto search = [&](int k) -> int {
      int x0 = -1, x1 = kInf; // (x0, x1]
      while (x0 + 1 < x1) {
        int x = (x0 + x1 + 1) / 2;
        if (evaluate(x) >= k) {
          x1 = x;
        } else {
          x0 = x;
        }
      }
      return x1;
    };

    return search(qk);
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 2 x 10^5]
  cin >> n >> nq;
  vector<int> ls(n);
  vector<array<int, 3>> qs(nq);
  cin >> ls >> qs;

  SegmentTree tree(ls);
  dbg(tree);

  for (auto [l, r, k] : qs) {
    int res = tree.query(l, r, k + 1);
    cout << res << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/range_kth_smallest/main.cpp --check

%%%% begin
5 3
1 4 0 1 3
0 5 2
1 3 1
3 4 0
%%%%
1
4
1
%%%% end
*/
