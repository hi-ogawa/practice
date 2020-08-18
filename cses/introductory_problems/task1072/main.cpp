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
  ll n; // <= 10^4
  cin >> n;

  vector<ll> res(n + 1, 0);
  res[1] = 0;
  res[2] = 6;
  FOR(i, 2, n) {
    // Both on new edges
    ll a = ((2 * i + 1) * (2 * i)) / 2 - 2;

    // Only one on new edge
    ll i2 = i * i;
    ll b = 0;
    b += i2 - 2; // one at corner
    b += 2 * 2 * (i2 - 2); // TODO: I thought these are valid only i >= 4, but seems working?
    b += 2 * 2 * (i2 - 3);
    b += 2 * (i - 4) * (i2 - 4);
    // DD(tie(i, a, b));
    res[i + 1] = res[i] + a + b;
  }

  FOR(i, 1, n + 1) {
    cout << res[i] << endl;
  }
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
python misc/run.py cses/introductory_problems/task1072/main.cpp --check

%%%% begin
4
%%%%
0
6
28
96
%%%% end

%%%% begin
8
%%%%
0
6
28
96
252
550
1056
1848
%%%% end
*/
