// CONTEST, AC

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
  int n; // 2^k in [4, 2^16]
  cin >> n;

  auto ask = [&](string t, int i, int j) -> int {
    i++; j++;
    cout << t << " " << i << " " << j << endl;
    int resp;
    cin >> resp;
    assert(resp != -1);
    return resp;
  };

  // 5 queries for x + y = 2 x & y + x ^ y
  int xy_and = ask("AND", 0, 1);
  int xy_xor = ask("XOR", 0, 1);
  int yz_and = ask("AND", 1, 2);
  int yz_xor = ask("XOR", 1, 2);
  int zx_and = ask("AND", 2, 0);
  int zx_xor = xy_xor ^ yz_xor;
  int xy = 2 * xy_and + xy_xor;
  int yz = 2 * yz_and + yz_xor;
  int zx = 2 * zx_and + zx_xor;
  int x2 = xy + zx - yz;
  assert(x2 % 2 == 0);
  int x = x2 / 2;

  vector<int> res(n);
  res[0] = x;
  res[1] = x ^ xy_xor;
  res[2] = x ^ zx_xor;

  // n - 3 queries
  FOR(i, 3, n) {
    int xw_xor = ask("XOR", 0, i);
    res[i] = x ^ xw_xor;
  }

  cout << "!";
  for (auto r : res) {
    cout << " " << r;
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest/1451/e1/main.cpp

%%%% begin
4

0

2

3
%%%%
OR 1 2

OR 2 3

XOR 2 4

! 0 0 2 3
%%%% end
*/
