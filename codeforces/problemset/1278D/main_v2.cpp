// AFTER EDITORIAL, AC

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

// Main
void mainCase() {
  int n; // [1, 5 x 10^5]
  cin >> n;
  vector<array<int, 2>> ls(n); // [1, 2n], l < r
  cin >> ls;

  vector<array<int, 4>> events; // (l/r, in/out, bias, id)
  FOR(i, 0, n) {
    auto [l, r] = ls[i];
    events.push_back({l, 0, -r, i}); // bias by "-r" so that longer interval comes first for same "l"
    events.push_back({r, 1, -1, i});
  }
  sort(ALL(events));

  multiset<array<int, 2>> st; // (r, id)
  vector<vector<int>> adj(n);
  int num_edges = 0;
  for (auto [x, t, bias, i] : events) {
    auto [l, r] = ls[i];
    if (t == 0) {
      st.insert({r, i});
      for (auto [rj, j] : st) { // This loop runs at most "n"
        if (r <= rj) { break; }
        num_edges++;
        if (num_edges >= n) { break; }
        adj[i].push_back(j);
        adj[j].push_back(i);
      }
    }
    if (t == 1) {
      st.erase({r, i});
    }
    if (num_edges >= n) { break; }
  }
  if (num_edges != n - 1) { cout << "NO" << "\n"; return; }

  // Check if connected
  vector<int> done(n);
  function<void(int)> dfs = [&](int v) {
    done[v] = 1;
    for (auto u : adj[v]) {
      if (done[u]) { continue; }
      dfs(u);
    }
  };
  dfs(0);
  bool ok = count(ALL(done), 0) == 0;
  cout << (ok ? "YES" : "NO") << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1278D/main_v2.cpp

%%%% begin
6
9 12
2 11
1 3
6 10
5 7
4 8
%%%%
YES
%%%% end

%%%% begin
5
1 3
2 4
5 9
6 8
7 10
%%%%
NO
%%%% end

%%%% begin
5
5 8
3 6
2 9
7 10
1 4
%%%%
NO
%%%% end
*/
