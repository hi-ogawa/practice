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

// min { x ∈ [x0, x1) | y ≤ f(x) } (f : increasing)
template<class T, class U, class FuncT>
T binarySearch(T x0, T x1, U y, FuncT f) {
  T count = x1 - x0;
  while (count > 0) {
    T step = count / 2;
    T x = x0 + step;
    if (f(x) < y) {
      x0 = ++x;
      count -= (step + 1);
    } else {
      count = step;
    }
  }
  return x0;
}

// Main
void mainCase() {
  ll n, k; // n \in [1, 10^5], k \in [1, n^2]
  cin >> n >> k;

  // #{ a | a <= x }
  auto evaluate = [&](ll x) -> ll {
    ll res = 0;
    FOR(i, 1, n + 1) {
      res += min(n, x / i);
    }
    dbg(x, res);
    return res;
  };

  ll x0 = 1;
  ll x1 = n * n + 1;
  auto res = binarySearch(x0, x1, k, evaluate);
  assert(res != x1);
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/edu/binary_search/5/b/main.cpp

%%%% begin
3 4
%%%%
3
%%%% end

%%%% begin
5 16
%%%%
10
%%%% end
*/
