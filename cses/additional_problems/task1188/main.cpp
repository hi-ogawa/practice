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
  string s;
  cin >> s;
  int nq;
  cin >> nq;
  vector<int> qs(nq);
  cin >> qs;
  for (auto& x : qs) { x--; }

  int n = s.size();
  vector<bool> ls(n, 0);
  FOR(i, 0, n) { ls[i] = s[i] - '0'; }
  // DD(ls);

  // Initial segments
  array<set<array<int, 2>>, 2> segs;
  {
    array<vector<array<int, 2>>, 2> _segs;
    _segs[ls[0]].push_back({0, -1});
    FOR(i, 0, n - 1) {
      if (ls[i + 1] == ls[i]) { continue; }
      _segs[ls[i]].back()[1] = i;
      _segs[ls[i + 1]].push_back({i + 1, -1});
    }
    _segs[ls[n - 1]].back()[1] = n - 1;
    FOR(b, 0, 2) { segs[b].insert(ALL(_segs[b])); }
  }
  // DD(segs);

  // Initial segment sizes
  multiset<int> res;
  for (auto [i, j] : segs[0]) { res.insert(j - i + 1); }
  for (auto [i, j] : segs[1]) { res.insert(j - i + 1); }
  // DD(res);

  vector<int> res2(nq, 0);
  FOR(iq, 0, nq) {
    int i = qs[iq];
    bool b = ls[i];
    bool c = !b;
    // DD(tie(i, b));

    auto itb = prev(segs[b].lower_bound({i + 1, -1}));
    auto [i0, i1] = *itb;

    if (i0 == i1) { // == i
      // 00100 -> 00000 (connect)

      segs[b].erase({i, i});
      res.erase(res.find(1));

      int j0 = i, j1 = i;
      if (i < n - 1) {
        auto itc = segs[c].lower_bound({i, -1});
        j1 = get<1>(*itc);
        segs[c].erase({i + 1, j1});
        res.erase(res.find(j1 - i));
      }
      if (i > 0) {
        auto itc = segs[c].lower_bound({i, -1});
        j0 = get<0>(*prev(itc));
        segs[c].erase({j0, i - 1});
        res.erase(res.find(i - j0));
      }
      segs[c].insert({j0, j1});
      res.insert(j1 - j0 + 1);

    } else if (i == i0) { // < i1
      // 00111 -> 00011 (move right)

      segs[b].erase({i0, i1});
      res.erase(res.find(i1 - i0 + 1));

      segs[b].insert({i0 + 1, i1});
      res.insert(i1 - i0);

      int j0 = i;
      if (i > 0) {
        auto itc = segs[c].lower_bound({i, -1});
        j0 = get<0>(*prev(itc));
        segs[c].erase({j0, i - 1});
        res.erase(res.find(i - j0));
      }
      segs[c].insert({j0, i});
      res.insert(i - j0 + 1);

    } else if (i == i1) { // > i0
      // 11100 -> 11000 (move left)

      segs[b].erase({i0, i1});
      res.erase(res.find(i1 - i0 + 1));

      segs[b].insert({i0, i1 - 1});
      res.insert(i1 - i0);

      int j1 = i;
      if (i < n - 1) {
        auto itc = segs[c].lower_bound({i, -1});
        j1 = get<1>(*itc);
        segs[c].erase({i + 1, j1});
        res.erase(res.find(j1 - i));
      }
      segs[c].insert({i, j1});
      res.insert(j1 - i + 1);

    } else {
      // i0 < i < i1
      // 11111 -> 11011 (split)

      segs[b].erase({i0, i1});
      res.erase(res.find(i1 - i0 + 1));

      segs[b].insert({i0, i - 1});
      segs[b].insert({i + 1, i1});
      res.insert(i - i0);
      res.insert(i1 - i);

      segs[c].insert({i, i});
      res.insert(1);
    }

    ls[i] = !b;
    // DD(ls);
    // DD(segs);
    // DD(res);
    res2[iq] = *res.rbegin();
  }

  FOR(i, 0, nq) {
    if (i) cout << " ";
    cout << res2[i];
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
python misc/run.py cses/additional_problems/task1188/main.cpp --check

%%%% begin
1111111111
10
1 7 6 6 5 1 5 8 5 8
%%%%
9 5 4 5 3 4 6 6 4 4
%%%% end

%%%% begin
001011
3
3 2 5
%%%%
4 2 3
%%%% end
*/
