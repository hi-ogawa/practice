// CONTEST, AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (decltype(Y) I = (X); I < (Y); ++I)
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

// Main
void mainCase() {
  int n; // [1, 2 x 10^5]
  cin >> n;
  int m; // [-n, n]
  cin >> m;

  //
  // CONJ.
  //    m : valid  \iff m = 0, 1, ..., n - 2
  //

  bool ok = 0 <= m && m <= max(0, n - 2);
  if (!ok) { cout << -1 << "\n"; return; }

  //
  // Given
  //
  //    <------------------------------------>
  //      <------->     <-> <-> <-> ... <->
  //       <------->      \-- m --/
  //         ...
  //         <------->

  //
  // Left greedy
  //    <------------------------------------>  = 1

  //
  // Right greedy
  //      <------->   <-> <-> <-> ... <->      = 1 + m  <= n - 1
  //

  vector<array<int, 2>> res; // [1, 10^9]
  res.push_back({1, (int)1e9});
  FOR(i, 0, n - (m + 1)) {
    int x = i + 2;
    res.push_back({x, x + (int)1e7});
  }
  FOR(i, 0, m) {
    int x = i * 2;
    res.push_back({x + (int)1e8, x + 1 + (int)1e8});
  }

  for (auto [x, y] : res) {
    cout << x << " " << y << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/arc106/c/main.cpp

%%%% begin
1 0
%%%%
1 1000000000
%%%% end

%%%% begin
2 1
%%%%
-1
%%%% end

%%%% begin
7 3
%%%%
1 1000000000
2 10000002
3 10000003
4 10000004
100000000 100000001
100000002 100000003
100000004 100000005
%%%% end
*/
