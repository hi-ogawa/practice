// AC

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

vector<pair<bool, array<int, 3>>> dp;

void mainPrecompute() {
  const int n = 1000;
  dp.resize(n + 1);

  // n = (x, y, z).(3, 5, 7)
  array<int, 3> ls = {3, 5, 7};
  dp[0] = {1, {0, 0, 0}};
  FOR(i, 0, 3) {
    int a = ls[i];
    FOR(j, 0, n + 1) {
      if (dp[j].first && j + a <= n) {
        auto xyz = dp[j].second;
        xyz[i]++;
        dp[j + a] = {1, xyz};
      }
    }
  }
  dbg(dp);
}

// Main
void mainCase() {
  int n; // [1, 1000]
  cin >> n;

  if (!dp[n].first) { cout << -1 << "\n"; return; }
  auto [x, y, z] = dp[n].second;
  cout << x << " " << y << " " << z << "\n";
}

int main() {
  mainPrecompute();
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/edu96/a/main.cpp

%%%% begin
4
30
67
4
14
%%%%
2 2 2
7 5 3
-1
0 0 2
%%%% end
*/
