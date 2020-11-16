// AFTER EDITORIAL, AC

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
  const int n = 5 * 1e5;
  int nq; // [1, 5 x 10^5]
  cin >> nq;
  vector<array<int, 3>> qs(nq);
  cin >> qs;

  // Simulate for large modulos
  vector<int> ls1(n + 1);

  // Simulate for small modulos
  const int sep = sqrt(n);
  vector<vector<int>> ls2(sep + 1, vector<int>(sep));

  for (auto [t, x, y] : qs) {

    if (t == 1) {
      // Large modulos
      ls1[x] += y;

      // Small modulos
      FOR(m, 1, sep + 1) { // O(n^1/2)
        ls2[m][(x % m)] += y;
      }
    }

    if (t == 2) {
      ll res = 0;
      if (x > sep) {
        // Large modulo
        for (int z = y; z <= n; z += x) { // O(n^1/2)
          res += ls1[z] ;
        }

      } else {

        // Small modulo
        res += ls2[x][y];

      }
      cout << res << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1207F/main.cpp

%%%% begin
5
1 3 4
2 3 0
2 4 3
1 4 -4
2 1 0
%%%%
4
4
0
%%%% end
*/
