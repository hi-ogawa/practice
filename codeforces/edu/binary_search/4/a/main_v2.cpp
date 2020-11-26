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

// Running reduction queue
template<class T, class Compare>
struct RunQueue {
  Compare compare;
  deque<T> data;
  RunQueue(Compare compare) : compare{compare} {}

  void push_back(T x) {
    while (!data.empty() && compare(x, data.back())) {
      data.pop_back();
    }
    data.push_back(x);
  }

  void erase(T x) {
    assert(!data.empty());
    if (reduce() == x) { data.pop_front(); }
  }

  T reduce() {
    assert(!data.empty());
    return data.front();
  }
};

// Max sum segment (bounded length)
template<class T>
tuple<T, int, int> findMaxSumSegment(const vector<T>& ls, int k0, int k1) {
  // Cumsum
  int n = ls.size();
  vector<T> ps(n + 1);
  FOR(i, 0, n) { ps[i + 1] = ps[i] + ls[i]; }

  // Running maximum
  auto compare = greater<pair<T, int>>();
  RunQueue<pair<T, int>, decltype(compare)> q(compare);

  T res = -1e18;
  int i0, i1;
  FOR(i, k0, k1 + 1) { q.push_back({ps[i], i}); }
  FOR(i, 0, n - k0 + 1) {
    auto [sum, j] = q.reduce();
    sum -= ps[i];
    if (sum > res) {
      res = sum; i0 = i; i1 = j;
    }
    if (i + k0 <= n) {
      q.erase({ps[i + k0], i + k0});
    }
    if (i + k1 + 1 <= n) {
      q.push_back({ps[i + k1 + 1], i + k1 + 1});
    }
  }

  return {res, i0, i1};
}

using Real = double;
const Real kEps = 1e-10;

// Main
void mainCase() {
  int n, d; // n \in [1, 10^5], d \in [1, n]
  cin >> n >> d;
  vector<int> ls(n); // [0, 100]
  cin >> ls;

  auto evaluate = [&](Real x) -> tuple<bool, int, int> {
    vector<Real> ls2(n);
    FOR(i, 0, n) { ls2[i] = ls[i] - x; }
    auto [sum, i, j] = findMaxSumSegment(ls2, d, n);
    bool ok = sum >= 0;
    return {ok, i, j};
  };

  // max { x | f(x) = ok }
  auto search = [&]() -> Real {
    Real x0 = *min_element(ALL(ls)) - 1;
    Real x1 = *max_element(ALL(ls)) + 1;
    while (x1 - x0 > kEps) {
      auto x = (x0 + x1) / 2;
      auto [ok, i, j] = evaluate(x);
      if (ok) { x0 = x; } else { x1 = x; }
    }
    return x1;
  };

  auto res = search();
  auto [_ok, i, j] = evaluate(res);
  cout << (i + 1) << " " << j << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/edu/binary_search/4/a/main_v2.cpp

%%%% begin
6 2
3 1 8 5 7 2
%%%%
3 5
%%%% end
*/
