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

// Trie for bit string
struct Trie {
  int cnt = 0;
  array<unique_ptr<Trie>, 2> children = {};

  void insert(int x, int b) {
    cnt++;
    if (b == -1) { return; }
    auto& c = children[(x >> b) & 1];
    if (!c) { c.reset(new Trie()); }
    c->insert(x, b - 1);
  }

  void erase(int x, int b) {
    cnt--;
    if (b == -1) { return; }
    auto& c = children[(x >> b) & 1];
    assert(c);
    c->erase(x, b - 1);
    if (c->cnt == 0) { c.reset(); }
  }

  void solve(int x, int b, vector<array<ll, 2>>& res) {
    if (b == -1) { return; }
    bool which = (x >> b) & 1;
    auto& c = children[which];
    assert(c);
    res[b][!which] += cnt - c->cnt; // Count elements where they differ bit for the first time at "b"
    c->solve(x, b - 1, res);
  }

  int solve2(int x, int b) {
    if (b == -1) { return 0; }
    bool which = (x >> b) & 1;
    auto& c = children[which];
    int res = 0;
    if (which) { res += cnt - c->cnt; }
    res += c->solve2(x, b - 1);
    return res;
  }
};

// Main
void mainCase() {
  int n; // [1, 3 x 10^5]
  cin >> n;
  vector<int> ls(n); // [0, 10^9]
  cin >> ls;

  int k = *max_element(ALL(ls));
  int b_lim = 0;
  while ((1 << b_lim) <= k) { b_lim++; }

  Trie trie;
  FOR(i, 0, n) { trie.insert(ls[i], b_lim); }

  vector<array<ll, 2>> ps(b_lim + 1); // (gain, cost) of flipping b-th bit
  FOR(i, 0, n) {
    trie.solve(ls[i], b_lim, ps);
    trie.erase(ls[i], b_lim);
  }
  dbg(ps);

  /// Flip bit where it gains
  int res1 = 0;
  FOR(b, 0, b_lim + 1) {
    if (ps[b][0] > ps[b][1]) {
      res1 |= (1 << b);
    }
  }

  // Count inversion after XOR
  ll res2 = 0;
  FOR(i, 0, n) { trie.insert(ls[i] ^ res1, b_lim); }
  FOR(i, 0, n) {
    res2 += trie.solve2(ls[i] ^ res1, b_lim);
    trie.erase(ls[i] ^ res1, b_lim);
  }

  cout << res2 << " " << res1 << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest673/c/main_v2.cpp

%%%% begin
4
0 1 3 2
%%%%
1 0
%%%% end

%%%% begin
9
10 7 9 10 7 5 5 3 5
%%%%
4 14
%%%% end

%%%% begin
3
8 10 3
%%%%
0 8
%%%% end
*/
