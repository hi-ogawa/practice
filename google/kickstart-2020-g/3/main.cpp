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
  int n_orig, m; // n \in [1, 10^5], m \in [1, 10^9]
  cin >> n_orig >> m;
  vector<ll> ls_orig(n_orig); // [1, m]
  cin >> ls_orig;

  // For simplicity, [0, m - 1)
  for (auto& x : ls_orig) { x %= m; }

  // For simplicity, duplicate to three sets [-m, -1), [0, m - 1), [m, 2 m - 1)
  int n = 3 * n_orig;
  vector<ll> ls;
  for (auto x : ls_orig) {
    ls.push_back(x);
    ls.push_back(x - m);
    ls.push_back(x + m);
  }
  sort(ALL(ls));

  // Cum sum
  vector<ll> ps(n + 1);
  FOR(i, 0, n) { ps[i + 1] = ps[i] + ls[i]; }

  //
  // PROP. Optimal value can be achieved by taking one of ls[i].
  //   PROOF.
  //     Consider optimal case range [x - m/2, x + m/2),
  //     then, this optimality coincides with usual "median problem".
  //

  auto evaluate = [&](ll x) -> ll {
    ll x0 = x - m / 2, x1 = x0 + m;
    int i0 = distance(ls.begin(), lower_bound(ALL(ls), x0));
    int i1 = distance(ls.begin(), lower_bound(ALL(ls), x1));
    int i = distance(ls.begin(), lower_bound(ALL(ls), x));
    ll res = 0;
    res += (i - i0) * x - (ps[i] - ps[i0]);
    res += (ps[i1] - ps[i]) - (i1 - i) * x;
    return res;
  };

  const ll kInf = 1e18;
  ll res = kInf;
  for (auto x : ls_orig) {
    ll t = evaluate(x);
    res = min(res, t);
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) {
    cout << "Case #" << (i + 1) << ": ";
    mainCase();
  }
  return 0;
}

/*
python misc/run.py google/kickstart-2020-g/3/main.cpp

%%%% begin
2
3 5
2 3 4
4 10
2 9 3 8
%%%%
Case #1: 2
Case #2: 8
%%%% end
*/
