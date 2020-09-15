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
  int n, nq; // [1, 10^5]
  cin >> n >> nq;
  vector<int> ls(n); // [1, 10^9] (no duplicates)
  cin >> ls;
  vector<array<int, 2>> qs(nq);
  cin >> qs;

  set<int> ps(ALL(ls));
  multiset<int> seps;
  sort(ALL(ls));
  FOR(i, 0, n - 1) { seps.insert(ls[i + 1] - ls[i]); }

  // f = (max(ls) - min(ls)) - max_{i,j}|ls[i] - ls[j]| (i.e. split at the largest separation)
  auto evaluate = [&]() -> int {
    if (ps.size() <= 2) { return 0; }
    return *ps.rbegin() - *ps.begin() - *seps.rbegin();
  };

  vector<int> res;
  res.push_back(evaluate());

  for (auto [qt, qx] : qs) {
    if (qt == 0) {
      if (ps.size() == 1) {
        ps.clear(); seps.clear();

      } else {
        auto it = ps.lower_bound(qx);
        if (it == ps.begin()) {
          int d = *next(it) - qx;
          seps.erase(seps.find(d));
        } else if (it == --ps.end()) {
          int d = qx - *prev(it);
          seps.erase(seps.find(d));
        } else {
          int d1 = *next(it) - qx;
          int d2 = qx - *prev(it);
          seps.erase(seps.find(d1));
          seps.erase(seps.find(d2));
          seps.insert(d1 + d2);
        }
        ps.erase(it);
      }
    }

    if (qt == 1) {
      auto it = ps.lower_bound(qx);
      if (it == ps.begin()) {
        int d = *it - qx;
        seps.insert(d);
      } else if (it == ps.end()) {
        int d = qx - *--ps.end();
        seps.insert(d);
      } else {
        int d1 = *it - qx;
        int d2 = qx - *prev(it);
        seps.erase(seps.find(d1 + d2));
        seps.insert(d1);
        seps.insert(d2);
      }
      ps.insert(qx);
    }
    res.push_back(evaluate());
  }

  for (auto x : res) {
    cout << x << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/edu95/d/main.cpp --check

%%%% begin
5 6
1 2 6 8 10
1 4
1 9
0 6
0 10
1 100
1 50
%%%%
5
7
7
5
4
8
49
%%%% end

%%%% begin
5 8
5 1 2 4 3
0 1
0 2
0 3
0 4
0 5
1 1000000000
1 1
1 500000000
%%%%
3
2
1
0
0
0
0
0
499999999
%%%% end
*/
