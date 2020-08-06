// CONTEST, AC

#include <bits/stdc++.h>

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (decltype(X) I = (X); I < (Y); I++)
using ll = int64_t;

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
namespace std { template<class ...Ts> ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "{"; apply([&](auto&&... ys){ ((o << ys << ", "), ...); }, x); o << "}"; return o; } }
namespace std { template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; } }
namespace std { template<class T> ostream& operator<<(ostream& o, const vector<T>& x) { o << "{"; for (auto& y : x) { o << y << ", "; } o << "}"; return o; } }
namespace std { template<class T> ostream& operator<<(ostream& o, const set<T>& x) { o << "{"; for (auto& y : x) { o << y << ", "; } o << "}"; return o; } }
namespace std { template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x) { o << "{"; for (auto& yz : x) { o << yz << ", "; } o << "}"; return o; } }

// Main
using namespace std;

int solve(vector<int>& ls) {
  int n = ls.size();
  sort(ALL(ls));

  // Brute-force
  int maxi = 0;
  int maxi_arg = 0;
  RANGE(s, 0, 2 * ls.back() + 1) {
    int i0 = 0;
    int i1 = n - 1;
    int count = 0;
    while (i0 < i1) {
      int sum = ls[i0] + ls[i1];
      if (sum == s) {
        count++;
        i0++;
        i1--;
        continue;
      }
      if (sum < s) {
        i0++;
        continue;
      }
      i1--;
    }
    if (count > maxi) {
      maxi = count;
      maxi_arg = s;
    }
  }
  // DD(tie(maxi, maxi_arg)); // debug
  return maxi;
}

int main() {
  int t;
  cin >> t;
  RANGE(i, 0, t) {
    int n;
    cin >> n;
    vector<int> ls(n, 0);
    RANGE(j, 0, n) {
      cin >> ls[j];
    }
    auto result = solve(ls);
    cout << result << endl;
  }
  return 0;
}

/*
python misc/run.py codeforces/ex1399C/main.cpp --check

%%%% begin
5
5
1 2 3 4 5
8
6 6 6 6 6 6 8 8
8
1 2 2 1 2 1 1 2
3
1 3 3
6
1 1 3 4 2 2
%%%%
2
3
4
1
2
%%%% end

%%%% begin
1
2
1 1
%%%%
1
%%%% end
*/
