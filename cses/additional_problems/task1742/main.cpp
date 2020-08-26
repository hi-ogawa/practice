// WIP

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
  int n; // <= 10^5
  cin >> n;
  vector<tuple<char, int>> ls(n, {0, 0}); // <= 10^6
  cin >> ls;
  DD(ls);

  // Generate segments
  vector<array<int, 2>> segs(n, {0}); // (x, y)
  {
    array<int, 2> p = {0, 0};
    map<char, array<int, 2>> mapping = {{'U', {0, 1}}, {'R', {1, 0}}, {'D', {0, -1}}, {'L', {-1, 0}}};
    FOR(i, 0, n) {
      auto [c, j] = ls[i];
      array<int, 2> dp = mapping[c];
      array<int, 2> pp = {p[0] + j * dp[0], p[1] + j * dp[1]};
      segs[i] = {p[0], p[1], pp[0], pp[1]};
      p = pp;
    }
  }
  DD(segs);

  // Segments as X-sweep events with distance label
  // TODO
  // vector<> events; // (x, )

  // Check if there's collision before distance
  // TODO

  // Binary search maximum no-collision distance
  // TODO
  // auto search = [&]() -> int {}
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
python misc/run.py cses/additional_problems/task1742/main.cpp --check

%%%% begin
5
U 2
R 3
D 1
L 5
U 2
%%%%
9
%%%% end
*/
