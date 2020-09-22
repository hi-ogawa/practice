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

vector<array<int, 2>> factorize(int n) {
  vector<array<int, 2>> res;
  for (int p = 2; p * p <= n; p++) {
    if (n % p == 0) {
      int e = 0;
      while (n % p == 0) { e++; n /= p; }
      res.push_back({p, e});
    }
  }
  if (n > 1) { res.push_back({n, 1}); }
  return res;
}

vector<int> generate(const vector<array<int, 2>>& factors) {
  vector<int> res;
  int k = factors.size();
  function<void(int, int)> rec = [&](int i, int x) {
    if (i == k) { res.push_back(x); return; }
    auto [p, e] = factors[i];
    FOR(j, 0, e + 1) {
      rec(i + 1, x);
      x *= p;
    }
  };
  rec(0, 1);
  return res;
}

// Main
void mainCase() {
  int n; // [4, 10^9]
  cin >> n;

  auto fs = factorize(n);

  vector<int> res;
  int res2 = 0;
  dbgv(n, fs);

  if (fs.size() == 1) {
    fs[0][1]--;
    auto xs = generate(fs);
    int p = fs[0][0];
    for (auto x : xs) {
      res.push_back(x * p);
    }
  }

  if (fs.size() == 2) {
    // Only this case, it necessarily have prime neighbors
    if (fs[0][1] == 1 && fs[1][1] == 1) {
      res2 = 1;
      res.push_back(fs[0][0]);
      res.push_back(fs[1][0]);
      res.push_back(fs[0][0] * fs[1][0]);
    } else {
      if (fs[0][1] == 1) { swap(fs[0], fs[1]); }
      fs[0][1]--;
      vector<int> xs = generate(fs);
      int p = fs[0][0];
      int q = fs[1][0];
      for (auto x : xs) { // divisors "p ..." except "p q"
        if (x == q) { continue; }
        res.push_back(p * x);
      }
      res.push_back(q);
      res.push_back(p * q);
    }
  }

  if (fs.size() >= 3) {
    int k = fs.size();
    FOR(i, 0, k) {
      int p = fs[i][0];
      int q = fs[(i + 1) % k][0];
      fs[i][1]--;
      auto xs = generate(fs);
      fs[i][1] = 0;
      dbgv(p, xs);
      for (auto x : xs) { // divosors "p ..." except "p q"
        if (x == q) { continue; }
        if (i == 0 && x == fs[k - 1][0]) { continue; } // also except "p1 pk" to connect to last
        res.push_back(p * x);
      }
      res.push_back(p * q);
    }
  }

  int nn = res.size();
  FOR(i, 0, nn) {
    cout << res[i] << " \n"[i == nn - 1];
  }
  cout << res2 << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest671/e/main.cpp --check

%%%% begin
1
18
%%%%
3 9 18 2 6
0
%%%% end

%%%% begin
1
30
%%%%
2 30 6 3 15 5 10
0
%%%% end

%%%% begin
1
12
%%%%
2 4 12 3 6
0
%%%% end

%%%% begin
3
6
4
30
%%%%
2 3 6
1
2 4
0
2 30 6 3 15 5 10
0
%%%% end
*/
