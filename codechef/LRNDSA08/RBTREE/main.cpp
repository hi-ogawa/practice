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
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  ll nq; // <= 10^5
  cin >> nq;

  vector<tuple<string, ull, ull>> qs(nq, {"", 0, 0});
  RANGE(iq, 0, nq) {
    string s;
    ull x = 0, y = 0;
    cin >> s;
    if (s == "Qr" || s == "Qb") {
      cin >> x >> y; // <= 10^9
    }
    qs[iq] = {s, x, y};
  }
  // DD(qs);

  // Answer queries
  bool state = 1;
  for (auto q : qs) {
    string s;
    ull x, y;
    tie(s, x, y) = q;
    if (s == "Qi") {
      state = !state;
      continue;
    }

    bool count_black = state;
    if (s == "Qr") { count_black = !count_black; }

    // WLOG, x <= y
    if (x > y) { swap(x, y); }

    // Common ancestor of binary tree
    int bx = 31 - __builtin_clz(x);
    int by = 31 - __builtin_clz(y);
    ull xx = x;
    ull yy = y >> (by - bx);
    while (xx != yy) {
      xx >>= 1;
      yy >>= 1;
    }
    ull z = xx;
    int bz = 31 - __builtin_clz(z);
    // DD(tie(x, y, z));
    // DD(tie(bx, by, bz));

    int path = bx + by - 2 * bz + 1;
    int black = 0;
    black += (bx + 2) / 2;
    black += (by + 2) / 2;
    black -= 2 * ((bz + 2) / 2);
    black += (bz % 2 == 0);
    // DD(tie(path, black));

    int res = count_black ? black : (path - black);
    cout << res << endl;
  }
}

int main() {
  // [ Single case ]
  mainCase();
  return 0;

  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // RANGE(i, 0, t) mainCase();
  // return 0;
}

/*
python misc/run.py codechef/LRNDSA08/RBTREE/main.cpp --check

%%%% begin
5
Qb 4 5
Qr 4 5
Qi
Qb 4 5
Qr 4 5
%%%%
2
1
1
2
%%%% end
*/
