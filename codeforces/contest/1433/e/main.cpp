// AC

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
  int n; // [2, 20] even
  cin >> n;

  int k = n / 2; // [1, 10]

  vector<ll> fact(n, 1);
  FOR(i, 2, n) {
    fact[i] = fact[i - 1] * i;
  }
  dbg(fact);

  vector<vector<ll>> comb(n + 1, vector<ll>(n + 1));
  comb[0][0] = 1;
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      array<int, 2> prevs[] = {{i - 1, j - 1}, {i - 1, j}};
      for (auto [ii, jj] : prevs) {
        if (ii >= jj && jj >= 0) {
          comb[i][j] += comb[ii][jj];
        }
      }
    }
  }
  dbg2(comb);

  ll res = fact[k - 1] * fact[k - 1] * comb[n - 1][k - 1];
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest/1433/e/main.cpp

%%%% begin
2
%%%%
1
%%%% end

%%%% begin
4
%%%%
3
%%%% end

%%%% begin
8
%%%%
1260
%%%% end

%%%% begin
20
%%%%
12164510040883200
%%%% end
*/
