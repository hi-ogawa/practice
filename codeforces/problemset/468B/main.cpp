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
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n, a, b; // n \in [1, 10^5]
  cin >> n >> a >> b;
  vector<int> ls(n); // [1, 10^9], distinct
  cin >> ls;

  bool swapped = a > b;
  if (swapped) { swap(a, b); }

  set<int> xs(ALL(ls));
  array<set<int>, 2> res;
  bool ok = 1;
  while (!xs.empty()) {
    auto x = *xs.begin();
    if (x == b - x || xs.count(b - x)) {
      // This pair target (b - x) cannot be in A because
      //   a - (b - x) = x - (b - a) < x
      // but smaller elements than x are already processed
      assert(x <= b - x);
      res[1].insert(x);
      res[1].insert(b - x);
      xs.erase(x);
      xs.erase(b - x);
      continue;
    }
    if (x == a - x || xs.count(a - x)) {
      assert(x <= a - x);
      res[0].insert(x);
      res[0].insert(a - x);
      xs.erase(x);
      xs.erase(a - x);
      continue;
    }
    ok = 0;
    break;
  }
  dbg(ok, res);

  cout << (ok ? "YES" : "NO") << "\n";
  if (!ok) { return; }

  FOR(i, 0, n) {
    int x = ls[i];
    int r = res[!swapped].count(x);
    cout << r << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/468B/main.cpp

%%%% begin
4 5 9
2 3 4 5
%%%%
YES
0 0 1 1
%%%% end

%%%% begin
3 3 4
1 2 4
%%%%
NO
%%%% end
*/
