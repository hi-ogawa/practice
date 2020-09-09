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
  int n, k;
  cin >> n >> k;
  string s;
  cin >> s;

  vector<int> fs(k), gs(k);
  int h = 0;
  FOR(i, 0, n) {
    fs[i % k] += s[i] == '1';
    gs[i % k] += s[i] == '0';
    h += s[i] == '1';
  }
  dbg(fs);
  dbg(gs);
  dbg(h);

  int res = 1 << 30;
  FOR(i, 0, k) {
    // Set s[j] = 0 if j % k != i
    int p = h - fs[i];

    // Find min range of s[j] cost (j % k = i)
    multiset<int> costs;
    {
      int cnt0 = 0, cnt1 = 0;
      costs.insert(fs[i]);
      for (int j = i; j < n; j += k) {
        cnt0 += s[j] == '0';
        cnt1 += s[j] == '1';
        costs.insert(cnt0 + fs[i] - cnt1);
      }
    }
    int q = 1 << 30;
    {
      int cnt0 = 0, cnt1 = 0;
      for (int j = i; j < n; j += k) {
        q = min(q, *costs.begin() + cnt1 - cnt0);
        costs.erase(costs.find(cnt0 + fs[i] - cnt1));
        cnt0 += s[j] == '0';
        cnt1 += s[j] == '1';
      }
      q = min(q, *costs.begin() + cnt1 - cnt0);
    }
    res = min(res, p + q);
  }
  cout << res << endl;
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
python misc/run.py codeforces/problemset/1353E/main.cpp --check

%%%% begin
1
9 3
111100000
%%%%
2
%%%% end

%%%% begin
6
9 2
010001010
9 3
111100000
7 4
1111111
10 3
1001110101
1 1
1
1 1
0
%%%%
1
2
5
4
0
0
%%%% end
*/
