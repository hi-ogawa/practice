// AC

// Cf. cses/sorting_and_searching/task1640/main.cpp

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
  ll n, x;
  cin >> n >> x;
  vector<ll> ls(n, 0);
  cin >> ls;

  vector<int> ls_arg(n, 0);
  iota(ALL(ls_arg), 0);
  sort(ALL(ls_arg), [&](auto x, auto y) { return ls[x] < ls[y]; });
  sort(ALL(ls));

  bool found = 0;
  array<ll, 3> res;
  auto itb = ls.begin();
  FOR(i, 0, n) {
    FOR(j, i + 1, n) {
      if (ls[i] + 2 * ls[j] > x) { break; }
      ll y = x - (ls[i] + ls[j]);
      auto it = lower_bound(itb + j + 1, itb + n, y);
      if (it != ls.end() && *it == y) {
        res = {i, j, distance(itb, it)};
        found = 1;
        break;
      }
    }
  }

  if (!found) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    FOR(i, 0, 3) {
      if (i) { cout << " "; }
      cout << (ls_arg[res[i]] + 1);
    }
    cout << endl;
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
python misc/run.py cses/sorting_and_searching/task1641/main.cpp --check

%%%% begin
1 3
1
%%%%
%%%% end

%%%% begin
4 8
2 7 5 1
%%%%
1 3 4
%%%% end
*/
