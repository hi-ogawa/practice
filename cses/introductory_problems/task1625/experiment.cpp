// AFTER EDITORIAL

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

void mainCase() {
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

  auto printHist = [&](ull hist) {
    FOR(i, 0, n) {
      FOR(j, 0, n) {
        cout << !!(enc({i, j}) & hist);
      }
      cout << endl;
    }
    // FOR(i, 0, n2) { cout << ((hist >> i) & 1); }
    // cout << endl;
  };

  ivec2 v_beg = {0, 0}, v_end = {6, 6};
  ull hamiltonian = ~((~0ULL) << n2);

  vector<tuple<ivec2, ull>> st; // ((i, j), path-history)
  st.push_back({v_beg, enc(v_beg)});

  ll res = 0;
  while (!st.empty()) {
    auto [v, hist] = st.back(); st.pop_back();
    if (v == v_end) {
      cout << "GOAL:" << endl;
      printHist(hist);
      res += (hist == hamiltonian);
      continue;
    }

    constexpr ivec2 dirs[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    bool ok[4];
    FOR(i, 0, 4) { ok[i] = check(add(v, dirs[i]), hist); }

    // Cull when path splits board (AFTER EDITORIAL)
    if ((ok[0] && ok[2]) && (!ok[1] && !ok[3])) { continue; }
    if ((ok[1] && ok[3]) && (!ok[0] && !ok[2])) { continue; }

    FOR(i, 0, 4) {
      if (ok[i]) {
        auto u = add(v, dirs[i]);
        st.push_back({u, enc(u) | hist});
      }
    }
  }
  DD(res);
}

int main() { mainCase(); }

/*
python misc/run.py cses/introductory_problems/task1625/experiment.cpp

%%%% begin
%%%%
%%%% end
*/
