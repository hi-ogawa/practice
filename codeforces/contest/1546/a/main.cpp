// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y){X}; I < (Y); ++I)
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
  int n; // [1, 100]
  cin >> n;
  vector<int> xs(n), ys(n); // [0, 100]
  cin >> xs >> ys;

  dbg(xs, ys);

  // Neccessary and sufficient condition
  if (accumulate(ALL(xs), 0) != accumulate(ALL(ys), 0)) {
    cout << -1 << "\n";
    return;
  }

  // Collect excess/deficit indices
  vector<int> excess;
  vector<int> deficit;
  FOR(i, 0, n) {
    if (xs[i] > ys[i]) {
      FOR(j, 0, xs[i] - ys[i]) {
        excess.push_back(i);
      }
    }
    if (xs[i] < ys[i]) {
      FOR(j, 0, ys[i] - xs[i]) {
        deficit.push_back(i);
      }
    }
  }
  assert(excess.size() == deficit.size());

  // Balance out excess/deficit
  vector<array<int, 2>> res;
  while (!excess.empty()) {
    res.push_back({excess.back(), deficit.back()});
    excess.pop_back();
    deficit.pop_back();
  }
  dbg(res);

  cout << res.size() << "\n";
  for (auto [i, j]: res) {
    cout << (i + 1) << " " << (j + 1) << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; // [1, 100]
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest/1546/a/main.cpp

%%%% begin
4
4
1 2 3 4
3 1 2 4
2
1 3
2 1
1
0
0
5
4 3 2 1 0
0 1 2 3 4
%%%%
2
2 1
3 1
-1
0
6
1 4
1 4
1 5
1 5
2 5
2 5
%%%% end
*/
