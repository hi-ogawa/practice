// Virtual, AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (int I = (X); I < (Y); I++)
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
vector<tuple<ll, ll>> factorize(ll n) {
  vector<tuple<ll, ll>> res(0, {0, 0});
  ll q = n;
  for (ll p = 2; p * p <= q; p++) {
    ll e = 0;
    while (q % p == 0) {
      q /= p;
      e++;
    }
    if (e > 0) {
      res.push_back({p, e});
    }
  }
  if (q > 1) {
    res.push_back({q, 1});
  }
  return res;
}

void mainCase() {
  ll n;
  cin >> n;

  auto factors = factorize(n);
  // DD(factors);

  ll res = 0;
  for (auto [_p, e] : factors) {
    // k-triangle-number <= e
    ll k = 1;
    while ((k * (k + 1)) <= 2 * e) {
      k++;
    }
    k--;
    // DD(tie(e, k));
    res += k;
  }
  cout << res << endl;
}

int main() {
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc169/d/main.cpp --check

%%%% begin
24
%%%%
3
%%%% end

%%%% begin
1
%%%%
0
%%%% end

%%%% begin
64
%%%%
3
%%%% end
*/
