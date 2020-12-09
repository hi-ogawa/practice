// AFTER EDITORIAL, WIP

// Cf. https://codeforces.com/blog/entry/47821 by zscoder
// TODO: I'm still not sure why their simplified formula works (i.e. without tracking slope delta explicitly).

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
  int n; // [1, 3000]
  cin >> n;
  vector<int> ls(n); // [1, 10^9]
  cin >> ls;
  FOR(i, 0, n) { ls[i] -= i; }
  dbg(ls);

  set<pair<int, int>> heap; // (x, slope delta)
  ll res = 0;

  heap.insert({ls[0], 1});
  FOR(i, 1, n) {
    dbg(res, heap);

    int x = ls[i];
    auto it = heap.lower_bound({x, -1});
    if (it == heap.end()) {
      heap.insert({x, 1});
      continue;
    }
    if (x == it->first) {
      int d = 2 + it->second;
      heap.erase(it);
      heap.insert({x, d});
    } else {
      heap.insert({x, 2});
    }
    auto [x1, d1] = *--heap.end(); heap.erase(--heap.end());
    res += (x1 - x);
    assert(d1 > 0);
    if (d1 > 1) {
      heap.insert({x1, d1 - 1});
    }
  }

  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/713C/main.cpp

%%%% begin
7
2 1 5 11 5 9 11
%%%%
9
%%%% end

%%%% begin
5
5 4 3 2 1
%%%%
12
%%%% end
*/
