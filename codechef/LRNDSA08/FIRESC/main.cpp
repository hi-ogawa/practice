// AFTER CONTEST, AC

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

// Main
void mainCase() {
  ll n, m; // <= 10^5
  cin >> n >> m;

  vector<pair<ll, ll>> es(m, {0, 0});
  cin >> es;
  // DD(es);

  /// Adjacency list
  vector<vector<ll>> adj(n, vector<ll>(0, 0));
  RANGE(i, 0, m) {
    int v0, v1;
    tie(v0, v1) = es[i];
    v0--; v1--; // zero-based index
    adj[v0].push_back(v1);
    adj[v1].push_back(v0);
  }

  // DFS
  vector<ll> compos(n, -1);
  ll compo = 0;

  RANGE(v, 0, n) {
    if (compos[v] >= 0) { continue; }
    vector<ll> st;
    st.push_back(v);
    compos[v] = compo++;
    while (!st.empty()) {
      ll v0 = st.back();  st.pop_back();
      for (auto v1 : adj[v0]) {
        if (compos[v1] >= 0) { continue; }
        compos[v1] = compos[v0];
        st.push_back(v1);
      }
    }
  }
  // DD(compos);

  // \prod_c |Compo_c|
  sort(ALL(compos));
  vector<ll> counts;
  counts.push_back(1);
  RANGE(i, 1, n) {
    if (compos[i] != compos[i - 1]) {
      counts.push_back(0);
    }
    counts.back()++;
  }
  // DD(counts);

  ll res = accumulate(ALL(counts), (ll)1, mmul);
  cout << counts.size() << " " << res << endl;
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
python misc/run.py codechef/LRNDSA08/FIRESC/main.cpp --check

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
