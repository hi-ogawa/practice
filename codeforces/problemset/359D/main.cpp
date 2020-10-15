// TLE

// TODO: Editorial says use sparse table instead of segment tree.

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

// Segment tree for gcd
struct SegmentTree {
  int n = 1;
  vector<int> data;
  SegmentTree(int _n) {
    while (n < _n) { n *= 2; }
    data.assign(2 * n, 1);
  }
  void set(int qi, int qv) {
    int j = qi + n;
    data[j] = qv;
    while (j > 1) {
      j /= 2;
      data[j] = gcd(data[2 * j], data[2 * j + 1]);
    }
  }
  int reduce(int ql, int qr) {
    function<int(int, int, int)> rec = [&](int l, int r, int j) {
      if (qr <= l || r <= ql) { return 0; }
      if (ql <= l && r <= qr) { return data[j]; }
      int m = (l + r) / 2;
      return gcd(rec(l, m, 2 * j), rec(m, r, 2 * j + 1));
    };
    return rec(0, n, 1);
  }
};

// Main
void mainCase() {
  int n; // [1, 3 x 10^5]
  cin >> n;
  vector<int> ls(n); // [1, 10^6]
  cin >> ls;

  SegmentTree tree(n);
  FOR(i, 0, n) { tree.set(i, ls[i]); }

  // For each index "i", find maximum segment divisible by "ls[i]"

  auto searchRight = [&](int i) -> int {
    int j0 = i + 1, j1 = n + 1; // [j0, j1)
    while (j0 + 1 < j1) {
      int j = (j0 + j1) / 2;
      int g = tree.reduce(i, j);
      if (g == ls[i]) {
        j0 = j;
      } else {
        j1 = j;
      }
    }
    return j0;
  };

  auto searchLeft = [&](int i) -> int {
    int j0 = -1, j1 = i; // (j0, j1]
    while (j0 + 1 < j1) {
      int j = (j0 + j1 + 1) / 2;
      int g = tree.reduce(j, i + 1);
      if (g == ls[i]) {
        j1 = j;
      } else {
        j0 = j;
      }
    }
    return j1;
  };

  map<int, set<array<int, 2>>> res;
  FOR(i, 0, n) {
    int l = searchLeft(i);
    int r = searchRight(i);
    res[r - l].insert({l, r});
  }

  auto [res1, res2] = *res.rbegin();
  int res3 = res2.size();
  cout << res3 << " " << (res1 - 1) << "\n";
  vector<array<int, 2>> res4(ALL(res2));
  FOR(i, 0, res3) {
    cout << (res4[i][0] + 1) << " \n"[i == res3 - 1];
  }
}


int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/359D/main.cpp

%%%% begin
5
4 6 9 3 6
%%%%
1 3
2
%%%% end

%%%% begin
5
1 3 5 7 9
%%%%
1 4
1
%%%% end

%%%% begin
5
2 3 5 7 11
%%%%
5 0
1 2 3 4 5
%%%% end
*/
