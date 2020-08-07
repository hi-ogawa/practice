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

void mainCase() {
  int n, k;
  cin >> n >> k;
  vector<int> ls(n, 0);
  cin >> ls;

  // Maximum separation for each types
  vector<int> max_seps(k, 0);
  vector<int> lasts(k, 0);
  RANGE(i, 0, n) {
    int t = ls[i] - 1; // zero-based
    max_seps[t] = max(max_seps[t], i - lasts[t]);
    lasts[t] = i + 1;
  }

  // Handle the tail segment
  bool take_all = false;
  RANGE(t, 0, k) {
    // Take all if some type doesn't occure
    if (lasts[t] == 0) {
      take_all = true;
      break;
    }
    max_seps[t] = max(max_seps[t], n - lasts[t]);
  }
  // DD(ls);
  // DD(max_seps);

  int res = take_all ? n : *max_element(ALL(max_seps));
  cout << res << endl;
}

int main() {
  int t;
  cin >> t;
  RANGE(i, 0, t) mainCase();
  return 0;
}

/*
python misc/run.py codechef/LRNDSA02/NOTALLFL/main.cpp --check

%%%% begin
2
6 2
1 1 1 2 2 1
5 3
1 1 2 2 1
%%%%
3
5
%%%% end
*/
