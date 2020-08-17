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
  ll n, x;
  cin >> n >> x;
  vector<ll> ls(n, 0);
  cin >> ls;

  vector<int> ls_arg(n, 0);
  iota(ALL(ls_arg), 0);
  sort(ALL(ls_arg), [&](auto x, auto y) { return ls[x] < ls[y]; });
  sort(ALL(ls));

  // Enumerate a + b
  vector<tuple<ll, int, int>> ps;
  FOR(i, 0, n) {
    FOR(j, i + 1, n) {
      ps.push_back({ls[i] + ls[j], i, j});
    }
  }
  sort(ALL(ps));
  // DD(ps);

  // Do similar to "Sum of Two Values"
  ll k = ps.size();
  array<ll, 4> res = {-1};
  auto itb = ps.begin();
  auto comp = [](auto x, auto y) { return get<0>(x) < get<0>(y); };
  FOR(i, 0, k) {
    auto [y, i0, i1] = ps[i];
    tuple<ll, int, int> query = {x - y, 0, 0};
    auto [itlow, itupp] = equal_range(itb + i + 1, itb + k, query, comp);
    // Check "distinct indices"
    for (auto it = itlow; it != itupp; it++) {
      auto [z, j0, j1] = *it;
      if (i0 != j0 && i1 != j1 && i1 != j0) {
        res = {i0, i1, j0, j1};
        break;
      }
    }
  }

  if (res[0] == -1) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    FOR(i, 0, 4) {
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
python misc/run.py cses/sorting_and_searching/task1642/main.cpp --check

%%%% begin
4 9
4 1 2 3
%%%%
IMPOSSIBLE
%%%% end

%%%% begin
8 15
3 2 5 8 1 3 2 3
%%%%
2 4 6 7
%%%% end
*/
