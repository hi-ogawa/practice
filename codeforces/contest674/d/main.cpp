// AFTER EDITORIAL, AC

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
  int n; // [2, 2 x 10^5]
  cin >> n;
  vector<int> ls(n);
  cin >> ls;

  // Cumsum
  vector<ll> ps(n + 1);
  FOR(i, 0, n) { ps[i + 1] = ps[i] + ls[i]; }

  // Cumsum index map
  map<ll, vector<int>> qs;
  FOR(i, 0, n + 1) {
    qs[ps[i]].push_back(i);
  }
  dbg(qs);

  // Collect (right-minimal) zero sum segments
  vector<array<int, 2>> segs;
  for (auto& [k, js] : qs) {
    FOR(i, 0, (int)js.size() - 1) {
      segs.push_back({js[i], js[i + 1]});
    }
  }

  // Cut when zero sum segment gets "out"
  vector<array<int, 3>> events; // (index, out/in, id)
  FOR(id, 0, (int)segs.size()) {
    auto [i0, i1] = segs[id];
    events.push_back({i0,     1, id});
    events.push_back({i1 - 1, 0, id});
  }
  sort(ALL(events));

  int res = 0;
  set<int> st;
  for (auto [_i, t, id] : events) {
    if (t == 0) { // out
      if (st.count(id)) { // segs[id] wasn't cut already
        res++;
        st.clear();
      }
    }
    if (t == 1) { // in
      st.insert(id);
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
python misc/run.py codeforces/contest674/d/main.cpp --check

%%%% begin
6
3 2 1 -1 -2 -3
%%%%
1
%%%% end

%%%% begin
5
1 -1 1 -1 1
%%%%
4
%%%% end

%%%% begin
11
-1 -1 1 -1 -1 -1 1 1 1 -1 1
%%%%
5
%%%% end

%%%% begin
4
1 -5 3 2
%%%%
1
%%%% end

%%%% begin
5
4 -2 3 -9 2
%%%%
0
%%%% end

%%%% begin
9
-1 1 -1 1 -1 1 1 -1 -1
%%%%
6
%%%% end

%%%% begin
8
16 -5 -11 -15 10 5 4 -4
%%%%
3
%%%% end
*/
