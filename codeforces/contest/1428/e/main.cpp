// AFTER EDITORIAL, WIP

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (decltype(Y) I = (X); I < (Y); ++I)
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
  int n, k; // [1, 10^5]
  cin >> n >> k;
  vector<int> ls(n); // [1, 10^6]
  cin >> ls;

  ll res = 0;
  for (auto x : ls) { res += (ll)x * x; }

  auto getSplitCost = [&](ll x, ll s) -> ll {
    ll q = x / s, r = x % s;
    return (q * q) * (s - r) + (q + 1) * (q + 1) * r;
  };

  auto getNextGain = [&](ll x, ll s) -> ll {
    return getSplitCost(x, s) - getSplitCost(x, s + 1);
  };

  // Maximize gain of total (k - n) splits
  multiset<array<ll, 3>> gains; // (next-gain, x, split)
  for (auto x : ls) {
    gains.insert({getNextGain(x, 1), x, 1});
  }
  FOR(i, 0, k - n) {
    auto [g, x, s] = *--gains.end(); gains.erase(--gains.end());
    res -= g;
    s++;
    gains.insert({getNextGain(x, s), x, s});
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest/1428/e/main.cpp

%%%% begin
3 6
5 3 1
%%%%
15
%%%% end

%%%% begin
1 4
19
%%%%
91
%%%% end
*/
