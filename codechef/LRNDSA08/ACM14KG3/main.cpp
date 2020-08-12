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
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Modulo
constexpr ll kModulo = 1000000000 + 7;
ll mmul(ll x, ll y) { return (x * y) % kModulo; }

// Main
void mainCase() {
  string s1, s2;
  cin >> s1 >> s2;

  int ne;
  cin >> ne;

  // a..z
  // 0..25
  int nv = 26;
  vector<pair<int, int>> es(ne, {0, 0});
  RANGE(i, 0, ne) {
    string s;
    cin >> s;
    es[i] = {s[0] - 'a', s[3] - 'a'};
  }
  // DD(es);

  // Adjacency matrix
  vector<vector<int>> adj(nv, vector<int>(0, 0));
  RANGE(i, 0, ne) {
    int x, y;  tie(x, y) = es[i];
    adj[x].push_back(y);
  }
  // DD(adj);

  // Reachability by DFS
  vector<vector<bool>> reachable(nv, vector<bool>(nv, 0));
  function<void(int, int)> search = [&](int x0, int x) {
    reachable[x0][x] = 1;
    for (auto y : adj[x]) {
      if (reachable[x0][y]) { continue; }
      search(x0, y);
    }
  };
  RANGE(i, 0, nv) {
    search(i, i);
  }
  // DD(reachable);

  ll res = 1;
  RANGE(i, 0, s1.size()) {
    if (!reachable[s1[i] - 'a'][s2[i] - 'a']) {
      res = 0;
      break;
    }
  }
  if (s1.size() != s2.size()) {
    res = 0;
  }
  cout << (res ? "YES" : "NO") << endl;
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
python misc/run.py codechef/LRNDSA08/ACM14KG3/main.cpp --check

%%%% begin
3
aa
bb
1
a->b
ab
ba
2
a->b
b->a
a
b
1
b->a
%%%%
YES
YES
NO
%%%% end
*/
