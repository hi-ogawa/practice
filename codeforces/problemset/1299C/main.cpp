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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

using Real = double;

struct Dsu {
  vector<int> parents;
  vector<int> sizes;
  vector<Real> data;

  Dsu(int n) {
    parents.assign(n, 0);
    iota(ALL(parents), 0);
    sizes.assign(n, 1);
    data.assign(n, 0);
  }

  int find(int x) {
    if (x == parents[x]) { return x; }
    return parents[x] = find(parents[x]);
  }

  void merge(int dst, int src) {
    dst = find(dst); src = find(src);
    data[dst] = (data[dst] * sizes[dst] + data[src] * sizes[src]) / (sizes[dst] + sizes[src]);
    sizes[dst] += sizes[src];
    parents[src] = dst;
  }

  Real getData(int x) {
    return data[find(x)];
  }
};

// Main
void mainCase() {
  int n; // [1, 10^6]
  cin >> n;
  vector<int> ls(n); // [1, 10^6]
  cin >> ls;

  //
  // PROP.
  //   The optimal sequence is increasing.
  //

  Dsu dsu(n);
  FOR(i, 0, n) { dsu.data[i] = ls[i]; }

  FOR(i, 0, n) {
    int j = i - 1;
    while (j >= 0) {
      if (dsu.getData(j) < dsu.getData(i)) { break; }
      dsu.merge(j, i);
      j = dsu.find(j) - 1;
    }
  }

  FOR(i, 0, n) {
    auto x = dsu.getData(i);
    cout << fixed << setprecision(15) << x << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1299C/main.cpp

%%%% begin
4
7 5 5 7
%%%%
5.666666667
5.666666667
5.666666667
7.000000000
%%%% end

%%%% begin
5
7 8 8 10 12
%%%%
7.000000000
8.000000000
8.000000000
10.000000000
12.000000000
%%%% end

%%%% begin
10
3 9 5 5 1 7 5 3 8 7
%%%%
3.000000000
5.000000000
5.000000000
5.000000000
5.000000000
5.000000000
5.000000000
5.000000000
7.500000000
7.500000000
%%%% end
*/
