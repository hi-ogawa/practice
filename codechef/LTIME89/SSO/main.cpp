// AFTER EDITORIAL, AC

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
  int n; // [1, 10^5]
  cin >> n;
  vector<ll> ls(n); // [1, 2^30]
  cin >> ls;

  //
  // PROP.
  //   a1, ..., an  < 2^k
  //   a1 + ...+ an ≥ 2^k
  //   =>
  //   ∃m. 2^k ≤ a1 + ... + a(m) < 2^(k+1)  (i.e. k-th bit is "1")
  //

  const int b_lim = 60;
  ll res = 0;
  FOR(b, 0, b_lim) {
    bool ok = 0;

    // Check if any ls[i] has b-th bit is "1"
    FOR(i, 0, n) {
      if ((ls[i] >> b) & 1) {
        ok = 1;
        break;
      }
    }
    if (ok) {
      res |= (1LL << b);
      continue;
    }

    // Check if sum of first (b-1) bits ≥ 2^b
    ll t = 0;
    FOR(i, 0, n) {
      t += ls[i] & ((1LL << b) - 1);
    }
    ok = t >= (1LL << b);
    if (ok) {
      res |= (1LL << b);
      continue;
    }
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codechef/LTIME89/SSO/main.cpp

%%%% begin
2
2
1 1
3
1 9 8
%%%%
3
27
%%%% end
*/
