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

// Hash by Chris Wellons https://nullprogram.com/blog/2018/07/31/
uint32_t hash32(uint32_t x) {
  x ^= x >> 16;
  x *= 0x7feb352dU;
  x ^= x >> 15;
  x *= 0x846ca68bU;
  x ^= x >> 16;
  return x;
}
struct Hash32 { size_t operator()(int x) const { return hash32(x); }; };
struct HashArray { size_t operator()(const array<int, 2>& x) const { return hash32(hash32(x[0]) ^ x[1]); }; };

// Main
void mainCase() {
  const int n = 1e9;
  int i_beg, j_beg, i_end, j_end;
  cin >> i_beg >> j_beg >> i_end >> j_end;
  int nq;
  cin >> nq;
  vector<array<int, 3>> qs(nq); // sum segments <= 10^5
  cin >> qs;

  // Merge segments
  unordered_map<int, vector<array<int, 2>>, Hash32> segs, segs_before;
  for (auto [i, j0, j1] : qs) {
    segs_before[i].push_back({j0, j1});
  }
  for (auto& [i, js_before] : segs_before) {
    sort(ALL(js_before));
    auto& js = segs[i];
    for (auto [j0, j1] : js_before) {
      if (js.empty() || js.back()[1] + 1 < j0) {
        js.emplace_back() = {j0, -1};
      }
      js.back()[1] = j1;
    }
  }
  dbg(segs_before);
  dbg(segs);

  auto isValid = [&](int i, int j) -> bool {
    if (!segs.count(i)) { return 0; }
    auto& js = segs[i];
    auto it = lower_bound(ALL(js), array<int, 2>({j + 1, -1}));
    if (it == js.begin()) { return 0; }
    auto [j0, j1] = *prev(it);
    return j0 <= j && j <= j1;
  };

  // BFS
  deque<array<int, 2>> q;
  unordered_map<array<int, 2>, int, HashArray> dists;
  q.push_back({i_beg, j_beg});
  dists[{i_beg, j_beg}] = 1; // Use non zero for "visited" state (subtract "1" later)
  while (!q.empty()) {
    auto [i, j] = q.front(); q.pop_front();
    if (i == i_end && j == j_end) {
      break;
    }
    constexpr array<int, 2> kDirs[8] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    for (auto [di, dj] : kDirs) {
      int ii = i + di, jj = j + dj;
      if (1 <= ii && ii <= n && 1 <= jj && jj <= n) {
        if (dists.count({ii ,jj})) { continue; }
        if (!isValid(ii, jj)) { continue; }
        dists[{ii ,jj}] = dists[{i, j}] + 1;
        q.push_back({ii, jj});
      }
    }
  }
  dbg(dists);

  int res = dists[{i_end, j_end}] - 1;
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/242C/main.cpp --check

%%%% begin
5 7 6 11
3
5 3 8
6 7 11
5 2 5
%%%%
4
%%%% end

%%%% begin
3 4 3 10
3
3 1 4
4 5 9
3 10 10
%%%%
6
%%%% end

%%%% begin
1 1 2 10
2
1 1 3
2 6 10
%%%%
-1
%%%% end
*/
