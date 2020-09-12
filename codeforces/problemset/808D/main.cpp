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
  int n;
  cin >> n;
  vector<ll> ls(n);
  cin >> ls;

  // cumsum
  vector<ll> ps(n + 1);
  vector<ll> qs(n + 1); // for reverse ls
  FOR(i, 0, n) {
    ps[i + 1] = ps[i] + ls[i];
    qs[i + 1] = qs[i] + ls[n - 1 - i];
  }

  ll total = ps[n];
  if (total % 2 == 1) { cout << "NO" << endl; return; }

  bool ok0 = binary_search(ALL(ps), total / 2);
  if (ok0) { cout << "YES" << endl; return; }

  // Find sum([0, i-1] + [i+1, j]) = total / 2
  bool ok1 = 0;
  FOR(i, 0, n) {
    ll x = total / 2 + ls[i];
    ok1 = binary_search(ps.begin() + i + 1, ps.end(), x);
    if (ok1) { break; }
  }
  if (ok1) { cout << "YES" << endl; return; }

  // Find sum-reverse([0, i-1] + [i+1, j]) = total / 2
  bool ok2 = 0;
  FOR(i, 0, n) {
    ll x = total / 2 + ls[n - 1 - i];
    ok2 = binary_search(qs.begin() + i + 1, qs.end(), x);
    if (ok2) { break; }
  }
  if (ok2) { cout << "YES" << endl; return; }

  cout << "NO" << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/808D/main.cpp --check

%%%% begin
3
1 3 2
%%%%
YES
%%%% end

%%%% begin
5
1 2 3 4 5
%%%%
NO
%%%% end

%%%% begin
5
2 2 3 4 5
%%%%
YES
%%%% end
*/
