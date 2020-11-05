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

// Main
void mainCase() {
  int n; // [1, 10^5]
  cin >> n;
  vector<array<ll, 2>> ls(n); // [-10^9, 10^9], distinct
  cin >> ls;

  if (n <= 4) { cout << "YES" << "\n"; return; }

  auto removeColinear = [&](int i0, int i1, vector<int>& ids) {
    auto [x0, y0] = ls[i0];
    auto [x1, y1] = ls[i1];
    vector<int> res;
    for (auto i : ids) {
      auto [x, y] = ls[i];
      ll det = (x - x0) * (y1 - y0) - (x1 - x0) * (y - y0);
      if (det != 0) {
        res.push_back(i);
      }
    }
    ids = res;
  };

  // Check if solvable when i0 and i1 are in the same group
  auto solve = [&](int i0, int i1) -> bool {
    vector<int> ids(n);
    iota(ALL(ids), 0);
    removeColinear(i0, i1, ids);
    if (ids.size() <= 2) { return 1; }
    removeColinear(ids[0], ids[1], ids);
    return ids.size() == 0;
  };

  // Pick any three, then two of them have to be in the same group
  bool res = solve(0, 1) || solve(1, 2) || solve(2, 0);
  cout << (res ? "YES" : "NO") << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/961D/main.cpp

%%%% begin
5
0 0
0 1
1 1
1 -1
2 2
%%%%
YES
%%%% end

%%%% begin
5
0 0
1 0
2 1
1 1
2 3
%%%%
NO
%%%% end
*/
