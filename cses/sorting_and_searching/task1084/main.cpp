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
  ll n, m, k;
  cin >> n >> m >> k;
  vector<ll> ls1(n, 0);
  vector<ll> ls2(m, 0);
  cin >> ls1 >> ls2;
  sort(ALL(ls1));
  sort(ALL(ls2));
  // DD(ls1);
  // DD(ls2);

  //
  // Normal form of matching
  //  (p, q), (p', q') with p < p' <=> q < q'
  //
  // Thus, it suffices to optimize within such normal forms
  //
  ll res = 0;
  int i = 0;
  int j = 0;
  while (j < m) {
    ll q = ls2[j];
    while (i < n && ls1[i] < q - k) { i++; }
    if (i < n && ls1[i] <= q + k) {
      // DD(tie(i, j, ls1[i], ls2[j]));
      res++;
      i++;
    }
    j++;
  }
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
python misc/run.py cses/sorting_and_searching/task1084/main.cpp --check

%%%% begin
10 10 10
90 41 20 39 49 21 35 31 74 86
14 24 24 7 82 85 82 4 60 95
%%%%
6
%%%% end

%%%% begin
4 3 5
60 45 80 60
30 60 75
%%%%
2
%%%% end
*/
