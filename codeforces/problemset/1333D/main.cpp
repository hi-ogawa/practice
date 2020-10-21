// WIP, WA

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
  int n, k; // n \in [2, 3000], k \in [1, 3 x 10^6]
  cin >> n >> k;
  string s;
  cin >> s;
  vector<int> ls(n);
  FOR(i, 0, n) { ls[i] = s[i] == 'R'; }
  dbg(ls);

  //
  // CLAIM.
  //   Regarding "R" = "1" and "L" = "0", then
  //     final position => 0..01..1 (i.e. zero inversions)
  //     turning operation => fixing neighboring inversion
  //
  // CLAIM.
  //   Maximum #steps = #inversions
  //   Minimum #steps = (computed below)
  //   Anything in between can be realized by properly delaying "1" to move to the right.
  //   (note that blocking only the left most "1" makes "no-movements" step, which is invalid)
  //   (see test case "6 6 RLRLRL")
  //

  vector<int> cs(n); // reverse cum count
  vector<int> bs(n); // how many times "1" blocked by "1" on the right side (when employing minimum strategy)
  cs[n - 1] = ls[n - 1];
  for (int i = n - 2; i >= 0; i--) {
    cs[i] = cs[i + 1] + ls[i];
    bs[i] = max(0, bs[i + 1] + (ls[i + 1] ? 1 : -1));
  }
  dbg(cs);
  dbg(bs);

  int inv_cnt = 0;
  int min_steps = 0;
  vector<int> ts(n); // min step for "1" at i to reach final position
  for (int i = n - 2; i >= 0; i--) {
    if (ls[i] == 0) { continue; }
    inv_cnt += (n - 1 - i) - (cs[i] - 1); // number of "0" on the right
    int j = n - cs[i]; // final position after all inversions are fixed
    int t = bs[i] + j - i; // "blocking number" + "necessarily moves"
    assert(t >= min_steps);
    min_steps = ts[i] = t;
  }
  dbg(inv_cnt, min_steps);
  if (k < min_steps || inv_cnt < k) { cout << -1 << "\n"; return; }

  // Additionally block some "1"s to make use of all k steps
  int kk = k;
  FOR(i, 0, n) {
    if (ls[i] == 1) {
      if (kk > ts[i]) {
        bs[i] += kk - ts[i];
      }
      kk = bs[i]; // propagate delay to next "1"
    }
  }
  dbg(bs);

  // Simulate based on "blocking number"
  vector<vector<int>> res(k);
  FOR(i, 0, n) {
    if (ls[i] == 0) { continue; }
    int j = n - cs[i];
    int k0 = bs[i];
    int k1 = bs[i] + j - i;
    int i0 = i;
    FOR(p, k0, k1) {
      res[p].push_back(i0++);
    }
  }
  dbg2(res);

  for (auto& r : res) {
    cout << r.size();
    for (auto rr : r) { cout << " " << (rr + 1); }
    cout << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1333D/main.cpp

%%%% begin
6 6
RLRLRL
%%%%
1 5
1 3
1 4
1 1
1 2
1 3
%%%% end

%%%% begin
4 3
RLRL
%%%%
1 3
1 1
1 2
%%%% end

%%%% begin
2 1
RL
%%%%
1 1
%%%% end

%%%% begin
2 1
LR
%%%%
-1
%%%% end

%%%% begin
4 2
RLRL
%%%%
2 1 3
1 2
%%%% end
*/
