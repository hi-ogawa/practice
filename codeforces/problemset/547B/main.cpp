// AFTER EDITORIAL, AC

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
  int n; // <= 10^6
  cin >> n;
  vector<int> ls(n);
  cin >> ls;

  // Compute "influence width" (cf. histogram rectangle)
  vector<int> widths(n);
  {
    vector<int> rights(n, n);
    vector<array<int, 2>> st;
    FOR(i, 0, n) {
      while (!st.empty() && st.back()[1] > ls[i]) {
        auto [j, _f] = st.back(); st.pop_back();
        rights[j] = i;
      }
      st.push_back({i, ls[i]});
    }

    vector<int> lefts(n, -1);
    st.clear();
    for (int i = n - 1; i >= 0; i--) {
      while (!st.empty() && st.back()[1] > ls[i]) {
        auto [j, _f] = st.back(); st.pop_back();
        lefts[j] = i;
      }
      st.push_back({i, ls[i]});
    }

    FOR(i, 0, n) {
      widths[i] = rights[i] - lefts[i] - 1;
    }
  }
  dbg(widths);

  // res(x) = max_{w(i) >= x} ls(i)
  vector<int> res(n + 1);
  FOR(i, 0, n) {
    int w = widths[i];
    res[w] = max(res[w], ls[i]);
  }
  // (reverse) cummax
  for (int w = n; w >= 1; w--) {
    res[w - 1] = max(res[w - 1], res[w]);
  }
  dbg(res);

  FOR(i, 0, n) {
    if (i) cout << " ";
    cout << res[i + 1];
  }
  cout << endl;
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
python misc/run.py codeforces/problemset/547B/main.cpp --check

%%%% begin
10
1 2 3 4 5 4 3 2 1 6
%%%%
6 4 4 3 3 2 2 1 1 1
%%%% end
*/
