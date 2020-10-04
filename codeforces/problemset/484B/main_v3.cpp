// AFTER EDITORIAL, AC

// NOTE: it turns out such segmen tree in main_v2.cpp isn't really necessarly.

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
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
  int n; // [1, 2 x 10^5]
  cin >> n;
  vector<int> ls(n); // [1, 10^6]
  cin >> ls;
  sort(ALL(ls));
  ls.erase(unique(ALL(ls)), ls.end());

  int k = *max_element(ALL(ls));
  vector<int> ps(k + 1); // Cummax of existing elements
  for (auto x : ls) { ps[x] = x; }
  FOR(x, 1, k + 1) { ps[x] = max(ps[x], ps[x - 1]); }
  dbg(ps);

  // Find max { y % x | y \in ls }
  auto evaluate = [&](int x) -> int {
    int res = 0;
    for (int mx = 2 * x; mx <= k; mx += x) {
      res = max(res, ps[mx - 1] % x);
    }
    res = max(res, ps[k] % x);
    return res;
  };

  int res = 0;
  for (auto x : ls) {
    res = max(res, evaluate(x));
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/484B/main_v3.cpp --check

%%%% begin
3
3 4 5
%%%%
2
%%%% end
*/
