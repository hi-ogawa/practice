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
  ll n, k; // n \in [2, 10^5], k \in [1, 10^14]
  cin >> n >> k;
  vector<ll> ls(n); // [1, 10^9]
  cin >> ls;
  sort(ALL(ls));

  int i = 0, j = n - 1;
  ll m = ls[0], M = ls[n - 1];
  while (m < M && k > 0) {
    while (i < n - 1 && m == ls[i]) { i++; }
    while (j > 0     && M == ls[j]) { j--; }
    ll c0 = i, c1 = n - j - 1; // NOTE: cost is always increasing as time goes, thus taking small cost is optimal strategy.
    if (c0 < c1) {
      // Increase "m"
      if (c0 * (ls[i] - m) > k) { // Use up all k
        m += k / c0;
        break;
      }
      k -= c0 * (ls[i] - m);
      m = ls[i];
    } else {
      // Decrease "M"
      if (c1 * (M - ls[j]) > k) { // Use up all k
        M -= k / c1;
        break;
      }
      k -= c1 * (M - ls[j]);
      M = ls[j];
    }
  }
  int res = M - m;
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1244E/main.cpp --check

%%%% begin
4 5
3 1 7 5
%%%%
2
%%%% end

%%%% begin
3 10
100 100 100
%%%%
0
%%%% end

%%%% begin
10 9
4 5 5 7 5 4 5 2 4 3
%%%%
1
%%%% end
*/
