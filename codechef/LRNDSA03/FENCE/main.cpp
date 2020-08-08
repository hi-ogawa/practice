// AFTER CONTEST, WIP

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
  int n, m, k;
  cin >> n >> m >> k;
  vector<pair<int, int>> ls(k, {0, 0});
  cin >> ls;
  // DD(ls);

  set<pair<int, int>> data1;
  set<pair<int, int>> data2;
  for (auto xy : ls) {
    data1.insert(xy);
    data2.insert({xy.second, xy.first});
  }
  // DD(data1);
  // DD(data2);

  int res1 = 0;
  {
    // Count (x, y) -> (x, y + 1)
    auto it = data1.begin();
    auto pr = it++;
    for (; it != data1.end(); pr = it++) {
      res1 += (pr->first == it->first && pr->second + 1 == it->second);
    }
  }

  int res2 = 0;
  {
    // Count (y, x) -> (y, x + 1)
    auto it = data2.begin();
    auto pr = it++;
    for (; it != data2.end(); pr = it++) {
      res2 += (pr->first == it->first && pr->second + 1 == it->second);
    }
  }

  int res = 4 * k - 2 * (res1 + res2);
  cout << res << endl;
}

int main() {
  int t;
  cin >> t;
  RANGE(i, 0, t) mainCase();
  return 0;
}

/*
python misc/run.py codechef/LRNDSA03/FENCE/main.cpp --check

%%%% begin
2
4 4 9
1 4
2 1
2 2
2 3
3 1
3 3
4 1
4 2
4 3
4 4 1
1 1
%%%%
20
4
%%%% end
*/
