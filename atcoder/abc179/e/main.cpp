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
  ll n, x, m; // n \in [1, 10^10], x, m \in [0, 10^5]
  cin >> n >> x >> m;

  // Check period
  vector<int> done(m, -1);
  vector<int> ys;
  int p, k1, k2; // period/start/end
  for (ll y = x, i = 0; ; i++) {
    if (done[y] != -1) {
      k1 = done[y];
      k2 = i;
      p = k2 - k1;
      break;
    }
    done[y] = i;
    ys.push_back(y);
    y = (y * y) % m;
  }
  dbg(p, k1, k2);
  dbg(ys);

  ll res = 0;
  if (n < k1) {
    // Only pre-period
    FOR(i, 0, n) { res += ys[i]; }

  } else {
    // Pre-period
    FOR(i, 0, k1) { res += ys[i]; }

    // Period
    ll res_p = 0;
    FOR(i, k1, k2) { res_p += ys[i]; }

    // Shortcut periods
    ll nn = n - k1;
    ll q = nn / p, r = nn % p;
    res += res_p * q;

    // Remainder
    FOR(i, k1, k1 + r) {
      res += ys[i];
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
python misc/run.py atcoder/abc179/e/main.cpp --check

%%%% begin
6 2 1001
%%%%
1369
%%%% end

%%%% begin
1000 2 16
%%%%
6
%%%% end

%%%% begin
10000000000 10 99959
%%%%
492443256176507
%%%% end
*/
