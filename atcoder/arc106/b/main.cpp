// CONTEST, AC

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

struct Dsu {
  vector<int> ps;
  Dsu(int n) { ps.resize(n); iota(ALL(ps), 0); }
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
  int n, m; // [0, 2 x 10^5]
  cin >> n >> m;
  vector<ll> xs(n), ys(n); // [-10^9, 10^9]
  cin >> xs >> ys;
  vector<array<int, 2>> edges(m);
  cin >> edges;

  // Connected components
  Dsu dsu(n);
  for (auto [x, y] : edges) {
    x--; y--;
    dsu.merge(x, y);
  }

  map<int, vector<int>> compos;
  FOR(v, 0, n) {
    compos[dsu.find(v)].push_back(v);
  }

  // Zero-sum within a component
  map<int, array<ll, 2>> sums;
  for (auto& [k, vs] : compos) {
    auto& sum = sums[k];
    for (auto v : vs) {
      sum[0] += xs[v];
      sum[1] += ys[v];
    }
  }
  dbg2(sums);

  bool ok = 1;
  for (auto [k, sum] : sums) {
    if (sum[0] != sum[1]) {
      ok = 0;
      break;
    }
  }
  cout << (ok ? "Yes" : "No") << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/arc106/b/main.cpp

%%%% begin
2 1
1 1
2 1
1 2
%%%%
No
%%%% end

%%%% begin
17 9
-905371741 -999219903 969314057 -989982132 -87720225 -175700172 -993990465 929461728 895449935 -999016241 782467448 -906404298 578539175 9684413 -619191091 -952046546 125053320
-440503430 -997661446 -912471383 -995879434 932992245 -928388880 -616761933 929461728 210953513 -994677396 648190629 -530944122 578539175 9684413 595786809 -952046546 125053320
2 10
6 12
9 11
11 5
7 6
3 15
3 1
1 9
10 4
%%%%
Yes
%%%% end
*/
