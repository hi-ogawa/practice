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
  int n; // [2, 4 x 10^5]
  cin >> n;
  vector<int> ls(n); // [1, 10^7]
  cin >> ls;

  //
  // PROP. (bit independency)
  //   ⨁ (ai + aj)
  //     = ∑_{b} 2^b ⨁_{i, j} b-th(ai + aj)
  //     = ∑_{b} 2^b  where #{ (i, j) | b-th(ai + aj) = 1 } is odd
  //

  int m = *max_element(ALL(ls)) * 2 + 1;
  int b_lim = 0;
  while ((1 << b_lim) < m) { b_lim++; }

  // Trim high bits and sort
  vector<vector<int>> xs(b_lim, vector<int>(n));
  FOR(b, 0, b_lim) {
    FOR(i, 0, n) {
      xs[b][i] = ls[i] & ((1 << (b + 1)) - 1);
    }
    sort(ALL(xs[b]));
  }
  dbg2(xs);

  auto countRange = [&](const vector<int>& ls, int l, int r) -> int {
    auto itl = lower_bound(ALL(ls), l);
    auto itr = lower_bound(ALL(ls), r);
    return distance(itl, itr);
  };

  int res = 0;
  FOR(b, 0, b_lim) {
    auto& ys = xs[b];
    ll cnt = 0; // = #{ (i, j) | b-th(yi + yj) = 1 }
    int y1 = 1 << b;
    FOR(i, 0, n) {
      int y = ys[i];
      // Count two ranges
      //
      // 1000...0 = y4 \
      //  110...0 = y3 /
      //
      //  100...0 = y2 \
      //   10...0 = y1 /
      //   ^
      //   b-th bit
      //
      int c1 = countRange(ys,     y1 - y, 2 * y1 - y);
      int c2 = countRange(ys, 3 * y1 - y, 4 * y1 - y);
      int c3 = (((y + y) >> b) & 1); // subtract self pair
      dbg(b, i, c1, c2, c3);
      cnt += c1 + c2 - c3;
    }
    // Remove double count
    assert(cnt % 2 == 0);
    cnt /= 2;
    // If odd, this bit gets enabled
    if (cnt % 2 == 1) {
      res += (1 << b);
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
python misc/run.py codeforces/problemset/1322B/main_v2.cpp

%%%% begin
2
1 2
%%%%
3
%%%% end

%%%% begin
3
1 2 3
%%%%
2
%%%% end
*/
