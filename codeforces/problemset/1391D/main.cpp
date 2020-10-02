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

// Main
void mainCase() {
  int n, m; // m \in [1, 10^6]
  cin >> n >> m;
  vector<vector<char>> board(n, vector<char>(m));
  cin >> board;

  // Not solvable if there's 4x4 square
  if (n >= 4) { cout << -1 << "\n"; return; }

  // No even length square
  if (n == 1) { cout << 0 << "\n"; return; }

  // Check 2x3 rectangle is valid (or 2x2)
  auto isValid = [&](int mask0, int mask1) -> bool {
    if (n == 2) {
      int cnt = 0;
      cnt += bool(mask0 & (1 << 0));
      cnt += bool(mask0 & (1 << 1));
      cnt += bool(mask1 & (1 << 0));
      cnt += bool(mask1 & (1 << 1));
      return cnt % 2 == 1;
    }
    int cnt0 = 0;
    int cnt1 = 0;
    cnt0 += bool(mask0 & (1 << 0));
    cnt0 += bool(mask0 & (1 << 1));
    cnt1 += bool(mask0 & (1 << 1));
    cnt1 += bool(mask0 & (1 << 2));
    cnt0 += bool(mask1 & (1 << 0));
    cnt0 += bool(mask1 & (1 << 1));
    cnt1 += bool(mask1 & (1 << 1));
    cnt1 += bool(mask1 & (1 << 2));
    return (cnt0 % 2 == 1) && (cnt1 % 2 == 1);
  };

  // Cost to make i-th column into 1x3 mask (or 1x2)
  auto getCost = [&](int i, int mask) -> int {
    int res = 0;
    FOR(j, 0, n) {
      res += (board[j][i] == '1') != bool(mask & (1 << j));
    }
    return res;
  };

  const int kInf = 1e9;

  // n = 2 => mask: 00, 01, 10, 11
  // n = 3 => mask: 000, 001, ..., 111
  auto solve = [&]() -> int {
    vector<array<int, 8>> dp(m, {kInf, kInf, kInf, kInf, kInf, kInf, kInf, kInf});
    FOR(mask, 0, 1 << n) {
      dp[0][mask] = getCost(0, mask);
    }
    FOR(i, 1, m) {
      FOR(mask1, 0, 1 << n) {
        int t = kInf;
        FOR(mask0, 0, 1 << n) {
          if (isValid(mask0, mask1)) { // TODO: we can precompute valid transition and cost
            t = min(t, dp[i - 1][mask0] + getCost(i, mask1));
          }
        }
        dp[i][mask1] = t;
      }
    }
    dbg2(dp);
    return *min_element(ALL(dp[m - 1]));
  };

  int res = solve();
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1391D/main.cpp --check

%%%% begin
2 3
101
001
%%%%
1
%%%% end

%%%% begin
3 3
101
001
110
%%%%
2
%%%% end

%%%% begin
7 15
000100001010010
100111010110001
101101111100100
010000111111010
111010010100001
000011001111101
111111011010011
%%%%
-1
%%%% end
*/
