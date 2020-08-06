// AFTER CONTEST, AC

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
    sort(ALL(ls));
    bool result = true;
    RANGE(j, 0, n - 1) {
      if (ls[j] <= ls[j + 1] - 2) {
        result = false;
        break;
      }
    }
    cout << (result ? "YES" : "NO") << endl;
  }
  return 0;
}

/*
python misc/run.py codeforces/ex1399A/main_v2.cpp --check

%%%% begin
5
3
1 2 2
4
5 5 5 5
3
1 2 4
4
1 3 4 4
1
100
%%%%
YES
YES
NO
NO
YES
%%%% end
*/
