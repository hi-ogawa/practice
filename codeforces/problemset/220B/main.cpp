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
  int n, m; // <= 10^5
  cin >> n >> m;
  vector<int> ls(n);
  vector<array<int, 2>> qs(m);
  cin >> ls >> qs;
  for (auto& [l, _r] : qs) { l--; } // [l, r)

  // Mo's query sorting
  int n_blk = sqrt(n);
  auto compare = [&](auto x, auto y) {
    x[0] /= n_blk; y[0] /= n_blk;
    if (x[0] == y[0]) { x[1] *= -1; y[1] *= -1; }
    return x < y;
  };
  vector<int> order(m);
  iota(ALL(order), 0);
  sort(ALL(order), [&](auto x, auto y) { return compare(qs[x], qs[y]); });

  // Range state
  int st_l = 0, st_r = 0;
  int n_ok = 0;
  vector<int> cnts(n + 1);

  auto add = [&](int i) {
    int x = ls[i];
    if (x > n) { return; }
    if (cnts[x] == x) { n_ok--; }
    cnts[x]++;
    if (cnts[x] == x) { n_ok++; }
  };

  auto remove = [&](int i) {
    int x = ls[i];
    if (x > n) { return; }
    if (cnts[x] == x) { n_ok--; }
    cnts[x]--;
    if (cnts[x] == x) { n_ok++; }
  };

  vector<int> res(m);
  FOR(i, 0, m) {
    int qi = order[i];
    auto [ql, qr] = qs[qi];
    while (ql < st_l) { add(--st_l); }
    while (st_r < qr) { add(st_r++); }
    while (st_l < ql) { remove(st_l++); }
    while (qr < st_r) { remove(--st_r); }
    dbgv(ql, qr, n_ok);
    res[qi] = n_ok;
  }
  dbg(res);

  for (auto r : res) { cout << r << endl; }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/220B/main.cpp --check

%%%% begin
7 2
3 1 2 2 3 3 7
1 7
3 4
%%%%
3
1
%%%% end
*/
