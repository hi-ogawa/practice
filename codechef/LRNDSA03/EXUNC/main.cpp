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
void mainCase() {
  int n, nq;
  cin >> n >> nq;
  vector<int> ls(n, 0);
  cin >> ls;
  vector<tuple<int, int, int>> qs(n, {0, 0, 0});
  RANGE(i, 0, nq) {
    int x, y, z = 0;
    cin >> x;
    cin >> y;
    if (x == 1) { cin >> z; }
    qs[i] = {x, y, z};
  }
  // DD(ls);
  // DD(qs);

  // Make boundaries
  set<int> bs;
  bs.insert(0);
  RANGE(i, 1, n) {
    if (ls[i] % ls[i - 1] != 0) {
      bs.insert(i);
    }
  }

  vector<int> res(0, 0);
  RANGE(iq, 0, nq) {
    // DD(ls);
    // DD(bs);
    // DD(qs[iq]);
    auto q = qs[iq];
    int i = get<1>(q) - 1; // To zero-based

    // Update boundaries
    if (get<0>(q) == 1) {
      int x = get<2>(q);
      int x1 = ls[i];
      if (0 < i) {
        int x0 = ls[i - 1];
        if (x1 % x0 == 0 && x % x0 != 0) { bs.insert(i); }
        if (x1 % x0 != 0 && x % x0 == 0) { bs.erase(i); }
      }
      if (i + 1 < n) {
        int x2 = ls[i + 1];
        if (x2 % x1 == 0 && x2 % x != 0) { bs.insert(i + 1); }
        if (x2 % x1 != 0 && x2 % x == 0) { bs.erase(i + 1); }
      }
      ls[i] = x;
    }

    // Search boundary
    if (get<0>(q) == 2) {
      int i0 = *(--bs.upper_bound(i)); // zero-based index
      res.push_back(i0 + 1);
    }
  }

  for (auto x : res) {
    cout << x << endl;
  }
}

int main() {
  // int t;
  // cin >> t;
  // RANGE(i, 0, t) mainCase();
  mainCase();
  return 0;
}

/*
python misc/run.py codechef/LRNDSA03/EXUNC/main.cpp --check

%%%% begin
5 5
2 2 7 14 14
1 1 3
1 2 6
2 2
2 4
2 5
%%%%
1
3
3
%%%% end
*/
