
// NOTE: Misread problem. This solves ∑_{i,j} (ai ^ aj) instead of ⨁_{i,j} (ai + aj)

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
  //   ∑ (ai ^ aj)
  //     = ∑_{b} 2^b ∑_{i, j} b-th(ai ^ aj)
  //     = ∑_{b} 2^b #{ i | b-th(ai) = 0 } . #{ i | b-th(ai) = 1 }
  //

  const int b_lim = 30;
  vector<int> cnts(b_lim);
  FOR(b, 0, b_lim) {
    for (auto x : ls) {
      if ((x >> b) & 1) {
        cnts[b]++;
      }
    }
  }
  dbg(cnts);

  ll res = 0;
  FOR(b, 0, b_lim) {
    res += ((ll)cnts[b] * (n - cnts[b])) << b;
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1322B/main.cpp

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
