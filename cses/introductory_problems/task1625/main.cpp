// WIP

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
// Enumerate including non-simple paths
void mainCase_v1() {
  string s;
  cin >> s;

  int n = 7;
  vector<vector<ll>> dp(n, vector<ll>(n, 0));

  dp[0][0] = 1;
  auto dp_prev = dp;
  for (auto c : s) {
    vector<array<int, 2>> dirs;
    if (c == '?') { dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; }
    if (c == 'D') { dirs = {{1, 0}}; }
    if (c == 'U') { dirs = {{-1, 0}}; }
    if (c == 'R') { dirs = {{0, 1}}; }
    if (c == 'L') { dirs = {{0, -1}}; }
    FOR(i, 0, n) {
      FOR(j, 0, n) {
        ll tmp = 0;
        for (auto [di, dj] : dirs) {
          int ii = i - di, jj = j - dj;
          if (0 <= ii && ii < n && 0 <= jj && jj < n) {
            tmp += dp_prev[ii][jj];
          }
        }
        dp[i][j] = tmp;
      }
    }
    dp_prev = dp;
    DD2(dp);
  }
}

struct Dsu {
  vector<int> data_;
  Dsu(int n) { data_.resize(n); iota(ALL(data_), 0); }
  int find(int a) {
    if (data_[a] == a) { return a; }
    return data_[a] = find(data_[a]);
  }
  void merge(int dst, int src) {
    data_[find(src)] = find(dst);
  }
  int getNumComponents() {
    map<int, int> ps;
    FOR(i, 0, (int)data_.size()) {
      ps[find(i)]++;
    }
    // DD(ps);
    return ps.size();
  }
};

void mainCase_v3() {
  string s;
  cin >> s;
  int ns = s.size();

  constexpr int n = 7;

  // Encode visited coordinate (i, j)
  auto encode1 = [](int i, int j) -> int { return i * n + j; };
  auto encode2 = [](int i, int j) -> ll { return 1L << (i * n + j); };

  // Check if non-visited coordinates are connected
  auto checkConnected = [&](ll visited) -> bool {
    Dsu dsu(n * n);
    FOR(i, 0, n) {
      FOR(j, 0, n) {
        int e1 = encode1(i, j);
        ll e2 = encode2(i, j);
        array<array<int, 2>, 4> dirs = {{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};
        for (auto [di, dj] : dirs) {
          int ii = i + di, jj = j + dj;
          if (0 <= ii && ii < n && 0 <= jj && jj < n) {
            int ee1 = encode1(ii, jj);
            ll ee2 = encode2(ii, jj);
            if ((e2 & visited) && (ee2 & visited)) { dsu.merge(e1, ee1); }
            if (!(e2 & visited) && !(ee2 & visited)) { dsu.merge(e1, ee1); }
          }
        }
      }
    }
    int nc = dsu.getNumComponents();
    // DD(nc);
    return nc == 2;
  };

  vector<tuple<int, int, ll>> queue;
  queue.push_back({0, 0, encode2(0, 0)});

  auto queue_prev = queue;
  FOR(ic, 0, ns) {
    char c = s[ic];
    queue.resize(0);
    for (auto [i, j, visited] : queue_prev) {
      vector<array<int, 2>> dirs;
      if (c == '?') { dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; }
      if (c == 'D') { dirs = {{ 1, 0}}; }
      if (c == 'U') { dirs = {{-1, 0}}; }
      if (c == 'R') { dirs = {{0,  1}}; }
      if (c == 'L') { dirs = {{0, -1}}; }
      for (auto [di, dj] : dirs) {
        int ii = i + di, jj = j + dj;
        ll ee = encode2(ii, jj);
        if (0 <= ii && ii < n && 0 <= jj && jj < n) {
          if (ee & visited) { continue; }
          if (!checkConnected(ee | visited)) { continue; }
          queue.push_back({ii, jj, ee | visited});
        }
      }
    }
    DD(tie(ic, c));
    // DD(queue);
    DD(queue.size());
    queue_prev = queue;
  }
}

// Only simple path
void mainCase_v2() {
  string s;
  cin >> s;

  int ns = s.size();
  constexpr int n = 7;

  // Encode visited coordinate (i, j)
  auto encode = [](int i, int j) -> ll { return 1L << (i * 7 + j); };

  vector<array<ll, 3>> queue;
  queue.push_back({0, 0, encode(0, 0)});

  auto queue_prev = queue;
  FOR(ic, 0, ns) {
    char c = s[ic];
    queue.resize(0);
    for (auto [i, j, visited] : queue_prev) {
      vector<array<int, 2>> dirs;
      if (c == '?') { dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; }
      if (c == 'D') { dirs = {{ 1, 0}}; }
      if (c == 'U') { dirs = {{-1, 0}}; }
      if (c == 'R') { dirs = {{0,  1}}; }
      if (c == 'L') { dirs = {{0, -1}}; }
      for (auto [di, dj] : dirs) {
        int ii = i + di, jj = j + dj;
        ll ee = encode(ii, jj);
        if (0 <= ii && ii < n && 0 <= jj && jj < n) {
          if (ee & visited) { continue; }
          queue.push_back({ii, jj, ee | visited});
        }
      }
    }
    // DD(queue);
    DD(tie(ic, c));
    DD(queue.size());
    queue_prev = queue;
  }
}

void mainCase() { mainCase_v3(); }

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
python misc/run.py cses/introductory_problems/task1625/main.cpp --check

%%%% begin
RRRDLU
%%%%
%%%% end

%%%% begin
????????????????????
%%%%
%%%% end

%%%% begin
????????????????????????????????????????????????
%%%%
%%%% end

%%%% begin
DRURRRRRDDDLUULDDDLDRRURDDLLLLLURULURRUULDLLDDDD
%%%%
%%%% end

%%%% begin
??????R??????U??????????????????????????LD????D?
%%%%
201
%%%% end
*/
