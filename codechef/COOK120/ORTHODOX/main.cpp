// AFTER EDITORIAL

#include <bits/stdc++.h>

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (decltype(X) I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
namespace std { template<class ...Ts> ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "{"; apply([&](auto&&... ys){ ((o << ys << ", "), ...); }, x); o << "}"; return o; } }
namespace std { template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; } }
namespace std { template<class T> ostream& operator<<(ostream& o, const vector<T>& x) { o << "{"; for (auto& y : x) { o << y << ", "; } o << "}"; return o; } }
namespace std { template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x) { o << "{"; for (auto& yz : x) { o << yz << ", "; } o << "}"; return o; } }

// Main
using namespace std;

bool solve(const vector<ull>& ls) {
  int n = ls.size();
  // ∀k. Ak \ ∪_{i < k} Ai ≠ ∅
  if (n > 64) {
    return 0;
  }

  // Brute-force the rest
  map<ull, int> counts;
  RANGE(i, 0, n) {
    RANGE(j, i, n) {
      ull x = 0;
      RANGE(k, i, j + 1) {
        x = x | ls[k];
      }
      counts[x]++;
    }
  }

  for (auto [_x, count] : counts) {
    if (count >= 2) {
      return 0;
    }
  }
  return 1;
}

int main() {
  int t;
  cin >> t;
  RANGE(i, 0, t) {
    int n;
    cin >> n;
    vector<ull> ls(n, 0);
    RANGE(j, 0, n) {
      cin >> ls[j];
    }
    cout << (solve(ls) ? "YES" : "NO") << endl;
  }
  return 0;
}

/*
python misc/run.py codechef/COOK120/ORTHODOX/main.cpp --check

%%%% begin
4
3
1 2 7
2
1 2
3
6 5 8
5
12 32 45 23 47
%%%%
NO
YES
YES
NO
%%%% end
*/
