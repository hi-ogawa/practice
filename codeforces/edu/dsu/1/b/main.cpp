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
  vector<array<int, 3>> data; // (min, max, size)

  Dsu(int n) {
    parents.resize(n);
    data.resize(n);
    FOR(i, 0, n) {
      parents[i] = i;
      data[i][0] = i;
      data[i][1] = i;
      data[i][2] = 1;
    }
  }

  int find(int x) {
    if (x == parents[x]) { return x; }
    return parents[x] = find(parents[x]);
  }

  void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) { return; }
    if (data[x][2] < data[y][2]) { swap(x, y); }

    data[x][0] = min(data[x][0], data[y][0]);
    data[x][1] = max(data[x][1], data[y][1]);
    data[x][2] = data[x][2] + data[y][2];
    parents[y] = x;
  }
};

// Main
void mainCase() {
  int n, nq;
  cin >> n >> nq;

  Dsu dsu(n);

  FOR(_, 0, nq) {
    string t;
    int x, y;
    cin >> t;

    if (t == "union") {
      cin >> x >> y;
      x--; y--;
      dsu.merge(x, y);
    }

    if (t == "get") {
      cin >> x;
      x--;
      x = dsu.find(x);
      auto [a, b, c] = dsu.data[x];
      a++; b++;
      cout << a << " " << b << " " << c << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/edu/dsu/1/b/main.cpp

%%%% begin
5 11
union 1 2
get 3
get 2
union 2 3
get 2
union 1 3
get 5
union 4 5
get 5
union 4 1
get 5
%%%%
3 3 1
1 2 2
1 3 3
5 5 1
4 5 2
1 5 5
%%%% end
*/
