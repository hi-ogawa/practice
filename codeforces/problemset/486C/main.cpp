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
  int n, p;
  cin >> n >> p;
  string s;
  cin >> s;
  p--; // zero-based

  // WLOG p is on the left side
  p = min(p, n - 1 - p);

  // Find unmatch positions
  vector<int> qs;
  FOR(i, 0, n / 2) {
    if (s[i] != s[n - 1 - i]) {
      qs.push_back(i);
    }
  }
  dbgv(qs);

  // Fix them

  auto getDist = [](char x, char y) -> int {
    int xx = x - 'a', yy = y - 'a';
    int m = 26;
    return min((xx - yy + m) % m, (yy - xx + m) % m);
  };

  int res = 0;
  for (auto q : qs) {
    res += getDist(s[q], s[n - 1 - q]);
  }

  int k = qs.size();
  if (k == 1) {
    res += abs(p - qs[0]);
  }
  if (k >= 2) {
    int q1 = qs.front();
    int q2 = qs.back();
    if (p < q1) {
      res += q2 - p;
    }
    if (q2 < p) {
      res += p - q1;
    }
    if (q1 <= p && p <= q2) {
      res += q2 - q1;
      res += min(p - q1, q2 - p);
    }
  }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/486C/main.cpp --check

%%%% begin
8 3
aeabcaez
%%%%
6
%%%% end
*/
