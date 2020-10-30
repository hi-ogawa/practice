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

// Main
void mainCase() {
  int n, m, k; // [1, 2 x 10^5] and 3 ≤ k ≤ n
  cin >> n >> m >> k;
  vector<array<int, 2>> edges(m); // connected
  cin >> edges;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  //
  // CLAIM.
  //   1. Find tree sub-graph of k vertices
  //   2. If there's a back edge, then we got |cycle| ≤ k
  //   3. Otherwise, we got |independent set| = k/2 by bipertite-ness of tree.
  //
  vector<int> done(n);
  vector<int> depths(n);
  vector<int> parents(n, -1);
  int cnt_done = 0;
  array<int, 2> back_edge = {-1, -1};
  function<void(int, int)> dfs = [&](int v, int vp) {
    cnt_done++;
    done[v] = 1;
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      if (done[u]) {
        back_edge = {v, u};
        continue;
      }
      parents[u] = v;
      depths[u] = depths[v] + 1;
      if (cnt_done < k) {
        dfs(u, v);
      }
    }
  };
  dfs(0, 0);
  dbg(back_edge);
  assert(cnt_done == k);

  if (back_edge[0] == -1) {
    // Independent set from bipartiteness of tree
    array<vector<int>, 2> bip;
    FOR(v, 0, n) {
      if (!done[v]) { continue; }
      bip[depths[v] % 2].push_back(v);
    }
    if (bip[0].size() < bip[1].size()) { swap(bip[0], bip[1]); }

    int l = (k + 1) / 2;
    assert((int)bip[0].size() >= l);

    vector<int> res = bip[0];
    cout << 1 << "\n";
    FOR(i, 0, l) {
      cout << (res[i] + 1) << " \n"[i == l - 1];
    }

  } else {

    // Cycle with back edge
    auto [x, y] = back_edge;
    int dx = depths[x], dy = depths[y];
    if (dx > dy) { swap(x, y); swap(dx, dy); }

    // LCA(x, y)
    deque<int> q;
    q.push_front(x);
    q.push_back(y);
    while (x != y) {
      if (dx < dy) {
        dy--;
        q.push_back(y = parents[y]);
        continue;
      }
      assert(dx == dy && dx > 0);
      dx--; dy--;
      q.push_front(x = parents[x]);
      q.push_back(y = parents[y]);
    }
    q.pop_front();
    assert((int)q.size() <= k);

    vector<int> res(ALL(q));
    int l = res.size();
    cout << 2 << "\n";
    cout << l << "\n";
    FOR(i, 0, l) {
      cout << (res[i] + 1) << " \n"[i == l - 1];
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1364D/main.cpp

%%%% begin
4 4 3
1 2
2 3
3 4
4 1
%%%%
1
1 3
%%%% end

%%%% begin
4 5 3
1 2
2 3
3 4
4 1
2 4
%%%%
2
3
2 3 4
%%%% end

%%%% begin
4 6 3
1 2
2 3
3 4
4 1
1 3
2 4
%%%%
2
3
1 2 3
%%%% end

%%%% begin
5 4 5
1 2
1 3
2 4
2 5
%%%%
1
1 4 5
%%%% end
*/
