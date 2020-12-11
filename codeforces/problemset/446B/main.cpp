// WA

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
  int n, m, k, p; // n, m \in [1, 1000], p \in [1, 100], k \in [1, 10^6]
  cin >> n >> m >> k >> p;
  vector<vector<int>> ls(n, vector<int>(m)); // [1, 1000]
  cin >> ls;

  // Sum for each row/column
  vector<int> rows(n), cols(m);
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      rows[i] += ls[i][j];
      cols[j] += ls[i][j];
    }
  }

  // Choose gain greedily
  ll res = 0;
  array<multiset<ll>, 2> heaps; // separately for row/col
  array<int, 2> cnts = {}; // count row/col steps
  FOR(i, 0, n) {
    heaps[0].insert(rows[i]);
  }
  FOR(j, 0, m) {
    heaps[1].insert(cols[j]);
  }
  FOR(_, 0, k) {
    auto row = *--heaps[0].end();
    auto col = *--heaps[1].end();
    ll g_row = row - cnts[1] * p; // Actual gain due to column steps
    ll g_col = col - cnts[0] * p;
    dbg(heaps);
    dbg(g_row, g_col);

    if (g_row > g_col) {
      res += g_row;
      heaps[0].erase(--heaps[0].end());
      heaps[0].insert(row - m * p);
      cnts[0]++;

    } else {
      res += g_col;
      heaps[1].erase(--heaps[1].end());
      heaps[1].insert(col - n * p);
      cnts[1]++;
    }
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/446B/main.cpp

%%%% begin
2 3 2 2
8 6 2
8 3 5
%%%%
32
%%%% end

%%%% begin
2 2 2 2
1 3
2 4
%%%%
11
%%%% end

%%%% begin
2 2 5 2
1 3
2 4
%%%%
11
%%%% end
*/
