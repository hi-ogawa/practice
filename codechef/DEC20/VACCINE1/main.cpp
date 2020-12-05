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

// Binary search
//   min { x ∈ [x0, x1) | y ≤ f(x) } (f : increasing)
//   max { x ∈ (x1, x0] | f(x) ≥ y } (f : decreasing)
template<class T, class U, class FuncT>
T binarySearch(T x0, T x1, U y, FuncT f, bool reverse = 0) {
  int s = reverse ? -1 : 1;
  T count = s * (x1 - x0);
  while (count > 0) {
    T step = count / 2;
    T x = x0 + s * step;
    if (f(x) < y) {
      x0 = x + s;
      count -= (step + 1);
    } else {
      count = step;
    }
  }
  return x0;
}

// Main
void mainCase() {
  ll d1, v1, d2, v2, p; // [1, 1000]
  cin >> d1 >> v1 >> d2 >> v2 >> p;

  auto evaluate = [&](ll x) -> ll {
    return max((ll)0, x + 1 - d1) * v1 + max((ll)0, x + 1 - d2) * v2;
  };

  ll x0 = 0;
  ll x1 = d1 + p + 1;
  ll res = binarySearch(x0, x1, p, evaluate);
  assert(res != x1);
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codechef/DEC20/VACCINE1/main.cpp

%%%% begin
1 2 1 3 14
%%%%
3
%%%% end

%%%% begin
5 4 2 10 100
%%%%
9
%%%% end
*/
