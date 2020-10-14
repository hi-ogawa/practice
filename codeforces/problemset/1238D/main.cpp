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
  int n; // [1, 3 x 10^5]
  cin >> n;
  string s;
  cin >> s;

  //
  // PROP.
  //   s is bad \iff
  //     |s| = 1 or
  //     s = 10...0 or
  //         01...1 or
  //         1...10 or
  //         0...01
  //

  // Count bads

  vector<array<int, 2>> segs;
  FOR(i, 0, n) {
    if (i == 0 || s[i] != s[i - 1]) { segs.push_back({i, -1}); }
    segs.back()[1] = i + 1;
  }

  int k = segs.size();
  ll cnt = 0;
  FOR(i, 0, k - 1) {
    auto [l1, r1] = segs[i];
    auto [l2, r2] = segs[i + 1];
    cnt += (r1 - l1) + (r2 - l2) - 1;
  }

  ll res = ((ll)n * (n - 1)) / 2 - cnt;
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1238D/main.cpp

%%%% begin
5
AABBB
%%%%
6
%%%% end

%%%% begin
3
AAA
%%%%
3
%%%% end

%%%% begin
7
AAABABB
%%%%
15
%%%% end
*/
