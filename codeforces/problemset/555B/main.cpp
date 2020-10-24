// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (decltype(Y) I = (X); I < (Y); ++I)
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
  int n, m; // [1, 2 x 10^5]
  cin >> n >> m;
  vector<array<ll, 2>> xs(n); // [1, 10^18]
  cin >> xs;
  vector<ll> ys(m); // [1, 10^18]
  cin >> ys;

  vector<array<ll, 2>> zs(n - 1);
  FOR(i, 0, n - 1) {
    auto [l1, r1] = xs[i];
    auto [l2, r2] = xs[i + 1];
    zs[i] = {l2 - r1, r2 - l1};
  }

  //
  // Maximum matching of points (ys) to intervals (zs)
  //

  vector<array<ll, 3>> events; // (x, type, id)
  FOR(i, 0, n - 1) {
    auto [x, y] = zs[i];
    events.push_back({x, 1, i});
    events.push_back({y + 1, 0, i});
  }
  FOR(i, 0, m) {
    events.push_back({ys[i], 2, i});
  }
  sort(ALL(events));

  // PROP. this strategy is optimal

  set<array<ll, 2>> st; // (interval-right-end, id)
  vector<int> res(n - 1, -1);
  int cnt = 0;
  for (auto [x, t, i] : events) {
    if (t == 0) { // interval out
      st.erase({x, i});
    }
    if (t == 1) { // interval in
      st.insert({zs[i][1] + 1, i});
    }
    if (t == 2) { // point
      // No matching avilable
      if (st.empty()) { continue; }

      // Pick first-out interval
      auto [r, j] = *st.begin(); st.erase(st.begin());
      res[j] = i;
      cnt++;
    }
  }

  bool ok = cnt == n - 1;
  cout << (ok ? "Yes" : "No") << "\n";
  if (!ok) { return; }

  FOR(i, 0, n - 1) {
    cout << (res[i] + 1) << " \n"[i == n - 2];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/555B/main.cpp

%%%% begin
4 4
1 4
7 8
9 10
12 14
4 5 3 8
%%%%
Yes
2 3 1
%%%% end

%%%% begin
2 2
11 14
17 18
2 9
%%%%
No
%%%% end

%%%% begin
2 1
1 1
1000000000000000000 1000000000000000000
999999999999999999
%%%%
Yes
1
%%%% end
*/
