// AFTER EDITORIAL, WA

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
  int n;
  cin >> n;
  vector<int> ls(n);
  cin >> ls;

  // cf. maximum histogram rectangle
  vector<int> hi(n, -1); // longest jump high
  vector<int> lo(n, -1); // longest jump low
  {
    // High
    vector<array<int, 2>> st; // (index, height)
    FOR(i, 0, n) {
      while (!st.empty() && st.back()[1] >= ls[i]) {
        auto [j, _h] = st.back(); st.pop_back();
        hi[j] = i;
      }
      st.push_back({i, ls[i]});
    }
    // (Need another pass for taking care of remaining "st")
    st.clear();
    for (int i = n - 1; i >= 0; i--) {
      while (!st.empty() && st.back()[1] >= ls[i]) {
        auto [j, _h] = st.back(); st.pop_back();
        if (hi[i] == -1) { hi[i] = j; } // such "i" is from reaming "st" in 1st pass.
      }
      st.push_back({i, ls[i]});
    }

    // Low
    st.clear();
    FOR(i, 0, n) {
      while (!st.empty() && st.back()[1] <= ls[i]) {
        auto [j, _h] = st.back(); st.pop_back();
        lo[j] = i;
      }
      st.push_back({i, ls[i]});
    }
    st.clear();
    for (int i = n - 1; i >= 0; i--) {
      while (!st.empty() && st.back()[1] <= ls[i]) {
        auto [j, _h] = st.back(); st.pop_back();
        if (lo[i] == -1) { lo[i] = j; }
      }
      st.push_back({i, ls[i]});
    }
  }
  dbg(ls);
  dbg(hi);
  dbg(lo);
  FOR(i, 0, n - 1) {
    assert(hi[i] != -1);
    assert(lo[i] != -1);
  }

  //
  // CONJ. (it seems incorrect)
  //   It suffices to consider high/low longest jump and single jump.
  //

  int kInf = 1 << 30;
  vector<int> dp(n, kInf);
  auto mineq = [](int& x, int y) -> int { return x = min(x, y); };

  dp[0] = 0;
  FOR(i, 0, n - 1) {
    mineq(dp[lo[i]], dp[i] + 1);
    mineq(dp[hi[i]], dp[i] + 1);
    mineq(dp[i + 1], dp[i] + 1);
  }

  int res = dp[n - 1];
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest669/d/main_v2.cpp --check

%%%% begin
5
1 3 1 4 5
%%%%
3
%%%% end

%%%% begin
4
4 2 2 4
%%%%
1
%%%% end

%%%% begin
2
1 1
%%%%
1
%%%% end

%%%% begin
5
100 1 100 1 100
%%%%
2
%%%% end
*/
