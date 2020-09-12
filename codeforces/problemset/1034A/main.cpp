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

vector<bool> makeSieve(int n) {
  vector<bool> sieve(n + 1, 1);
  for (int p = 2; p <= sqrt(n); p++) {
    if (!sieve[p]) { continue; }
    for (int x = p * p; x <= n; x += p) {
      sieve[x] = 0;
    }
  }
  return sieve;
}

// Main
void mainCase() {
  int n;
  cin >> n;
  vector<int> ls(n);
  cin >> ls;

  // WLOG gcd(ls) = 1
  int g = ls[0];
  FOR(i, 1, n) { g = gcd(g, ls[i]); }
  FOR(i, 0, n) { ls[i] /= g; }
  dbg(ls);

  // Not solvable if ls = {1, .., 1}
  sort(ALL(ls));
  if (ls[n - 1] == 1) { cout << -1 << endl; return; }

  int k = ls[n - 1];
  vector<int> cnts(k + 1);
  for (auto x : ls) { cnts[x]++; }

  auto sieve = makeSieve(k);
  int res = 0;
  FOR(p, 2 , k + 1) {
    if (!sieve[p]) { continue; }
    // f(p) = #{ a | p divides a } (maximize #{not removed elements})
    int t = 0;
    for (int x = p; x <= k; x += p) { t += cnts[x]; }
    res = max(res, t);
  }
  int res2 = n - res;
  cout << res2 << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1034A/main.cpp --check

%%%% begin
3
1 2 4
%%%%
1
%%%% end

%%%% begin
4
6 9 15 30
%%%%
2
%%%% end

%%%% begin
3
1 1 1
%%%%
-1
%%%% end
*/
