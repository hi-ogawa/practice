// AFTER EDITORIAL, AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i,       tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; bool b = 0; apply([&](auto&&... y){ ((o << (b ? ", " : "") << y, b = 1), ...); }, x); return o << ")"; }
template<class T1, class T2> istream& operator>>(istream& i,       pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
istream& operator>>(istream& i,       T& x) { for (auto& y : x) { i >> y; } return i; }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
ostream& operator<<(ostream& o, const T& x) { o << "{"; bool b = 0; for (auto& y : x) { o << (b ? ", " : "") << y; b = 1; } return o << "}"; }
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
  int n, z; // n \in [2, 2 x 10^5]
  cin >> n >> z;
  vector<int> ls(n);
  cin >> ls;
  sort(ALL(ls));

  //
  // PROP. (normal form theorem)
  //   for any valid configuration, there's a configuration with the same score s.t.
  //      l1 --- r1
  //         l2 ---- r2
  //            ....
  //

  // f(k) = 1 \iff we can make k pairs
  auto evaluate = [&](int k) -> bool {
    bool ok = 1;
    FOR(i, 0, k) {
      if (ls[n - k + i] < ls[i] + z) {
        ok = 0; break;
      }
    }
    dbg(k, ok);
    return ok;
  };

  // max { k | f(k) = 1 }
  auto search = [&]() -> int {
    int k0 = 0, k1 = n / 2 + 1; // [k0, k1)
    while (k0 + 1 < k1) {
      int k = (k0 + k1) / 2;
      if (evaluate(k)) {
        k0 = k;
      } else {
        k1 = k;
      }
    }
    return k0;
  };

  int res = search();
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1156C/main.cpp --check

%%%% begin
4 2
1 2 3 4
%%%%
2
%%%% end

%%%% begin
4 2
1 3 3 7
%%%%
2
%%%% end

%%%% begin
5 5
10 9 5 8 7
%%%%
1
%%%% end
*/
