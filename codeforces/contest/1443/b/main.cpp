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
  int a, b; // [1, 1000]
  cin >> a >> b;
  string s;
  cin >> s;
  int n = s.size(); // [1, 10^5]

  deque<array<int, 2>> segs;
  FOR(i, 0, n) {
    if (i == 0 || s[i] != s[i - 1]) {
      segs.push_back({i, -1});
    }
    segs.back()[1] = i + 1;
  }

  if (s[segs.front()[0]] == '0') {
    segs.pop_front();
  }

  if (segs.empty()) {
    cout << 0 << "\n";
    return;
  }

  if (s[segs.back()[0]] == '0') {
    segs.pop_back();
  }

  int k = segs.size();
  ll res = a;
  for (int i = 1; i < k; i += 2) {
    auto [l, r] = segs[i];
    assert(s[l] == '0');
    res += min(a, (r - l) * b);
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
python misc/run.py codeforces/contest/1443/b/main.cpp

%%%% begin
2
1 1
01000010
5 1
01101110
%%%%
2
6
%%%% end
*/
