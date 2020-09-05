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
  int n, k; // <= 10^5
  cin >> n >> k;
  vector<int> ls(n);
  cin >> ls;
  vector<int> cs(k);
  cin >> cs;

  // fs[l] = #{arrays with length l}
  vector<int> fs(k);
  FOR(i, 0, n) { fs[ls[i] - 1]++; }

  // (reverse) cumsum of fs
  vector<int> gs = fs;
  for (int i = k - 2; i >= 0; i--) { gs[i] += gs[i + 1]; }
  dbg(fs);
  dbg(gs);

  //
  // PROP.
  //   The lower bound "q" is achievable.
  //
  auto divCeil = [](int x, int y) -> int { return (x + y - 1) / y; };
  int q = 0;
  for (int i = k - 1; i >= 0; i--) {
    q = max(q, divCeil(gs[i], cs[i]));
  }

  vector<vector<int>> res(q);
  sort(ALL(ls));
  FOR(i, 0, n) {
    res[i % q].push_back(ls[i]);
  }

  cout << res.size() << endl;
  for (auto& r : res) {
    cout << r.size();
    for (auto x : r) {
      cout << " " << x;
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
python misc/run.py codeforces/problemset/1342D/main.cpp --check

%%%% begin
6 10
5 8 1 10 8 7
6 6 4 4 3 2 2 2 1 1
%%%%
2
3 1 7 8
3 5 8 10
%%%% end

%%%% begin
4 3
1 2 2 3
4 1 1
%%%%
3
1 2
2 1 3
1 2
%%%% end
*/
