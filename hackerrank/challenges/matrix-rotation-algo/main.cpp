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
  int m, n, r; // m, n \in [2, 300]
  cin >> m >> n >> r;
  vector<vector<int>> ls(m, vector<int>(n));
  cin >> ls;

  // WLOG m <= n and 2 | m
  bool rot90 = m > n;
  if (rot90) {
    swap(m, n);
    auto tmp = ls;
    ls = vector<vector<int>>(m, vector<int>(n));
    FOR(i, 0, m) {
      FOR(j, 0, n) {
        ls[i][j] = tmp[j][m - 1 - i];
      }
    }
  }

  int k = m / 2; // number of layers
  int w0 = n - 2 * (k - 1); // width of layer at the center

  // Layer geometry
  vector<array<int, 3>> gs(k); // (height, width, period)
  FOR(l, 0, k) {
    int h = 2 + 2 * l;
    int w = w0 + 2 * l;
    int p = 2 * (h + w - 2);
    gs[l] = {h, w, p};
  }

  // grid => layer
  auto toLayers = [&](const vector<vector<int>>& grid) {
    vector<vector<int>> layers(k);
    FOR(l, 0, k) {
      auto [h, w, _p] = gs[l];
      int i = k - 1 - l;
      int j = i;
      FOR(_, 0, h - 1) { layers[l].push_back(grid[i++][j]); }
      FOR(_, 0, w - 1) { layers[l].push_back(grid[i][j++]); }
      FOR(_, 0, h - 1) { layers[l].push_back(grid[i--][j]); }
      FOR(_, 0, w - 1) { layers[l].push_back(grid[i][j--]); }
    }
    return layers;
  };

  // grid <= layer
  auto fromLayers = [&](vector<vector<int>>& layers) {
    vector<vector<int>> grid(m, vector<int>(n));
    FOR(l, 0, k) {
      auto [h, w, _p] = gs[l];
      int i = k - 1 - l;
      int j = i;
      int p = 0;
      FOR(_, 0, h - 1) { grid[i++][j] = layers[l][p++]; }
      FOR(_, 0, w - 1) { grid[i][j++] = layers[l][p++]; }
      FOR(_, 0, h - 1) { grid[i--][j] = layers[l][p++]; }
      FOR(_, 0, w - 1) { grid[i][j--] = layers[l][p++]; }
    }
    return grid;
  };

  // Rotate layers
  auto layers = toLayers(ls);
  FOR(l, 0, k) {
    auto [_h, _w, p] = gs[l];
    auto& v = layers[l];
    rotate(v.begin(), v.end() - (r % p), v.end());
  }
  auto ls2 = fromLayers(layers);

  vector<vector<int>> res = ls2;
  if (rot90) {
    res = vector<vector<int>>(n, vector<int>(m));
    FOR(i, 0, m) {
      FOR(j, 0, n) {
        res[j][m - 1 - i] = ls2[i][j];
      }
    }
    swap(m, n);
  }

  FOR(i, 0, m) {
    FOR(j, 0, n) {
      cout << res[i][j] << " \n"[j == n - 1];
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py hackerrank/challenges/matrix-rotation-algo/main.cpp --check

%%%% begin
4 4 2
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
%%%%
3 4 8 12
2 11 10 16
1 7 6 15
5 9 13 14
%%%% end

%%%% begin
5 4 7
1 2 3 4
7 8 9 10
13 14 15 16
19 20 21 22
25 26 27 28
%%%%
28 27 26 25
22 9 15 19
16 8 21 13
10 14 20 7
4 3 2 1
%%%% end

%%%% begin
2 2 3
1 1
1 1
%%%%
1 1
1 1
%%%% end
*/
