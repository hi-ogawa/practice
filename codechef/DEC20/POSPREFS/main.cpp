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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n, k; // [1, 1000]
  cin >> n >> k;

  //
  // PROP.
  //   Cusum of (-1, +2, -3, +4 ...) is (-1, +1, -2, +2, ...).
  //   Thus, it's easy to make half positives and half negatives.
  //

  vector<int> res(n + 1, 0);
  FOR(i, 1, n + 1) {
    res[i] = ((i % 2 == 0) ? 1 : -1) * i;
  }
  dbg(res);

  // Fix up difference by flipping the sign from the end
  int diff = k - n / 2;
  dbg(diff);

  if (diff > 0) {
    if (n % 2 == 0) {
      FOR(i, 0, diff) {
        int j = n - 1 - 2 * i;
        res[j] = j;
      }
    } else {
      FOR(i, 0, diff) {
        int j = n - 2 * i;
        res[j] = j;
      }
    }
  }

  if (diff < 0) {
    if (n % 2 == 0) {
      FOR(i, 0, -diff) {
        int j = n - 2 * i;
        res[j] = -j;
      }
    } else {
      FOR(i, 0, -diff) {
        int j = n - 1 - 2 * i;
        res[j] = -j;
      }
    }
  }

  FOR(i, 1, n + 1) {
    cout << res[i] << " \n"[i == n];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; // [1, 1000]
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codechef/DEC20/POSPREFS/main.cpp

%%%% begin
1
3 3
%%%%
1 2 3
%%%% end
*/
