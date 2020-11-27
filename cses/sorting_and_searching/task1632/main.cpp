// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y)(X); I < (Y); ++I)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i,       tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; auto s = ""; apply([&](auto&&... y){ ((o << s << y, s = ", "), ...); }, x); return o << ")"; }
template<class T1, class T2> istream& operator>>(istream& i,       pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
istream& operator>>(istream& i,       T& x) { for (auto& y : x) { i >> y; } return i; }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
ostream& operator<<(ostream& o, const T& x) { o << "{"; auto s = ""; for (auto& y : x) { o << s << y; s = ", "; } return o << "}"; }
}

#ifdef DEBUG
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n, k; // [1, 2 x 10^5]
  cin >> n >> k;
  vector<array<int, 2>> ls(n); // [1, 10^9]
  cin >> ls;
  sort(ALL(ls), [](auto lhs, auto rhs) { return lhs[1] < rhs[1]; });
  dbg(ls);

  int res = 0;

  // Not optimal strategy
  // deque<int> ts; // Finish time for each member
  // for (auto [l, r] : ls) {
  //   if (!ts.empty() && ts[0] <= l) {
  //     ts.pop_front();
  //   }
  //   if ((int)ts.size() < k) {
  //     ts.push_back(r);
  //     res++;
  //   }
  // }

  multiset<int> ts; // Finish time for each member
  for (auto [l, r] : ls) {
    dbg(ts);
    // Assign to member with closest finish time
    auto it = ts.upper_bound(l);
    if (it != ts.begin()) {
      ts.erase(prev(it));
    }
    if ((int)ts.size() < k) {
      ts.insert(r);
      res++;
    }
  }

  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/sorting_and_searching/task1632/main.cpp

%%%% begin
10 5
46 95
80 90
53 78
77 79
75 94
49 87
35 72
57 69
22 99
64 95
%%%%
8
%%%% end

%%%% begin
5 2
1 5
8 10
3 6
2 5
6 9
%%%%
4
%%%% end
*/
