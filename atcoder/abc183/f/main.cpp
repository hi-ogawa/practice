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

// DSU
struct Dsu {
  vector<int> parents;
  vector<int> sizes;
  vector<map<int, int>> data;

  Dsu(int n) {
    parents.resize(n);
    iota(ALL(parents), 0);
    sizes.assign(n, 1);
    data.resize(n);
  }

  int find(int a) {
    if (a == parents[a]) { return a; }
    return parents[a] = find(parents[a]);
  }

  void merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) { return; }
    if (sizes[a] < sizes[b]) { swap(a, b); }

    sizes[a] += sizes[b];
    parents[b] = a;
    for (auto [k, v] : data[b]) { // Loop runs at most n log(n) since small-to-large merge
      data[a][k] += v;
    }
  }
};

// Main
void mainCase() {
  int n, nq;
  cin >> n >> nq;
  vector<int> ls(n); // [1, n]
  cin >> ls;
  vector<array<int, 3>> qs(nq);
  cin >> qs;

  Dsu dsu(n);
  FOR(i, 0, n) {
    dsu.data[i][ls[i]] = 1;
  }

  for (auto [t, x, y] : qs) {
    if (t == 1) {
      x--; y--;
      dsu.merge(x, y);
    }
    if (t == 2) {
      x--;
      x = dsu.find(x);
      int res = dsu.data[x].count(y) ? dsu.data[x][y] : 0;
      cout << res << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc183/f/main.cpp

%%%% begin
5 5
1 2 3 2 1
1 1 2
1 2 5
2 1 1
1 3 4
2 3 4
%%%%
2
0
%%%% end

%%%% begin
5 4
2 2 2 2 2
1 1 2
1 1 3
1 2 3
2 2 2
%%%%
3
%%%% end

%%%% begin
12 9
1 2 3 1 2 3 1 2 3 1 2 3
1 1 2
1 3 4
1 5 6
1 7 8
2 2 1
1 9 10
2 5 6
1 4 8
2 6 1
%%%%
1
0
0
%%%% end
*/
