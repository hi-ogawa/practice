// AC

//
// NOTE:
//   Proof is similar to codeforces/problemset/1268B/main_v2.cpp
//   Here, we can consider "4-color-parity" as in
//     0 1 0 1 ...
//     2 3 2 3
//     0 1 ...
//     2 3
//   Then, it's clear that we have to use even number of 1x2 blocks (also same for 2x1 block).
//

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
  int n, m, a, b, c; // n, m \in [1, 100]
  cin >> n >> m >> a >> b >> c;

  // WLOG, m : even
  bool do_swap = m % 2 == 1;
  if (do_swap) { swap(n, m); swap(a, b); }
  if (m % 2 == 1) { cout << "IMPOSSIBLE\n"; return; }

  vector<vector<int>> res(n, vector<int>(m, 0));
  if (n % 2 == 1) {
    // Fill last row : 44 55 44 55 ...
    FOR(j, 0, m) {
      res[n - 1][j] = (j % 4 < 2) ? 4 : 5;
    }
    a -= m / 2;
    if (a < 0) { cout << "IMPOSSIBLE\n"; return; }
  }

  // Fill even x even
  int nn = (n / 2) * 2;
  int aa = (a / 2) * 2;
  int bb = (b / 2) * 2;
  if (aa / 2 + bb / 2 + c < (nn * m) / 4) { cout << "IMPOSSIBLE\n"; return; }

  int cnt = 0;
  FOR(i, 0, nn / 2) {
    FOR(j, 0, m / 2) {
      // Color by 4-parity,
      // 0 0 2 2 ...
      // 0 0 2 2
      // 2 2 0 0 ...
      // 2 2 0 0
      if ((i + j) % 2 == 1) {
        res[2 * i + 0][2 * j + 0] = 2;
        res[2 * i + 1][2 * j + 0] = 2;
        res[2 * i + 0][2 * j + 1] = 2;
        res[2 * i + 1][2 * j + 1] = 2;
      }
      // Split 4x4 by 1x2 blocks or 2x1 blocks
      if (cnt < aa / 2) {
        // 0 0 or 2 2
        // 1 1    3 3
        res[2 * i + 1][2 * j + 0]++;
        res[2 * i + 1][2 * j + 1]++;
      }
      else if (cnt < aa / 2 + bb / 2) {
        // 0 1 or 2 3
        // 0 1    2 3
        res[2 * i + 0][2 * j + 1]++;
        res[2 * i + 1][2 * j + 1]++;
      }
      cnt++;
    }
  }
  dbg2(res);

  if (do_swap) {
    auto tmp = res;
    res = vector<vector<int>>(m, vector<int>(n));
    swap(n, m);
    FOR(i, 0, n) FOR(j, 0, m) res[i][j] = tmp[j][i];
  }

  FOR(i, 0, n) {
    FOR(j, 0, m) {
      cout << (char)(res[i][j] + 'a');
    }
    cout << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/26C/main.cpp

%%%% begin
3 6 10 10 10
%%%%
%%%% end

%%%% begin
2 6 2 2 1
%%%%
aabcca
aabdda
%%%% end

%%%% begin
1 1 100 100 100
%%%%
IMPOSSIBLE
%%%% end

%%%% begin
4 4 10 10 10
%%%%
aabb
aabb
bbaa
bbaa
%%%% end
*/
