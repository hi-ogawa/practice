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

// Fenwick tree for prefix sum
struct FenwickTree {
  int n;
  vector<int> data;
  FenwickTree(int n) : n{n} { data.resize(n); }
  void incr(int i, int v) {
    while (i < n) {
      data[i] += v;
      i = i | (i + 1);
    }
  }
  int reduce(int r) { // [0, r)
    int i = min(r - 1, n - 1);
    int res = 0;
    while (i >= 0) {
      res += data[i];
      i = (i & (i + 1)) - 1;
    }
    return res;
  }
};

// Main
void mainCase() {
  int n; // [2, 2 x 10^5]
  cin >> n;
  string s;
  cin >> s;
  string s_rev = s;
  reverse(ALL(s_rev));

  const int k = 26; // a..z
  vector<FenwickTree> trees(k, FenwickTree(n));
  FOR(i, 0, n) {
    trees[(s_rev[i] - 'a')].incr(i, 1);
  }

  // Find min { i | trees[t][i] = 1 }
  auto search = [&](int t) -> int {
    int i0 = -1, i1 = n - 1; // (i0, i1]
    while (i0 + 1 < i1) {
      int i = (i0 + i1 + 1) / 2;
      if (trees[t].reduce(i + 1) >= 1) {
        i1 = i;
      } else {
        i0 = i;
      }
    }
    return i1;
  };

  // TODO: prove/disprove optimality
  ll res = 0;
  FenwickTree used(n);

  FOR(i, 0, n) {
    int t = s[i] - 'a';
    int j = search(t); // Swap with unused same character at the left most
    int cnt = used.reduce(j);
    res += j - cnt;
    trees[t].incr(j, -1);
    used.incr(j, 1);
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/edu96/e/main.cpp

%%%% begin
5
aaaza
%%%%
2
%%%% end

%%%% begin
6
cbaabc
%%%%
0
%%%% end

%%%% begin
9
icpcsguru
%%%%
30
%%%% end
*/
