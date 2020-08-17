// AC

// cf. cses/sorting_and_searching/task1619/main.cpp

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
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  ll n;
  cin >> n;
  vector<tuple<ll, int, int>> ls;
  FOR(i, 0, n) {
    ll x, y;
    cin >> x >> y;
    y++;
    ls.push_back({x, 1, i});
    ls.push_back({y, -1, i});
  }
  sort(ALL(ls)); // NOTE: it's essential that (x, -1) < (x, 1)
  // DD(ls);

  vector<int> res(n, 0);
  set<int> rooms;
  int tot = 0;
  int cur = 0;
  for (auto [_t, c, i] : ls) {
    cur += c;
    if (c == -1) {
      rooms.insert(res[i]);
    }
    if (c == 1) {
      if (cur > tot) {
        rooms.insert(cur);
        tot = cur;
      }
      auto r = *rooms.begin();
      res[i] = r;
      rooms.erase(r);
    }
    // DD(tie(tot, cur, rooms, res));
  }

  cout << tot << endl;
  FOR(i, 0, n) {
    if (i) { cout << " "; }
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
python misc/run.py cses/sorting_and_searching/task1164/main.cpp --check

%%%% begin
3
1 2
2 4
4 4
%%%%
2
1 2 1
%%%% end
*/
