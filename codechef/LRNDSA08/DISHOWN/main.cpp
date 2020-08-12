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
}

// Main
void mainCase() {
  ll n; // <= 10^4
  cin >> n;

  vector<ll> ls(n, 0); // <= 10^6
  cin >> ls;

  ll nq; // <= 10^4
  cin >> nq;

  // "Directed" DSU (merge happens only between root nodes)
  vector<int> dsu(n, 0);
  iota(ALL(dsu), 0);
  auto score = ls;
  function<int(int)> find = [&](int x) {
    if (dsu[x] == x) { return x; }
    return dsu[x] = find(dsu[x]);
  };
  auto merge = [&](int dest, int src) {
    dsu[src] = dest;
    score[dest] = max(score[dest], score[src]);
  };

  RANGE(iq, 0, nq) {
    // DD(dsu);
    // DD(score);
    ll mode, x, y;
    cin >> mode;

    if (mode == 0) {
      cin >> x >> y;
      x--; y--;  // zero-based
      ll fx = find(x);
      ll fy = find(y);
      if (fx == fy) {
        cout << "Invalid query!" << endl;
        continue;
      }
      if (score[fx] == score[fy]) { continue; }
      if (score[fx] < score[fy]) { swap(fx, fy); }
      merge(fx, fy);
    }

    if (mode == 1) {
      cin >> x;
      x--; // zero-based
      cout << (find(x) + 1) << endl;
    }
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
python misc/run.py codechef/LRNDSA08/DISHOWN/main.cpp --check

%%%% begin
1
2
1 2
2
0 1 2
1 1
%%%%
2
%%%% end
*/
