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

// Modulo op
constexpr ll kModulo = 1000000000 + 7;
ll madd(ll x, ll y) { return (x + y) % kModulo; }
ll mmul(ll x, ll y) { return (x * y) % kModulo; }

// Main
void mainCase() {
  ll n, k; // <= 10^5
  cin >> n >> k;

  vector<ll> ls(n, 0); // <= 10^5
  cin >> ls;

  // Count each types occurence
  sort(ALL(ls));
  vector<ll> counts;
  counts.push_back(1);
  RANGE(i, 1, n) {
    if (ls[i] != ls[i - 1]) { counts.push_back(0); }
    counts.back()++;
  }
  ll m = counts.size(); // <= π(8000) = 1007
  // DD(m);
  // DD(counts);

  // Operate inplace row-by-row for DP[i, j]
  vector<ll> dp(k + 1, 0);
  dp[0] = 1;
  RANGE(i, 0, m) {
    ll c = counts[i];
    for (int j = k - 1; j >= 0; j--) {
      dp[j + 1] = madd(dp[j + 1], mmul(dp[j], c));
    }
    // DD(dp);
  }

  cout << accumulate(ALL(dp), 0, madd) << endl;
}

int main() {
  // [ Single case ]
  mainCase();
  return 0;

  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // RANGE(i, 0, t) mainCase();
  // return 0;
}

/*
python misc/run.py codechef/LRNDSA07/GDSUB/main.cpp --check

%%%% begin
5 3
2 2 3 3 5
%%%%
18
%%%% end
*/
