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
  int n, k; // [1, 10^5]
  cin >> n >> k;
  string s;
  cin >> s;

  // Collect segments
  vector<array<int, 2>> segs;
  FOR(i, 0, n) {
    if (i == 0 || s[i] != s[i - 1]) { segs.push_back({i, -1}); }
    segs.back()[1] = i + 1;
  }

  // Handle single segment case specifically
  if (segs.size() == 1) {
    auto [l, r] = segs[0];
    int m = s[l] == 'W' ? n : k;
    int res = m ? 2 * m - 1 : 0;
    cout << res << "\n";
    return;
  }

  int res = 0; // Score
  vector<array<int, 2>> l_segs, end_segs; // "L" segment and special left/right ends

  for (auto [l, r] : segs) {
    if (s[l] == 'W') {
      res += 2 * (r - l) - 1;
      continue;
    }
    if (l == 0) {
      end_segs.push_back({l, r});
      continue;
    }
    if (r == n) {
      end_segs.push_back({l, r});
      continue;
    }
    l_segs.push_back({l, r});
  }
  dbg(res, l_segs, end_segs);

  // Fix from short "L" segment
  sort(ALL(l_segs), [](auto x, auto y) { return (x[1] - x[0]) < (y[1] - y[0]); });
  for (auto [l, r] : l_segs) {
    int dk = r - l;
    if (dk > k) {
      res += 2 * k;
      k = 0;
      break;
    }
    res += 2 * dk + 1; // bonus for WLW -> WWW
    k -= dk;
  }

  // Fix end_segs
  for (auto [l, r] : end_segs) {
    int dk = r - l;
    if (dk > k) {
      res += 2 * k;
      k = 0;
      break;
    }
    res += 2 * dk; // no bonus
    k -= dk;
  }

  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest-global-round-11/b/main.cpp

%%%% begin
8
5 2
WLWLL
6 5
LLLWWL
7 1
LWLWLWL
15 5
WWWLLLWWWLLLWWW
40 7
LLWLWLWWWLWLLWLWWWLWLLWLLWLLLLWLLWWWLWWL
1 0
L
1 1
L
6 1
WLLWLW
%%%%
7
11
6
26
46
0
1
6
%%%% end
*/
