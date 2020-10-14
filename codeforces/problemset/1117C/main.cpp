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
  int x1, y1, x2, y2; // [0, 10^9]
  cin >> x1 >> y1 >> x2 >> y2;
  int n; // [1, 10^5]
  cin >> n;
  string s;
  cin >> s;

  // p(i) = delta position after i-step wind
  vector<array<int, 2>> ps(n + 1);
  map<char, array<int, 2>> moves = {
      {'U', {0, +1}},
      {'D', {0, -1}},
      {'L', {-1, 0}},
      {'R', {+1, 0}}};
  FOR(i, 0, n) {
    auto [dx, dy] = moves[s[i]];
    auto [x, y] = ps[i];
    ps[i + 1] = {x + dx, y + dy};
  }
  dbg(ps);

  //
  // PROP.
  //   Reachable after k steps
  //     <=>  distance((x2, y2), (x1, y1) + p(k)) ≤ k
  //
  // PROP.
  //   By periodicity, we have
  //     p(a * n + i) = a * p(n) + p(i)
  //

  const ll kInf = 1e18;

  // f(k) = 1 \iff reachable after k steps
  auto evaluate = [&](ll k) -> bool {
    ll i = k % n, a = k / n;
    auto [xi, yi] = ps[i];
    auto [xn, yn] = ps[n];
    ll x = x1 + a * xn + xi;
    ll y = y1 + a * yn + yi;
    return abs(x - x2) + abs(y - y2) <= k;
  };

  // min { k | f(k) = 1 }
  auto search = [&]() -> ll {
    ll k0 = -1, k1 = kInf; // (k0, k1]
    while (k0 + 1 < k1) {
      ll k = (k0 + k1 + 1) / 2;
      if (evaluate(k)) {
        k1 = k;
      } else {
        k0 = k;
      }
    }
    return k1 == kInf ? -1 : k1;
  };

  ll res = search();
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1117C/main.cpp

%%%% begin
0 0
4 6
3
UUU
%%%%
5
%%%% end

%%%% begin
0 3
0 0
3
UDD
%%%%
3
%%%% end

%%%% begin
0 0
0 1
1
L
%%%%
-1
%%%% end
*/
