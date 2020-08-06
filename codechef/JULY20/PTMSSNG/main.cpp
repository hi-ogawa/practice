// VC, AC

#include <bits/stdc++.h>

// Utils
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (decltype(X) I = (X); I < (Y); I++)

// Debugging
#define PP(X) std::cout << #X ": " << (X) << std::endl
#define PPP(X) std::cout << #X ": {"; for (auto x : X) { std::cout << x << ", "; } std::cout << "}" << std::endl;
namespace std { template<typename ...Tp> std::ostream& operator<<(std::ostream& o, const std::tuple<Tp...>& x) { o << "("; std::apply([&](auto&&... ys){ ((o << ys << ", "), ...); }, x); o << ")"; return o; } }

// Main
using namespace std;

tuple<int, int> solve(const vector<tuple<int, int>>& ls) {
  set<int> xs;
  set<int> ys;
  for (auto [x, y] : ls) {
    xs.count(x) ? (void)xs.erase(x) : (void)xs.insert(x);
    ys.count(y) ? (void)ys.erase(y) : (void)ys.insert(y);
  }
  assert(xs.size() == 1);
  assert(ys.size() == 1);
  return {*xs.begin(), *ys.begin()};
}

int main() {
  int t;
  cin >> t;
  RANGE(i, 0, t) {
    int n;
    cin >> n;
    vector<tuple<int, int>> ls(4 * n - 1, {0, 0});
    RANGE(j, 0, 4 * n - 1) {
      cin >> get<0>(ls[j]) >> get<1>(ls[j]);
    }
    auto [x, y] = solve(ls);
    cout << x << " " << y << endl;
  }
  return 0;
}

/*
python misc/run.py codechef/JULY20/PTMSSNG/main.cpp --check

%%%% begin
1
2
1 1
1 2
4 6
2 1
9 6
9 3
4 3
%%%%
2 2
%%%% end
*/
