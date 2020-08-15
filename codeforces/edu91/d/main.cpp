// AFTER CONTEST, AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T>            istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
template<class T, size_t N>  istream& operator>>(istream& i, array<T, N>& x)  { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T, size_t N>  ostream& operator<<(ostream& o, const array<T, N>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  ll n, m, x, k, y;
  cin >> n >> m >> x >> k >> y;

  vector<ll> ls1(n, 0);
  vector<ll> ls2(m, 0);
  cin >> ls1 >> ls2;
  // DD(tie(ls1, ls2));

  // Check and decompose subsequence
  bool subseq_ok = 1;
  vector<int> subseq;
  {
    int i = 0;
    FOR(j, 0, m) {
      while (i < n && ls1[i] != ls2[j]) { i++; }
      if (i == n) {
        subseq_ok = 0;
        break;
      }
      subseq.push_back(i);
    }
  }
  if (!subseq_ok) {
    cout << -1 << endl;
    return;
  }
  // DD(subseq);

  // Find minimum for each component
  auto solve = [&](ll i0, ll i1) -> ll {
    ll a0 = -1;
    ll a1 = -1;
    if (i0 - 1 >= 0) { a0 = ls1[i0 - 1]; }
    if (i1 + 1 <  n) { a1 = ls1[i1 + 1]; }
    ll size = i1 - i0 + 1;
    ll maxi = *max_element(ls1.begin() + i0, ls1.begin() + i1 + 1);
    ll res = numeric_limits<ll>::max();

    // Brute force strategy (p-times "x" and q-times "y")
    if (maxi < max(a0, a1)) {
      // (p, q) = (0, size) strategy is available only when maxi < max(a0, a1)
      res = min(res, size * y);
    }
    FOR(p, 1, size / k + 1) {
      int q = size - p * k;
      res = min(res, p * x + q * y);
    }
    // DD(tie(i0, i1, res));

    // Strategy not found
    if (res == numeric_limits<ll>::max()) { return -1; }

    return res;
  };

  ll res = 0;
  // Handle left-end
  if (subseq[0] > 0) {
    ll tmp = solve(0, subseq[0] - 1);
    if (tmp == -1) {
      cout << -1 << endl;
      return;
    }
    res += tmp;
  }
  // Handle middles
  FOR(i, 0, m - 1) {
    if (subseq[i] + 1 == subseq[i + 1]) { continue; }
    ll tmp = solve(subseq[i] + 1, subseq[i + 1] - 1);
    if (tmp == -1) {
      cout << -1 << endl;
      return;
    }
    res += tmp;
  }
  // Handle right-end
  if (subseq[m - 1] < n - 1) {
    ll tmp = solve(subseq[m - 1] + 1, n - 1);
    if (tmp == -1) {
      cout << -1 << endl;
      return;
    }
    res += tmp;
  }
  cout << res << endl;
}

int main() {
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
python misc/run.py codeforces/edu91/d/main.cpp --check

%%%% begin
5 2
5 2 3
3 1 4 5 2
3 5
%%%%
8
%%%% end

%%%% begin
4 4
5 1 4
4 3 1 2
2 4 3 1
%%%%
-1
%%%% end

%%%% begin
4 4
2 1 11
1 3 2 4
1 3 2 4
%%%%
0
%%%% end
*/
