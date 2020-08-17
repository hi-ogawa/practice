// AC

// NOTE:
//   Sum of convex functions is convex f(x) = ∑_i |ai - x|
//   Instead of using closed formula (main.cpp), here trisecting search convex minimum.

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
  ll n;
  cin >> n;
  vector<ll> ls(n, 0);
  cin >> ls;

  // f(x)
  auto evaluate = [&](ll x) -> ll {
    ll res = 0;
    FOR(i, 0, n) { res += abs(ls[i] - x); }
    return res;
  };

  // min_x f(x)
  auto search = [&]() -> ll {
    // [x0, x1)
    ll x0 = 0;
    ll x1 = *max_element(ALL(ls)) + 1;
    while (x0 + 2 < x1) {
      ll p = x0 + ((x1 - x0) / 3);
      ll q = x0 + ((x1 - x0) / 3) * 2;
      ll fp = evaluate(p);
      ll fq = evaluate(q);
      if (fp < fq) {
        x1 = q;
      } else {
        x0 = p;
      }
    }
    ll x2 = (x0 + x1) / 2;
    ll f0 = evaluate(x0);
    ll f2 = evaluate(x2);
    ll res = min(f0, f2);
    return res;
  };

  ll res = search();
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
python misc/run.py cses/sorting_and_searching/task1074/main_v2.cpp --check

%%%% begin
5
1 2 3 4 5
%%%%
6
%%%% end

%%%% begin
5
1 2 2 3 3
%%%%
3
%%%% end

%%%% begin
10
1 1 1 1 1 1 1 1 1 1
%%%%
0
%%%% end

%%%% begin
5
2 3 1 5 2
%%%%
5
%%%% end
*/
