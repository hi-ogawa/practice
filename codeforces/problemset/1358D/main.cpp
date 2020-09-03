// AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
template<typename T> struct is_container {
template<typename C> static char test(typename C::const_iterator*); template<typename> static int test(...);
static bool const value = sizeof(test<T>(nullptr)) == sizeof(char) && !std::is_same<std::string, T>::value;
};
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#ifndef DEBUG
#define DEBUG 0
#endif
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  ll n, x;
  cin >> n >> x;
  vector<ll> ls(n);
  cin >> ls;

  // Allow cyclic
  FOR(i, 0, n) { ls.push_back(ls[i]); }
  dbgv(n, ls);

  // Cumsum
  vector<ll> ps(2 * n + 1);
  vector<ll> qs(2 * n + 1);
  FOR(i, 0, 2 * n) { ps[i + 1] = ps[i] + ls[i]; }
  FOR(i, 0, 2 * n) { qs[i + 1] = qs[i] + (ls[i] * (ls[i] + 1)) / 2; }
  dbg(ps);
  dbg(qs);

  ll res = 0;
  FOR(i, 0, n) {
    // Optimize for each starting month

    // Find max j s.t. ps[j] < x + ps[i]
    auto it = lower_bound(ALL(ps), x + ps[i]);
    int j = distance(ps.begin(), --it);
    ll s = x + ps[i] - ps[j];

    ll tmp = qs[j] - qs[i];
    if (ls[j] == s) {
      tmp += (s * (s + 1)) / 2;
      dbgv(i, j, s, tmp);
    } else {
      ll u = min(ls[j] - s, ls[i]);
      // [1, u] ==> [1, s + u]
      tmp += - (u * (u + 1)) / 2 + ((s + u) * (s + u + 1)) / 2;
      dbgv(i, j, s, tmp, u);
    }
    res = max(res, tmp);
  }

  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  mainCase();
  return 0;
  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // FOR(i, 0, t) { mainCase(); }
  // return 0;
}

/*
python misc/run.py codeforces/problemset/1358D/main.cpp --check

%%%% begin
4 14
4 9 2 7
%%%%
66
%%%% end

%%%% begin
5 6
4 2 3 1 3
%%%%
15
%%%% end
*/
