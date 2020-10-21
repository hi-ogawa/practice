// WIP

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

constexpr ll modulo = 998244353;
using mint = int;

// Main
void mainCase() {
  int n, m; // [1, 10^5]
  cin >> n >> m;
  vector<mint> ls(n);
  cin >> ls;
  vector<array<int, 2>> edges(m);
  cin >> edges;
  for (auto& [x, y] : edges) { if (x > y) { swap(x, y); } }

  vector<set<int>> adj(n);
  for (auto [x, y] : edges) {
    adj[x].insert(y);
    adj[y].insert(x);
  }

  // edges ordered in two ways
  auto edges1 = edges;
  auto edges2 = edges;
  auto compare1 = [](auto x, auto y) { return x[0] < y[0]; }
  auto compare2 = [](auto x, auto y) { return x[1] < y[1]; }
  sort(ALL(edges1), compare1);
  sort(ALL(edges2), compare2);

  // Divide and conquer
  function<mint(int, int)> solve = [&](int l, int r) -> mint {
    if ((r - l) <= 2) { return 0; }
    int m = (l + r) / 2;
    mint res1 = solve(l, m);
    mint res2 = solve(m, r);
    mint res3 = 0;
    auto it1 = lower_bound(ALL(edges1), {m, 0}, compare1);
    while (it1 != edges1.end()) {
      auto [i, j] = *it1;
      // adj[i];
      // adj[j];
      // if (i)
      it1++;
    }
    // auto it2 = lower_bound(ALL(edges2), {m, 0}, compare2);
    // auto it2 = upper
    // FOR(i, l, m) {
    //   // adj[x];
    // }
    // FOR(i, m, r) {
    // }
    return res1 + res2 + res3;
  };
  auto res = solve(0, n);
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/enumerate_triangles/main.cpp

%%%% begin
4 5
1 2 3 4
0 3
2 0
2 1
2 3
1 3
%%%%
36
%%%% end
*/
