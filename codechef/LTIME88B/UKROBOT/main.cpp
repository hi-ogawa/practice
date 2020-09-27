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

void check(int w, int h, const string& s) {
  map<char, array<int, 2>> kMoves = {
    {'L', {-1, 0}}, {'R', {1, 0}}, {'D', {0, -1}}, {'U', {0, 1}}};

  auto run = [&](int x0, int y0) -> array<int, 2> {
    int x = 0, y = 0;
    for (auto c : s) {
      auto [dx, dy] = kMoves[c];
      if (x + dx == x0 && y + dy == y0) { continue; }
      x += dx; y += dy;
    }
    return {x, y};
  };

  vector<vector<array<int, 2>>> res(w + 1, vector<array<int, 2>>(h + 1));
  FOR(x, 1, w + 1) {
    FOR(y, 1, h + 1) {
      res[x][y] = run(x, y);
    }
  }
  dbg2(res);
}

// Main
void mainCase() {
  int h, w; // [1, 20]
  cin >> h >> w;

  // NOTE: All obstacle positions generate different number of "blocked up-moves"
  string res;
  FOR(x, 1, w + 1) {
    // Sweep each vertical line by different multiple of "up moves"
    res += 'R';
    res += string(x * h, 'U');
    res += string(x * h, 'D');
  }
  cout << res << "\n";

  if (DEBUG) {
    check(w, h, res);
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codechef/LTIME88B/UKROBOT/main.cpp --check

%%%% begin
2 2
%%%%
RUUDDRUUUUDDDD
%%%% end

%%%% begin
1 2
%%%%
UR
%%%% end
*/
