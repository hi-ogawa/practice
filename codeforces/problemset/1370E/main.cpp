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
  int n;
  cin >> n;
  string s1, s2;
  cin >> s1 >> s2;

  // WLOG, we only consider differing indices
  vector<int> ls;
  array<int, 2> cnts = {};
  FOR(i, 0, n) {
    if (s1[i] != s2[i]) {
      int x = s1[i] - '0';
      ls.push_back(x);
      cnts[x]++;
    }
  }
  dbg(cnts, ls);
  if (cnts[0] != cnts[1]) { cout << -1 << "\n"; return; }
  if (cnts[0] == 0) { cout << 0 << "\n"; return; }

  // Get length of each segment
  vector<int> segs;
  segs.push_back(1);
  FOR(i, 1, (int)ls.size()) {
    if (ls[i] != ls[i - 1]) {
      segs.push_back(0);
    }
    segs.back()++;
  }
  dbg(segs);

  // TODO: prove/disprove optimality of this strategy
  // TODO: estimate time complexity (I thought this gets TLE)

  // Fix by taking maximum alternating length
  int res = 0;
  while (segs.size()) {
    // WLOG, we can wrap around if #segs : odd
    if (segs.size() % 2 == 1) {
      segs[0] += segs.back();
      segs.pop_back();
    }
    // Rotate alternating length
    int l = *min_element(ALL(segs));
    res += l;
    for (auto& x : segs) { x -= l; }

    // Merge remaining parts
    vector<int> segs_next;
    int i0 = -1;
    while (true) {
      auto it = find_if(segs.begin() + i0 + 1, segs.end(), [](int x) { return x > 0; });
      if (it == segs.end()) { break; }
      int i = distance(segs.begin(), it);
      if (i0 == -1 || (i - i0) % 2 == 1) {
        segs_next.push_back(0);
      }
      segs_next.back() += segs[i];
      i0 = i;
    }
    segs = segs_next;
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1370E/main.cpp --check

%%%% begin
6
010000
000001
%%%%
1
%%%% end

%%%% begin
10
1111100000
0000011111
%%%%
5
%%%% end

%%%% begin
8
10101010
01010101
%%%%
1
%%%% end

%%%% begin
10
1111100000
1111100001
%%%%
-1
%%%% end
*/
