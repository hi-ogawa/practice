// AFTER EDITORIAL, AC

// NOTE: barely AC after using custom hashing and removing assertions...

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

// Hash by Chris Wellons https://nullprogram.com/blog/2018/07/31/
uint32_t hash32(uint32_t x) {
  x ^= x >> 16;
  x *= 0x7feb352dU;
  x ^= x >> 15;
  x *= 0x846ca68bU;
  x ^= x >> 16;
  return x;
}
struct Hash32 { size_t operator()(int x) const { return hash32(x); }; };
struct Hash32x2 { size_t operator()(const array<int, 2>& x) const { return hash32(hash32(x[0]) ^ x[1]); }; };

using mint = uint32_t; // modulo = 2^32

// Main
void mainCase() {
  int n, nq; // [1, 3 x 10^5]
  cin >> n >> nq;
  vector<mint> ls(n); // [1, 10^9]
  cin >> ls;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;
  vector<array<int, 2>> qs(nq);
  cin >> qs;

  for (auto& [x, y] : edges) { x--; y--; }
  for (auto& [x, y] : qs) { x--; y--; }

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // DFS for depths, parents, ...
  vector<int> depths(n);
  vector<int> parents(n);
  function<void(int, int)> dfs = [&](int v, int vp) {
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      depths[u] = depths[v] + 1;
      parents[u] = v;
      dfs(u, v);
    }
  };
  dfs(0, 0);

  // Binary lifting
  int nb = 0;
  while ((1 << nb) <= n) { nb++; }
  vector<vector<int>> table(nb, vector<int>(n));
  table[0] = parents;
  FOR(b, 1, nb) {
    FOR(i, 0, n) {
      table[b][i] = table[b - 1][table[b - 1][i]];
    }
  }

  auto lift = [&](int x, int e) -> int {
    int b = 0;
    while (e > 0) {
      if (e & 1) { x = table[b][x]; }
      e >>= 1; b++;
    }
    return x;
  };

  // Count vertices by depth
  int d_lim = *max_element(ALL(depths)) + 1;
  vector<vector<int>> inv_depths(d_lim);
  FOR(i, 0, n) {
    inv_depths[depths[i]].push_back(i);
  }
  vector<int> cnts(d_lim);
  FOR(d, 0, d_lim) {
    cnts[d] = inv_depths.size();
  }

  // Find "special depth" for each block
  int d_blk = sqrt(n);
  int s_lim = (d_lim + d_blk - 1) / d_blk; // ~ n / d_blk = n^1/2
  vector<int> specials(s_lim);
  FOR(i, 0, s_lim) {
    int d0 = d_blk * i;
    int d1 = min(d_blk * (i + 1), d_lim);
    auto it = min_element(cnts.begin() + d0, cnts.begin() + d1);
    assert(*it > 0);
    specials[i] = distance(cnts.begin(), it);
  }
  dbg(specials);
  assert(specials[0] == 0);

  // Precompute for vertices at "special depth"

  using map_impl = unordered_map<array<int, 2>, mint, Hash32x2>;
  // using map_impl = map<array<int, 2>, mint>;
  vector<map_impl> precomp(s_lim);

  FOR(i, 1, s_lim) {
    int d0 = specials[i - 1];
    int d1 = specials[i];
    auto& xs = inv_depths[d1];
    for (auto x : xs) {
      for (auto y : xs) {
        if (x > y) { continue; }
        mint t = 0;
        // assert(depths[x] == depths[y]);
        // assert(depths[x] == d1);
        // assert(d0 < d1);
        auto xx = x, yy = y;
        FOR(_, 0, d1 - d0) {
          xx = parents[xx]; yy = parents[yy];
          t += ls[xx] * ls[yy];
        }
        precomp[i][{x, y}] = t;
      }
    }
  }
  dbg(precomp);

  // Answer query
  auto solve = [&](int x, int y) -> mint {
    assert(depths[x] == depths[y]);
    mint res = 0;

    // Brute force at most "d_blk"
    int dx = depths[x];
    auto it = upper_bound(ALL(specials), dx);
    assert(it != specials.begin());
    it--;
    int i_init = distance(specials.begin(), it);
    int d_init = *it;
    assert(d_init <= dx);

    auto xx = x, yy = y;
    res += ls[xx] * ls[yy];
    FOR(_, 0, dx - d_init) {
      xx = parents[xx]; yy = parents[yy];
      res += ls[xx] * ls[yy];
    }

    // Collect precomputed results with binary lifting
    for (int i = i_init; i >= 1; i--) {
      int d0 = specials[i - 1];
      int d1 = specials[i];
      // assert(depths[xx] == depths[yy]);
      // assert(depths[xx] == d1);
      if (xx > yy) { swap(xx, yy); }
      // assert(precomp[i].count({xx, yy}));
      res += precomp[i][{xx, yy}];
      xx = lift(xx, d1 - d0);
      yy = lift(yy, d1 - d0);
    }

    return res;
  };

  for (auto [x, y] : qs) {
    auto res = solve(x, y);
    cout << res << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codechef/NOV20/SCALSUM/main.cpp

%%%% begin
5 2
5 4 3 2 1
1 2
1 3
2 4
2 5
2 3
4 5
%%%%
37
43
%%%% end
*/
