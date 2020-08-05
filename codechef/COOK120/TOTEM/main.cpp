// AFTER CONTEST

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

//
// PROP.
//   For N <= M, A ∈ ℕ^(N.M)
//     Score(A) <= min(M, 2N) + 1
//
//   PROOF.
//     Few lemma,
//       1. Mex(S) <= |S|
//       2. Mex(S) <= max(S) + 1
//     Thus, writing Ri = Mex(i-th row) and Ci = Mex(i-th col), then,
//       Ci <= N (<= M)
//       Ri <= M
//     So, Score(A) = Mex(C1.., R1..) <= M + 1.
//     Now, assuming 2N < M, then we can see that
//       C1, ..., CM <= N,
//       |{R1,.., RN}| <= N,
//       Mex(C1.., R1..) <= Mex(0,..,N, R1,.., RN) <= 2N + 1
//
// N.B.
//   As seen below, we can construct such upper bound.
//

vector<vector<int>> solve(int n, int m) {
  // WLOG. Give construction for n <= m and transpose later.
  bool transpose = n > m;
  if (transpose) { swap(n, m); }

  vector<vector<int>> A(n, vector<int>(m, 0));
  int big = 1000; // Big enough to become irrelavant for MEX.

  if (n < m) {
    // Construction for n < m
    RANGE(i, 0, n) {
      RANGE(j, 0, m) {
        if (j < i || 2 * n <= j) {
          A[i][j] = big;
          continue;
        }
        A[i][j] = j - i;
      }
    }
  } else {
    // A bit special construction for n = m
    // (Apply same construction for (n-1)x(n) submatrix)
    RANGE(i, 0, n - 1) {
      RANGE(j, 0, n) {
        if (j < i) {
          A[i][j] = big;
          continue;
        }
        A[i][j] = j - i;
      }
    }
    // (Fill big for the last row)
    RANGE(j, 0, n) {
      A[n - 1][j] = big;
    }
  }

  if (!transpose) {
    return A;
  }

  vector<vector<int>> AT(m, vector<int>(n, 0));
  RANGE(i, 0, n) {
    RANGE(j, 0, m) {
      AT[j][i] = A[i][j];
    }
  }
  return AT;
}

void main_case() {
  int n, m;
  cin >> n >> m;
  auto result = solve(n, m);
  RANGE(i, 0, n) {
    RANGE(j, 0, m) {
      if (j) { cout << " "; }
      cout << result[i][j];
    }
    cout << endl;
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
python misc/run.py codechef/COOK120/TOTEM/main.cpp

%%%% begin
1
3 8
%%%%
%%%% end

%%%% begin
1
1 1
%%%%
%%%% end

%%%% begin
2
3 3
4 2
%%%%
9 1 0
1 0 2
7 5 8
2 2
3 0
1 1
0 1
%%%% end
*/
