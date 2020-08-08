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
  int n1, n2;
  cin >> n1 >> n2;
  vector<int> ls1(n1, 0);
  vector<int> ls2(n2, 0);
  cin >> ls1 >> ls2;
  vector<int> ls1_arg(n1, 0);
  vector<int> ls2_arg(n2, 0);
  iota(ALL(ls1_arg), 0);
  iota(ALL(ls2_arg), 0);
  sort(ALL(ls1_arg), [&](auto x, auto y) { return ls1[x] < ls1[y]; });
  sort(ALL(ls2_arg), [&](auto x, auto y) { return ls2[x] < ls2[y]; });

  RANGE(i, 0, n1) {
    // ls1[i] + ls2[0] < ls1[i + 1] + ls2[0]
    cout << ls1_arg[i] << " " << ls2_arg[0] << endl;
  }

  RANGE(i, 1, n2) {
    // ls1[n1 - 1] + ls2[0] < ls1[n1 - 1] + ls2[i] < ls1[n1 - 1] + ls2[i + 1]
    cout << ls1_arg[n1 - 1] << " " << ls2_arg[i] << endl;
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
python misc/run.py codechef/LRNDSA03/DPAIRS/main.cpp --check

%%%% begin
3 2
10 1 100
4 3
%%%%
2 1
0 0
1 0
0 1
%%%% end
*/
