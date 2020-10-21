// CONTEST, AC

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
  int n; // [2, 5000]
  cin >> n;
  vector<int> ls(n); // [1, 10^9]
  cin >> ls;

  map<int, vector<int>> ps;
  FOR(i, 0, n) {
    ps[ls[i]].push_back(i);
  }

  bool ok = ps.size() > 1;
  if (!ok) { cout << "NO" << "\n"; return; }

  vector<array<int, 2>> edges;
  auto s1 = ps.begin()->second; ps.erase(ps.begin());
  int v1 = s1[0];
  int v2 = ps.begin()->second[0];
  FOR(i, 1, s1.size()) {
    edges.push_back({v2, s1[i]});
  }
  for (auto& [k, vs] : ps) {
    for (auto v : vs) {
      edges.push_back({v1, v});
    }
  }

  cout << "YES" << "\n";
  for (auto [x, y] : edges) {
    x++; y++;
    cout << x << " " << y << "\n";
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
python misc/run.py codeforces/contest/1433/d/main.cpp

%%%% begin
4
5
1 2 2 1 3
3
1 1 1
4
1 1000 101 1000
4
1 2 3 4
%%%%
YES
1 3
3 5
5 4
1 2
NO
YES
1 2
2 3
3 4
YES
1 2
1 3
1 4
%%%% end
*/
