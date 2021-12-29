// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y){X}; I < (Y); ++I)
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

// High dimentional vector
template<class T>
T NdVector(T value) { return value; }

template<class ...Ts>
decltype(auto) NdVector(size_t n, Ts ...rest) {
  auto inner = NdVector(rest...);
  return vector<decltype(inner)>(n, inner);
}

vector<int> toDigits(ll x) {
  vector<int> res;
  do {
    res.push_back(x % 10);
    x /= 10;
  } while (x > 0);
  return res;
}

ll solve(ll a) {
  assert(a >= 0);

  auto digits = toDigits(a);

  // For simplicity, append "leading zero"
  digits.push_back(0);
  int n = digits.size();

  // dp(k, d, is_bound, is_leading_zero) = #{ ... }
  constexpr ll kUndefined = -1;
  auto dp = NdVector(n, 10, 2, 2, kUndefined);

  function<ll(int, int, int, int)> dpRec = [&](int k, int d, int is_bound, int is_leading_zero) -> ll {
    auto& res = dp[k][d][is_bound][is_leading_zero];
    if (res != kUndefined) {
      return res;
    }

    if (k == 0) {
      res = 1;

    } else {
      res = 0;
      int e_lim = digits[k - 1];
      for (int e = 0; e < 10; e++) {
        if (is_bound && e > e_lim) {
          break;
        }
        int e_is_bound = is_bound && (e == e_lim);
        int e_is_leading_zero = is_leading_zero && (e == 0);
        if (e != d || e_is_leading_zero) {
          res += dpRec(k - 1, e, e_is_bound, e_is_leading_zero);
        }
      }
    }
    return res;
  };

  ll res = dpRec(n - 1, 0, true, true);
  return res;
}

// Main
void mainCase() {
  ll a, b; // [0, 10^18]
  cin >> a >> b;

  ll res = solve(b) - (a > 0 ? solve(a - 1) : 0);
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/dynamic_programming/task2220/main.cpp

%%%% begin
0 10
%%%%
11
%%%% end

%%%% begin
123 321
%%%%
171
%%%% end
*/
