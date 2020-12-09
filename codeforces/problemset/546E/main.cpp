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

const int kInf = 1e9;

int solveMaxFlow(int v0, int v1, vector<vector<int>>& cap) {
  int n = cap.size();

  int flow = 0, flow_total = 0;
  vector<int> done(n);
  vector<int> parents(n);
  deque<array<int, 2>> q; // (vertex, flow)

  auto bfs = [&]() {
    q.clear();
    q.push_back({v0, kInf});
    fill(ALL(done), 0);
    done[v0] = 1;
    while (!q.empty()) {
      auto [v, f] = q.front(); q.pop_front();
      if (v == v1) { flow_total += f; flow = f; return 1; }
      FOR(u, 0, n) {
        if (done[u]) { continue; }
        if (cap[v][u] == 0) { continue; }
        done[u] = 1;
        parents[u] = v;
        q.push_back({u, min(cap[v][u], f)});
      }
    }
    return 0;
  };

  auto update = [&]() {
    int v = v1;
    while (v != v0) {
      int u = parents[v];
      cap[u][v] -= flow;
      cap[v][u] += flow;
      v = u;
    }
  };

  while (bfs()) { update(); }

  return flow_total;
}

// Main
void mainCase() {
  int n, m; // [1, 100], [0, 200]
  cin >> n >> m;
  vector<int> ls1(n), ls2(n); // [0, 100]
  cin >> ls1 >> ls2;
  vector<array<int, 2>> edges(m);
  cin >> edges;
  for (auto& [x, y] : edges) { x--; y--; }

  if (accumulate(ALL(ls1), 0) != accumulate(ALL(ls2), 0)) {
    cout << "NO" << "\n";
    return;
  }

  // Max flow problem
  int nv = 2 * n + 2; // Split one vertex "v" into two "v" and "v + n" in order to constrain out-flow
  vector<vector<int>> cap(nv, vector<int>(nv));
  int v0 = 2 * n, v1 = 2 * n + 1;
  for (auto [x, y] : edges) {
    cap[x + n][y] = kInf;
    cap[y + n][x] = kInf;
  }
  int flow_target = 0;
  FOR(v, 0, n) {
    // Constrain out-flow
    cap[v][v + n] = ls1[v];

    // Deficit/excess compensated by source/sink
    int d = ls2[v] - ls1[v];
    if (d > 0) {
      cap[v][v1] = d;
      flow_target += d;
    } else {
      cap[v0][v] = -d;
    }
  }
  auto cap_init = cap;
  int flow = solveMaxFlow(v0, v1, cap);
  dbg2(cap_init);
  dbg2(cap);
  dbg(flow, flow_target);

  bool ok = flow == flow_target;
  cout << (ok ? "YES" : "NO") << "\n";
  if (!ok) { return; }

  FOR(i, 0, n) {
    FOR(j, 0, n) {
      int t = 0;
      if (i == j) {
        t = cap[i][i + n];
      } else {
        int d = cap_init[i + n][j] - cap[i + n][j];
        if (d > 0) { t = d; }
      }
      cout << t << " \n"[j == n - 1];
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/546E/main.cpp

%%%% begin
4 4
1 2 6 3
3 5 3 1
1 2
2 3
3 4
4 2
%%%%
YES
1 0 0 0
2 0 0 0
0 5 1 0
0 0 2 1
%%%% end

%%%% begin
2 0
1 2
2 1
%%%%
NO
%%%% end
*/
