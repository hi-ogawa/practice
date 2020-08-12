// AFTER CONTEST, AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T>            istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T, size_t N>  ostream& operator<<(ostream& o, const array<T, N>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  ll n, nq; // <= 10^5
  cin >> n >> nq;

  vector<ull> ls(n, 0); // <= 10^8
  cin >> ls;
  // DD(ls);

  vector<tuple<ll, ll>> es(n - 1, {0, 0});
  RANGE(i, 0, n - 1) { cin >> get<0>(es[i]) >> get<1>(es[i]); }
  // cin >> es; // c++17
  // DD(es);

  vector<tuple<ll, ll>> qs(nq, {0, 0});
  RANGE(i, 0, nq) { cin >> get<0>(qs[i]) >> get<1>(qs[i]); }
  // cin >> qs; // c++17
  // DD(qs);

  // Adjacency list
  vector<vector<ll>> adj(n, vector<ll>(0, 0));
  for (auto xy : es) {
    ll x, y;  tie(x, y) = xy;
    x--; y--; // to zero-based
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  // DD(adj);

  // XOR from (arbitrary) root to each node (DFS)
  vector<ll> stack;
  vector<ull> xors(n, ~0UL);
  vector<ll> depths(n, -1); // for common ancestor
  vector<ll> parents(n, -1);
  stack.push_back(0);
  xors[0] = ls[0];
  depths[0] = 0;
  while (!stack.empty()) {
    ll i = stack.back();  stack.pop_back();
    for (auto j : adj[i]) {
      if (xors[j] != ~0UL) { continue; }
      xors[j] = xors[i] ^ ls[j];
      depths[j] = depths[i] + 1;
      parents[j] = i;
      stack.push_back(j);
    }
  }
  // DD(xors);
  // DD(depths);
  // DD(parents);

  // Answer queries
  for (auto q : qs) {
    int x, y;  tie(x, y) = q;
    x--; y--; // to zero-based

    // Common ancestors
    if (depths[x] > depths[y]) { swap(x, y); } // WLOG, depths[x] <= depths[y]
    int xx = x, yy = y;
    RANGE(i, 0, depths[y] - depths[x]) { yy = parents[yy]; } // depths[xx] == depth[yy]
    while (xx != yy) {
      xx = parents[xx];
      yy = parents[yy];
    }
    int z = xx;
    // DD(tie(x, y, z));

    // Path xor
    ull res = xors[x] ^ xors[y] ^ ls[z];
    cout << res << endl;
  }
}

int main() {
  // [ Single case ]
  // mainCase();
  // return 0;

  // [ Multiple cases ]
  int t;
  cin >> t;
  RANGE(i, 0, t) mainCase();
  return 0;
}

/*
python misc/run.py codechef/LRNDSA08/ENOC1/main.cpp --check

%%%% begin
1
5 2
1 2 3 4 5
1 2
1 3
2 4
2 5
3 5
4 5
%%%%
5
3
%%%% end
*/
