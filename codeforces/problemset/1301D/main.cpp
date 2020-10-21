// AC

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

// Main
void mainCase() {
  int n, m; // [1, 500]
  cin >> n >> m;
  int k; // [1, 10^9]
  cin >> k;

  int num_edges = 2 * n * (m - 1) + 2 * (n - 1) * m;
  if (k > num_edges) { cout << "NO" << "\n"; return; }

  //
  // Euler tour by
  //
  // (1,1)-------->    R x (m - 1)    \
  //  <------------    L x (m - 1)    | x (n - 1)
  // ⇓                 D x 1         /
  //
  //  ....
  //
  //           (1, 2)          R x 1         \
  //            ⇑ ⇓            U x (n - 1)   | x (m - 1)
  //            ⇑ ⇓            D x (n - 1)   /
  // (n, 1) -> (n, 2) ....
  //
  //
  // (1.1)                    L x (m - 1)
  //  ⇑                       U x (n - 1)
  //  ⇑
  // (n, 1) <------ (n, m)
  //

  vector<tuple<char, int>> res;

  auto update = [](int& x, int y) -> int {
    assert(x > 0);
    int z = x;
    x -= min(z, y);
    return min(z, y);
  };

  auto solve = [&]() {
    FOR(i, 0, n - 1) {
      if (m > 1) {
        res.push_back({'R', update(k, m - 1)});
        if (k == 0) { return; }

        res.push_back({'L', update(k, m - 1)});
        if (k == 0) { return; }
      }

      res.push_back({'D', update(k, 1)});
      if (k == 0) { return; }
    }

    FOR(i, 0, m - 1) {
      res.push_back({'R', update(k, 1)});
      if (k == 0) { return; }

      if (n > 1) {
        res.push_back({'U', update(k, n - 1)});
        if (k == 0) { return; }

        res.push_back({'D', update(k, n - 1)});
        if (k == 0) { return; }
      }
    }

    if (m > 1) {
      res.push_back({'L', update(k, m - 1)});
      if (k == 0) { return; }
    }

    if (n > 1) {
      res.push_back({'U', update(k, n - 1)});
      if (k == 0) { return; }
    }
  };

  solve();
  assert(res.size() <= 3000);

  cout << "YES" << "\n";
  cout << res.size() << "\n";
  for (auto [x, y] : res) {
    cout << y << " " << x << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1301D/main.cpp

%%%% begin
1 4 6
%%%%
YES
%%%% end

%%%% begin
3 4 34
%%%%
YES
???
%%%% end

%%%% begin
3 3 4
%%%%
YES
2
2 R
2 L
%%%% end

%%%% begin
3 3 1000000000
%%%%
NO
%%%% end

%%%% begin
3 3 8
%%%%
YES
3
2 R
2 D
1 LLRR
%%%% end

%%%% begin
4 4 9
%%%%
YES
1
3 RLD
%%%% end

%%%% begin
3 4 16
%%%%
YES
8
3 R
3 L
1 D
3 R
1 D
1 U
3 L
1 D
%%%% end
*/
