// CONTEST, AC

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

// Euler sieve
tuple<vector<int>, vector<int>> makeEulerSieve(int n) {
  tuple<vector<int>, vector<int>> res;
  auto& [ps, lp] = res;
  lp.resize(n + 1);
  for (int x = 2; x <= n; x++) {
    if (lp[x] == 0) { lp[x] = x; ps.push_back(x); }
    for (auto p : ps) {
      if (x * p > n || p > lp[x]) { break; }
      lp[x * p] = p;
    }
  }
  return res;
}

// Main
void mainCase() {
  int n; // [2, 10^5]
  cin >> n;
  vector<int> ls(n); // [2, 10^5]
  cin >> ls;

  // Factorization
  int k = *max_element(ALL(ls));
  vector<int> ps, lp;
  tie(ps, lp) = makeEulerSieve(k);
  dbg(k, ps, lp);

  auto getFactors = [&](int x) -> vector<int> {
    vector<int> res;
    while (x > 1) {
      int p = lp[x];
      while (x % p == 0) { x /= p; }
      res.push_back(p);
    }
    return res;
  };

  // For each prime, find first and last occurence as factor
  const int kInf = 1e6;
  vector<array<int, 2>> segs(k + 1, {kInf, -1});
  FOR(i, 0, n) {
    int x = ls[i];
    auto fs = getFactors(x);
    dbg(x, fs);
    for (auto f : fs) {
      segs[f][0] = min(segs[f][0], i);
      segs[f][1] = max(segs[f][1], i);
    }
  }
  dbg(segs);

  // Take union of bad ranges to split
  vector<int> bads(n + 1);
  for (auto p : ps) {
    auto [l, r] = segs[p];
    if (l == kInf) { continue; }
    if (l == r) { continue; }
    // as difference array
    bads[l]++;
    bads[r]--;
  }
  FOR(i, 1, n + 1) {
    bads[i] += bads[i - 1];
  }
  dbg(bads);

  // Find smallest good "i"
  int res = 0;
  FOR(i, 0, n) {
    if (bads[i] == 0) {
      res = i;
      break;
    }
  }
  cout << (res + 1) << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codechef/LTIME89/COPAR/main.cpp

%%%% begin
1
3
2 16 7
%%%%
2
%%%% end

%%%% begin
1
4
2 3 4 5
%%%%
3
%%%% end
*/
