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
  string s;
  cin >> s;

  map<char, int> ps;
  for (auto c : s) { ps[c]++; }

  map<char, int> evens;
  map<char, int> odds;
  for (auto [c, k] : ps) {
    if (k % 2) {
      odds[c] = k;
    } else {
      evens[c] = k;
    }
  }
  // DD(tie(evens, odds));

  auto solve = [&]() -> string {
    int n = s.size();
    if (odds.size() >= 2) {
      return "NO SOLUTION";
    }
    if (odds.size() == 1 && n % 2 == 0) {
      return "NO SOLUTION";
    }
    string res;
    if (n % 2 == 1) {
      auto [c, k] = *odds.begin();
      res = string(k, c);
    }
    for (auto [c, k] : evens) {
      string s = string(k / 2, c);
      res = s + res + s;
    }
    return res;
  };

  auto res = solve();
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
python misc/run.py cses/introductory_problems/task1755/main.cpp --check

%%%% begin
AAAACACBA
%%%%
%%%% end

%%%% begin
AAAACACA
%%%%
%%%% end

%%%% begin
AAACAA
%%%%
%%%% end
*/
