// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y)(X); I < (Y); ++I)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i,       tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; auto s = ""; apply([&](auto&&... y){ ((o << s << y, s = ", "), ...); }, x); return o << ")"; }
template<class T1, class T2> istream& operator>>(istream& i,       pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
istream& operator>>(istream& i,       T& x) { for (auto& y : x) { i >> y; } return i; }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
ostream& operator<<(ostream& o, const T& x) { o << "{"; auto s = ""; for (auto& y : x) { o << s << y; s = ", "; } return o << "}"; }
}

#ifdef DEBUG
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {

  // x % a < y % a
  auto ask = [&](int x, int y) -> bool {
    cout << "? " << x << " " << y << endl;
    string resp;
    cin >> resp;
    assert(resp == "x" || resp == "y");
    return resp == "y";
  };

  // Special case for a = 0
  if (!ask(0, 1)) {
    cout << "! 1" << endl;
    return;
  }

  // Find b s.t. 2^b < a ≤ 2^(b+1)
  auto search1 = [&]() -> int {
    int b = 0;
    while (ask(1 << b, 1 << (b + 1))) {
      b++;
    }
    return b;
  };
  int b = search1();

  // Find min { x | ask(2^b, x) = 0 }
  auto search2 = [&]() -> int {
    int x0 = (1 << b);
    int x1 = (1 << (b + 1)); // (x0, x1]
    while (x0 + 1 < x1) {
      int x = (x0 + x1 + 1) / 2;
      if (ask(1 << b, x) == 0) {
        x1 = x;
      } else {
        x0 = x;
      }
    }
    return x1;
  };

  int res = search2(); // [1, 10^9]
  cout << "! " << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  while (true) {
    string t;
    cin >> t;
    if (t == "end") { break; }
    assert(t == "start");
    mainCase();
  }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1103B/main.cpp

%%%% begin
start
x
x
start
x
x
y
start
x
x
y
y
end
%%%%
? 0 0
? 10 1
! 1
? 0 0
? 3 4
? 2 5
! 2
? 2 4
? 2 5
? 3 10
? 9 1
! 3
%%%% end
*/
