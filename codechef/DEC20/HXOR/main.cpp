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
//   max { x ∈ (x1, x0] | f(x) ≥ y } (f : decreasing) (reverse = 1)
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
  int n, x; // n \in [2, 10^5], x \in [1, 10^9]
  cin >> n >> x;
  vector<int> ls(n); // [1, 10^9]
  cin >> ls;

  // Consider m x n binary digits
  const int m = 30;

  // "1" position for each bit
  vector<vector<int>> ps(m);
  FOR(i, 0, m) {
    FOR(j, 0, n) {
      if ((ls[j] >> (m - 1 - i)) & 1) {
        ps[i].push_back(j);
      }
    }
  }
  dbg(ps);

  // f(l) = number of operations needed to make "l"-prefix to be all zero
  auto evaluate = [&](int l) -> int {
    int ln = l / m, lm = l % m;
    int res = 0;
    FOR(i, 0, m) {
      int j1 = ln + (i < lm);
      assert(j1 <= n - 1);
      auto it = lower_bound(ALL(ps[i]), j1);
      int cnt = distance(ps[i].begin(), it);
      res += (cnt + 1) / 2;
    }
    return res;
  };

  int l0 = 0;
  int l1 = m * (n - 1);
  int l_opt = binarySearch(l0, l1, x, evaluate);
  dbg(l_opt, evaluate(l_opt));
  dbg(l1, evaluate(l1));

  auto operate = [&](int l) -> vector<int> {
    int ln = l / m, lm = l % m;
    vector<int> res = ls;
    FOR(i, 0, m) {
      int j1 = ln + (i < lm);
      assert(j1 <= n - 1);

      auto it = lower_bound(ALL(ps[i]), j1);
      int cnt = distance(ps[i].begin(), it);
      vector<int> flips(ps[i].begin(), it); // Indices to flip
      if (cnt % 2 == 1) {
        if (it != ps[i].end()) {
          flips.push_back(*it); // Cancel one more
        } else {
          flips.push_back(n - 1); // Flip last indices
        }
      }
      for (auto j : flips) {
        res[j] ^= (1 << (m - 1 - i));
      }
    }
    return res;
  };

  auto res = operate(l_opt);

  if (l_opt < l1) {
    assert(evaluate(l_opt) == x);

  } else {
    // Take care the parity of left-over operations
    bool trick = 0;
    FOR(i, 0, m) {
      int k = ps[i].size();
      if (0 < k && k < n) { trick = 1; }
    }
    trick = trick && x >= 2 && n >= 3;
    int y = evaluate(l1);
    if (!trick && (x - y) % 2 == 1) {
      res[n - 2] ^= 1;
      res[n - 1] ^= 1;
    }
  }

  FOR(i, 0, n) {
    cout << res[i] << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; // [1, 10]
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codechef/DEC20/HXOR/main.cpp

%%%% begin
1
3 2
0 1 1
%%%%
0 0 0
%%%% end

%%%% begin
1
3 3
2 2 3
%%%%
0 0 3
%%%% end
*/
