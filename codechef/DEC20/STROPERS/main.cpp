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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  string s;
  cin >> s;
  int n = s.size(); // [1, 1000]

  // Position of "1"
  vector<int> ps;
  FOR(i, 0, n) {
    if (s[i] == '1') {
      ps.push_back(i);
    }
  }

  // Cum count "1"
  vector<int> ks(n + 1);
  FOR(i, 0, n) { ks[i + 1] = ks[i] + (s[i] - '0'); }

  set<array<int, 3>> classes; // (length, "1"-count, p0 - p1 + p2 - ...)

  FOR(i, 0, n) {
    int cnt = 0;
    int st = 0;
    FOR(j, i, n) {
      int x = s[j] - '0';
      cnt += x;
      st += x * (cnt % 2 ? -1 : 1) * (j - i);
      classes.insert({j - i + 1, cnt, st});
    }
  }

  int res = classes.size();
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; // [1, 10]
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codechef/DEC20/STROPERS/main.cpp

%%%% begin
1
10111
%%%%
11
%%%% end

%%%% begin
10
00000
10001
10101
01111
11001
01101
10110
10010
10111
11001
%%%%
5
11
8
9
12
10
10
11
11
12
%%%% end
*/
