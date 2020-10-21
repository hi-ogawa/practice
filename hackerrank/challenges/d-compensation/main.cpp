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

using vec2 = array<int, 2>;
const int kInf = 1e9;

void solveDivisibleMaxFlow(vector<vector<vec2>>& cap, int v0, int v1) {
  int n = cap.size();
  vector<int> parents(n);
  vector<bool> done(n);

  auto search = [&]() -> int {
    deque<vec2> q; // (flow, vertex)
    fill(ALL(done), 0);
    done[v0] = 1;
    q.push_back({kInf, v0});
    while (!q.empty()) {
      dbg(q);
      auto [f, v] = q.front(); q.pop_front();
      if (v == v1) { return f; }
      FOR(u, 0, n) {
        if (done[u]) { continue; }
        auto [residue, divisor] = cap[v][u];
        int ff = (min(f, residue) / divisor) * divisor;
        if (ff == 0) { continue; }
        done[u] = 1;
        parents[u] = v;
        q.push_back({ff, u});
      }
    }
    return 0;
  };

  auto update = [&](int flow) {
    int v = v1;
    while (v != v0) {
      int u = parents[v];
      cap[u][v][0] -= flow;
      cap[v][u][0] += flow;
      v = u;
    }
  };

  while (true) {
    int flow = search();
    dbg(flow);
    if (flow == 0) { break; }
    update(flow);
  }
}

// Main
void mainCase() {
  int n, x, a, y, b; // [1, 10^3]
  cin >> n >> x >> a >> y >> b;

  int nv = 1 + n + 2 + 1;
  int v0 = 0;
  int va = n + 1;
  int vb = n + 2;
  int v1 = n + 3;
  vector<vector<vec2>> cap_init(nv, vector<vec2>(nv, {0, 1})); // (capacity, divisibility)
  FOR(i, 1, n + 1) {
    cap_init[i][va] = {kInf, a};
    cap_init[i][vb] = {kInf, b};
    cap_init[va][i] = {0, a};
    cap_init[vb][i] = {0, b};
  }
  cap_init[va][v1] = {a * x, a};
  cap_init[vb][v1] = {b * y, b};
  cap_init[v1][va] = {0, a};
  cap_init[v1][vb] = {0, b};

  dbg(n, x, a, y, b);
  dbg2(cap_init);

  // f(c) = 1  \iff  we can achieve minimum >= c
  auto evaluate = [&](int c) -> bool {
    auto cap = cap_init;
    FOR(i, 1, n + 1) {
      cap[0][i] = {c, 1};
    }
    solveDivisibleMaxFlow(cap, v0, v1);
    dbg(c);
    dbg2(cap);
    bool ok = 1;
    FOR(i, 1, n + 1) {
      if (cap[0][i][0] > 0) {
        ok = 0;
        break;
      }
    }
    return ok;
  };

  dbg(evaluate(30));
  return;

  // Find max { c | f(c) = 1 }
  auto search = [&]() -> int {
    int c0 = 0, c1 = a * x + b * y; // [c0, c1)
    while (c0 + 1 < c1) {
      int c = (c0 + c1) / 2;
      if (evaluate(c)) {
        c0 = c;
      } else {
        c1 = c;
      }
    }
    return c0;
  };

  int res = search();
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
python misc/run.py hackerrank/challenges/d-compensation/main.cpp

%%%% begin
1
3 3 10 2 40
%%%%
30
%%%% end

%%%% begin
2
3 3 10 2 40
7 8 60 2 40
%%%%
30
60
%%%% end
*/
