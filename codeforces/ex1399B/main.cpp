// CONTEST, AC

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
namespace std { template<class T> ostream& operator<<(ostream& o, const set<T>& x) { o << "{"; for (auto& y : x) { o << y << ", "; } o << "}"; return o; } }
namespace std { template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x) { o << "{"; for (auto& yz : x) { o << yz << ", "; } o << "}"; return o; } }

// Main
using namespace std;

ll solve(const vector<int>& ls1, const vector<int>& ls2) {
  int m1 = *min_element(ALL(ls1));
  int m2 = *min_element(ALL(ls2));
  // DD(tie(ls1, ls2)); // debug
  // DD(tie(m1, m2)); // debug
  int n = ls1.size();
  ll result = 0;
  RANGE(i, 0, n) {
    result += max(ls1[i] - m1, ls2[i] - m2);
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
    auto result = solve(ls1, ls2);
    cout << result << endl;
  }
  return 0;
}

/*
python misc/run.py codeforces/ex1399B/main.cpp --check

%%%% begin
5
3
3 5 6
3 2 3
5
1 2 3 4 5
5 4 3 2 1
3
1 1 1
2 2 2
6
1 1000000000 1000000000 1000000000 1000000000 1000000000
1 1 1 1 1 1
3
10 12 8
7 5 4
%%%%
6
16
0
4999999995
7
%%%% end
*/
