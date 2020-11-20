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
  Dsu(int n) {
    parents.assign(n, 0);
    iota(ALL(parents), 0);
  }
  int find(int x) {
    if (x == parents[x]) { return x; }
    return parents[x] = find(parents[x]);
  }
  void merge(int x, int y) {
    parents[find(x)] = find(y);
  }
};

// Main
void mainCase() {
  int n, m; // n \in [1, 1500], m \in [1, 4 x 10^5]
  cin >> n >> m;
  vector<array<int, 3>> edges(m); // weight \in [0, 10^4]
  cin >> edges;
  sort(ALL(edges), [](auto x, auto y) { return x[2] < y[2]; });
  for (auto& [x, y, w] : edges) { x--; y--; }

  dbg(edges);

  // f(w) = 1 \iff some spanning tree with max(weight) <= w
  auto evaluate = [&](int w_lim) -> bool {
    Dsu dsu(n);
    int cnt = 0;
    for (auto [x, y, w] : edges) {
      if (w > w_lim) { break; }
      x = dsu.find(x);
      y = dsu.find(y);
      if (x != y) {
        dsu.merge(x, y);
        cnt++;
      }
    }
    dbg(w_lim, cnt);
    return cnt == n - 1;
  };

  // min { w | f(w) = 1 }
  auto search = [&]() -> int {
    int x0 = -1, x1 = 1e4; // (x0, x1]
    while (x0 + 1 < x1) {
      int x = (x0 + x1 + 1) / 2;
      if (evaluate(x)) {
        x1 = x;
      } else {
        x0 = x;
      }
    }
    return x1;
  };

  auto res = search();
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/edu/dsu/2/g/main.cpp

%%%% begin
3 2
1 2 5
1 3 10
%%%%
10
%%%% end
*/
