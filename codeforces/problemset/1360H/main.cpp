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
  int n, m; // n \in [1, 100], m \in [1, 60]
  cin >> n >> m;
  vector<string> ls_str(n);
  cin >> ls_str;
  ll k = (1LL << m) - n;

  auto toBinary = [](ll x, int width) -> string {
    string res(width, ' ');
    FOR(i, 0, width) {
      res[i] = ((x >> (width - 1 - i)) & 1) + '0';
    }
    return res;
  };

  auto fromBinary = [](const string& x) -> ll {
    ll res = 0;
    int width = x.size();
    FOR(i, 0, width) {
      res |= (ll)(x[i] - '0') << (width - 1 - i);
    }
    return res;
  };

  vector<ll> ls(n);
  FOR(i, 0, n) { ls[i] = fromBinary(ls_str[i]); }
  sort(ALL(ls));

  // f(x) = #{ y | y <= x }
  auto evaluate = [&](ll x) -> ll {
    auto it = upper_bound(ALL(ls), x);
    return x + 1 - distance(ls.begin(), it);
  };

  // min { x | f(x) >= k / 2 }
  auto search = [&]() -> ll {
    ll x0 = -1, x1 = (1LL << m) - 1; // (x0, x1]
    while (x0 + 1 < x1) {
      ll x = (x0 + x1 + 1) / 2;
      if (evaluate(x) >= (k + 1) / 2) {
        x1 = x;
      } else {
        x0 = x;
      }
    }
    return x1;
  };

  ll res = search();
  auto res2 = toBinary(res, m);
  cout << res2 << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1360H/main.cpp

%%%% begin
5
3 3
010
001
111
4 3
000
111
100
011
1 1
1
1 1
0
3 2
00
01
10
%%%%
100
010
0
1
11
%%%% end
*/
