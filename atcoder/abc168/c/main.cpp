// Virtual, AC

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
  double a, b, h, m;
  cin >> a >> b >> h >> m;

  // [ Naive ]
  // double tm = 60 * h + m;
  // double s1 = 2 * M_PI * tm / (12 * 60);
  // double s2 = 2 * M_PI * tm / 60;
  // double x1 = a * cos(s1), y1 = a * sin(s1);
  // double x2 = b * cos(s2), y2 = b * sin(s2);
  // double dx = x1 - x2;
  // double dy = y1 - y2;
  // double l = sqrt(dx * dx + dy * dy);
  // cout << l << endl;

  // [ A bit more algebra ]
  // |v1 - v2|^2 = |v1|^2 + |v2|^2 - 2<v1, v2>
  //             = a^2 + b^2 - 2ab(cos(s1)cos(s2) + sin(s1)sin(s2))
  //             = a^2 + b^2 - 2ab cos(s1 - s2)
  double s = 2 * M_PI * (60 * h + m - 12 * m) / (12 * 60);
  double l2 = a * a + b * b - 2 * a * b * cos(s);
  double l = sqrt(l2);
  cout << setprecision(numeric_limits<double>::digits10 + 1) << l << endl;
}

int main() {
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc168/c/main.cpp --check

%%%% begin
3 4 9 0
%%%%
5
%%%% end

%%%% begin
3 4 10 40
%%%%
4.56425719433005567605
%%%% end
*/
