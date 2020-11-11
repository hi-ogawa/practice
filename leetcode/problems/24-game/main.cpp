// AC

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

using Real = double;
const Real kEps = 1e-10;

// Main
bool mainSolve(vector<int>& ls, int target) {

  function<vector<Real>(int, int)> evaluate = [&](int l, int r) -> vector<Real> {
    vector<Real> res;
    if (l + 1 == r) {
      res.push_back(ls[l]);
      return res;
    }
    FOR(k, l + 1, r) {
      auto res1 = evaluate(l, k);
      auto res2 = evaluate(k, r);
      for (auto x : res1) {
        for (auto y : res2) {
          res.push_back(x + y);
          res.push_back(x - y);
          res.push_back(x * y);
          if (y != 0) {
            res.push_back(x / y);
          }
        }
      }
    }
    return res;
  };

  // Enumerate all evaluations
  int n = ls.size();
  sort(ALL(ls));
  do {
    auto res = evaluate(0, n);
    for (auto x : res) {
      if (abs(target - x) < kEps) {
        return 1;
      }
    }
  } while (next_permutation(ALL(ls)));
  return 0;
}

// Submission
class Solution {
  public:
    bool judgePoint24(vector<int>& nums) {
      return mainSolve(nums, 24);
    }
};


// Testing
void mainCase() {
  int n, x;
  cin >> n >> x;
  vector<int> ls(n);
  cin >> ls;
  bool res = mainSolve(ls, x);
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py leetcode/problems/24-game/main.cpp

%%%% begin
4 24
4 1 8 7
%%%%
1
%%%% end

%%%% begin
4 24
1 2 1 2
%%%%
0
%%%% end
*/
