
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

// Enumerate digits for brute force solution
bool nextDigits(vector<int>& ls, int base) {
  int c = 1;
  for (auto& x : ls) {
    x += c;
    c = x / base;
    x %= base;
    if (c == 0) { break; }
  }
  return c == 0;
}

// Main
void mainCase() {
  int n, m, k, p; // n, m \in [1, 1000], p \in [1, 100], k \in [1, 10^6]
  cin >> n >> m >> k >> p;
  vector<vector<int>> ls(n, vector<int>(m)); // [1, 1000]
  cin >> ls;

  // Enumerate (n + m)^k
  vector<int> pattern(k);

  auto solve = [&](auto ls) -> ll {
    ll res = 0;
    for (auto c : pattern) {
      if (c < n) {
        // Pick row
        int i = c;
        FOR(j, 0, m) {
          res += ls[i][j];
          ls[i][j] -= p;
        }
      } else {
        // Pick column
        int j = c - n;
        FOR(i, 0, n) {
          res += ls[i][j];
          ls[i][j] -= p;
        }
      }
    }
    return res;
  };

  ll res = -1e18;
  do {
    ll t = solve(ls);
    res = max(res, t);
  } while (nextDigits(pattern, n + m));

  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/446B/brute.cpp

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
