// WIP

#include <bits/stdc++.h>

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (decltype(X) I = (X); I < (Y); I++)
using ll = int64_t;

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl
namespace std { template<class ...Ts> ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "{"; apply([&](auto&&... ys){ ((o << ys << ", "), ...); }, x); o << "}"; return o; } }
namespace std { template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; } }
namespace std { template<class T> ostream& operator<<(ostream& o, const vector<T>& x) { o << "{"; for (auto& y : x) { o << y << ", "; } o << "}"; return o; } }
namespace std { template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x) { o << "{"; for (auto& yz : x) { o << yz << ", "; } o << "}"; return o; } }

// Main
using namespace std;

ll solve(vector<int>& ls1, vector<int>& ls2) {
  map<int, int> counts;
  for (auto x : ls1) counts[x]++;
  for (auto x : ls2) counts[x]++;

  // Check if solvable (i.e. we can separate each distinct element)
  for (auto& [_x, c] : counts) {
    if (c % 2 == 1) {
      return -1;
    }
  }

  // Fix up from larger pairs
  // TODO: This doesn't feel optimal but cannot find counter example.
  // A: 2  3 3     100 100
  // B: 2      4 4          101 101
  sort(ALL(ls1));
  sort(ALL(ls2));
  int mini = (*counts.begin()).first;
  int n = ls1.size();
  ll result = 0;
  for (int i = n - 1; i >= 0; i--) {
    int a = ls1[i];
    int b = ls2[i];
    if (a == b) { continue; }

    // single swap a and b vs. double swap via minimal element
    result = min(min(a, b), 2 * mini);
    i--;
  }
  return result;
}

int main() {
  int t;
  cin >> t;
  RANGE(i, 0, t) {
    int n;
    cin >> n;
    vector<int> ls1(n, 0);
    vector<int> ls2(n, 0);
    RANGE(j, 0, n) {
      cin >> ls1[j];
    }
    RANGE(j, 0, n) {
      cin >> ls2[j];
    }
    cout << solve(ls1, ls2) << endl;
  }
  return 0;
}

/*
python misc/run.py codechef/JULY20/CHFNSWPS/main.cpp --check

%%%% begin
3
1
1
2
2
1 2
2 1
2
1 1
2 2
%%%%
-1
0
1
%%%% end
*/
