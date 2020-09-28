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

// Order statistics tree (cf. https://codeforces.com/blog/entry/11080 by adamant)
#include <ext/pb_ds/assoc_container.hpp>
template<class Key, class Compare = std::less<Key>>
using ordered_set = __gnu_pbds::tree<
  Key, __gnu_pbds::null_type, Compare,
  __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

// Main
void mainCase() {
  int nq; // [1, 10^5]
  cin >> nq;
  vector<pair<char, int>> qs(nq);
  cin >> qs;

  ordered_set<pair<int, int>> ls;
  FOR(i, 0, nq) {
    char t; int x;
    tie(t, x) = qs[i];
    if (t == 'r') {
      auto it = ls.lower_bound({x, 0});
      if (it == ls.end() || x < it->first) {
        cout << "Wrong!" << "\n";
        continue;
      }
      ls.erase(it);
    }
    if (t == 'a') {
      ls.insert({x, i});
    }

    int n = ls.size();
    if (n == 0) {
      cout << "Wrong!" << "\n";
      continue;
    }

    double res;
    if (n % 2 == 0) {
      auto it1 = ls.find_by_order(n / 2 - 1);
      auto it2 = ls.find_by_order(n / 2);
      res = ((double)it1->first + it2->first) / 2;
    } else {
      auto it = ls.find_by_order(n / 2);
      res = it->first;
    }
    cout << setprecision(numeric_limits<double>::digits10 + 1) << res << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py hackerrank/challenges/median/main.cpp --check

%%%% begin
7
r 1
a 1
a 2
a 1
r 1
r 2
r 1
%%%%
Wrong!
1
1.5
1
1.5
1
Wrong!
%%%% end
*/
