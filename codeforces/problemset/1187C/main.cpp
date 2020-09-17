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
  int n, nq;
  cin >> n >> nq;
  vector<array<int, 3>> qs(nq);
  cin >> qs;
  for (auto& [_t, x, y] : qs) { x--; y--; }

  enum { kIn1, kOut1, kIn0, kOut0 };
  vector<array<int, 3>> events; // (x, type, id)
  FOR(qi, 0, nq) {
    auto [t, x, y] = qs[qi];
    if (t == 1) {
      events.push_back({x, kIn1, qi});
      events.push_back({y, kOut1, qi});
    }
    if (t == 0) {
      events.push_back({x, kIn0, qi});
      events.push_back({y, kOut0, qi});
    }
  }
  sort(ALL(events));
  dbg(events);

  vector<int> res(n);
  bool ok = 1;
  int incr = 0; // incr request on/off
  set<int> decrs; // pending decr requests
  int ie = 0, ne = events.size();
  res[0] = 1000;
  FOR(x, 0, n) {
    while (ie < ne && events[ie][0] <= x) {
      auto [qx, t, qi] = events[ie++];
      if (t == kIn1)  { incr++; }
      if (t == kOut1) { incr--; }
      if (t == kIn0) { decrs.insert(qi); }
      if (t == kOut0) {
        if (decrs.count(qi)) { ok = 0; break; }
      }
    }
    dbgv(x, incr, decrs);
    if (!ok) { break; }
    if (x == n - 1) { break; }

    res[x + 1] = res[x];
    if (!incr && !decrs.empty()) {
      decrs.clear();
      res[x + 1]--;
    }
  }
  dbgv(ok, res);

  if (!ok) { cout << "NO" << endl; return; }
  cout << "YES" << endl;
  FOR(i, 0, n) {
    cout << res[i] << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1187C/main.cpp --check

%%%% begin
7 4
1 1 3
1 2 5
0 5 6
1 6 7
%%%%
YES
1 2 2 3 5 4 4
%%%% end

%%%% begin
4 2
1 1 4
0 2 3
%%%%
NO
%%%% end
*/
