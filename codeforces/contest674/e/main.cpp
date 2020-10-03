// AFTER EDITORIAL, AC

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

int solveMaxFlow(vector<vector<int>>& cap, int v0, int v1) {
  int n = cap.size();
  auto cap_init = cap;
  vector<int> parents(n); // path found by search

  auto search = [&]() -> int {
    deque<array<int, 2>> q; // (vertex, flow)
    vector<bool> done(n);
    q.push_back({v0, (int)1e9 + 1});
    done[v0] = 1;
    while (!q.empty()) {
      auto [v, f] = q.front(); q.pop_front();
      if (v == v1) { return f; }
      FOR(u, 0, n) {
        if (done[u]) { continue; }
        if (cap[v][u] == 0) { continue; }
        q.push_back({u, min(cap[v][u], f)});
        done[u] = 1;
        parents[u] = v;
      }
    }
    return 0;
  };

  auto update = [&](int f) {
    int u = v1;
    while (u != v0) {
      int v = parents[u];
      cap[v][u] -= f;
      cap[u][v] += f;
      u = v;
    }
  };

  while (true) {
    int f = search();
    if (f == 0) { break; }
    update(f);
  }

  int res = 0;
  FOR(v, 0, n) { res += cap_init[v0][v] - cap[v0][v]; }
  return res;
};

// Main
void mainCase() {
  int n;
  cin >> n;
  array<int, 3> xs, ys;
  cin >> xs >> ys;

  // Align "win relation" index, for simplicity.
  ys = {ys[1], ys[2], ys[0]};

  // Maximize win
  ll res1 = 0;
  FOR(i, 0, 3) { res1 += min(xs[i], ys[i]); }

  // Maximize draw/loss by max flow
  vector<vector<int>> cap(8, vector<int>(8));
  //   / 0   3 \
  // 6 - 1   4 - 7
  //   \ 2   5 /
  cap[0][4] = n;
  cap[0][5] = n;
  cap[1][5] = n;
  cap[1][3] = n;
  cap[2][3] = n;
  cap[2][4] = n;
  cap[6][0] = xs[0];
  cap[6][1] = xs[1];
  cap[6][2] = xs[2];
  cap[3][7] = ys[0];
  cap[4][7] = ys[1];
  cap[5][7] = ys[2];
  ll res2 = solveMaxFlow(cap, 6, 7);

  array<ll, 2> res = {n - res2, res1};
  FOR(i, 0, 2) {
    cout << res[i] << " \n"[i == 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest674/e/main.cpp --check

%%%% begin
2
0 1 1
1 1 0
%%%%
0 1
%%%% end

%%%% begin
15
5 5 5
5 5 5
%%%%
0 15
%%%% end

%%%% begin
3
0 0 3
3 0 0
%%%%
3 3
%%%% end

%%%% begin
686
479 178 29
11 145 530
%%%%
22 334
%%%% end

%%%% begin
319
10 53 256
182 103 34
%%%%
119 226
%%%% end
*/
