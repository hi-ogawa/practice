// AFTER EDITORIAL, AC

// NOTE: Run task1142 for each "height sub matrix"

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
template<typename T> struct is_container {
template<typename C> static char test(typename C::const_iterator*); template<typename> static int test(...);
static bool const value = sizeof(test<T>(nullptr)) == sizeof(char) && !std::is_same<std::string, T>::value;
};
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#define DD(X) do { cout << #X ": " << (X) << endl << flush; } while (0)
#define DD2(X) do { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } while (0)
#define DDX(...) do { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  int n, m; // <= 10^3
  cin >> n >> m;
  vector<vector<char>> board(n, vector<char>(m, '?'));
  cin >> board;
  // DD2(board);

  // Solve task1142
  auto solve = [&](const vector<int>& ls) -> int {
    vector<int> rights(m, m);
    {
      vector<tuple<int, int>> st;
      FOR(i, 0, m) {
        while (!st.empty() && get<0>(st.back()) > ls[i]) {
          auto [_v, j] = st.back(); st.pop_back();
          rights[j] = i;
        }
        st.push_back({ls[i], i});
      }
    }
    vector<int> lefts(m, -1);
    {
      vector<tuple<int, int>> st;
      for (int i = m - 1; i >= 0; i--) {
        while (!st.empty() && get<0>(st.back()) > ls[i]) {
          auto [_v, j] = st.back(); st.pop_back();
          lefts[j] = i;
        }
        st.push_back({ls[i], i});
      }
    }
    int res = 0;
    FOR(i, 0, m) {
      int tmp = ls[i] * (rights[i] - lefts[i] - 1);
      res = max(res, tmp);
    }
    // DD(ls); DD(lefts); DD(rights); DD(res);
    return res;
  };

  vector<int> ls(m, 0); // Max height from the ground at "i"
  int res = 0;
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      ls[j] = board[i][j] == '.' ? (ls[j] + 1) : 0;
    }
    res = max(res, solve(ls));
  }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
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
python misc/run.py cses/additional_problems/task1147/main.cpp --check

%%%% begin
4 7
...*.*.
.*.....
.......
......*
%%%%
12
%%%% end
*/
