// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = begin(x); it != end(x); it++) { if (it != begin(x)) { o << ", "; } o << *it; } o << "}"; return o; }
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
  int n, m, k; // m \in [1, 10]
  cin >> n >> m >> k;
  vector<int> ls(n);
  cin >> ls;

  // Cumsum with "length cost = - k(size / m)"
  vector<vector<ll>> ps(m, vector<ll>(n + 1));
  FOR(j, 0, m) {
    FOR(i, 0, n) {
      ps[j][i + 1] = ps[j][i] + ls[i];
      if (i % m == j) {
        ps[j][i + 1] -= k;
      }
    }
  }
  dbg2(ps);

  ll res = 0;
  FOR(j, 0, m) {
    // Find max segment for this "j-th pattern"
    multiset<ll> ms(ALL(ps[j]));
    FOR(i, 0, n) {
      ms.erase(ms.find(ps[j][i]));
      if (i % m == j) {
        res = max(res, *ms.rbegin() - ps[j][i]);
      }
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
python misc/run.py codeforces/problemset/1197D/main.cpp --check

%%%% begin
7 3 10
2 -4 15 -3 4 8 3
%%%%
7
%%%% end

%%%% begin
5 2 1000
-13 -4 -9 -20 -11
%%%%
0
%%%% end
*/
