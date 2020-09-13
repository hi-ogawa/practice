// AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
template<typename T> struct is_container {
template<typename C> static char test(typename C::const_iterator*); template<typename> static int test(...);
static bool const value = sizeof(test<T>(nullptr)) == sizeof(char) && !std::is_same<std::string, T>::value;
};
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#ifndef DEBUG
#define DEBUG 0
#endif
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  int n; // [3, 10^6]
  cin >> n;
  vector<vector<int>> ls(3, vector<int>(n));
  cin >> ls;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;
  for (auto& [x, y] : edges) { x--; y--; }

  vector<int> degs(n);
  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    degs[x]++;
    degs[y]++;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // Solvable iff degs[v] = 1 or 2 (i.e. tree is a single line)
  if (*max_element(ALL(degs)) >= 3) { cout << -1 << endl; return; }
  assert(count(ALL(degs), 1) == 2);

  // BFS
  int v0 = distance(degs.begin(), find(ALL(degs), 1));
  vector<int> dists(n, -1);
  {
    deque<int> q;
    q.push_back(v0);
    dists[v0] = 0;
    while (!q.empty()) {
      int v = q.front(); q.pop_front();
      for (auto u : adj[v]) {
        if (dists[u] == -1) {
          dists[u] = dists[v] + 1;
          q.push_back(u);
        }
      }
    }
  }
  vector<int> dists_inv(n);
  FOR(i, 0, n) { dists_inv[dists[i]] = i; }
  dbgv(v0, dists, dists_inv);

  // Generate S3 ((0, 1, 2), (0, 2, 1), ...)
  vector<array<int, 3>> s3(6, {0, 1, 2});
  FOR(i, 0, 5) {
    s3[i + 1] = s3[i];
    next_permutation(ALL(s3[i + 1]));
  }

  // Brute force all patterns
  ll res1 = 1LL << 60;
  array<int, 3> res2;
  for (auto perm : s3) {
    ll t = 0;
    FOR(i, 0, n) {
      int v = dists_inv[i];
      t += ls[perm[i % 3]][v];
    }
    if (t < res1) {
      res1 = t;
      res2 = perm;
    }
  }
  dbgv(res1, res2);

  cout << res1 << endl;
  FOR(v, 0, n) {
    if (v) cout << " ";
    cout << (res2[dists[v] % 3] + 1);
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1244D/main.cpp --check

%%%% begin
3
3 2 3
4 3 2
3 1 3
1 2
2 3
%%%%
6
1 3 2
%%%% end

%%%% begin
5
3 4 2 1 2
4 2 1 5 4
5 3 2 1 1
1 2
3 2
4 3
5 3
%%%%
-1
%%%% end

%%%% begin
5
3 4 2 1 2
4 2 1 5 4
5 3 2 1 1
1 2
3 2
4 3
5 4
%%%%
9
1 3 2 1 3
%%%% end
*/
