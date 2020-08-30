// AFTER CONTEST, WA

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
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  string s;
  cin >> s;
  int x;
  cin >> x;
  int n = s.size(); // <= 10^5

  // -1 for indeterminate
  vector<int> t(n, -1);
  bool ok = 1;
  auto update = [&](int i, int v) -> bool {
    if (v == -1) { return ok = 1; }
    if (t[i] == -1) { t[i] = v; return ok = 1; }
    if (t[i] == v) { return ok = 1; }
    return ok = 0;
  };

  FOR(i, 0, x) {
    if (i + x < n) {
      update(i + x, s[i] == '1');
    }
  }
  FOR(i, n - x, n) {
    if (i - x >= 0) {
      if (!update(i - x, s[i] == '1')) { break; }
    }
  }
  if (!ok) {
    cout << -1 << endl;
    return;
  }

  FOR(i, x, n - x) {
    if (s[i] == '0') {
      if (!update(i - x, 0)) { break; }
      if (!update(i + x, 0)) { break; }
    }
    if (s[i] == '1') {
      if (t[i - x] == 1) {
        // noop
      }
      if (t[i - x] == 0) {
        if (!update(i + x, 1)) { break; }
      }
      if (t[i - x] == -1) {
        if (t[i + x] == 0) {
          update(i - x, 1);
        }
      }
    }
  }
  // DD(t);
  // DD(ok);

  if (!ok) {
    cout << -1 << endl;
    return;
  }

  FOR(i, 0, n) {
    cout << (t[i] == -1 ? 1 : t[i]);
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  // mainCase();
  // return 0;
  // [ Multiple cases ]
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/edu94/c/main.cpp --check

%%%% begin
3
101110
2
01
1
110
1
%%%%
111011
10
-1
%%%% end
*/
