// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
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
  int n;  // [1, 1000]
  cin >> n;
  vector<array<int, 2>> ls(n); // [-100, 100]
  cin >> ls;

  if (n <= 2) { cout << 0 << "\n"; return; }

  auto binom2 = [](ll x) -> ll { return (x * (x - 1)) / 2; };
  auto binom3 = [](ll x) -> ll { return (x * (x - 1) * (x - 2)) / (3 * 2); };

  // Count bad triangles
  ll cnt = 0;
  FOR(i, 0, n) {
    // Count points on the line passing "ls[i]"
    map<array<int, 2>, int> lines;
    int zeros = 0; // count origin
    FOR(j, 0, n) {
      if (i == j) { continue; }
      int dx = ls[j][0] - ls[i][0];
      int dy = ls[j][1] - ls[i][1];
      if (dx == 0 && dy == 0) {
        zeros++;
        continue;
      }
      // Normalize slope to (1, 0) or (dx, dy > 0)
      if (dy <= 0) { dx *= -1; dy *= -1; }
      if (dy == 0) { dx = 1; }
      int g = gcd(abs(dx), abs(dy));
      dx /= g; dy /= g;
      lines[{dx, dy}]++;
    }

    // Count two points on the same line as "ls[i]"
    for (auto [k, v] : lines) {
      cnt += binom2(v + zeros);
    }
  }
  cnt /= 3; // Fix triple counting

  ll res = binom3(n) - cnt;
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/552D/main.cpp

%%%% begin
4
0 0
1 1
2 0
2 2
%%%%
3
%%%% end

%%%% begin
3
0 0
1 1
2 0
%%%%
1
%%%% end

%%%% begin
1
1 1
%%%%
0
%%%% end
*/
