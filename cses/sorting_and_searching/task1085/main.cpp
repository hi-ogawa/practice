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
  ll n, k; // <= 10^6
  cin >> n >> k;
  vector<ll> ls(n, 0);
  cin >> ls;

  // DEF.
  //   f(part) = max_{I ∈ part} { ∑_{i ∈ I} ls[i] }

  // g(y, k) = "∃k-part. f(part) <= y"
  auto evaluate = [&](auto y) -> bool {
    int cnt = 0;
    int i = 0;
    while (i < n) {
      cnt++;
      ll s = ls[i]; // s <= y since "ll y0 = *max_element(ALL(ls)) - 1" below.
      int j = i + 1;
      while (j < n && s + ls[j] <= y) {
        s += ls[j];
        j++;
      }
      i = j;
    }
    // DD(tie(y, cnt));
    return cnt <= k;
  };

  // min { y | g(y) }
  auto search = [&]() -> ll {
    // (y0, y1]
    ll y0 = *max_element(ALL(ls)) - 1;
    ll y1 = accumulate(ALL(ls), (ll)0);
    while (y0 + 1 < y1) {
      ll y = (y0 + y1 + 1) / 2;
      if (evaluate(y)) {
        y1 = y;
      } else {
        y0 = y;
      }
    }
    return y1;
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
python misc/run.py cses/sorting_and_searching/task1085/main.cpp --check

%%%% begin
1 1
2
%%%%
2
%%%% end

%%%% begin
5 3
2 4 7 3 5
%%%%
8
%%%% end
*/
