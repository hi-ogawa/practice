// AC

// TODO: Editorial says it doesn't have to resort to Mo's range query trick.

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

// Count elements in segment
vector<int> solve(const vector<int>& ls, const vector<array<int, 3>>& qs) {
  int n = ls.size();
  int nq = qs.size();

  // Mo's query ordering
  int n_blk = sqrt(n);
  auto compare = [&](array<int, 3> x, array<int, 3> y) {
    x[0] /= n_blk; y[0] /= n_blk;
    if (x[0] == y[0] && x[0] % 2 == 1) { swap(x[1], y[1]); }
    return x < y;
  };
  vector<int> order(nq);
  iota(ALL(order), 0);
  sort(ALL(order), [&](auto x, auto y) { return compare(qs[x], qs[y]); });

  // State to count [l, r)
  int k = *max_element(ALL(ls));
  vector<int> cnts(k + 1);
  int l = 0, r = 0;

  auto insert = [&](int i) { cnts[ls[i]]++; };
  auto erase = [&](int i) { cnts[ls[i]]--; };

  vector<int> res(nq);
  FOR(i, 0, nq) {
    int iq = order[i];
    auto [lq, rq, xq] = qs[iq];
    if (lq == -1) { res[iq] = 0; continue; }

    while (lq < l) { insert(--l); }
    while (r < rq) { insert(r++); }
    while (l < lq) { erase(l++); }
    while (rq < r) { erase(--r); }

    res[iq] = cnts[xq];
  }
  return res;
}

// Main
void mainCase() {
  int n; // [1, 10^5]
  cin >> n;
  vector<int> parents(n); // not necessarily connected (i.e. forest)
  cin >> parents;
  int nq; // [1, 10^5]
  cin >> nq;
  vector<array<int, 2>> qs(nq);
  cin >> qs;

  vector<vector<int>> adj(n);
  FOR(i, 0, n) {
    int& j = parents[i];
    j = (j > 0) ? (j - 1) : i; // self parent if root
    if (j == i) { continue; }
    adj[j].push_back(i);
  }

  // DFS for depth, subtree size, ...
  vector<int> depths(n);
  vector<int> sizes(n);
  vector<int> in_times(n);
  int time = 0;
  function<void(int)> dfs = [&](int v) {
    sizes[v] = 1;
    in_times[v] = time++;
    for (auto u : adj[v]) {
      depths[u] = depths[v] + 1;
      dfs(u);
      sizes[v] += sizes[u];
    }
  };
  FOR(i, 0, n) {
    if (parents[i] == i) { dfs(i); }
  }

  // Binary lifting
  int b_lim = 0;
  while ((1 << b_lim) <= n) { b_lim++; }
  vector<vector<int>> table(b_lim, vector<int>(n));
  table[0] = parents;
  FOR(b, 1, b_lim) {
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

  // By "subtree as segment" trick, problem is reduced to counting elements in segment.
  vector<int> ls(n);
  FOR(i, 0, n) {
    ls[in_times[i]] = depths[i];
  }

  vector<array<int, 3>> new_qs; // (l, r, x) : count "x" in segment "ls[l:r]"
  for (auto [i, p] : qs) {
    i--;
    int di = depths[i];
    if (p > di) {
      // no "p"-ancestor of "i"
      new_qs.push_back({-1, -1, -1});
      continue;
    }
    // "p"-ancestor of "i"
    int j = lift(i, p);
    int tj = in_times[j];
    new_qs.push_back({tj, tj + sizes[j], depths[i]});
  }
  dbg(ls);
  dbg(new_qs);

  auto res = solve(ls, new_qs);
  FOR(i, 0, nq) {
    auto k = res[i];
    if (k > 0) { k--; } // Subtract yourself
    cout << k << " \n"[i == nq - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/208E/main.cpp

%%%% begin
6
0 1 1 0 4 4
7
1 1
1 2
2 1
2 2
4 1
5 1
6 1
%%%%
0 0 1 0 0 1 1
%%%% end
*/
