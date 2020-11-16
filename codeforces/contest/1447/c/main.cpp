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
  ll w; // [1, 10^18]
  cin >> w;
  vector<ll> ls(n); // [1, 10^9]
  cin >> ls;

  ll x = (w + 1) / 2;

  // Keep original order
  vector<int> order(n);
  iota(ALL(order), 0);
  sort(ALL(order), [&](auto x, auto y) { return ls[x] < ls[y]; });
  sort(ALL(ls));
  dbg(ls);

  auto solve = [&]() -> vector<int> {
    vector<int> res;

    // a > w is useless
    ls.erase(upper_bound(ALL(ls), w), ls.end());

    // Ok if x <= a <= w
    auto it = lower_bound(ALL(ls), x);
    if (it != ls.end()) {
      res.push_back(distance(ls.begin(), it));
      return res;
    }

    // Cum sum of smalls < x
    int k = ls.size();
    vector<ll> ps(k + 1);
    FOR(i, 0, k) { ps[i + 1] = ps[i] + ls[i]; }

    // Impossible if total < x
    if (ps[k] < x) {
      return res;
    }

    // if x <= total, then we have a solution
    int m = -1;
    FOR(i, 1, k + 1) {
      if (x <= ps[i]) {
        assert(ps[i] <= w); // since each element < x
        m = i;
        break;
      }
    }
    assert(m != -1);

    res.resize(m);
    iota(ALL(res), 0);
    return res;
  };

  auto res = solve();
  dbg(res);

  if (res.empty()) { cout << -1 << "\n"; return; }

  int m = res.size();
  cout << m << "\n";
  FOR(i, 0, m) {
    cout << (order[res[i]] + 1) << " \n"[i == m - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest/1447/c/main.cpp

%%%% begin
3
1 3
3
6 2
19 8 19 69 9 4
7 12
1 1 1 17 1 1 1
%%%%
1
1
-1
6
1 2 3 5 6 7
%%%% end
*/
