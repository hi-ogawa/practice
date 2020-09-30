// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i,       tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; bool b = 0; apply([&](auto&&... y){ ((o << (b ? ", " : "") << y, b = 1), ...); }, x); return o << ")"; }
template<class T1, class T2> istream& operator>>(istream& i,       pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
istream& operator>>(istream& i,       T& x) { for (auto& y : x) { i >> y; } return i; }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
ostream& operator<<(ostream& o, const T& x) { o << "{"; bool b = 0; for (auto& y : x) { o << (b ? ", " : "") << y; b = 1; } return o << "}"; }
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
  int n; // [1, 4000]
  cin >> n;
  string s;
  cin >> s;

  const int k = 3;
  map<char, int> enc = {{'R', 0}, {'G', 1}, {'B', 2}};

  vector<int> ls(n);
  FOR(i, 0, n) { ls[i] = enc[s[i]]; }

  // Cum counts
  vector<vector<int>> cnts(k, vector<int>(n + 1));
  FOR(x, 0, k) {
    FOR(i, 0, n) {
      cnts[x][i + 1] = cnts[x][i] + (ls[i] == x);
    }
  }

  // Enumerate S3
  vector<array<int, 3>> perms;
  array<int, 3> _p = {0, 1, 2};
  do { perms.push_back(_p); } while (next_permutation(ALL(_p)));

  ll res = 0;
  for (auto [x, y, z] : perms) {
    FOR(i, 0, n) {
      FOR(l, 1, n - i) {
        if (ls[i] == x && ls[i + l] == y) {
          res += cnts[z][n] - cnts[z][i + l];
          if (i + 2 * l < n && ls[i + 2 * l] == z) { res--; }
        }
      }
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
python misc/run.py atcoder/abc162/d/main.cpp --check

%%%% begin
4
RRGB
%%%%
1
%%%% end

%%%% begin
39
RBRBGRBGGBBRRGBBRRRBGGBRBGBRBGBRBBBGBBB
%%%%
1800
%%%% end
*/
