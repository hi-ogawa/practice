// AFTER EDITORIAL, AC

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

// High dimentional vector
template<class T>
T makeNdVector(T value) { return value; }

template<class ...Ts>
decltype(auto) makeNdVector(size_t n, Ts ...rest) {
  auto inner = makeNdVector(rest...);
  return vector<decltype(inner)>(n, inner);
}

// Main
void mainCase() {
  int n, k; // [0, 200]
  cin >> n >> k;
  string s1, s2; // a..z
  cin >> s1 >> s2;
  char x = s2[0], y = s2[1];

  const int kInf = 1 << 30;

  // dp(i, k, c) = max #{ s2 \in s1[:i] } after modifing k times with c = #{ x \in s1[:i] }
  auto dp = makeNdVector(k + 1, n + 1, -kInf);
  auto dp_prev = dp;
  dp[0][0] = 0;
  FOR(i, 0, n) {
    dp_prev = dp;
    char a = s1[i];
    FOR(j, 0, k + 1) {
      FOR(c, 0, n + 1) {
        int t = -kInf;
        if (x == y) {
          if (a == x) {
            // x -> x
            if (c >= 1) {
              t = max(t, dp_prev[j][c - 1] + (c - 1));
            }
          }
          // z -> x
          if (j >= 1 && c >= 1) {
            t = max(t, dp_prev[j - 1][c - 1] + (c - 1));
          }
        }
        if (a == x) {
          // x -> x
          if (c >= 1) {
            t = max(t, dp_prev[j][c - 1]);
          }
          // x -> y
          if (j >= 1) {
            t = max(t, dp_prev[j - 1][c] + c);
          }
        }
        if (a == y) {
          // y -> y
          t = max(t, dp_prev[j][c] + c);
          // y -> x
          if (c >= 1 && j >= 1) {
            t = max(t, dp_prev[j - 1][c - 1]);
          }
        }
        // z -> z
        t = max(t, dp_prev[j][c]);
        // z -> x
        if (j >= 1 && c >= 1) {
          t = max(t, dp_prev[j - 1][c - 1]);
        }
        // z -> y
        if (j >= 1) {
          t = max(t, dp_prev[j - 1][c] + c);
        }
        dp[j][c] = t;
      }
    }
    dbg2(dp);
  }

  int res = 0;
  FOR(j, 0, k + 1) {
    FOR(c, 0, n + 1) {
      res = max(res, dp[j][c]);
    }
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1409D/main.cpp

%%%% begin
4 2
bbaa
ab
%%%%
3
%%%% end

%%%% begin
7 3
asddsaf
sd
%%%%
10
%%%% end

%%%% begin
15 6
qwertyhgfdsazxc
qa
%%%%
16
%%%% end

%%%% begin
7 2
abacaba
aa
%%%%
15
%%%% end
*/
