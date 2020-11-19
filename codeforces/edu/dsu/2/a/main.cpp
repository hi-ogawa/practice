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
  int n, nq; // [1, 10^6]
  cin >> n >> nq;
  vector<tuple<char, int>> qs(nq);
  cin >> qs;

  Dsu dsu(n + 1); // Dummy at the boundary as "n"
  for (auto [t, x] : qs) {
    x--;
    if (t == '-') {
      dsu.merge(x + 1, x);
    }
    if (t == '?') {
      auto y = dsu.find(x);
      int res = (y == n) ? -1 : (y + 1);
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
python misc/run.py codeforces/edu/dsu/2/a/main.cpp

%%%% begin
5 10
? 1
- 3
? 3
- 2
? 1
? 2
- 4
? 3
- 5
? 3
%%%%
1
4
1
4
5
-1
%%%% end
*/
