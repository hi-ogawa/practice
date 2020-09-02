// WA

// NOTE: hoping something will happen, but this clearly doesn't work. (see 1st test case)

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
  int n; // <= 10^3
  cin >> n;
  vector<int> ls(n);
  cin >> ls;

  vector<int> res;

  // 1. Convert to Mex(ls) = n (i.e. ls = permutation{0, 1, .., n - 1})
  {
    map<int, int> cnts;
    set<tuple<int, int>> ps;
    vector<int> dups;
    FOR(i, 0, n) {
      cnts[ls[i]]++;
      if (cnts[ls[i]] >= 2) {
        dups.push_back(i);
      } else {
        ps.insert({ls[i], i});
      }
    }

    FOR(m, 0, n) {
      if (cnts[m] > 0) { continue; }
      if (!dups.empty()) {
        int i = dups.back(); dups.pop_back();
        res.push_back(i);
        cnts[ls[i]]--;
        ls[i] = m;
        continue;
      }
      ps.erase(ps.begin(), ps.lower_bound({m, 0}));
      for (auto [x, i] : ps) {
        res.push_back(i);
        ls[i] = m;
        cnts[x]--;
        ps.erase({x, i});
        break;
      }
    }
    dbg(ls);
    dbg(res);
  }

  // 2. Fix from large value
  int k = n - 1;
  while (k >= 0 && ls[k] == k) {
    res.push_back(k);
    ls[k] = k + 1;
    k--;
  }
  dbg(ls);
  dbg(res);

  if (k >= 0) {
    dbg(k);
    set<int> qs;
    FOR(i, 0, k + 1) { qs.insert(i); }

    while (!qs.empty()) {
      int a = *qs.rbegin();
      while (ls[a] != a) {
        res.push_back(a);
        qs.erase(a);
        a = ls[a];
        if (!qs.count(a)) { break; }
      }
      qs.erase(a);
    }
  }
  dbg(res);

  cout << res.size() << endl;
  FOR(i, 0, (int)res.size()) {
    if (i) cout << " ";
    cout << (res[i] + 1);
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  // mainCase();
  // return 0;
  // [ Multiple cases ]
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1375D/main.cpp --check

%%%% begin
1
5
0 2 1 4 3
%%%%
%%%% end

%%%% begin
1
3
2 2 3
%%%%
%%%% end

%%%% begin
5
3
2 2 3
3
2 1 0
7
0 7 3 1 3 7 7
9
2 0 1 1 2 4 4 2 0
9
8 4 7 6 1 2 3 0 5
%%%%
0

2
3 1
4
2 5 5 4
11
3 8 9 7 8 5 9 6 4 1 2
10
1 8 1 9 5 2 4 6 3 7
%%%% end
*/
