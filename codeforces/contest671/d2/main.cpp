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
  int n; // [1, 10^5]
  cin >> n;
  vector<int> ls(n);
  cin >> ls;
  if (n <= 2) {
    cout << 0 << endl;
    FOR(i, 0, n) {
      cout << ls[i] << " \n"[i == n - 1];
    }
    return;
  }

  //
  // CLAIM. (normal form)
  //   for any configuration with k = #{strict local minimum},
  //   we can find configuration where local minimums are achieved by k smallest elements.
  //

  sort(ALL(ls));
  int k = (n - 1) / 2;
  int x = ls[k - 1];
  dbgv(x, ls);

  auto [itl, itr] = equal_range(ALL(ls), x);
  int k1 = distance(ls.begin(), itl);
  int k2 = distance(ls.begin(), itr);
  dbgv(k, k1, k2);

  int l1 = k - k1;
  int l2 = n - k2;
  int res = k1 + max(0, min(l1, l2 - 1));

  vector<int> ls1(ls.begin(), ls.begin() + res);
  vector<int> ls2(ls.begin() + res, ls.end());

  vector<int> res2;
  while (!ls1.empty() || !ls2.empty()) {
    if (!ls2.empty()) { res2.push_back(ls2.back()); ls2.pop_back(); }
    if (!ls1.empty()) { res2.push_back(ls1.back()); ls1.pop_back(); }
  }
  dbg(res2);

  cout << res << endl;
  FOR(i, 0, n) {
    cout << res2[i] << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest671/d2/main.cpp --check

%%%% begin
1
1
%%%%
0
1
%%%% end

%%%% begin
5
1 2 2 3 3
%%%%
2
3 2 3 1 2
%%%% end

%%%% begin
7
1 3 2 2 4 5 4
%%%%
3
3 1 4 2 4 2 5
%%%% end
*/
