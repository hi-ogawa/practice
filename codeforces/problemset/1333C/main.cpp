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
  ll n;
  cin >> n;
  vector<ll> ls(n);
  cin >> ls;

  vector<ll> ps(n + 1);
  FOR(i, 0, n) { ps[i + 1] = ps[i] + ls[i]; }

  set<pair<ll, int>> qs;
  FOR(i, 0, n + 1) { qs.insert({ps[i], i}); }

  // Find "right minimal bad"
  vector<int> segs(n, -1);
  FOR(i, 0, n) {
    qs.erase({ps[i], i});
    auto it = qs.lower_bound({ps[i], -1});
    if (it != qs.end() && it->first == ps[i]) {
      segs[i] = it->second;
    }
  }

  // Find "minimal bad"
  vector<int> dp(n, -1);
  dp[n - 1] = segs[n - 1];
  for (int i = n - 2; i >= 0; i--) {
    if (segs[i] != -1 || dp[i + 1] != -1) {
      if (segs[i] == -1) { dp[i] = dp[i + 1]; continue; }
      if (dp[i + 1] == -1) { dp[i] = segs[i]; continue; }
      dp[i] = min(dp[i + 1], segs[i]);
    }
  }
  dbg(dp);

  // Count "bad"
  ll m = 0;
  FOR(i, 0, n) {
    if (dp[i] != -1) {
      m += n + 1 - dp[i];
    }
  }

  ll res = (n * (n + 1)) / 2 - m;
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1333C/main.cpp --check

%%%% begin
5
0 0 0 0 0
%%%%
0
%%%% end

%%%% begin
5
1 1 0 -1 -1
%%%%
6
%%%% end

%%%% begin
2
1 0
%%%%
1
%%%% end

%%%% begin
3
1 2 -3
%%%%
5
%%%% end

%%%% begin
3
41 -41 41
%%%%
3
%%%% end
*/
