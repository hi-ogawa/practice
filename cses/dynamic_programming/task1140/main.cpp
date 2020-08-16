// AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
template<typename T> struct is_container {
template<typename C> static char test(typename C::const_iterator*); template<typename> static int test(...);
static bool const value = sizeof(test<T>(nullptr)) == sizeof(char) && !std::is_same<std::string, T>::value;
};
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  ll n; // <= 10^6
  cin >> n;
  vector<tuple<ll, ll, ll>> ls(n, {0, 0, 0});
  cin >> ls;
  sort(ALL(ls), [](auto x, auto y) { return tie(get<1>(x), get<0>(x)) < tie(get<1>(y), get<0>(y)); });
  // DD(ls);

  // max { i | get<1>(ls[i]) < x }
  auto search = [&](ll x) -> int {
    if (x <= get<1>(ls[0])) { return -1; }
    // [i0, i1)
    int i0 = 0;
    int i1 = n;
    while (i0 + 1 < i1) {
      int i = (i0 + i1) / 2;
      if (get<1>(ls[i]) < x) {
        i0 = i;
      } else {
        i1 = i;
      }
    }
    return i0;
  };

  vector<ll> dp(n, 0);
  ll dp_max = 0;
  FOR(i, 0, n) {
    auto [a, _b, p] = ls[i];
    int j = search(a);
    ll y = j != -1 ? dp[j] : 0;
    dp_max = max(dp_max, y + p);
    dp[i] = dp_max;
    // DD(dp);
  }

  ll res = dp_max;
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  mainCase();
  return 0;
  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // FOR(i, 0, t) { mainCase(); }
  // return 0;
}

/*
python misc/run.py cses/dynamic_programming/task1140/main.cpp --check

%%%% begin
4
2 4 4
3 6 6
6 8 2
5 7 3
%%%%
7
%%%% end
*/
