// AFTER CONTEST, AC

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
vector<ll> squares(0, 0);

void precompute() {
  // Square up to 10^10
  ll n = 100000ULL;
  squares.resize(n + 1);
  for (ll i = 0; i <= n; i++) {
    squares[i] = i * i;
  }
  // DD(squares);
}

void mainCase() {
  ll y;
  cin >> y; // <= 10^10

  // max { i | f(i) < x }
  auto search = [&](ll x) {
    // half open [i0, i1)
    ll i0 = 0;
    ll i1 = squares.size();
    while (i0 + 1 < i1) {
      ll i = (i0 + i1) / 2;
      // DD(tie(x, i0, i1, i));

      if (x <= squares[i]) {
        i1 = i;
      } else {
        i0 = i;
      }
    }
    return i0;
  };

  ll res = 0;
  for (ll x = max(1LL, y - 700LL); x <= y - 1LL; x++) {
    // DD(x);
    // DD(search(x + 1));
    res += search(x + 1);
  }
  cout << res << endl;
}

int main() {
  precompute();

  // [ Single case ]
  // mainCase();
  // return 0;

  // [ Multiple cases ]
  int t;
  cin >> t;
  RANGE(i, 0, t) mainCase();
  return 0;
}

/*
python misc/run.py codechef/LRNDSA06/CK87QUER/main.cpp --check

%%%% begin
4
2
3
4
10000000000
%%%%
1
2
3
69999300
%%%% end
*/
