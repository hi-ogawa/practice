// WA

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

// Z function
vector<int> makeZ(const string& s) {
  int n = s.size();
  vector<int> z(n);
  FOR(i, 1, n) {
    while (i + z[i] < n && s[i + z[i]] == s[i]) { z[i]++; }
  }
  return z;
}

// Main
void mainCase() {
  int n; // [1, 1000]
  cin >> n;
  string s;
  cin >> s;
  int m = s.size(); // [1, 100]

  const int k = 26; // A..Z

  auto z = makeZ(s);
  dbg(z);

  const ll modulo = 1e9 + 7;
  auto add = [&](ll x, ll y) { return (x + y) % modulo; };
  auto sub = [&](ll x, ll y) { return add(x, - y + modulo); };
  auto mul = [&](ll x, ll y) { return (x * y) % modulo; };
  auto pow = [&](ll x, ll e) {
    ll y = 1;
    while (e) {
      if (e & 1) { y = mul(y, x); }
      e >>= 1; x = mul(x, x);
    }
    return y;
  };

  ll res = 0;
  FOR(i, 0, n - m + 1) {
    // Count strings having "s" starting from "i"
    ll pref = pow(k, i);
    ll suff = pow(k, n - m - i);
    FOR(j, 1, i + 1) {
      // Subtract double couting
      // TODO: this does double subtraction...
      if (j >= m) {
        pref = sub(pref, pow(k, i - m));
      } else if (z[j] == m - j) {
        pref = sub(pref, pow(k, i - j));
      }
    }
    dbgv(i, n - m - i, pref, suff);
    res = add(res, mul(pref, suff));
  }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/string_algorithms/task1112/main.cpp --check

%%%% begin
4
AA
%%%%
%%%% end

%%%% begin
6
AA
%%%%
2212651
%%%% end

%%%% begin
6
ABCDB
%%%%
52
%%%% end
*/
