// CONTEST, AC

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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
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

  const int b_lim = 30;

  vector<int> msbs(n);
  FOR(i, 0, n) {
    int x = ls[i];
    int t = 0;
    FOR(b, 0, b_lim) {
      if ((x >> b) & 1) {
        t = max(t, b);
      }
    }
    msbs[i] = t;
  }
  dbg(msbs);

  // If there is triplets with same MSB then we're done.
  bool ok2 = 0;
  FOR(i, 0, n - 2) {
    int b = msbs[i];
    if (b == msbs[i + 1] && b == msbs[i + 2]) {
      ok2 = 1;
      break;
    }
  }
  if (ok2) { cout << 1 << "\n"; return; }

  // Otherwise, n <= 2 * b_lim, so we can brute force
  assert(n <= 3 * b_lim);

  vector<int> xors(n + 1);
  FOR(i, 0, n) {
    xors[i + 1] = xors[i] ^ ls[i];
  }

  const int kInf = 1e9;
  int res = kInf;
  FOR(l, 2, n + 1) {
    FOR(i, 0, n - l + 1) {
      int j = i + l;
      FOR(k, i + 1, j) {
        int x = xors[k] ^ xors[i];
        int y = xors[j] ^ xors[k];
        if (x > y) {
          res = min(res, l - 2);
        }
      }
    }
  }

  if (res == kInf) { res = -1; }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest/1457/d/main.cpp

%%%% begin
4
2 5 6 8
%%%%
1
%%%% end

%%%% begin
3
1 2 3
%%%%
-1
%%%% end

%%%% begin
5
1 2 4 6 20
%%%%
2
%%%% end
*/
