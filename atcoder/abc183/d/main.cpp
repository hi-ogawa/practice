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
  int n, w; // n \in [1, 2 x 10^5], w \in [1, 10^9]
  cin >> n >> w;
  vector<array<int, 3>> ls(n); // time \in [0, 2 x 10^5]
  cin >> ls;

  vector<array<int, 3>> events; // (x, out/in, p)
  for (auto [l, r, p] : ls) {
    events.push_back({l, 1, p});
    events.push_back({r, 0, p});
  }
  sort(ALL(events));

  ll st = 0;
  bool ok = 1;
  for (auto [x, t, p] : events) {
    if (t == 0) {
      st -= p;
    }
    if (t == 1) {
      st += p;
      if (st > w) {
        ok = 0;
        break;
      }
    }
  }

  cout << (ok ? "Yes" : "No") << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc183/d/main.cpp

%%%% begin
4 10
1 3 5
2 4 4
3 10 6
2 4 1
%%%%
No
%%%% end

%%%% begin
4 10
1 3 5
2 4 4
3 10 6
2 3 1
%%%%
Yes
%%%% end

%%%% begin
6 1000000000
0 200000 999999999
2 20 1
20 200 1
200 2000 1
2000 20000 1
20000 200000 1
%%%%
Yes
%%%% end
*/
