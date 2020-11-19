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

struct Dsu {
  vector<int> parents;
  vector<int> data;

  Dsu(int n) {
    parents.assign(n, 0);
    iota(ALL(parents), 0);
    data.assign(n, 0);
  }

  int find(int x) {
    int xp = parents[x];
    if (x == xp) { return x; }
    int root = find(xp);
    data[x] += data[xp]; // Accumulate compression
    parents[x] = root;
    return root;
  }

  void merge(int src, int dst) {
    assert(parents[src] == src);
    assert(parents[dst] == dst);
    parents[src] = dst;
    data[src] = 1;
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 3e5]
  cin >> n >> nq;
  vector<array<int, 3>> qs(nq);
  for (auto& q : qs) {
    cin >> q[0];
    if (q[0] == 1) {
      cin >> q[1] >> q[2];
    }
    if (q[0] == 2) {
      cin >> q[1];
    }
  }

  Dsu dsu(n);

  for (auto [t, x, y] : qs) {
    if (t == 1) {
      x--; y--;
      dsu.merge(x, y);
    }
    if (t == 2) {
      x--;
      dsu.find(x);
      auto res = dsu.data[x];
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
python misc/run.py codeforces/edu/dsu/2/d/main.cpp

%%%% begin
10 20
1 9 4
1 2 6
2 10
1 10 5
2 5
1 7 4
1 8 5
2 1
1 6 5
1 3 5
1 1 4
1 5 4
2 7
2 2
2 4
2 3
2 4
2 2
2 2
2 10
%%%%
0
0
0
1
3
0
2
0
3
3
2
%%%% end
*/
