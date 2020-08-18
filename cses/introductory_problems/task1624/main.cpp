// AC

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
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  vector<vector<char>> board(8, vector<char>(8, '?'));
  cin >> board;
  // DD2(board);

  auto checkBoard = [&](array<int, 8>& perm) -> bool {
    FOR(i, 0, 8) {
      if (board[i][perm[i]] == '*') {
        return 0;
      }
    }
    return 1;
  };

  auto checkDiagonal = [](array<int, 8>& perm) -> bool {
    FOR(i, 0, 8) {
      FOR(j, i + 1, 8) {
        if ((j - i) == abs(perm[i] - perm[j])) {
          return 0;
        }
      }
    }
    return 1;
  };

  // Inversion-based enumeration of permutation group
  function<ll(int, array<int, 8>&)>
  enumerateRec = [&](int i, array<int, 8>& perm) {
    if (i == 8) {
      ll ok = checkBoard(perm) && checkDiagonal(perm);
      return ok;
    }
    ll res = 0;
    res += enumerateRec(i + 1, perm); // Keep perm[i]
    FOR(j, i + 1, 8) {
      swap(perm[i], perm[j]);
      res += enumerateRec(i + 1, perm); // Inversion perm[i] <=> perm[j]
      swap(perm[i], perm[j]);
    }
    return res;
  };

  auto enumerate = [&]() -> ll {
    array<int, 8> perm;
    iota(ALL(perm), 0);
    return enumerateRec(0, perm);
  };

  ll res = enumerate();
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
python misc/run.py cses/introductory_problems/task1624/main.cpp --check

%%%% begin
........
........
..*.....
........
........
.....**.
...*....
........
%%%%
65
%%%% end
*/
