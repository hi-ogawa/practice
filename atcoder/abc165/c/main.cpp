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

template<class CallbackT>
void generateBinom(
    int n, int k, int n0, int k0,
    const vector<int>& ls_in, vector<int>& ls_out,
    CallbackT& f) {
  if (k0 == k) { f(ls_out); return; }
  if (k - k0 > n - n0) { return; }

  // Pick ls[n0]
  ls_out[k0] = ls_in[n0];
  generateBinom(n, k, n0 + 1, k0 + 1, ls_in, ls_out, f);
  // Otherwise
  generateBinom(n, k, n0 + 1, k0    , ls_in, ls_out, f);
};

// Main
void mainCase() {
  int n, m, nq;
  cin >> n >> m >> nq;
  vector<array<int, 4>> qs(nq);
  cin >> qs;
  for (auto& [a, b, _c, _d] : qs) { a--; b--; } // zero-based

  int res = 0;
  auto check = [&](const vector<int>& ls) {
    int t = 0;
    for (auto [a, b, c, d] : qs) {
      if ((ls[b] - b + 1) == (ls[a] - a + 1) + c) { t += d; }
    }
    res = max(res, t);
  };

  // Choose n from {1..m} (with multiple allowed) = binom(n + m - 1, n)
  vector<int> ls_in(n + m - 1);
  vector<int> ls_out(n);
  iota(ALL(ls_in), 0);
  generateBinom(n + m - 1, n, 0, 0, ls_in, ls_out, check);
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc165/c/main.cpp --check

%%%% begin
4 6 10
2 4 1 86568
1 4 0 90629
2 3 0 90310
3 4 1 29211
3 4 3 78537
3 4 2 8580
1 2 1 96263
1 4 2 2156
1 2 0 94325
1 4 3 94328
%%%%
357500
%%%% end
*/
