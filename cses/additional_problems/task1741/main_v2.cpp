// WIP

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

struct SegmentTree {
  int n = 1;
  vector<int> data, lazy, data_nz;

  SegementTree(int _n) {
    while (n < _n) { n *= 2; }
    data.resize(2 * n);
    lazy.resize(2 * n);
    data_nz.resize(2 * n);
  }

  int value(int l, int r, int j) {
    return data[j] + (r - l) * lazy[j];
  }

  void push(int l, int r, int j) {
    data[j] = value(l, r, j);
    lazy[2 * j] += lazy[j];
    lazy[2 * j + 1] += lazy[j];
    lazy[j] = 0;
  }

  void incr(int ql, int qr, int qv) {
    function<int(int, int, int)> rec = [&](int l, int r, int j) {
      if (qr <= l || r <= ql) { return value(l, r, j); }
      if (ql <= l && r <= qr) { lazy[j] += qv; return value(l, r, j); }
      push(l, r, j);
      int vl = rec(l, (l + r) / 2, 2 * j);
      int vr = rec((l + r) / 2, r, 2 * j + 1);
      return data[j] = vl + vr;
    };
    rec(0, n, 1);

    function<int(int, int, int)> rec2 = [&](int l, int r, int j) {
      if (lazy[j] > 0) { return data_nz[j] = r - l; }
      int vl = rec2(l, (l + r) / 2, 2 * j);
      int vr = rec2((l + r) / 2, r, 2 * j + 1);
      return data_nz[j] = vl + vr;
    };
    rec2(0, n, 1);
  }

  int reduce(int ql, int qr) {
    function<int(int, int, int)> rec = [&](int l, int r, int j) {
      if (qr <= l || r <= ql) { return 0; }
      if (ql <= l && r <= qr) { return data_nz[j]; }
      push(l, r, j);
      int vl =
      return rec(l, (l + r) / 2, 2 * j) + rec((l + r) / 2, r, 2 * j + 1);
    };
    return 0;
  }
};

// Main
void mainCase() {
  int n; // [1, 10^5]
  cin >> n;
  vector<array<int, 4>> lines(n, {0}); // [-10^6, 10^6]
  cin >> lines;

  // Horizontal-sweep events
  enum { kIn, kOut };

  vector<array<int, 4>> events; // (x, y1, y2, in/out)
  for (auto [x1, y1, x2, y2] : lines) {
    assert(x1 <= x2);
    assert(y1 <= y2);
    events.push_back({x1, y1, y2, kIn});
    events.push_back({x2, y1, y2, kOut});
  }
  sort(ALL(events));

  // Sweep
  int lim = 1e6; // Translate y coord to positive
  SegmentTree isects(2 * lim + 1);
  ll res = 0;
  int sweep_x = -lim;
  for (auto [x, y1, y2, t] : events) {
    // Integrate union
    ll w = x - sweep_x;
    ll h = isects.reduce(0, 2 * lim + 1);
    res += w * h;

    // Update isects
    y1 += lim; y2 += lim;
    if (t == kIn) { isects.incr(y1, y2, 1); }
    if (t == kOut) { isects.incr(y1, y2, -1); }
    sweep_x = x;
  }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/additional_problems/task1741/main_v2.cpp

%%%% begin
3
1 3 4 5
3 1 7 4
5 3 8 6
%%%%
24
%%%% end
*/
