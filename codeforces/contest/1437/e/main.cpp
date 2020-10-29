// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y)(X); I < (Y); ++I)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i,       tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; auto s = ""; apply([&](auto&&... y){ ((o << s << y, s = ", "), ...); }, x); return o << ")"; }
template<class T1, class T2> istream& operator>>(istream& i,       pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
istream& operator>>(istream& i,       T& x) { for (auto& y : x) { i >> y; } return i; }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
ostream& operator<<(ostream& o, const T& x) { o << "{"; auto s = ""; for (auto& y : x) { o << s << y; s = ", "; } return o << "}"; }
}

#ifdef DEBUG
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n; // [1, 5 x 10^5]
  cin >> n;
  int k; // [0, n]
  cin >> k;
  vector<int> ls(n); // [1, 10^9]
  cin >> ls;
  vector<int> ps(k); // [1, n] (increasing)
  cin >> ps;

  // (x_i)_i : strict increasing  \iff  (x_i - i)_i : increasing
  FOR(i, 0, n) { ls[i] -= i; }

  // Dummy fixed elements at the front and the end
  ls.insert(ls.begin(), -1e9);
  ls.push_back(1e9);
  ps.insert(ps.begin(), 0);
  ps.push_back(n + 1);
  n += 2;
  k += 2;

  // Find longest increasing subsequence with fixed bound
  auto solveLIS = [&](int i0, int i1) -> int {
    int x0 = ls[i0], x1 = ls[i1];
    vector<int> xs;
    // Ignore out of [x0, x1]
    FOR(i, i0 + 1, i1) {
      int x= ls[i];
      if (x0 <= x && x <= x1) {
        xs.push_back(x);
      }
    }
    // Usual LIS
    vector<int> dp;
    for (auto x : xs) {
      auto it = upper_bound(ALL(dp), x);
      if (it == dp.end()) {
        dp.push_back(x);
      } else {
        *it = x;
      }
    }
    return dp.size();
  };

  // Solve LIS for each non-fixed elements
  int res = 0;
  FOR(j, 0, k - 1) {
    int i0 = ps[j];
    int i1 = ps[j + 1];
    if (ls[i0] > ls[i1]) { res = -1; break; } // Not solvable
    if (i0 + 1 == i1) { continue; }
    int t = solveLIS(i0, i1);
    dbg(i0, i1, t);
    res += i1 - i0 - 1 - t;
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest/1437/e/main.cpp

%%%% begin
7 2
1 2 1 1 3 5 1
3 5
%%%%
4
%%%% end

%%%% begin
3 3
1 3 2
1 2 3
%%%%
-1
%%%% end

%%%% begin
5 0
4 3 1 2 3
%%%%
2
%%%% end

%%%% begin
10 3
1 3 5 6 12 9 8 10 13 15
2 4 9
%%%%
3
%%%% end
*/
