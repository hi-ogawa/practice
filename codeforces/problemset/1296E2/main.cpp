// WA

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
  int n; // [1, 2x10^5]
  cin >> n;
  string s;
  cin >> s;

  const int k = 26;
  vector<list<int>> ps(k);
  FOR(i, 0, n) {
    ps[s[i] - 'a'].push_back(i);
  }

  // Resolve inversion from small characters on the tail
  vector<int> cs(k, -1);
  vector<int> res(n, -1);
  function<void(int, int, int)> dfs = [&](int t, int i, int c) {
    FOR(tt, t + 1, k) {
      for (auto it = ps[tt].begin(); it != ps[tt].end(); ) {
        int j = *it;
        if (j > i) { break; }
        // Found inversion (i < j) && (s[j] > s[i])
        assert(res[j] == -1);
        dbgv(t, tt, i, j, c);
        it = ps[tt].erase(it);
        res[j] = c + 1;
        dfs(tt, j, c + 1);
      }
    }
  };

  FOR(t, 0, k) {
    for (auto it = ps[t].begin(); it != ps[t].end(); it++) {
      int i = *it;
      assert(res[i] == -1);
      res[i] = 0;
      dfs(t, i, 0);
    }
  }

  if (DEBUG) {
    FOR(i, 0, n) {
      cout << setfill(' ') << setw(2) << (int)(s[i] - 'a') << " \n"[i == n - 1];
    }
    FOR(i, 0, n) {
      cout << setfill(' ') << setw(2) << res[i] << " \n"[i == n - 1];
    }
    return;
  }

  int res2 = *max_element(ALL(res));
  cout << (res2 + 1) << endl;
  FOR(i, 0, n) {
    cout << (res[i] + 1) << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1296E2/main.cpp --check

%%%% begin
4
dacb
%%%%
%%%% end

%%%% begin
9
abacbecfd
%%%%
2
1 1 2 1 2 1 2 1 2
%%%% end

%%%% begin
8
aaabbcbb
%%%%
2
1 2 1 2 1 2 1 1
%%%% end

%%%% begin
7
abcdedc
%%%%
3
1 1 1 1 1 2 3
%%%% end

%%%% begin
5
abcde
%%%%
1
1 1 1 1 1
%%%% end
*/
