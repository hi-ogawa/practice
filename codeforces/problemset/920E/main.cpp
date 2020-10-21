// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (decltype(Y) I = (X); I < (Y); ++I)
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
  int n, m; // [1, 2 x 10^5]
  cin >> n >> m;
  vector<array<int, 2>> neg_edges(m);
  cin >> neg_edges;

  vector<set<int>> neg_adj(n);
  for (auto [x, y] : neg_edges) {
    x--; y--;
    neg_adj[x].insert(y);
    neg_adj[y].insert(x);
  }

  // Non visited vertices
  list<int> ls(n);
  iota(ALL(ls), 0);

  // Components
  vector<vector<int>> cs;

  function<void(int)> dfs = [&](int v) {
    cs.back().push_back(v);
    vector<int> nexts;
    for (auto it = ls.begin(); it != ls.end(); ) {
      int u = *it;
      if (neg_adj[v].count(u)) {
        // This runs at most m times
        it++;
        continue;
      }
      it = ls.erase(it);
      nexts.push_back(u);
    }
    for (auto u : nexts) {
      dfs(u);
    }
  };

  while (!ls.empty()) {
    cs.emplace_back();
    int v = ls.front(); ls.pop_front();
    dfs(v);
  }
  dbg(cs);

  sort(ALL(cs), [](auto& x, auto& y) { return x.size() < y.size(); });
  int k = cs.size();
  cout << k << "\n";
  FOR(i, 0, k) {
    cout << cs[i].size() << " \n"[i == k - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/920E/main.cpp

%%%% begin
5 5
1 2
3 4
3 2
4 2
2 5
%%%%
2
1 4
%%%% end
*/
