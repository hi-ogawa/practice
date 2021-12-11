// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
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

struct Dsu {
  int n;
  vector<int> parents;
  vector<int> sizes;

  Dsu(int n): n{n} {
    parents.resize(n);
    sizes.resize(n);
    iota(ALL(parents), 0);
    fill(ALL(sizes), 1);
  }

  int find(int x) {
    if (x == parents[x]) return x;
    return parents[x] = find(parents[x]);
  }

  void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (sizes[x] > sizes[y]) swap(x, y);
    parents[x] = y;
    sizes[x] += sizes[y];
  }
};

// Main
void mainCase() {
  int n, nq;
  cin >> n >> nq;
  vector<tuple<int, int, int>> qs(nq);
  cin >> qs;

  Dsu dsu(n);
  for (auto [t, u, v] : qs) {
    if (t == 0) {
      dsu.merge(u, v);
    }
    if (t == 1) {
      cout << int(dsu.find(u) == dsu.find(v)) << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/unionfind/main.cpp

%%%% begin
4 7
1 0 1
0 0 1
0 2 3
1 0 1
1 1 2
0 0 2
1 1 3
%%%%
0
1
0
1
%%%% end
*/
