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
    parents.resize(n);
    iota(ALL(parents), 0);
    data.resize(n);
  }

  int value(int x) {
    compress(x);
    int root = parents[x];
    return data[x] + (x == root ? 0 : data[root]);
  }

  tuple<int, int> compress(int x) {
    int xp = parents[x];
    if (x == xp) { return {x, 0}; }
    auto [root, data_acc] = compress(xp);
    data[x] += data_acc; // Accumulate "non-root" values
    parents[x] = root;
    return {root, data[x]};
  }

  int find(int x) {
    return get<0>(compress(x));
  }

  void merge(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) { return; }
    parents[x] = y;
    data[x] -= data[y]; // Subtract irrelavant group increment
  }

  void incr(int x, int v) {
    data[find(x)] += v;
  }
};

// Main
void mainCase() {
  int n, nq;
  cin >> n >> nq;

  Dsu dsu(n);

  FOR(_, 0, nq) {
    string t;
    cin >> t;
    int x, y;

    if (t == "join") {
      cin >> x >> y;
      x--; y--;
      dsu.merge(x, y);
    }

    if (t == "add") {
      cin >> x >> y;
      x--;
      dsu.incr(x, y);
    }

    if (t == "get") {
      cin >> x;
      x--;
      auto res = dsu.value(x);
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
python misc/run.py codeforces/edu/dsu/1/c/main.cpp

%%%% begin
3 6
add 1 100
join 1 3
add 1 50
get 1
get 2
get 3
%%%%
150
0
50
%%%% end
*/
