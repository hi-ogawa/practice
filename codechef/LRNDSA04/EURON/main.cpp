// AFTER EDITORIAL, AC

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
  int n;
  cin >> n;
  vector<int> ls(n, 0);
  cin >> ls;

  ll res = 0;
  vector<int> ls_tmp(n, 0);
  function<void(int, int)> mergeSort = [&](int x0, int x1) {
    if (x0 == x1 - 1) { return; }
    int x = (x0 + x1) / 2;
    mergeSort(x0, x);
    mergeSort(x, x1);
    int i = x0;
    int j = x;
    int k = x0;
    while (i < x && j < x1) {
      if (ls[i] <= ls[j]) {
        ls_tmp[k++] = ls[i++];
      } else {
        ls_tmp[k++] = ls[j++];
        res += (x - i); // Count inversion
      }
    }
    while (i < x)  { ls_tmp[k++] = ls[i++]; }
    while (j < x1) { ls_tmp[k++] = ls[j++]; }
    RANGE(p, x0, x1) {
      ls[p] = ls_tmp[p];
    }
    // DD(tie(x0, x, x1, ls));
  };
  mergeSort(0, n);

  cout << res << endl;
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
python misc/run.py codechef/LRNDSA04/EURON/main.cpp --check

%%%% begin
5
5 4 3 2 1
%%%%
10
%%%% end
*/
