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
  Dsu(int n) {
    parents.assign(n, 0);
    iota(ALL(parents), 0);
  }
  int find(int a) {
    if (a == parents[a]) { return a; }
    return parents[a] = find(parents[a]);
  }
  void merge(int dst, int src) {
    parents[find(src)] = find(dst);
  }
};

// Main
void mainCase() {
  int n; // [1, 3 x 10^5]
  cin >> n;
  vector<int> ls(n); // [1, n]
  cin >> ls;

  Dsu dsu(n + 1); // Dummy right boundary as "n"
  dsu.merge(0, n); // Connect the last to the first

  vector<int> res(n);
  FOR(i, 0, n) {
    int x = ls[i] - 1;
    int y = dsu.find(x);
    res[i] = y;
    dsu.merge(y + 1, y);
  }

  FOR(i, 0, n) {
    cout << (res[i] + 1) << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/edu/dsu/2/b/main.cpp

%%%% begin
3
2 2 2
%%%%
2 3 1
%%%% end
*/
