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
  int n0, n1, n2, n3; // [1, 10^5]
  cin >> n0 >> n1 >> n2 >> n3;
  int n = n0 + n1 + n2 + n3;

  // NOTE: consider the parity of position

  vector<int> res;

  auto solve = [&]() -> bool {
    // n : even
    if (n % 2 == 0) {
      bool ok = n0 + n2 == n1 + n3 && n0 <= n1 && n2 >= n3; // actually n0 <= n1 implies n2 >= n3
      if (!ok) { return 0; }

      // 01...01 21...21 23..23
      FOR(i, 0, n0)      { res.push_back(0); res.push_back(1); }
      FOR(i, 0, n1 - n0) { res.push_back(2); res.push_back(1); }
      FOR(i, 0, n3)      { res.push_back(2); res.push_back(3); }
      return 1;
    }

    // n : odd

    // Swap to handling odd case easily
    bool swapped = n0 + n2 + 1 == n1 + n3;
    if (swapped) { swap(n0, n3); swap(n1, n2); }

    if (n0 + n2 != n1 + n3 + 1) { return 0; }
    if (n2 < n3) { return 0; }
    if (n2 == n3) {
      if (n2 > 0) { return 0; }

      // Special construction 010...010
      assert(n0 == n1 + 1);
      FOR(i, 0, n1) { res.push_back(0); res.push_back(1); }
      res.push_back(0);

    } else {
      // n2 > n3 and n0 <= n1
      // 01..01 21..21 23..23 2
      FOR(i, 0, n0)      { res.push_back(0); res.push_back(1); }
      FOR(i, 0, n1 - n0) { res.push_back(2); res.push_back(1); }
      FOR(i, 0, n3)      { res.push_back(2); res.push_back(3); }
      res.push_back(2);
    }

    if (swapped) {
      array<int, 4> mapping = {3, 2, 1, 0};
      FOR(i, 0, n) { res[i] = mapping[res[i]]; }
    }
    return 1;
  };

  bool ok = solve();
  if (!ok) { cout << "NO\n"; return; }
  cout << "YES\n";

  FOR(i, 0, n) {
    cout << res[i] << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1264B/main.cpp

%%%% begin
2 2 2 1
%%%%
YES
0 1 0 1 2 3 2
%%%% end

%%%% begin
1 2 3 4
%%%%
NO
%%%% end

%%%% begin
2 2 2 3
%%%%
NO
%%%% end
*/
