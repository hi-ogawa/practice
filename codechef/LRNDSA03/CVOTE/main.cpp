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
  int n, m;
  cin >> n >> m;
  vector<pair<string, string>> ls1(n, {"", ""});
  vector<string> ls2(m, "");
  cin >> ls1;
  cin >> ls2;

  map<string, string> data1;
  for (auto xy : ls1) {
    string x, y;
    tie(x, y) = xy;
    data1[x] = y;
  }
  // DD(data1);

  map<string, int> data2;
  map<string, int> data3;
  for (auto s : ls2) {
    data2[s]++;
    data3[data1[s]]++;
  }
  // DD(data2);
  // DD(data3);

  auto compare = [](auto x, auto y) {
    return x.second < y.second || (x.second == y.second && x.first > y.first);
  };

  auto max2 = *max_element(ALL(data2), compare);
  auto max3 = *max_element(ALL(data3), compare);
  // DD(max2);
  // DD(max3);

  cout << max3.first << endl;
  cout << max2.first << endl;
}

int main() {
  // int t;
  // cin >> t;
  // RANGE(i, 0, t) mainCase();
  mainCase();
  return 0;
}

/*
python misc/run.py codechef/LRNDSA03/CVOTE/main.cpp --check

%%%% begin
4 5
Ramanujan India
Torricelli Italy
Gauss Germany
Lagrange Italy
Ramanujan
Torricelli
Torricelli
Ramanujan
Lagrange
%%%%
Italy
Ramanujan
%%%% end
*/
