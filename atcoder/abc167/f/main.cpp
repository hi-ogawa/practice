// VC, WA

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T>            istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase_v1() {
  ll n; // n <= 10^6
  cin >> n;
  vector<string> ls(n, "");
  cin >> ls;

  // Count #push - #pop
  vector<ll> ps(n, 0);
  FOR(i, 0, n) {
    for (auto c : ls[i]) {
      ps[i] += ((c == '(') ? 1 : -1);
    }
  }

  // Sort and cumsum
  sort(ALL(ps), greater<ll>());
  vector<ll> qs(n + 1, 0);
  FOR(i, 0, n) { qs[i + 1] = qs[i] + ps[i]; }
  // DD(ps);
  // DD(qs);

  bool res = qs[n] == 0;
  cout << (res ? "YES" : "NO") << endl;
}

void mainCase_v2() {
  ll n; // n <= 10^6
  cin >> n;
  vector<string> ls(n, "");
  cin >> ls;

  // Count "#push - #pop" and "local maximum pop depth"
  vector<ll> ps(n, 0);
  vector<ll> qs(n, 0);
  FOR(i, 0, n) {
    ll x = 0, y = 0;
    for (auto c : ls[i]) {
      x += ((c == '(') ? 1 : -1);
      y = min(y, x);
    }
    ps[i] = x;
    qs[i] = y;
  }
  // DD(tie(ps, qs));

  // Conjecture: Such ordering is obtained from any correct ordering.
  vector<tuple<ll, ll>> rs(n, {0, 0});
  FOR(i, 0, n) { rs[i] = {ps[i], qs[i]}; }
  sort(ALL(rs), greater<tuple<ll, ll>>());
  // DD(rs);

  // Cumsum
  vector<ll> xs(n + 1, 0);
  FOR(i, 0, n) { xs[i + 1] = xs[i] + get<0>(rs[i]); }
  // DD(xs);

  bool res0 = 1;
  FOR(i, 0, n) {
    res0 = res0 && (xs[i] + get<1>(rs[i]) >= 0);
  }
  bool res1 = xs[n] == 0;
  bool res = res0 && res1;
  cout << (res ? "YES" : "NO") << endl;
}

void mainCase() { mainCase_v2(); }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  // [ Single case ]
  mainCase();
  return 0;

  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // FOR(i, 0, t) { mainCase(); }
  // return 0;
}

/*
python misc/run.py atcoder/abc167/f/main.cpp --check

%%%% begin
4
((()))
((((((
))))))
()()()
%%%%
YES
%%%% end

%%%% begin
2
)(
()
%%%%
NO
%%%% end
*/
