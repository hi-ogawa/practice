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
  int n, x; // n \in [1, 3 x 10^5], x \in [-100, 100]
  cin >> n >> x;
  vector<int> ls(n); // [-10^9, 10^9]
  cin >> ls;

  // (Reverse) cumsum
  vector<ll> ps1(n + 1), ps2(n + 1);
  FOR(i, 0, n) {
    ps1[i + 1] = ps1[i] + ls[i];
    ps2[i + 1] = ps2[i] + ls[n - 1 - i];
  }
  dbg(ps1, ps2);

  // Max sum segment with fixed left end or right end
  vector<ll> segs1(n), segs2(n);
  multiset<ll> ms1(ALL(ps1)), ms2(ALL(ps2));
  FOR(i, 0, n) {
    segs1[i] = *ms1.rbegin() - ps1[i];
    ms1.erase(ms1.find(ps1[i]));
    segs2[n - 1 - i] = *ms2.rbegin() - ps2[i];
    ms2.erase(ms2.find(ps2[i]));
  }
  dbg(segs1, segs2);

  // q[i] = x * ls[:i] + max-sum-seg(ls[i:])
  vector<ll> qs(n + 1);
  FOR(i, 0, n + 1) {
    qs[i] = x * ps1[i] + ((i < n) ? segs1[i] : 0);
  }
  dbg(qs);

  ll res = 0;
  multiset<ll> ms(ALL(qs));
  FOR(i, 0, n + 1) {
    // Max value where separation "@" of (..1..)@(..x..)(...1...) is fixed at "i"
    ll t0 = *ms.rbegin() - x * ps1[i];
    ll t1 = i ? segs2[i - 1] : 0;
    ll t = t0 + t1;
    dbg(i, t0, t1, t);
    res = max(res, t);
    ms.erase(ms.find(qs[i]));
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1155D/main.cpp

%%%% begin
5 -2
-3 8 -2 1 -6
%%%%
22
%%%% end

%%%% begin
12 -3
1 3 3 7 1 3 3 7 1 3 3 7
%%%%
42
%%%% end

%%%% begin
5 10
-1 -2 -3 -4 -5
%%%%
0
%%%% end
*/
