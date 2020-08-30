// AFTER CONTEST, WA

// NOTE: here only managed to count patterns a, a, b, b

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
  int n; // <= 3000
  cin >> n;
  vector<int> ls(n, 0);
  cin >> ls;
  for (auto& x : ls) { x--; } // 0 .. n-1

  auto binom2 = [](ll n) -> ll { return (n * (n - 1)) / 2; };
  auto binom4 = [](ll n) -> ll { return (n * (n - 1) * (n - 2) * (n - 3)) / (4 * 3 * 2); };

  // Count each occurence
  vector<int> cnts(n, 0);
  for (auto x : ls) { cnts[x]++; }
  DD(cnts);

  // Count any order of a, a, b, b
  ll res1 = 0;
  FOR(i, 0, n) {
    res1 += binom4(cnts[i]);
    FOR(j, i + 1, n) {
      res1 += binom2(cnts[i]) * binom2(cnts[j]);
    }
  }
  DD(res1);

  ll res2 = 0; // count a, a, b, b
  ll res3 = 0; // count a, b, b, a (TODO: doesn't seem to be possible to count by sliding trick)
  {
    vector<int> cnts1(n, 0); // left
    vector<int> cnts2 = cnts; // right
    FOR(i, 0, n) {
      int x = ls[i];
      cnts1[x]++;
      cnts2[x]--;
      FOR(y, 0, n) {
        if (x == y) { continue; }
        res2 += binom2(cnts1[y]) * cnts2[x];
        // res3 ??
      }
      // DD(tie(cnts1, cnts2));
    }
  }
  DD(res2);
  DD(res3);

  ll res = res1 - res2 - res3;
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  // mainCase();
  // return 0;
  // [ Multiple cases ]
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/edu94/d/main.cpp --check

%%%% begin
2
5
2 2 2 2 2
6
1 3 3 1 2 3
%%%%
5
2
%%%% end
*/
