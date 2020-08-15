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
  ll n, m, x;
  cin >> n >> m >> x;

  vector<ll> c(n, 0);
  vector<vector<ll>> a(n, vector<ll>(m, 0));
  FOR(i, 0, n) {
    cin >> c[i];
    FOR(j, 0, m) {
      cin >> a[i][j];
    }
  }

  // Brute force 2^n
  ll res = -1;
  FOR(b, 0, 1 << n) {
    ll cost = 0;
    FOR(i, 0, n) {
      cost += c[i] * ((b >> i) & 1);
    }

    vector<ll> zs(m, 0);
    FOR(j, 0, m) {
      FOR(i, 0, n) {
        zs[j] += ((b >> i) & 1) * a[i][j];
      }
    }
    // DD(tie(cost, zs));

    if (*min_element(ALL(zs)) >= x) {
      if (res == -1 || cost < res) {
        res = cost;
      }
    }
  }

  cout << res << endl;
}

int main() {
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc167/c/main.cpp --check

%%%% begin
3 3 10
60 2 2 4
70 8 7 9
50 2 3 9
%%%%
120
%%%% end

%%%% begin
8 5 22
100 3 7 5 3 1
164 4 5 2 7 8
334 7 2 7 2 9
234 4 7 2 8 2
541 5 4 3 3 6
235 4 8 6 9 7
394 3 6 1 6 2
872 8 4 3 7 2
%%%
1067
%%%% end

*/
