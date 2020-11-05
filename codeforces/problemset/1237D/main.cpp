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
  int n; // [2, 10^5]
  cin >> n;
  vector<int> ls(n); // [1, 10^9]
  cin >> ls;

  // Construct increasing subseq from right
  vector<array<int, 2>> st; // (value, index)
  vector<int> res(n, -1);
  for (int i = 2 * n - 1; i >= 0; i--) { // Loop [0, 2 * n) to immitate cyclic array
    int x = ls[i % n];
    int y = 2 * x;
    while (!st.empty() && st.back()[0] > y) {
      st.pop_back();
    }
    st.push_back({y, i});
    if (i < n) {
      // Search "blocker" to the right
      array<int, 2> q = {x, -1};
      auto it = upper_bound(ALL(st), q);
      if (it != st.begin()) {
        auto [z, j] = *prev(it);
        res[i] = j;
      }
    }
  }
  dbg(res);

  vector<int> res2(n, -1);

  if (count(ALL(res), -1) < n) { // Found at least one blocker
    // Propagate "blocker"
    FOR(i, 0, n) {
      int j = res[i];
      res2[i] = (j == -1) ? (int)1e9 : (res[i] - i);
    }
    auto it = min_element(ALL(res2));
    int i0 = distance(res2.begin(), it);
    int dp = *it;
    FOR(di, 1, n) {
      int i = (i0 - di + n) % n;
      res2[i] = min(res2[i], dp + 1);
      dp = res2[i];
    }
  }

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
python misc/run.py codeforces/problemset/1237D/main.cpp

%%%% begin
4
11 5 2 7
%%%%
1 1 3 2
%%%% end

%%%% begin
4
3 2 5 3
%%%%
5 4 3 6
%%%% end

%%%% begin
3
4 3 6
%%%%
-1 -1 -1
%%%% end
*/
