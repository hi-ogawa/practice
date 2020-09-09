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
  int n, k;
  cin >> n >> k;
  vector<int> ls(n);
  cin >> ls;

  vector<int> diff(2 * k + 2); // difference array for range update
  int m = n / 2;

  // For each pair, count how many steps needed for target "x"
  FOR(i, 0, m) {
    int a = ls[m - i - 1];
    int b = ls[m + i];
    if (a > b) { swap(a, b); }
    // a + b          => 0 step
    // [a + 1, b + k] => 1 step
    // other          => 2 steps
    diff[2] += 2;
    diff[a + 1] -= 2;
    diff[a + 1] += 1;
    diff[a + b] -= 1;
    diff[a + b + 1] += 1;
    diff[b + k + 1] -= 1;
    diff[b + k + 1] += 2;
    diff[2 * k + 1] -= 2;
  }

  vector<int> sum(2 * k + 2);
  FOR(i, 1, 2 * k + 2) {
    sum[i] = sum[i - 1] + diff[i];
  }
  dbg(diff);
  dbg(sum);

  int res = *min_element(sum.begin() + 2, sum.begin() + 2 * k + 1);
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
python misc/run.py codeforces/problemset/1343D/main.cpp --check

%%%% begin
1
4 2
1 2 1 2
%%%%
0
%%%% end

%%%% begin
4
4 2
1 2 1 2
4 3
1 2 2 1
8 7
6 1 1 7 6 3 4 6
6 6
5 2 6 1 3 4
%%%%
0
1
4
2
%%%% end
*/
