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
#ifndef DEBUG
#define DEBUG 0
#endif
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  int n; // [4, 1000], 4 | n
  cin >> n;
  int m = n / 4;

  // Copy 4x4 block with multiplicity 1, 2, .. m
  vector<vector<int>> res(n, vector<int>(n));
  FOR(ki, 0, m) {
    FOR(kj, 0, m) {
      FOR(i, 0, 4) {
        FOR(j, 0, 4) {
          res[ki * 4 + i][kj * 4 + j] = (i * 4 + j) + 16 * ((ki * m) + kj);
        }
      }
    }
  }
  dbg2(res);

  auto check = [&]() {
    vector<int> rows(n);
    vector<int> cols(n);
    FOR(i, 0, n) {
      FOR(j, 0, n) { rows[i] ^= res[i][j]; }
    }
    FOR(j, 0, n) {
      FOR(i, 0, n) { cols[j] ^= res[i][j]; }
    }
    dbg(rows);
    dbg(cols);
    assert(count(ALL(rows), 0) == n);
    assert(count(ALL(cols), 0) == n);
  };
  check();

  FOR(i, 0, n) {
    FOR(j, 0, n) {
      cout << res[i][j] << " \n"[j == n - 1];
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1208C/main.cpp --check

%%%% begin
12
%%%%
0 1 2 3 16 17 18 19 32 33 34 35
4 5 6 7 20 21 22 23 36 37 38 39
8 9 10 11 24 25 26 27 40 41 42 43
12 13 14 15 28 29 30 31 44 45 46 47
48 49 50 51 64 65 66 67 80 81 82 83
52 53 54 55 68 69 70 71 84 85 86 87
56 57 58 59 72 73 74 75 88 89 90 91
60 61 62 63 76 77 78 79 92 93 94 95
96 97 98 99 112 113 114 115 128 129 130 131
100 101 102 103 116 117 118 119 132 133 134 135
104 105 106 107 120 121 122 123 136 137 138 139
108 109 110 111 124 125 126 127 140 141 142 143
%%%% end
*/
