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

  //     +
  //     |   ....
  //     |     b
  //     +----+--------+
  //  c  |    |
  //     |    | 2a
  //     |    |
  //     +----+
  //          a

  auto ask = [&](int x, int y) {
    cout << "? " << x << " " << y << endl << flush;
    string resp;
    cin >> resp;
    return resp;
  };

  // Find a
  int a0 = 1;
  int a1 = 499;
  while (a0 < a1) {
    int a = (a0 + a1 + 1) / 2;
    auto resp = ask(a, 0);
    if (resp == "YES") {
      a0 = a;
    } else {
      a1 = a - 1;
    }
  }
  int res_a = a0;

  // Find b
  int b0 = res_a + 1;
  int b1 = 1000;
  while (b0 < b1) {
    int b = (b0 + b1 + 1) / 2;
    auto resp = ask(b, 2 * res_a);
    if (resp == "YES") {
      b0 = b;
    } else {
      b1 = b - 1;
    }
  }
  int res_b = b0;

  // Find c
  int c0 = 2 * res_a + 1;
  int c1 = 1000;
  while (c0 < c1) {
    int c = (c0 + c1 + 1) / 2;
    auto resp = ask(0, c);
    if (resp == "YES") {
      c0 = c;
    } else {
      c1 = c - 1;
    }
  }
  int res_c = c0;

  // DD(tie(res_a, res_b, res_c));
  int res = 4 * res_a * res_a + res_b * (res_c - 2 * res_a);
  cout << "! " << res << endl;
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
python misc/run.py codechef/LRNDSA04/QHOUSE/main.cpp --check

%%%% begin
%%%%
%%%% end
*/
