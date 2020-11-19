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

// DFS out-time sorting
vector<int> dfsOutSort(const vector<vector<int>>& adj) {
  int n = adj.size();

  vector<int> done(n);
  vector<int> out_time(n);
  int time = 0;
  function<void(int)> dfs = [&](int v) {
    done[v] = 1;
    for (auto u : adj[v]) {
      if (done[u]) { continue; }
      dfs(u);
    }
    out_time[v] = time++;
  };

  FOR(i, 0, n) {
    if (done[i]) { continue; }
    dfs(i);
  }

  vector<int> order(n);
  iota(ALL(order), 0);
  sort(ALL(order), [&](auto x, auto y) { return out_time[x] > out_time[y]; });
  return order;
}

// Condensation graph
tuple<vector<int>, vector<vector<int>>> makeSCC(const vector<vector<int>>& adj) {
  int n = adj.size();
  auto order = dfsOutSort(adj);

  vector<int> cg(n, -1);
  vector<vector<int>> cg_adj;

  vector<vector<int>> adjT(n);
  FOR(i, 0, n) {
    for (auto j : adj[i]) {
      adjT[j].push_back(i);
    }
  }

  function<void(int)> dfs = [&](int v) {
    for (auto u : adjT[v]) {
      if (cg[u] != -1) {
        if (cg[u] != cg[v]) {
          cg_adj[cg[u]].push_back(cg[v]);
        }
        continue;
      }
      cg[u] = cg[v];
      dfs(u);
    }
  };

  int cg_cnt = 0;
  FOR(i, 0, n) {
    int v = order[i];
    if (cg[v] != -1) { continue; }
    cg[v] = cg_cnt++;
    cg_adj.emplace_back();
    dfs(v);
  }

  return {move(cg), move(cg_adj)};
}

// 2SAT
optional<vector<int>> solve2SAT(int n_vars, const vector<array<int, 2>>& cnf) {
  //
  // Encoding of literals
  //   0,  1,  2, ..  =>  1, 3, 5, ...
  //  ¬0, ¬1, ¬2, ..  =>  0, 2, 4, ...
  //
  int n = 2 * n_vars;
  vector<vector<int>> adj(n);
  for (auto [x, y] : cnf) {
    adj[x ^ 1].push_back(y);
    adj[y ^ 1].push_back(x);
  }

  // Condensation
  auto [cg, cg_adj] = makeSCC(adj);

  // Check satisfiability
  bool ok = 1;
  FOR(i, 0, n_vars) {
    if (cg[2 * i] == cg[2 * i + 1]) {
      ok = 0;
      break;
    }
  }
  if (!ok) { return {}; }

  // Assign valuations
  int n_cg = cg_adj.size();
  vector<vector<int>> inv_cg(n_cg);
  FOR(i, 0, n) {
    inv_cg[cg[i]].push_back(i);
  }

  auto order = dfsOutSort(cg_adj);
  vector<int> res(n_vars, -1);
  FOR(i, 0, n_cg) {
    for (auto v : inv_cg[order[i]]) {
      if (res[v / 2] == -1) {
        res[v / 2] = !(v & 1);
      }
    }
  }

  return {move(res)};
}

// Main
void mainCase() {
  string head;
  cin >> head; assert(head == "p");
  cin >> head; assert(head == "cnf");

  int n, m; // [1, 5 x 10^5]
  cin >> n >> m;
  vector<array<int, 3>> ls(m);
  cin >> ls;

  vector<array<int, 2>> cnf(m);
  FOR(i, 0, m) {
    auto [x, y, _z] = ls[i];
    int a = 2 * (abs(x) - 1) + (x > 0);
    int b = 2 * (abs(y) - 1) + (y > 0);
    cnf[i] = {a, b};
  }

  auto res = solve2SAT(n, cnf);
  if (!res) {
    cout << "s UNSATISFIABLE" << "\n";
    return;
  }
  cout << "s SATISFIABLE" << "\n";
  cout << "v";
  FOR(i, 0, n) {
    cout << " " << ((*res)[i] ? "" : "-") << (i + 1);
  }
  cout << " 0\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/two_sat/main.cpp

%%%% begin
p cnf 5 6
1 2 0
-3 -1 0
-4 -3 0
2 -5 0
5 -2 0
1 4 0
%%%%
s SATISFIABLE
v -1 2 -3 4 5 0
%%%% end

%%%% begin
p cnf 2 4
1 2 0
1 -2 0
-1 2 0
-1 -2 0
%%%%
s UNSATISFIABLE
%%%% end
*/
