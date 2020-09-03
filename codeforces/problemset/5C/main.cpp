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
  int n = s.size(); // <= 10^6

  vector<array<int, 2>> segs;
  vector<int> st;
  FOR(i, 0, n) {
    if (s[i] == '(') {
      st.push_back(i);
    }
    if (s[i] == ')') {
      if (!st.empty()) {
        int i0 = st.back(); st.pop_back();
        while (!segs.empty() && segs.back()[1] >= i0) {
          // Concat with previous segments
          if (segs.back()[1] == i0) {
            i0 = segs.back()[0];
          }
          segs.pop_back();
        }
        segs.push_back({i0, i + 1});
      }
    }
  }
  dbg(segs);

  map<int, int> cnts;
  for (auto [i, j] : segs) {
    cnts[j - i]++;
  }
  dbg(cnts);

  cnts[0] = 1;
  auto [l, k] = *cnts.rbegin();
  cout << l << " " << k << endl;
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
python misc/run.py codeforces/problemset/5C/main.cpp --check

%%%% begin
(()())()(())()()())())()((()(()(())()()())((()(())()(()()()()))()(())()(((()())()(()((())()(())(()))
%%%%
28 1
%%%% end

%%%% begin
(()(()
%%%%
2 2
%%%% end

%%%% begin
)((())))(()())
%%%%
6 2
%%%% end

%%%% begin
))(
%%%%
0 1
%%%% end
*/
