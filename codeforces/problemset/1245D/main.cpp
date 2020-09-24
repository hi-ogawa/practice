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

struct Dsu {
  int n;
  vector<int> ps;
  Dsu(int _n) { n = _n; ps.resize(n); iota(ALL(ps), 0); }
  int find(int a) {
    if (a == ps[a]) { return a; }
    return ps[a] = find(ps[a]);
  }
  void merge(int dst, int src) {
    ps[find(src)] = find(dst);
  }
};

// Main
void mainCase() {
  int n; // [1,2000]
  cin >> n;
  vector<array<ll, 2>> ps(n);
  cin >> ps;
  vector<ll> cs(n), ks(n);
  cin >> cs >> ks;

  vector<tuple<ll, int, int>> edges;
  FOR(i, 0, n) {
    FOR(j, i + 1, n) {
      ll d = abs(ps[i][0] - ps[j][0]) + abs(ps[i][1] - ps[j][1]);
      ll k = ks[i] + ks[j];
      edges.push_back({d * k, i, j});
    }
  }

  // "dummy" power source vertex/edge
  int v0 = n;
  int m = n + 1;
  FOR(i, 0, n) {
    edges.push_back({cs[i], v0, i});
  }
  sort(ALL(edges));
  dbg(edges);

  // MST
  Dsu dsu(m);
  ll res = 0;
  vector<int> res1;
  vector<array<int, 2>> res2;
  for (auto [d, i, j] : edges) {
    if (dsu.find(i) == dsu.find(j)) { continue; }
    dsu.merge(i, j);
    res += d;
    if (i == v0) {
      res1.push_back(j);
    } else {
      res2.push_back({i, j});
    }
  }

  cout << res << endl;
  int n1 = res1.size(), n2 = res2.size();
  cout << n1 << endl;
  FOR(i, 0, n1) {
    cout << (res1[i] + 1) << " \n"[i == n1 - 1];
  }
  cout << n2 << endl;
  FOR(i, 0, n2) {
    cout << (res2[i][0] + 1) << " " << (res2[i][1] + 1) << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1245D/main.cpp --check


%%%% begin
3
2 3
1 1
3 2
3 2 3
3 2 3
%%%%
8
3
1 2 3
0
%%%% end

%%%% begin
3
2 1
1 2
3 3
23 2 23
3 2 3
%%%%
27
1
2
2
1 2
2 3
%%%% end
*/
