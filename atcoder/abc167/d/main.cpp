// VC, AC

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
void mainCase() {
  ll n, k; // n <= 10^6
  cin >> n >> k;

  vector<ll> ls(n, 0);
  cin >> ls;
  for (auto& x : ls) { x--; } // zero-based

  // Identify loop
  vector<ll> ts(n, -1);
  ll x = 0;
  ll t = 0;
  while (true) {
    if (ts[x] != -1) { break; }
    ts[x] = t;
    x = ls[x];
    t++;
  }
  ll period = t - ts[x];
  // DD(tie(x, period, ts));

  ll m, y;
  if (k < t) {
    // Done before loop so just do it again
    m = k;
    y = 0;
  } else {
    // Shortcut loop
    m = (k - t) % period;
    y = x;
  }
  // DD(tie(m, y));

  FOR(i, 0, m) { y = ls[y]; }
  cout << (y + 1) << endl; // one-based
}

int main() {
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc167/d/main.cpp --check

%%%% begin
4 5
3 2 4 1
%%%%
4
%%%% end

%%%% begin
6 727202214173249351
6 5 2 5 3 2
%%%%
2
%%%% end
*/
