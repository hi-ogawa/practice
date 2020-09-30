// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i,       tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; bool b = 0; apply([&](auto&&... y){ ((o << (b ? ", " : "") << y, b = 1), ...); }, x); return o << ")"; }
template<class T1, class T2> istream& operator>>(istream& i,       pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
istream& operator>>(istream& i,       T& x) { for (auto& y : x) { i >> y; } return i; }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
ostream& operator<<(ostream& o, const T& x) { o << "{"; bool b = 0; for (auto& y : x) { o << (b ? ", " : "") << y; b = 1; } return o << "}"; }
}

#ifdef DEBUG
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

template<class T> using V = vector<T>;
using vec3 = array<double, 3>;

// Main
void mainCase() {
  int n1, n2, n3; // \in [1, 100]
  cin >> n1 >> n2 >> n3;

  // dp(n1, n2, n3) = {p1, p2, p3} \iff ....
  V<V<V<vec3>>> dp(n1 + 1, V<V<vec3>>(n2 + 1, V<vec3>(n3 + 1)));

  FOR(i, 0, n1 + 1) {
    FOR(j, 0, n2 + 1) {
      FOR(k, 0, n3 + 1) {
        if (!i && !j && !k) { continue; }
        if (!j && !k) { dp[i][j][k][0] = 1; continue; }
        if (!k && !i) { dp[i][j][k][1] = 1; continue; }
        if (!i && !j) { dp[i][j][k][2] = 1; continue; }
        double total = (double)i * j + (double)j * k + (double)k * i;
        FOR(l, 0, 3) {
          double p = 0;
          if (i && j) {
            p += dp[i][j - 1][k][l] * (double)i * j;
          }
          if (j && k) {
            p += dp[i][j][k - 1][l] * (double)j * k;
          }
          if (k && i) {
            p += dp[i - 1][j][k][l] * (double)k * i;
          }
          dp[i][j][k][l] = p / total;
        }
      }
    }
  }
  dbg2(dp);

  auto res = dp[n1][n2][n3];
  FOR(i, 0, 3) {
    cout << setprecision(numeric_limits<double>::digits10 + 1) << res[i] << " \n"[i == 2];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/540D/main.cpp --check

%%%% begin
2 2 2
%%%%
0.333333333333 0.333333333333 0.333333333333
%%%% end

%%%% begin
2 1 2
%%%%
0.150000000000 0.300000000000 0.550000000000
%%%% end

%%%% begin
1 1 3
%%%%
0.057142857143 0.657142857143 0.285714285714
%%%% end
*/
