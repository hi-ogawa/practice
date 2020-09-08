// AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
template<typename T> struct is_container {
template<typename C> static char test(typename C::const_iterator*); template<typename> static int test(...);
static bool const value = sizeof(test<T>(nullptr)) == sizeof(char) && !std::is_same<std::string, T>::value;
};
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#ifndef DEBUG
#define DEBUG 0
#endif
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Modulo op
constexpr ll modulo = 1e9 + 7;
ll madd(ll x, ll y) { return (x + y) % modulo; }
ll mmul(ll x, ll y) { return (x * y) % modulo; }

// 64bit hash by Chris Wellons https://nullprogram.com/blog/2018/07/31/
ull hash64(ull x) {
  x ^= x >> 30;
  x *= 0xbf58476d1ce4e5b9ULL;
  x ^= x >> 27;
  x *= 0x94d049bb133111ebULL;
  x ^= x >> 31;
  return x;
};

ull getHash(const string& s) {
  ull h = 0;
  for (auto c : s) { h = hash64(h ^ c); }
  return h;
}

// Main
void mainCase() {
  string s; // |s| <= 5000
  cin >> s;
  int nq; // <= 10^5
  cin >> nq;
  vector<string> qs(nq); // \sum |q| <= 10^6
  cin >> qs;

  int lim = 5000;
  vector<map<ull, int>> cnts(lim + 1);
  for (auto& q : qs) {
    if ((int)q.size() <= lim) {
      cnts[q.size()][getHash(q)]++;
    }
  }
  dbg(cnts);

  int n = s.size();
  vector<vector<ull>> hs(n, vector<ull>(n + 1));
  FOR(i, 0, n) {
    ull h = 0;
    FOR(j, i + 1, n + 1) {
      hs[i][j - i] = h = hash64(h ^ s[j - 1]);
    }
  }
  dbg2(hs);

  vector<ll> dp(n + 1);
  dp[0] = 1;
  FOR(i, 0, n) {
    FOR(j, i + 1, n + 1) {
      ull h = hs[i][j - i];
      dp[j] = madd(dp[j], mmul(dp[i], cnts[j - i].count(h)));
    }
  }
  dbg(dp);

  ll res = dp[n];
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  mainCase();
  return 0;
  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // FOR(i, 0, t) { mainCase(); }
  // return 0;
}

/*
python misc/run.py cses/string_algorithms/task1731/main.cpp --check

%%%% begin
ababc
4
ab
abab
c
cb
%%%%
2
%%%% end
*/
