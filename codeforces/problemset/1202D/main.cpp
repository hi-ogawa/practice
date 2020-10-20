// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
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
  int n; // [1, 10^9]
  cin >> n;

  // (a..a) (b..b) (a..a) bbc
  // --k1-- --k2-- --k3--

  // n = k1 x binom(k2 + 2, 2) + k3

  auto binom2 = [](ll x) -> ll { return (x * (x - 1)) / 2; };

  int k2 = 0;
  while (binom2(k2 + 2) <= 50000) { k2++; }
  int bk2 = binom2(k2 + 2);
  assert(k2 == 315 && bk2 == 50086);

  int k1 = n / bk2; // [1, n / bk2] ~ [1, 2000]
  int k3 = n % bk2; // [1, bk2] ~ [1, 50086]
  int k = k1 + k2 + k3 + 3;
  dbg(k1, k2, k3, k);
  assert(k <= (int)1e5);

  vector<int> res(k);
  FOR(i, 0, k1) { res[i] = 1; }
  FOR(i, 0, k2) { res[i + k1] = 3; }
  FOR(i, 0, k3) { res[i + k1 + k2] = 1; }
  res[k - 3] = 3;
  res[k - 2] = 3;
  res[k - 1] = 7;
  dbg(res);

  FOR(i, 0, k) {
    cout << res[i];
  }
  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1202D/main.cpp

%%%% begin
2
6
1
%%%%
113337
1337
%%%% end
*/
