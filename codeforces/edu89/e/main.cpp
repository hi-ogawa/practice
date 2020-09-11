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
  int n, m;
  cin >> n >> m;
  vector<int> xs(n), ys(m);
  cin >> xs >> ys;

  // right cummin
  auto ps = xs;
  for (int i = n - 2; i >= 0; i--) {
    ps[i] = min(ps[i], ps[i + 1]);
  }
  dbg(ps);
  if (ps[0] != ys[0]) { cout << 0 << endl; return; }

  // q[j][0] = max{i | p[i] < y[j]}
  // q[j][1] = max{i | p[i] = y[j]}
  vector<array<int, 2>> qs(m);
  bool ok = 1;
  FOR(j, 1, m) {
    int y = ys[j];
    if (!binary_search(ALL(ps), y)) { ok = 0; break; }
    auto [itl, itu] = equal_range(ALL(ps), y);
    qs[j][0] = distance(ps.begin(), itl);
    qs[j][1] = distance(ps.begin(), itu);
  }
  dbg(qs);
  if (!ok) { cout << 0 << endl; return; }

  ll res = 1;
  ll modulo = 998244353;
  auto mul   = [&](ll x, ll y) -> ll { return (x * y) % modulo; };
  auto muleq = [&](ll&x, ll y) -> ll { return x = mul(x, y); };
  FOR(j, 1, m) {
    assert(qs[j][1] > qs[j][0]);
    muleq(res, qs[j][1] - qs[j][0]);
  }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/edu89/e/main.cpp --check

%%%% begin
13 1
88335 25981751 676025574 594198834 441470583 83030129 228139198 862264233 174165886 589744985 611000957 116923 295763763
88335
%%%%
1
%%%% end

%%%% begin
6 3
12 10 20 20 25 30
10 20 30
%%%%
2
%%%% end

%%%% begin
4 2
1 3 3 7
3 7
%%%%
0
%%%% end

%%%% begin
8 2
1 2 2 2 2 2 2 2
1 2
%%%%
7
%%%% end
*/
