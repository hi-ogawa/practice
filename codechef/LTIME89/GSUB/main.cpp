// CONTEST, AC

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

// Main
void mainCase() {
  int n, nq; // [1, 10^5]
  cin >> n >> nq;
  vector<int> ls(n);
  cin >> ls;
  vector<array<int, 2>> qs(nq);
  cin >> qs;

  // Consecutive segments
  vector<array<int, 3>> _segs; // (l, r, value)
  FOR(i, 0, n) {
    if (i == 0 || ls[i] != ls[i - 1]) {
      _segs.push_back({i, -1, ls[i]});
    }
    _segs.back()[1] = i + 1;
  }

  // Use "set" for fast update (TODO: does it pass 1 sec??)
  set<array<int, 3>> segs(ALL(_segs));

  auto correct = [&](int qi) {
    auto it = segs.lower_bound({qi, 0, 0});
    assert(it != segs.end());

    if (it != segs.begin() && next(it) != segs.end()) {
      auto [l0, r0, v0] = *prev(it);
      auto [l1, r1, v1] = *it;
      auto [l2, r2, v2] = *next(it);
      if (v0 == v1 && v1 == v2) {
        segs.erase(prev(it));
        segs.erase(next(it));
        segs.erase(it);
        segs.insert({l0, r2, v1});
        return;
      }
      if (v0 == v1) {
        segs.erase(prev(it));
        segs.erase(it);
        segs.insert({l0, r1, v1});
        return;
      }
      if (v1 == v2) {
        segs.erase(next(it));
        segs.erase(it);
        segs.insert({l1, r2, v1});
        return;
      }
      return;
    }

    if (it != segs.begin()) {
      auto [l0, r0, v0] = *prev(it);
      auto [l1, r1, v1] = *it;
      if (v0 == v1) {
        segs.erase(prev(it));
        segs.erase(it);
        segs.insert({l0, r1, v1});
        return;
      }
      return;
    }

    if (next(it) != segs.end()) {
      auto [l1, r1, v1] = *it;
      auto [l2, r2, v2] = *next(it);
      if (v1 == v2) {
        segs.erase(next(it));
        segs.erase(it);
        segs.insert({l1, r2, v1});
        return;
      }
      return;
    }
  };

  auto update = [&](int qi, int qv) {
    auto it = segs.lower_bound({qi + 1, 0, 0});
    assert(it != segs.begin());

    auto [l, r, v] = *prev(it);
    assert(l <= qi && qi < r);

    if (qv == v) { return; } // no change

    // Split in the middle
    segs.erase({l, r, v});
    if (l      != qi) { segs.insert({l,      qi, v}); }
    if (qi + 1 != r)  { segs.insert({qi + 1, r,  v}); }
    segs.insert({qi, qi + 1, qv});

    // Correct connected segments if any
    correct(qi);
  };

  for (auto [x, y] : qs) {
    update(x - 1, y);
    dbg(segs);
    int res = segs.size();
    cout << res << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codechef/LTIME89/GSUB/main.cpp

%%%% begin
1
5 2
1 1 2 5 2
1 3
4 2
%%%%
5
3
%%%% end
*/
