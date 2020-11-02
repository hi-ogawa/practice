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
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n, nq, k; // [0, 10^6]
  cin >> n >> nq >> k;
  vector<int> ls(n); // [0, 10^6]
  cin >> ls;
  vector<array<int, 2>> qs(nq);
  cin >> qs;

  // Prefix XOR sum
  vector<int> xs(n + 1);
  FOR(i, 0, n) {
    xs[i + 1] = xs[i] ^ ls[i];
  }
  dbg(xs);

  // Mo's query ordering
  int n_blk = sqrt(n);
  auto compare = [&](array<int, 2> x, array<int, 2> y) {
    x[0] /= n_blk; y[0] /= n_blk;
    if (x[0] == y[0] && x[0] % 2 == 1) { swap(x[1], y[1]); }
    return x < y;
  };

  vector<int> order(nq);
  iota(ALL(order), 0);
  sort(ALL(order), [&](auto x, auto y) { return compare(qs[x], qs[y]); });

  // State
  const int lim = 1 << 20;
  vector<int> cnts(lim); // Count prefix XOR sum which end at [l, r)
  int l = 0, r = 0;
  ll tmp = 0;

  auto insert = [&](int i) {
    int x = xs[i];
    dbg(i, x, x ^ k, cnts[x ^ k]);
    tmp += cnts[k ^ x];
    cnts[x]++;
  };
  auto erase = [&](int i) {
    int x = xs[i];
    dbg(i, x, x ^ k, cnts[x ^ k]);
    cnts[x]--;
    tmp -= cnts[k ^ x];
  };

  vector<ll> res(nq);
  FOR(i, 0, nq) {
    int iq = order[i];
    auto [ql, qr] = qs[iq];
    ql--; qr++;
    while (ql < l) { insert(--l); }
    while (r < qr) { insert(r++); }
    while (l < ql) { erase(l++); }
    while (qr < r) { erase(--r); }
    dbg(l, r, tmp);
    res[iq] = tmp;
  }

  for (auto x : res) {
    cout << x << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/617E/main.cpp

%%%% begin
1 1 0
0
1 1
%%%%
1
%%%% end

%%%% begin
2 1 0
0 0
1 2
%%%%
3
%%%% end

%%%% begin
6 2 3
1 2 1 1 0 3
1 6
3 5
%%%%
7
0
%%%% end

%%%% begin
5 3 1
1 1 1 1 1
1 5
2 4
1 3
%%%%
9
4
4
%%%% end
*/
