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
  string s;
  cin >> s;

  map<char, int> cnts_map;
  for (auto t : s) { cnts_map[t]++; }
  vector<pair<char, int>> cnts(ALL(cnts_map));

  int k = cnts.size();
  dbg(cnts);

  string res;
  bool ok = 0;

  if (k == 1) {
    ok = 1;
    res = s;
  }

  if (k == 2) {
    if (cnts[1].first > cnts[0].first + 1) {
      ok = 1;
      res = s;
    }
  }

  if (k == 3) {
    if (cnts[1].first > cnts[0].first + 1) {
      ok = 1;
      cnts = {cnts[1], cnts[0], cnts[2]};
    } else if (cnts[2].first > cnts[1].first + 1) {
      ok = 1;
      cnts = {cnts[0], cnts[2], cnts[1]};
    }
    if (ok) {
      for (auto [t, c] : cnts) {
        res += string(c, t);
      }
    }
  }

  if (k >= 4) {
    ok = 1;
    vector<pair<char, int>> cnts2; // reorder to make it valid
    for (int i = 0; i < k / 2; i++) {
      cnts2.push_back(cnts[i + k / 2]);
      cnts2.push_back(cnts[i]);
    }
    if (k % 2 == 1) {
      cnts2.push_back(cnts[k - 1]);
    }
    dbg(cnts2);

    for (auto [t, c] : cnts2) {
      res += string(c, t);
    }
  }

  cout << (ok ? res : "No answer") << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1156B/main.cpp --check

%%%% begin
1
abcde
%%%%
cadbe
%%%% end

%%%% begin
2
abd
acd
%%%%
adb
cad
%%%% end

%%%% begin
4
abcd
gg
codeforces
abaca
%%%%
cadb
gg
fccoodrees
No answer
%%%% end
*/
