// AC

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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n; // [1, 2 x 10^5]
  cin >> n;
  ll k; // [1, 10^18]
  cin >> k;
  vector<ll> ls(n); // [1, k]
  cin >> ls;

  // Fake cyclic by doubling
  vector<ll> ls_dup(2 * n);
  FOR(i, 0, n) {
    ls_dup[i] = ls_dup[i + n] = ls[i];
  }

  // Cum sum
  vector<ll> ps(2 * n + 1);
  FOR(i, 0, 2 * n) {
    ps[i + 1] = ps[i] + ls_dup[i];
  }

  // Done if one suffices
  if (ps[n] <= k) { cout << 1 << "\n"; return; }

  // Find boundary index from each index
  vector<int> bs(2 * n);
  FOR(i, 0, 2 * n) {
    auto it = upper_bound(ps.begin() + i, ps.end(), ps[i] + k);
    bs[i] = distance(ps.begin(), it) - 1;
  }
  dbg(bs);

  // Binary lifting
  int num_verts = 2 * n + 1;
  int b_lim = 0;
  while ((1 << b_lim) < num_verts) { b_lim++; }
  vector<vector<int>> table(b_lim, vector<int>(num_verts));

  FOR(i, 0, 2 * n) { table[0][i] = bs[i]; } // Parent relation
  table[0][2 * n] = 2 * n; // Special vertex to take care out-of-bound

  FOR(b, 1, b_lim) {
    FOR(i, 0, num_verts) {
      table[b][i] = table[b - 1][table[b - 1][i]];
    }
  }
  dbg2(table);

  // Count how many steps are needed to move "x" => "x + n"
  auto solve = [&](int x) -> int {
    int res = 0;
    int b = b_lim - 1;
    int y = x;
    while (b >= 0) {
      int z = table[b][y];
      if (z >= x + n) { b--; continue; }
      y = z;
      res += (1 << b);
    }
    res++;
    return res;
  };

  // Check all starting indices
  int res = 1e9;
  FOR(i, 0, n) {
    int t = solve(i);
    res = min(res, t);
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/additional_problems/task1191/main.cpp

%%%% begin
8 5
2 2 2 1 3 1 2 1
%%%%
3
%%%% end
*/
