
//
// PROP.
//   Ford-Fulkerson correctness (i.e. maximul => maximum) holds for the "divisible-flow".
//   (the almost same proof works)
//

// NOTE: but it's obviously not the objective we want to maximize...

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

template<class T> using V = vector<T>;
using vec2 = array<ll, 2>;
constexpr ll kInf = 1e18;

void solveDivisibleMaxFlow(V<V<vec2>>& cap, int v0, int v1) {
  int n = cap.size();
  vector<int> parents(n);
  vector<bool> done(n);

  auto search = [&]() -> ll {
    deque<vec2> q; // (flow, vertex)
    q.push_back({kInf, v0});
    fill(ALL(done), 0);
    done[v0] = 1;
    while (!q.empty()) {
      auto [f, v] = q.front(); q.pop_front();
      if (v == v1) { return f; }
      FOR(u, 0, n) {
        if (done[u]) { continue; }
        auto [residue, div] = cap[v][u];
        auto ff = (min(f, residue) / div) * div;
        if (ff == 0) { continue; }
        done[u] = 1;
        parents[u] = v;
        q.push_back({ff, u});
      }
    }
    return 0;
  };

  auto update = [&](ll flow) {
    int v = v1;
    while (v != v0) {
      int u = parents[v];
      cap[u][v][0] -= flow;
      cap[v][u][0] += flow;
      v = u;
    }
  };

  while (true) {
    ll flow = search();
    if (flow == 0) { break; }
    update(flow);
  }
}

// Main
void mainCase() {
  ll z, w, b1, b2, c1, c2; // b \in [1, 2 x 10^5], z, w, c \in [1, 10^9]
  cin >> z >> w >> b1 >> b2 >> c1 >> c2;

  // max x1 + x2 + y1 + y2 s.t.
  //   0 <= x1 + y1 <= b1
  //   0 <= x2 + y2 <= b2
  //   |x1 x2| |c1| <= |z|
  //   |y1 y2| |c2|    |w|

  int n = 6;
  V<V<vec2>> cap(n, V<vec2>(n, {0, 1})); // cap[v][u] = {capacity(v, u), flow-unit(v, u)}
  //    1   3
  // 0          5
  //    2   4
  cap[0][1] = {z, 1};
  cap[0][2] = {w, 1};
  cap[1][3] = {kInf, c1};    cap[3][1] = {0, c1};
  cap[1][4] = {kInf, c2};    cap[4][1] = {0, c2};
  cap[2][3] = {kInf, c1};    cap[3][2] = {0, c1};
  cap[2][4] = {kInf, c2};    cap[4][2] = {0, c2};
  cap[3][5] = {c1 * b1, c1}; cap[5][3] = {0, c1};
  cap[4][5] = {c2 * b2, c2}; cap[5][4] = {0, c2};
  auto cap_init = cap;
  solveDivisibleMaxFlow(cap, 0, 5);

  dbg2(cap_init);
  dbg2(cap);

  //
  // This maximize
  //   (cap_init[3][5][0] - cap[3][5][0]) +
  //   (cap_init[4][5][0] - cap[4][5][0])
  // instead of
  //   (cap_init[3][5][0] - cap[3][5][0]) / c1 +
  //   (cap_init[4][5][0] - cap[4][5][0]) / c2
  // Thus, obviously WA
  //

  ll res1 = (cap_init[3][5][0] - cap[3][5][0]) / c1;
  ll res2 = (cap_init[4][5][0] - cap[4][5][0]) / c2;
  ll res = res1 + res2;
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/edu94/b/main.cpp

%%%% begin
1
1 19
1 3
19 5
%%%%
3
%%%% end

%%%% begin
3
33 27
6 10
5 6
100 200
10 10
5 5
1 19
1 3
19 5
%%%%
11
20
3
%%%% end
*/
