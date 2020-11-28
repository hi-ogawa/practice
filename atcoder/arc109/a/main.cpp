// CONTEST, AC

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

// Main
void mainCase() {
  int a, b, x, y; // [1, 100]
  cin >> a >> b >> x >> y;

  int n = 100, m = 2;
  const int kInf = 1e9;

  vector<vector<int>> dists(n + 1, vector<int>(m, kInf));
  set<array<int, 3>> heap; // (distance, i, j)
  heap.insert({dists[a][0] = 0, a, 0});
  while (!heap.empty()) {
    auto [d, i, j] = *heap.begin(); heap.erase(heap.begin());
    if (i == b && j == 1) { break; }

    if (j == 0) {
      // (i+1, 0)
      // (i,   0)  (i,   1)
      // (i-1, 0)  (i-1, 1)
      array<array<int, 3>, 4> nexts = {{
        {i + 1, 0, y},
                       {i    , 1, x},
        {i - 1, 0, y}, {i - 1, 1, x}
      }};
      for (auto [ii, jj, w] : nexts) {
        if (!(1 <= ii && ii <= n)) { continue; }
        if (d + w >= dists[ii][jj]) { continue; }
        heap.erase({dists[ii][jj], ii, jj});
        heap.insert({dists[ii][jj] = d + w, ii, jj});
      }
    }

    if (j == 1) {
      // (i+1, 0)  (i+1, 1)
      // (i,   0)  (i,   1)
      //           (i-1, 1)
      array<array<int, 3>, 4> nexts = {{
        {i + 1, 0, x}, {i + 1, 1, y},
        {i    , 0, x},
                       {i - 1, 1, y}
      }};
      for (auto [ii, jj, w] : nexts) {
        if (!(1 <= ii && ii <= n)) { continue; }
        if (d + w >= dists[ii][jj]) { continue; }
        heap.erase({dists[ii][jj], ii, jj});
        heap.insert({dists[ii][jj] = d + w, ii, jj});
      }
    }
  }

  auto res = dists[b][1];
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/arc109/a/main.cpp

%%%% begin
2 1 1 5
%%%%
1
%%%% end

%%%% begin
1 2 100 1
%%%%
101
%%%% end

%%%% begin
1 100 1 100
%%%%
199
%%%% end
*/
