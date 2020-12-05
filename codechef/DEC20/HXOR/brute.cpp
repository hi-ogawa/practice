
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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Enumerate digits for brute force solution
bool nextDigits(vector<int>& ls, int base) {
  int c = 1;
  for (auto& x : ls) {
    x += c;
    c = x / base;
    x %= base;
  }
  return c == 0;
}

// Main
void mainCase() {
  int n, x;
  cin >> n >> x;
  vector<int> ls(n);
  cin >> ls;

  const int m = 8;
  const int base = m * n * n;
  auto dec = [&](int d) -> array<int, 3> {
    int b = (d % (m * n * n)) / (n * n);
    int i = (d % (n * n)) / n;
    int j = (d % n) / 1;
    return {i, j, b};
  };

  vector<int> pattern(x);

  auto solve = [&](vector<int>& res) -> bool {
    res = ls;
    for (auto op : pattern) {
      auto [i, j, b] = dec(op);
      if (i == j) { return 0; }
      res[i] ^= (1 << b);
      res[j] ^= (1 << b);
    }
    return 1;
  };

  vector<int> res(n, 1 << 30), t(n);
  do {
    auto valid = solve(t);
    if (valid && t < res) { res = t; }
  } while (nextDigits(pattern, base));

  FOR(i, 0, n) {
    cout << res[i] << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; // [1, 10]
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codechef/DEC20/HXOR/brute.cpp

%%%% begin
1
3 2
0 1 6
%%%%
0 0 7
%%%% end

%%%% begin
1
3 3
2 2 3
%%%%
0 0 3
%%%% end
*/
