// AFTER EDITORIAL, AC

//
// PROP.
//   Define
//     F(b) = {x | fs(x) = b }
//     G(b) = {x | fs(x) > b and x[b] = 1 }
//   Then
//     ⨆_b F(b) x G(b) = {(x, y) | x != 0 ∧ (x <= (x xor y) <= y)}  (note that union at LHS is disjoint)
//
// N.B.
//   - We need to take into account "x = 0" separately,
//   - Here, we need to consider "range" counter part F(b, l, r), G(b, l, r)
//     but they can be quickly computed via cumulative counting.
//

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
template<class ...Ts> ostream&        operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T> ostream&            operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }

// Main
vector<ll> solve(vector<uint>& ls, vector<tuple<int, int>>& qs) {
  int n = ls.size();

  // Find first set (-1 for zero)
  vector<int> fs(n, -1);
  RANGE(i, 0, n) {
    uint x = ls[i];
    RANGE(b, 0, 32) {
      if (x & 1) { fs[i] = b; }
      x >>= 1;
    }
  }

  // Cumulative count for F
  vector<vector<int>> F(32, vector<int>(n + 1, 0));
  RANGE(b, 0, 32) {
    RANGE(i, 0, n) {
      F[b][i + 1] = F[b][i] + (fs[i] == b);
    }
  }

  // Cumulative count for G
  vector<vector<int>> G(32, vector<int>(n + 1, 0));
  RANGE(b, 0, 32) {
    RANGE(i, 0, n) {
      G[b][i + 1] = G[b][i] + (fs[i] > b && ((ls[i] >> b) & 1));
    }
  }

  // Cumulative count for zero
  vector<int> Z(n + 1, 0);
  RANGE(i, 0, n) {
    Z[i + 1] = Z[i] + (ls[i] == 0);
  }

  #ifdef DEBUG
    DD(ls);
    DD(fs);
    DD(Z);
    DD(F);
    DD(G);
  #endif

  // Answer queries
  int nq = qs.size();
  vector<ll> result(nq, 0);
  RANGE(iq, 0, nq) {
    auto [l, r] = qs[iq];
    l--; // To zero-based
    result[iq] += (ll)(Z[r] - Z[l]) * (r - l);
    RANGE(b, 0, 32) {
      result[iq] += (ll)(F[b][r] - F[b][l]) * (G[b][r] - G[b][l]);
    }
  }
  return result;
}

void main_case() {
  int n, q; // <= 10^6
  cin >> n >> q;

  vector<uint> ls(n, 0); // <= 2^30
  RANGE(j, 0, n) {
    cin >> ls[j];
  }

  vector<tuple<int, int>> qs(q, {0, 0});
  RANGE(j, 0, q) {
    cin >> get<0>(qs[j]) >> get<1>(qs[j]);
  }

  auto result = solve(ls, qs);
  for (auto r : result) {
    cout << r << endl;
  }
}

int main() {
  int t;
  cin >> t;
  RANGE(i, 0, t) {
    main_case();
  }
}

/*
python misc/run.py codechef/COOK120/XORCIST/main_v2.cpp --check

%%%% begin
1
3 1
0 0 0
1 3
%%%%
9
%%%% end

%%%% begin
1
6 1
2 7 1 5 2
1 6
%%%%
4
%%%% end

%%%% begin
2
5 4
2 7 1 5 2
1 5
2 3
4 5
2 4
10 1
123 667 232 989 0 104 305 329 567 345
1 10
%%%%
4
1
0
2
23
%%%% end
*/
