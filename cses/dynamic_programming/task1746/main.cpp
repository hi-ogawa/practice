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
  ll n, m; // n <= 10^5, m <= 100
  cin >> n >> m;

  vector<ll> ls(n, 0);
  cin >> ls;
  for (auto& x : ls) { x--; } // -1, 0, .., m-1

  constexpr ll modulo = 1000'000'000 + 7;
  auto add = [](ll x, ll y) { return (x + y) % modulo; };

  vector<ll> dp(m, 0);
  if (ls[0] == -1) {
    fill(ALL(dp), 1);
  } else {
    dp[ls[0]] = 1;
  }
  // DD(dp);

  auto dp_prev = dp;
  FOR(i, 1, n) {
    FOR(y, 0, m) {
      for (auto d : {-1, 1}) {
        if (0 <= y + d && y + d < m) {
          dp[y] = add(dp[y], dp_prev[y + d]);
        }
      }
    }
    if (ls[i] >= 0) {
      FOR(y, 0, m) {
        if (y != ls[i]) { dp[y] = 0; }
      }
    }
    dp_prev = dp;
    // DD(dp);
  }

  ll res = accumulate(ALL(dp), (ll)0, add);
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
python misc/run.py cses/dynamic_programming/task1746/main_v2.cpp --check

%%%% begin
10 100
0 0 0 0 0 0 0 0 0 0
%%%%
1908416
%%%% end

%%%% begin
7 3
0 1 3 0 2 0 0
%%%%
0
%%%% end

%%%% begin
3 5
2 0 2
%%%%
3
%%%% end
*/
