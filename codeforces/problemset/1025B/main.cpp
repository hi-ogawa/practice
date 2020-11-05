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
  int n; // [1, 2 x 10^5]
  cin >> n;
  vector<array<int, 2>> ls(n); // [2, 2 x 10^9]
  cin >> ls;

  auto factorize = [](int n) -> vector<int> {
    vector<int> res;
    for (int p = 2; p * p <= n; p++) {
      if (n % p == 0) {
        res.push_back(p);
        while (n % p == 0) { n /= p; }
      }
    }
    if (n > 1) { res.push_back(n); }
    return res;
  };

  int res = -1;
  FOR(i, 0, 2) {
    int x = ls[0][i];
    auto ps = factorize(x); // |ps| ≤ #{2, 3, 5, 7, ..., } ≤ 30 (since x ≤ 2^30)
    for (auto p : ps) {
      bool ok = 1;
      FOR(j, 1, n) {
        auto [a, b] = ls[j];
        if (a % p != 0 && b % p != 0) {
          ok = 0;
          break;
        }
      }
      if (ok) {
        res = p;
        break;
      }
    }
    if (res != -1) {
      break;
    }
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1025B/main.cpp

%%%% begin
3
17 18
15 24
12 15
%%%%
6
%%%% end

%%%% begin
2
10 16
7 17
%%%%
-1
%%%% end

%%%% begin
5
90 108
45 105
75 40
165 175
33 30
%%%%
5
%%%% end
*/
