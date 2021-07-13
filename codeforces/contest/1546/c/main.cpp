// AFTER EDITORIAL, WA

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y){X}; I < (Y); ++I)
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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n; // [1, 10^5]
  cin >> n;
  vector<int> xs(n); // [1, 10^5]
  cin >> xs;

  // Stable sort indices (as achieved via insertion sort operations)
  vector<int> ys(n);
  iota(ALL(ys), 0);
  stable_sort(ALL(ys), [&](auto i, auto j) { return xs[i] < xs[j]; });

  // Sort values
  sort(ALL(xs));

  // Parity of each index difference
  vector<int> ps(n);
  FOR(i, 0, n) {
    ps[i] = (ys[i] - i + 2 * n) % 2;
  }

  dbg(xs, ys, ps);

  // Check parity of each index
  bool res = true;
  FOR(i, 0, n) {
    // When dupicate elements exist, they can adjust parity by each other.
    // Here, try to push parity towords end as in
    // 1 0 0 => 0 0 1
    // 1 0 1 => x x x (impossibility)
    // 1 1 0 => 0 0 0
    // 1 1 1 => 0 0 1
    if (ps[i]) {
      if (i + 1 == n || xs[i] != xs[i + 1]) {
        res = false;
        break;
      }
      if (ps[i + 1]) {
        ps[i] = ps[i + 1] = 0;
        continue;
      }
      if (i + 2 == n || xs[i] != xs[i + 2]) {
        res = false;
        break;
      }
      if (ps[i + 2]) {
        res = false;
        break;
      }
      ps[i] = 0;
      ps[i + 2] = 1;
    }
  }

  cout << (res ? "YES" : "NO") << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; // [1, 50]
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest/1546/c/main.cpp

%%%% begin
3
4
4 3 2 5
4
3 3 2 2
5
1 2 3 5 4
%%%%
YES
YES
NO
%%%% end

%%%% begin
1
3
2 1 1
%%%%
YES
%%%% end

*/
