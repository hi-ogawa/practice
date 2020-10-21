// WIP, WA

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
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
  int n, m; // n \in [1, 10^9], m \in [1, 10^5]
  cin >> n >> m;
  vector<array<ll, 2>> ls(m); // [0, 10^9]
  cin >> ls;

  // Sort by "b"
  sort(ALL(ls), [](auto x, auto y) { return x[1] < y[1]; });

  // Big/small partition with tracking thier sums
  array<multiset<ll>, 2> parts;
  array<ll, 2> parts_sum = {};

  auto update = [&](int b) {
    // Move so that "big" > b
    while (!parts[0].empty() && *parts[0].rbegin() > b) {
      int a = *parts[0].rbegin();
      parts[0].erase(parts[0].find(a)); parts_sum[0] -= a;
      parts[1].insert(a);               parts_sum[1] += a;
    }
    while (!parts[1].empty() && *parts[1].begin() <= b) {
      int a = *parts[1].begin();
      parts[0].insert(a);               parts_sum[0] += a;
      parts[1].erase(parts[1].find(a)); parts_sum[1] -= a;
    }
    if (!parts[0].empty()) { assert(*parts[0].rbegin() <= b); }
    if (!parts[1].empty()) { assert(*parts[1].begin() > b); }
  };

  auto insert = [&](int a) {
    if (parts[1].empty() || a < *parts[1].begin()) {
      parts[0].insert(a);
      parts_sum[0] += a;
      return;
    }
    parts[1].insert(a);
    parts_sum[1] += a;
  };

  dbg(n, m, ls);

  ll res = 0;
  FOR(i, 0, m) {
    // Maximize when b = max_i bi
    auto [a, b] = ls[i];
    update(b);
    int s = parts[1].size();
    ll t = (n - s - 1) * b + a + parts_sum[1]; // Only take big a' > b
    dbg(i, a, b, parts, parts_sum, t);
    res = max(res, t);
    insert(a);
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1379C/main.cpp --check

%%%% begin
2
4 3
5 0
1 4
2 2

5 3
5 2
4 2
3 1
%%%%
14
16
%%%% end
*/
