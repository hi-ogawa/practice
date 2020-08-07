// AFTER CONTEST, AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts> istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T>     istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
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

constexpr ll kModulo = 1e9 + 7;

ll mul(ll x, ll y) {
  return (x * y) % kModulo;
}

void mainCase() {
  int n, k;
  cin >> n >> k;
  vector<int> ls(n, 0); // elem ~ 10^6
  cin >> ls;

  ll res = 1;
  vector<tuple<int, int>> ts(0, {0, 0});
  RANGE(i, 0, n) {
    int a = ls[i];
    while (!ts.empty()) {
      int a0, i0;
      tie(a0, i0) = ts.back();
      if (a0 <= a) { break; }

      // a < a0
      ts.pop_back();
      res = mul(res, i - i0 + 1);
    }
    ts.push_back({a, i});
  }

  cout << res << endl;
}

int main() {
  mainCase();
  return 0;
}

/*
python misc/run.py codechef/LRNDSA02/CHFQUEUE/main.cpp --check

%%%% begin
4 2
1 2 1 2
%%%%
2
%%%% end

%%%% begin
10 2
1 1 1 1 1 1 1 1 1 1
%%%%
1
%%%% end
*/
