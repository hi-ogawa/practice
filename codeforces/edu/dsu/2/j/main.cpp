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
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

struct Dsu {
  vector<int> parents;
  vector<int> data;
  vector<vector<int>> adj;

  Dsu(int n) {
    parents.resize(n);
    iota(ALL(parents), 0);
    data.resize(n);
    adj.resize(n);
    FOR(i, 0, n) { adj[i].push_back(i); }
  }

  int find(int x) {
    if (x == parents[x]) { return x; }
    return parents[x] = find(parents[x]);
  }

  void merge(int x, int y) {
    int xr = find(x);
    int yr = find(y);
    if (xr == yr) { return; }
    if (adj[xr].size() > adj[yr].size()) { swap(x, y); swap(xr, yr); }

    int flip = data[x] == data[y];
    for (auto z : adj[xr]) {
      adj[yr].push_back(z);
      data[z] ^= flip;
    }
    parents[xr] = yr;
    adj[xr].clear();
  }
};

// Main
void mainCase() {
  int n, m; // [1, 3e5]
  cin >> n >> m;
  vector<array<int, 2>> edges(m);
  cin >> edges;

  Dsu dsu(n);

  int res = -1;
  FOR(i, 0, m) {
    auto [x, y] = edges[i];
    x--; y--;
    int xr = dsu.find(x), yr = dsu.find(y);
    if (xr == yr) {
      if (dsu.data[x] == dsu.data[y]) {
        res = i + 1;
        break;
      }
      continue;
    }
    dsu.merge(x, y);
  }

  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/edu/dsu/2/j/main.cpp

%%%% begin
3 3
1 2
2 3
1 3
%%%%
3
%%%% end

%%%% begin
4 5
1 2
2 3
3 4
1 4
2 4
%%%%
5
%%%% end
*/
