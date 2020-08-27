// AFTER EDITORIAL, TLE

// TODO: On my machine, it takes about 0.7sec, but TLE on the server.

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

  constexpr int n = 7;
  constexpr int n2 = n * n;

  using ivec2 = array<int, 2>;
  auto add = [](const ivec2& x, const ivec2& y) -> ivec2 { return {x[0] + y[0], x[1] + y[1]}; };

  // Encode (i, j) into 64bit
  auto enc = [](const ivec2& v) -> ull { return 1ULL << (v[0] * n + v[1]); };

  // Check valid step
  auto check = [&](const ivec2& v, ull hist) -> bool {
    return (0 <= v[0] && v[0] < n) && (0 <= v[1] && v[1] < n) && ((enc(v) & hist) == 0);
  };

  ivec2 v_beg = {0, 0}, v_end = {6, 0};
  ull hamiltonian = ~((~0ULL) << n2);

  vector<tuple<ivec2, ull, int>> st; // ((i, j), path-history, path-length)
  st.push_back({v_beg, enc(v_beg), 0});
  // [ Micro optimization using raw pointer ]
  // int ptr = 0;
  // st.resize(1 << 10);
  // st[ptr++] = {v_beg, enc(v_beg), 0};

  ll res = 0;
  while (!st.empty()) {
  // while (ptr > 0) {
    auto [v, hist, len] = st.back(); st.pop_back();
    // auto [v, hist, len] = st[--ptr];
    if (v == v_end) {
      res += (hist == hamiltonian);
      continue;
    }

    constexpr ivec2 dirs[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    bool ok[4];
    FOR(i, 0, 4) { ok[i] = check(add(v, dirs[i]), hist); }

    // Cull when path splits board (AFTER EDITORIAL)
    if ((ok[0] && ok[2]) && (!ok[1] && !ok[3])) { continue; }
    if ((ok[1] && ok[3]) && (!ok[0] && !ok[2])) { continue; }

    char c = s[len];
    char mapping[4] = {'D', 'R', 'U', 'L'};
    FOR(i, 0, 4) {
      if (ok[i] && (c == '?' || mapping[i] == c)) {
        auto u = add(v, dirs[i]);
        st.push_back({u, enc(u) | hist, len + 1});
        // st[ptr++] = {u, enc(u) | hist, len + 1};
      }
    }
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
python misc/run.py cses/introductory_problems/task1625/main.cpp --check

%%%% begin
????????????????????????????????????????????????
%%%%
88418
%%%% end

%%%% begin
DRURRRRRDDDLUULDDDLDRRURDDLLLLLURULURRUULDLLDDDD
%%%%
1
%%%% end

%%%% begin
??????R??????U??????????????????????????LD????D?
%%%%
201
%%%% end
*/
