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

// cf. misc/misc.py fib_modulo
vector<int> fib_modulo(int m) {
  // TODO: prove/disprove it's necessarily "pure" periodic (i.e. repeat starts from 1st element)
  //       at least, this seems the case for some examples I experimented.
  int x0 = 0;
  int x1 = 1;
  vector<int> res(0, 0);
  while (true) {
    res.push_back(x0);
    x0 = (x0 + x1) % m;
    swap(x0, x1);
    if (x0 == 0 && x1 == 1) { break; }
  }
  return res;
}

void mainCase() {
  ll n;
  cin >> n;

  // Find fibonacci modulo period
  auto ls = fib_modulo(10);
  int period = ls.size();
  // DD(tie(period, ls));

  // what's left is 2^k-th element (2^k <= n < 2^(k+1) (i.e. first set))
  ll m = 0;
  RANGE(i, 0, 64) {
    if (n & (1ULL << i)) {
      m = 1ULL << i;
    }
  }
  m--; // zero-based
  // DD(m);

  // find elem within period
  int res = ls[m % period];
  cout << res << endl;
}

int main() {
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
python misc/run.py codechef/LRNDSA05/FIBEASY/main.cpp --check

%%%% begin
1
9
%%%%
3
%%%% end
*/
