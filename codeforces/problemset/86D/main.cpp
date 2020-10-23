// AC

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
  int n, nq; // [1, 2 x 10^5]
  cin >> n >> nq;
  vector<int> ls(n); // [1, 10^6]
  cin >> ls;
  vector<array<int, 2>> qs(nq);
  cin >> qs;
  for (auto& [l, r] : qs) { l--; }

  // Time ~ n^2 / n_blk + nq x n_blk

  const int n_blk = sqrt(n);
  auto compare = [&](array<int, 2> x, array<int, 2> y) {
    x[0] /= n_blk; y[0] /= n_blk;
    if (x[0] == y[0] && (x[0] & 1)) { swap(x[1], y[1]); }
    return x < y;
  };
  vector<int> order(nq);
  iota(ALL(order), 0);
  sort(ALL(order), [&](auto x, auto y) { return compare(qs[x], qs[y]); });

  int k = *max_element(ALL(ls));
  vector<int> cnts(k + 1);
  ll tmp = 0;
  int l = 0, r = 0;

  auto insert = [&](int i) {
    ll x = ls[i], c = cnts[x]++;
    tmp -= c * c * x;
    tmp += (c + 1) * (c + 1) * x;

  };

  auto erase = [&](int i) {
    ll x = ls[i], c = cnts[x]--;
    tmp -= c * c * x;
    tmp += (c - 1) * (c - 1) * x;
  };

  vector<ll> res(nq);
  FOR(i, 0, nq) {
    auto [ql, qr] = qs[order[i]];
    while (ql < l) { insert(--l); }
    while (r < qr) { insert(r++); }
    while (l < ql) { erase(l++); }
    while (qr < r) { erase(--r); }
    res[order[i]] = tmp;
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
python misc/run.py codeforces/problemset/86D/main.cpp

%%%% begin
3 2
1 2 1
1 2
1 3
%%%%
3
6
%%%% end

%%%% begin
8 3
1 1 2 2 1 3 1 1
2 7
1 6
2 7
%%%%
20
20
20
%%%% end
*/
