// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
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
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n, k; // n \in [2, 1000], k \in [1, n]
  cin >> n >> k;
  vector<vector<int>> sets(k);
  FOR(i, 0, k) {
    int m;
    cin >> m;
    sets[i].resize(m);
    cin >> sets[i];
    for (auto& x : sets[i]) { x--; } // zero-based
  }

  auto ask = [&](const vector<int>& ls) -> int {
    cout << "? " << ls.size();
    for (auto x : ls) { cout << " " << (x + 1); }
    cout << endl;
    int res;
    cin >> res;
    return res;
  };

  auto askRange = [&](int l, int r) -> int {
    vector<int> ls;
    FOR(i, l, r) { ls.push_back(i); }
    return ask(ls);
  };

  // Binary search
  auto askFindIndex = [&](int x) -> int {
    int i0 = -1, i1 = n - 1; // (i0, i1]
    while (i0 + 1 < i1) {
      int i = (i0 + i1 + 1) / 2;
      int res = askRange(0, i + 1);
      if (res >= x) {
        i1 = i;
      } else {
        i0 = i;
      }
    }
    return i1;
  };

  auto askNegation = [&](const vector<int>& ls) -> int {
    vector<int> lsb(n);
    for (auto i : ls) { lsb[i] = 1; }
    vector<int> ls_neg;
    FOR(i, 0, n) {
      if (lsb[i] == 0) { ls_neg.push_back(i); }
    }
    return ask(ls_neg);
  };

  // Find maximum (at most 11 queries)
  int m = askRange(0, n);
  int im = askFindIndex(m);
  dbg(m, im);

  vector<int> res(k, m);
  FOR(i, 0, k) {
    auto& ls = sets[i];
    if (count(ALL(ls), im)) {
      res[i] = askNegation(ls); // Single query
      break;
    }
  }
  dbg(res);

  cout << "!";
  FOR(i, 0, k) { cout << " " << res[i]; }
  cout << endl;

  string verdict;
  cin >> verdict;
  assert(verdict == "Correct");
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; // [1, 10]
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1363D/main.cpp

%%%% begin
1
4 2
2 1 3
2 2 4

1

2

3

4

Correct
%%%%
? 1 1

? 1 2

? 1 3

? 1 4

! 4 3
%%%% end
*/
