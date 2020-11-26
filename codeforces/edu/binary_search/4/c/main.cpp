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

using Real = double;
const Real kEps = 1e-10;
const Real kInf = 1e18;

// Main
void mainCase() {
  int n, k; // [1, 10^5]
  cin >> n >> k;
  vector<array<int, 2>> ls(n); // [1, 10^5]
  cin >> ls;

  //
  // PROP.
  //    (∑_{i ∈ S} a(i)) / (∑_{i ∈ S} b(i)) ≥ x
  //    <=>
  //    ∑ a(i) ≥ x ∑ b(i)
  //    <=>
  //    ∑_{i ∈ S} (a(i) - x b(i)) ≥ 0
  //
  // PROP.
  //    Answer = max { x | ∃S. |S| = k => sum(S(a)) / sum(S(b)) >= x }
  //           = max { x | max_{|S| = k} ∑_{i ∈ S} (a(i) - x b(i)) ≥ 0 }
  //

  // f(x) = max_{|S| = k} ∑_{i ∈ S} (a(i) - x b(i))
  auto evaluate = [&](Real x) -> Real {
    vector<Real> ls2(n);
    FOR(i, 0, n) {
      auto [a, b] = ls[i];
      ls2[i] = a - x * b;
    }
    sort(ALL(ls2));
    Real res = 0;
    FOR(i, n - k, n) { res += ls2[i]; }
    return res;
  };

  // max { x | f(x) >= 0 }
  auto search = [&]() -> Real {
    Real x0 = 0;
    Real x1 = kInf;
    while (x1 - x0 > kEps) {
      auto x = (x0 + x1) / 2;
      if (evaluate(x) >= 0) {
        x0 = x;
      } else {
        x1 = x;
      }
    }
    return x0;
  };

  auto res = search();
  cout << fixed << setprecision(10) << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/edu/binary_search/4/c/main.cpp

%%%% begin
3 2
10 3
9 5
7 4
%%%%
2.4285714286
%%%% end

%%%% begin
8 3
4 2
4 2
2 2
1 5
5 3
3 5
2 2
5 3
%%%%
1.8571428571
%%%% end
*/
