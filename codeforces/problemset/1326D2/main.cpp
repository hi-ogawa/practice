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

// cf. cses/string_algorithms/task1111/main.cpp
array<vector<int>, 2> makePalin(const string& s) {
  int n = s.size();
  array<vector<int>, 2> res; // NRVO
  auto& [d1, d2] = res;
  d1.resize(n);
  d2.resize(n);
  int l, r;
  l = r = 0; // (l, r)
  FOR(i, 0, n) {
    if (i < r) { d1[i] = min(d1[l + r - i], r - i); }
    while (
      0 <= i - d1[i] && i + d1[i] < n &&
      s[i - d1[i]] == s[i + d1[i]]) { d1[i]++; }
    if (i + d1[i] > r) { l = i - d1[i]; r = i + d1[i]; }
  }
  l = r = 0; // (l, r)
  FOR(i, 0, n) {
    if (i + 1 < r) { d2[i] = min(d2[l + r - (i + 1)], r - (i + 1)); }
    while (
      0 <= i - d2[i] && i + d2[i] + 1 < n &&
      s[i - d2[i]] == s[i + d2[i] + 1]) { d2[i]++; }
    if (i + d2[i] + 1 > r) { l = i - d2[i]; r = i + d2[i] + 1; }
  }
  return res;
};

// Main
void mainCase() {
  string s;
  cin >> s;
  int n = s.size(); // <= 10^6

  auto [d1, d2] = makePalin(s);
  dbg(d1); dbg(d2);

  vector<int> ps(n); // maximal palin length starts at i
  vector<int> qs(n); // maximal palin length end at i
  FOR(i, 0, n / 2 + (n % 2)) { // center on the left
    int l1 = 2 * d1[i] - 1;
    ps[i - d1[i] + 1] = max(ps[i - d1[i] + 1], l1);
    if (i > 0 && d2[i - 1] > 0) {
      int l2 = 2 * d2[i - 1];
      ps[i - d2[i - 1]] = max(ps[i - d2[i - 1]], l2);
    }
  }
  FOR(i, n / 2 + (n % 2), n) { // center on the right
    int l1 = 2 * d1[i] - 1;
    qs[i + d1[i] - 1] = max(qs[i + d1[i] - 1], l1);
    if (d2[i - 1] > 0) {
      int l2 = 2 * d2[i - 1];
      qs[i - 1 + d2[i - 1]] = max(qs[i - 1 + d2[i - 1]], l2);
    }
  }
  dbg(ps); dbg(qs);

  int res1 = 0, res2 = 0, res3 = 0, res4 = 0; // (length, index, head/tail, p/q)
  FOR(i, 0, n / 2 + 1) {
    int p = 2 * i + ps[i];
    int q = 2 * i + qs[n - i - 1];
    if (res1 < p) {
      res1 = p, res2 = i, res3 = 0, res4 = ps[i];
    }
    if (res1 < q) {
      res1 = q, res2 = i, res3 = 1, res4 = qs[n - i - 1];
    }
    if (s[i] != s[n - i - 1]) { break; }
  }
  dbgv(res1, res2, res3, res4);

  string res;
  res += s.substr(0, res2);
  if (res3 == 0) {
    res += s.substr(res2, res4);
  } else {
    res += s.substr(n - res2 - res4, res4);
  }
  res += s.substr(n - res2, res2);
  dbg(s);
  dbg(res);

  cout << res << endl;
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
python misc/run.py codeforces/problemset/1326D2/main.cpp --check

%%%% begin
1
acbba
%%%%
abba
%%%% end

%%%% begin
1
yvaamavy
%%%%
yvamavy
%%%% end

%%%% begin
5
a
abcdfdcecba
abbaxyzyx
codeforces
acbba
%%%%
a
abcdfdcba
xyzyx
c
abba
%%%% end
*/
