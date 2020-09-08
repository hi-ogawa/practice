// AC

// NOTE: Less error prone implementation of median tracking (compared to main_v2.cpp)
// cf. codeforces/edu93/e/main.cpp

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
  int n, k; // <= 10^6
  cin >> n >> k;
  vector<int> ls(n);
  cin >> ls;

  int m = (k + 1) / 2;
  multiset<int> smalls, bigs;
  auto insert = [&](int x) {
    if (bigs.size() == 0 || x < *bigs.begin()) {
      smalls.insert(x);
    } else {
      bigs.insert(x);
    }
  };
  auto erase = [&](int x) {
    if (bigs.count(x)) {
      bigs.erase(bigs.find(x));
    } else {
      smalls.erase(smalls.find(x));
    }
  };
  auto correct = [&]() {
    while ((int)smalls.size() < m) {
      smalls.insert(*bigs.begin());
      bigs.erase(bigs.begin());
    }
    while ((int)smalls.size() > m) {
      bigs.insert(*--smalls.end());
      smalls.erase(--smalls.end());
    }
  };

  vector<int> res;
  smalls.insert(ls.begin(), ls.begin() + k);
  correct();
  res.push_back(*--smalls.end());
  dbgv(smalls, bigs);

  FOR(i, 0, n - k) {
    erase(ls[i]);
    insert(ls[i + k]);
    correct();
    res.push_back(*--smalls.end());
    dbgv(smalls, bigs);
  }

  FOR(i, 0, n - k + 1) {
    if (i) cout << " ";
    cout << res[i];
  }
  cout << endl;
}

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
python misc/run.py cses/sorting_and_searching/task1076/main_v3.cpp --check

%%%% begin
10 9
8 10 6 1 5 10 1 3 4 2
%%%%
5 4
%%%% end

%%%% begin
8 3
2 4 3 5 8 1 2 1
%%%%
3 4 5 5 2 1
%%%% end
*/
