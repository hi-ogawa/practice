// AFTER CONTEST, AC

// Using DSU

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T>            istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Modulo
constexpr ll kModulo = 1000000000 + 7;
ll mmul(ll x, ll y) { return (x * y) % kModulo; }

// DSU
struct Dsu {
  vector<int> data_;
  Dsu(int n) {
    data_.resize(n);
    iota(ALL(data_), 0);
  }
  int find(int a) {
    if (data_[a] == a) { return a; }
    return data_[a] = find(data_[a]);
  }
  void merge(int a, int b) {
    data_[find(a)] = find(b);
  }
};

// Main
void mainCase() {
  ll n, m; // <= 10^5
  cin >> n >> m;

  vector<pair<ll, ll>> es(m, {0, 0});
  cin >> es;
  // DD(es);

  Dsu s(n);
  RANGE(i, 0, m) {
    int a, b;  tie(a, b) = es[i];
    a--; b--; // zero-based
    s.merge(a, b);
  }
  // DD(s.data_);

  map<ll, ll> compos;
  RANGE(i, 0, n) {
    compos[s.find(i)]++;
  }
  // DD(compos);

  // res = \prod_c |Compo_c|
  ll res = accumulate(ALL(compos), (ll)1, [](auto x, auto y) { return mmul(x, y.second); });
  cout << compos.size() << " " << res << endl;
}

int main() {
  // [ Single case ]
  // mainCase();
  // return 0;

  // [ Multiple cases ]
  int t;
  cin >> t;
  RANGE(i, 0, t) mainCase();
  return 0;
}

/*
python misc/run.py codechef/LRNDSA08/FIRESC/main_v2.cpp --check

%%%% begin
3
4 2
1 2
2 3
5 3
1 2
2 3
1 3
6 3
1 2
3 4
5 6
%%%%
2 3
3 3
3 8
%%%% end
*/
