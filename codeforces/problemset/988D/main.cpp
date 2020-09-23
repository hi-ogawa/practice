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
  int n;
  cin >> n;
  vector<ll> ls(n); // distinct
  cin >> ls;
  sort(ALL(ls));

  auto solve = [&](ll d) -> vector<int> {
    map<ll, vector<int>> chains;
    int res1 = 0;
    ll res2 = 0;
    FOR(i, 0, n) {
      ll x = ls[i];
      if (chains.count(x - d)) {
        chains[x] = chains[x - d];
        chains.erase(x - d);
      }
      chains[x].push_back(i);
      if ((int)chains[x].size() > res1) {
        res1 = chains[x].size();
        res2 = x;
      }
      if (res1 == 3) { return chains[x]; }
    }
    return chains[res2];
  };

  int res1 = 0;
  vector<int> res2;
  FOR(b, 0, 32) {
    ll d = 1LL << b;
    auto tmp = solve(d);
    if ((int)tmp.size() > res1) {
      res1 = tmp.size();
      res2 = tmp;
    }
  }
  dbgv(res1, res2);

  int k = res2.size();
  cout << k << endl;
  FOR(i, 0, k) {
    cout << ls[res2[i]] << " \n"[i == k - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/988D/main.cpp --check

%%%% begin
6
3 5 4 7 10 12
%%%%
3
7 3 5
%%%% end

%%%% begin
5
-1 2 5 8 11
%%%%
1
8
%%%% end
*/
