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
  int w, m;
  cin >> w >> m;

  // base-w digits
  vector<int> ls;
  while (m > 0) {
    ls.push_back(m % w);
    m /= w;
  }
  dbg(ls);

  // ∑_i w^i = m + ∑_j w^j
  bool ok = 1;
  int k = ls.size();
  FOR(i, 0, k) {
    int d = ls[i];
    // digit = 0 => no-op
    if (d == 0) { continue; }
    // digit = 1 => ok  [pick for w^i]
    if (d == 1) { continue; }
    // digit = w - 1 => carry by adding 1  [pick for w^j]
    if (d == w - 1) {
      ls[i]++;
      FOR(j, i, k) {
        if (ls[j] < w) { break; }
        ls[j] = 0;
        if (j + 1 < k) { ls[j + 1]++; }
      }
      continue;
    }
    ok = 0; break;
  }
  cout << (ok ? "YES" : "NO") << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/552C/main.cpp --check

%%%% begin
10 999
%%%%
YES
%%%% end

%%%% begin
2 9596
%%%%
YES
%%%% end

%%%% begin
3 7
%%%%
YES
%%%% end

%%%% begin
100 99
%%%%
YES
%%%% end

%%%% begin
100 50
%%%%
NO
%%%% end
*/
