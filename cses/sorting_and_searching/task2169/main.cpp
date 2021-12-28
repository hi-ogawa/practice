// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y){X}; I < (Y); ++I)
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

// Order statistics tree
#include <ext/pb_ds/assoc_container.hpp>
template<class Key, class Compare = less<Key>>
using ordered_set = __gnu_pbds::tree<
  Key, __gnu_pbds::null_type, Compare,
  __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

// Main
void mainCase() {
  int n;
  cin >> n;
  vector<array<int, 2>> ls(n);
  cin >> ls;

  vector<tuple<int, int, int, bool>> events;
  for (int i = 0; i < n; ++i) {
    auto [x, y] = ls[i];
    events.push_back({x, 0, i, true});
    events.push_back({y, -x, i, false});
  }
  sort(ALL(events));

  vector<int> contains(n, 0);
  vector<int> contained(n, 0);
  ordered_set<array<int, 2>> pending;
  ordered_set<array<int, 2>> finished;

  for (auto [_0, _1, i, is_start]: events) {
    auto [x, _2] = ls[i];
    if (is_start) {
      pending.insert({x, i});

    } else {
      pending.erase({x, i});
      contained[i] = pending.order_of_key({x + 1, -1});
      contains[i] = finished.size() - finished.order_of_key({x, -1});
      finished.insert({x, i});
    }
  }

  for (int i = 0; i < n; ++i) {
    cout << contains[i] << " \n"[i == n - 1];
  }
  for (int i = 0; i < n; ++i) {
    cout << contained[i] << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/sorting_and_searching/task2169/main.cpp

%%%% begin
4
1 6
2 4
4 8
3 6
%%%%
2 0 0 0
0 1 0 1
%%%% end
*/
