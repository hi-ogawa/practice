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
  int n; // [1, 5x10^5]
  cin >> n;
  vector<ll> ls(n); // [1, 10^9]
  cin >> ls;

  // lefts[i]  = max { j < i | ls[j] <= ls[i] }
  // rights[i] = max { j > i | ls[j] <= ls[i] }
  vector<int> lefts(n, -1);
  vector<int> rights(n, n);
  {
    // For "lefts"
    vector<array<ll, 2>> st; // (index, height)
    st.push_back({-1, 0}); // dummy minimum at left most
    FOR(i, 0, n) {
      while (!st.empty() && st.back()[1] > ls[i]) { st.pop_back(); }
      lefts[i] = st.back()[0];
      st.push_back({i, ls[i]});
    }
    // for "rights"
    st.clear();
    st.push_back({n, 0}); // dummy minimum at right most
    for (int i = n - 1; i >= 0; i--) {
      while (!st.empty() && st.back()[1] > ls[i]) { st.pop_back(); }
      rights[i] = st.back()[0];
      st.push_back({i, ls[i]});
    }
  }
  dbg(lefts);
  dbg(rights);

  // Cum sum
  vector<ll> sums(n + 1);
  FOR(i, 0, n) { sums[i + 1] = sums[i] + ls[i]; }

  // Precompute "left incr. fix cost" and "right decr. fix cost"
  vector<ll> ps(n), qs(n);
  FOR(i, 1, n) {
    int j = lefts[i];
    if (j != -1) { ps[i] = ps[j]; }
    ps[i] += sums[i + 1] - sums[j + 1] - ls[i] * (i - j); // Cutting down the excess of ls[i+1]...ls[j]
  }
  for (int i = n - 2; i >= 0; i--) {
    int j = rights[i];
    if (j != n) { qs[i] = qs[j]; }
    qs[i] += sums[j] - sums[i] - ls[i] * (j - i);
  }
  dbg(ps);
  dbg(qs);

  // Min fix cost to make "i"-pyramid  (min fix cost <=> max count)
  ll c_res = 1ULL << 62;
  int i_res = 0;
  FOR(i, 0, n) {
    ll tmp = ps[i] + qs[i];
    if (tmp < c_res) {
      c_res = tmp;
      i_res = i;
    }
  }
  dbgv(i_res, c_res);

  // Make "i"-pyramid
  vector<ll> res(n);
  res[i_res] = ls[i_res];
  for (int i = i_res - 1; i >= 0; i--) {
    res[i] = min(ls[i], res[i + 1]);
  }
  for (int i = i_res + 1; i < n; i++) {
    res[i] = min(ls[i], res[i - 1]);
  }
  dbg(res);

  FOR(i, 0, n) {
    cout << res[i] << " \n"[i == n -1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1313C2/main.cpp --check

%%%% begin
5
1 2 3 2 1
%%%%
1 2 3 2 1
%%%% end

%%%% begin
3
10 6 8
%%%%
10 6 6
%%%% end
*/
