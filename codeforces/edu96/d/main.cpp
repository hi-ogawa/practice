// AC

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
  int n; // [1, 2 x 10^5]
  cin >> n;
  string s;
  cin >> s;

  // Find consecutive segments and its sizes
  vector<array<int, 2>> segs;
  FOR(i, 0, n) {
    if (i == 0 || s[i] != s[i - 1]) { segs.push_back({i, -1}); }
    segs.back()[1] = i + 1;
  }

  int k = segs.size();
  vector<int> sizes(k);
  deque<int> larges; // |seg| >= 2
  FOR(i, 0, k) {
    sizes[i] = segs[i][1] - segs[i][0];
    if (sizes[i] >= 2) {
      larges.push_back(i);
    }
  }
  dbg(segs, sizes, larges);

  //
  // CLAIM. minizie 2nd op consumption
  //

  // TODO: prove optimality of this strategy
  int res = 0;
  int i = 0;
  while (i < k) {
    res++;

    // 1st op
    if (!larges.empty()) {
      // Pick closest large
      auto j = larges.front();
      if (--sizes[j] == 1) { larges.pop_front(); }

    } else {
      // Or pick this
      sizes[i++] = 0;
      if (i == k) { break; }
    }

    // 2nd op
    sizes[i] = 0;
    if (!larges.empty() && larges.front() == i) {
      larges.pop_front();
    }
    i++;
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
python misc/run.py codeforces/edu96/d/main.cpp

%%%% begin
5
6
111010
1
0
1
1
2
11
6
101010
%%%%
3
1
1
1
3
%%%% end
*/
