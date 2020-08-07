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
  int n;
  cin >> n;
  vector<int> ls(n, 0); // "(" = 1 and ")" = 2
  cin >> ls;

  int max1 = 0;
  int max1_arg = 0;
  int max2 = 0;
  int max2_arg = 0;
  vector<int> xs(0, 0);
  RANGE(i, 0, n) {
    // "("
    if (ls[i] == 1) {
      xs.push_back(i);
      if ((int)xs.size() > max1) {
        max1 = xs.size();
        max1_arg = i;
      }
    }
    // ")"
    if (ls[i] == 2) {
      int j = xs.back();  xs.pop_back();
      if (i - j > max2) {
        max2 = i - j;
        max2_arg = j;
      }
    }
  }
  // One-based index
  printf("%d %d %d %d\n", max1, max1_arg + 1, max2 + 1, max2_arg + 1);
}

int main() {
  mainCase();
  return 0;
}

/*
python misc/run.py codechef/LRNDSA02/ZCO12001/main.cpp --check

%%%% begin
20
1 2 1 1 2 2 1 2 1 1 2 1 2 2 1 1 2 1 2 2
%%%%
2 4 6 9
%%%% end

*/
