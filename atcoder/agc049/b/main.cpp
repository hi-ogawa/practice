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
  int n; // [1, 5 x 10^5]
  cin >> n;
  string s1, s2;
  cin >> s1 >> s2;

  //
  // CLAIM.
  //   Operation is a one of two
  //     01 => 10 or
  //     11 => 00
  //

  // Need to match position of "1"s
  deque<int> ps1, ps2;
  FOR(i, 0, n) {
    if (s1[i] == '1') {
      ps1.push_back(i);
    }
    if (s2[i] == '1') {
      ps2.push_back(i);
    }
  }

  // Solve from front
  ll res = 0;
  bool ok = 1;
  while (!ps1.empty()) {
    dbg(ps1, ps2);
    if (ps2.empty() || ps1.front() < ps2.front()) {
      // Move and cancel
      // 01 => 10
      // 11 => 00
      if (ps1.size() < 2) { ok = 0; break; }
      int i = ps1.front(); ps1.pop_front();
      int j = ps1.front(); ps1.pop_front();
      res += j - i;

    } else {
      // Move only
      // 01 => 10
      int i = ps2.front(); ps2.pop_front();
      int j = ps1.front(); ps1.pop_front();
      res += j - i;
    }
  }
  if (!ps2.empty()) { ok = 0; }

  if (!ok) { res = -1; }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/agc049/b/main.cpp

%%%% begin
3
001
100
%%%%
2
%%%% end

%%%% begin
3
001
110
%%%%
-1
%%%% end

%%%% begin
5
10111
01010
%%%%
5
%%%% end
*/
