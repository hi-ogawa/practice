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
  vector<int> ls(n); // [1, n]
  cin >> ls;

  //
  // PROP.
  //   #{components} = #{vertices} - #{edges}, thus
  //
  //     Answer = ∑_{l ≤ r} V(l, r) - E(l, r)  (we can independently compute the sums)
  //

  ll res_v = 0;
  FOR(i, 0, n) {
    int x = ls[i];
    res_v += (ll)x * (n - x + 1);
  }
  ll res_e = 0;
  FOR(i, 0, n - 1) {
    int x = ls[i], y = ls[i + 1];
    if (x > y) { swap(x, y); }
    res_e += (ll)x * (n - y + 1);
  }

  ll res = res_v - res_e;
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1151E/main.cpp

%%%% begin
3
2 1 3
%%%%
7
%%%% end

%%%% begin
4
2 1 1 3
%%%%
11
%%%% end

%%%% begin
10
1 5 2 5 5 3 10 6 5 1
%%%%
104
%%%% end
*/
