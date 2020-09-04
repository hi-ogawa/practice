// AC

// Cf. codeforces/edu94/e/main.cpp

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
#ifndef DEBUG
#define DEBUG 0
#endif
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  int n; // <= 5000
  cin >> n;
  vector<int> ls(n);
  cin >> ls;

  function<int(int, int)> solveRec = [&](int l, int r) {
    // Split to non-zero segments
    vector<array<int, 2>> segs;
    int res = 0;
    FOR(i, l, r) {
      if ((i == l || ls[i - 1] == 0) && ls[i] > 0) {
        segs.push_back({i, -1});
      }
      if (ls[i] > 0 && (i + 1 == r || ls[i + 1] == 0)) {
        segs.back()[1] = i + 1;
      }
    }
    dbgv(l, r, segs);

    // Divide and conquer
    for (auto [ll, rr] : segs) {
      int m = *min_element(ls.begin() + ll, ls.begin() + rr);
      FOR(i, ll, rr) { ls[i] -= m; }
      res += min(rr - ll, solveRec(ll, rr) + m);
    }
    return res;
  };

  ll res = solveRec(0, n);
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
python misc/run.py codeforces/problemset/448C/main.cpp --check

%%%% begin
5
2 2 1 2 1
%%%%
3
%%%% end
*/
