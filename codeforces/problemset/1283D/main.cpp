// AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
template<typename T> struct is_container {
template<typename C> static char test(typename C::const_iterator*); template<typename> static int test(...);
static bool const value = sizeof(test<T>(nullptr)) == sizeof(char) && !std::is_same<std::string, T>::value;
};
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#ifndef DEBUG
#define DEBUG 0
#endif
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  int n, m;
  cin >> n >> m;
  vector<ll> ls(n); // [-10^9, 10^9]
  cin >> ls;
  sort(ALL(ls));

  vector<ll> diffs(n - 1);
  FOR(i, 0, n - 1) { diffs[i] = ls[i + 1] - ls[i]; }

  // f(k) = #{ x | d(x, trees) <= k }
  auto evaluate = [&](ll k) -> ll {
    ll cnt = 0;
    cnt += 2 * k; // left/right most
    FOR(i, 0, n - 1) {
      cnt += min(diffs[i], 2 * k + 1) - 1; // in-between
    }
    return cnt;
  };

  // min { k | m <= f(k) }
  auto search = [&]() -> ll {
    ll k0 = 0, k1 = 1 << 30; // (k0, k1]
    while (k0 + 1 < k1) {
      ll k = (k0 + k1 + 1) / 2;
      if (m <= evaluate(k)) {
        k1 = k;
      } else {
        k0 = k;
      }
    }
    return k1;
  };

  int k = search();

  // Enumerate { x | d(x, trees) <= k}
  set<array<ll, 2>> ps; // (d(p, trees), p)
  FOR(d, 1, k + 1) {
    ps.insert({d, ls[0] - d});
    ps.insert({d, ls[n - 1] + d});
  }
  FOR(i, 0, n - 1) {
    if (diffs[i] >= 2 * k + 1) {
      FOR(d, 1, k + 1) {
        ps.insert({d, ls[i] + d});
        ps.insert({d, ls[i + 1] - d});
      }
    } else {
      FOR(d, 1, diffs[i]) {
        ll x = ls[i] + d;
        ll dd = min((ll)d, ls[i + 1] - x);
        ps.insert({dd, x});
      }
    }
  }
  dbg(ps);
  assert((int)ps.size() >= m);

  // Fill up from min distance
  vector<ll> res;
  ll res2 = 0;
  for (auto [d, p] : ps) {
    if ((int)res.size() >= m) { break; }
    res.push_back(p);
    res2 += d;
  }
  dbg(res);
  dbg(res2);

  cout << res2 << endl;
  FOR(i, 0, m) {
    cout << res[i] << " \n"[i == m - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1283D/main.cpp --check

%%%% begin
2 6
1 5
%%%%
8
-1 2 6 4 0 3
%%%% end

%%%% begin
3 5
0 3 1
%%%%
7
5 -2 4 -1 2
%%%% end
*/
