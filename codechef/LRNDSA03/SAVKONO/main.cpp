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
  int n, z;
  cin >> n >> z;
  vector<int> ls(n, 0);
  cin >> ls;

  // AFTER EDITORIAL
  // Max-heap (add "id" to support duplicate values)
  set<pair<int, int>, greater<pair<int, int>>> heap;
  RANGE(i, 0, n) {
    heap.insert({ls[i], i});
  }

  ll k = 0;
  bool fail = 0;
  while (z > 0) {
    if (heap.empty()) {
      fail = 1;
      break;
    }
    k++;
    auto top = heap.begin();
    int x = top->first;
    z -= x;
    heap.erase(top);
    if (x > 1) {
      heap.insert({x / 2, top->second});
    }
  }

  cout << (fail ? "Evacuate" : to_string(k)) << endl;
}

int main() {
  int t;
  cin >> t;
  RANGE(i, 0, t) mainCase();
  return 0;
}

/*
python misc/run.py codechef/LRNDSA03/SAVKONO/main.cpp --check

%%%% begin
1
5 25
7 13 8 17 3
%%%%
2
%%%% end

%%%% begin
1
5 200
100 20 10 2 1
%%%%
5
%%%% end

%%%% begin
1
5 25
1 2 1 2 1
%%%%
Evacuate
%%%% end

%%%% begin
1
5 200
100 100 100 100 100
%%%%
2
%%%% end
*/
