// AFTER EDITORIAL, AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
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
  int n; // [1, 500]
  cin >> n;
  vector<int> ls(n); // [1, 1000]
  cin >> ls;

  // Find segment where it can be squashed into single element
  vector<array<int, 2>> segs;
  FOR(i, 0, n) {
    vector<int> st;
    FOR(j, i, n) {
      st.push_back(ls[j]);
      while (st.size() >= 2) {
        int x = *--st.end(), y = *----st.end();
        if (x != y) { break; }
        st.pop_back(); st.pop_back();
        st.push_back(x + 1);
      }
      if (st.size() == 1) {
        segs.push_back({i, j + 1});
      }
    }
  }
  dbg(segs);

  // DP
  const int kInf = n;
  vector<vector<int>> dp(n, vector<int>(n + 1, kInf));
  for (auto [i, j] : segs) {
    dp[i][j] = 1;
  }
  FOR(len, 2, n + 1) {
    FOR(i, 0, n - len + 1) {
      int j = i + len;
      int t = dp[i][j];
      FOR(k, i + 1, j) {
        t = min(t, dp[i][k] + dp[k][j]);
      }
      dp[i][j] = t;
    }
  }

  int res = dp[0][n];
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1312E/main.cpp

%%%% begin
5
4 3 2 2 3
%%%%
2
%%%% end

%%%% begin
7
3 3 4 4 4 3 3
%%%%
2
%%%% end

%%%% begin
3
1 3 5
%%%%
3
%%%% end

%%%% begin
1
1000
%%%%
1
%%%% end
*/
