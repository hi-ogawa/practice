// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y)(X); I < (Y); ++I)
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
  int n; // [1, 10^5]
  cin >> n;
  vector<int> ls(n); // {0, 1}
  cin >> ls;

  ll s = accumulate(ALL(ls), 0);
  if (s == 0) {
    cout << 0 << "\n";
    return;
  }
  if (s == 1) {
    cout << -1 << "\n";
    return;
  }

  // Position of "1"
  vector<int> xs;
  FOR(i, 0, n) {
    if (ls[i]) { xs.push_back(i); }
  }
  int k = xs.size();

  // Brute force all partitions by prime
  auto factorize = [](int x) -> vector<int> {
    vector<int> res;
    for (int p = 2; (ll)p * p <= x; p++) {
      if (x % p) { continue; }
      while (x % p == 0) { x /= p; }
      res.push_back(p);
    }
    if (x >= 2) { res.push_back(x); }
    return res;
  };
  auto ps = factorize(s);

  ll res = 1e18;
  for (auto p : ps) {
    ll t = 0;
    // Median for each "p" positions
    assert(k % p == 0);
    FOR(i, 0, k / p) {
      int m = xs[i * p + p / 2];
      FOR(j, 0, p) {
        int x = xs[i * p + j];
        t += abs(x - m);
      }
    }
    res = min(res, t);
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1254B1/main.cpp

%%%% begin
3
1 0 1
%%%%
2
%%%% end

%%%% begin
1
1
%%%%
-1
%%%% end
*/
