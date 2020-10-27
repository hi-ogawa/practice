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
  int n; // [1, 3 x 10^5]
  cin >> n;
  vector<int> ls(n); // [1, n]
  cin >> ls;

  // Handle no-op case
  bool ok = 1;
  FOR(i, 0, n - 1) {
    if (ls[i] > ls[i + 1]) {
      ok = 0;
      break;
    }
  }
  if (ok) { cout << 0 << "\n"; return; }

  // WLOG, compress to {0, 1, 2, .., m - 1}
  auto dec = ls;
  sort(ALL(dec));
  dec.erase(unique(ALL(dec)), dec.end());
  int m = dec.size();
  map<int, int> enc;
  FOR(i, 0, m) { enc[dec[i]] = i; }

  for (auto& x : ls) { x = enc[x]; }
  dbg(ls);

  // Find inversions
  //   inv_min(x) = min { y | there is an inversion (y, x) }
  //   inv_max(y) = max { x | there is an inversion (y, x) }
  vector<int> inv_min(m, m), inv_max(m, -1);
  set<int> tmp;
  FOR(i, 0, n) {
    int x = ls[i];
    auto it = tmp.upper_bound(x);
    if (it != tmp.end()) { inv_min[x] = *it; }
    tmp.insert(x);
  }
  tmp.clear();
  for (int i = n - 1; i >= 0; i--) {
    int x = ls[i];
    auto it = tmp.lower_bound(x);
    if (it != tmp.begin()) { inv_max[x] = *prev(it); }
    tmp.insert(x);
  }
  dbg(inv_min);
  dbg(inv_max);

  // Cum minimum/maximum
  auto cum_inv_min = inv_min;
  for (int x = m - 2; x >= 0; x--) {
    cum_inv_min[x] = min(cum_inv_min[x], cum_inv_min[x + 1]);
  }
  auto cum_inv_max = inv_max;
  FOR(x, 1, m) {
    cum_inv_max[x] = max(cum_inv_max[x], cum_inv_max[x - 1]);
  }
  dbg(cum_inv_min);
  dbg(cum_inv_max);

  int res = m;

  // Optimal cost when moving "k" to the right
  FOR(k, 0, m) {
    int t1 = (k == 0) ? 0 : (cum_inv_max[k - 1] + 1);
    int t2 = m - k; // Need to move all k, k+1, .., m-1
    int t = t1 + t2;
    res = min(res, t);
  }

  // Optimal cost when moving "k" to the left
  FOR(k, 0, m) {
    int t1 = k + 1; // Need to move all 0, 1, .., k
    int t2 = (k == m - 1) ? 0 : (m - cum_inv_min[k + 1]);
    int t = t1 + t2;
    res = min(res, t);
  }

  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1223D/main.cpp

%%%% begin
3
7
3 1 6 6 3 1 1
8
1 1 4 4 4 7 8 8
7
4 2 5 2 6 2 7
%%%%
2
0
1
%%%% end
*/
