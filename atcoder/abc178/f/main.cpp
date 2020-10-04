// AFTER EDITORIAL, AC

// Cf. https://codeforces.com/blog/entry/82566?#comment-695615

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
  int n; // [1, 2 x 10^5]
  cin >> n;
  vector<int> ls1(n), ls2(n); // [1, n]
  cin >> ls1 >> ls2;

  //
  // PROP.
  //   Solvable  \iff max_t freq(t in a) + freq(t in b) <= n
  //
  //   PROOF. see construction below for how invariance is kept from 2n to 2(n-1)
  //

  map<int, int> cnts1, cnts2;
  set<int> rem1, rem2; // remaining types
  for (auto x : ls1) { cnts1[x]++; rem1.insert(x); }
  for (auto x : ls2) { cnts2[x]++; rem2.insert(x); }

  set<array<int, 2>> freqs; // (cnts1[x] + cnts2[x], x)
  FOR(x, 1, n + 1) {
    if (cnts1.count(x) || cnts2.count(x)) {
      freqs.insert({cnts1[x] + cnts2[x], x});
    }
  }
  dbg(freqs);

  bool ok = (*freqs.rbegin())[0] <= n;
  if (!ok) { cout << "No" << "\n"; return; }

  vector<array<int, 2>> res; // (ai, bj) pairs

  auto pickPair = [&](int x, int y) {
    res.push_back({x, y});
    freqs.erase({cnts1[x] + cnts2[x], x});
    freqs.erase({cnts1[y] + cnts2[y], y});
    freqs.insert({cnts1[x] + cnts2[x] - 1, x});
    freqs.insert({cnts1[y] + cnts2[y] - 1, y});
    assert(cnts1[x]);
    assert(cnts2[y]);
    if (--cnts1[x] == 0) { rem1.erase(x); }
    if (--cnts2[y] == 0) { rem2.erase(y); }
  };

  FOR(i, 0, n) {
    int m = n - i;
    dbg(m, freqs);
    dbg(cnts1, cnts2);
    dbg(rem1, rem2);

    auto [fx, x] = *freqs.rbegin();
    assert(fx <= m);

    int x_lambda_workaround = x;
    if (cnts1[x]) {
      auto it = find_if(ALL(rem2), [&](auto y) { return y != x_lambda_workaround; });
      assert(it != rem2.end());
      pickPair(x, *it);
    } else {
      assert(cnts2[x]);
      auto it = find_if(ALL(rem1), [&](auto y) { return y != x_lambda_workaround; });
      assert(it != rem1.end());
      pickPair(*it, x);
    }
  }

  sort(ALL(res));
  cout << "Yes" << "\n";
  FOR(i, 0, n) {
    cout << res[i][1] << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc178/f/main.cpp --check

%%%% begin
4
1 2 3 4
1 1 1 4
%%%%
4 1 1 1
%%%% end

%%%% begin
9
1 1 1 2 2 2 3 3 3
1 1 1 2 2 2 3 3 3
%%%%
Yes
2 2 3 1 3 3 1 1 2
%%%% end

%%%% begin
6
1 1 1 2 2 3
1 1 1 2 2 3
%%%%
Yes
2 2 3 1 1 1
%%%% end

%%%% begin
3
1 1 2
1 1 3
%%%%
No
%%%% end

%%%% begin
4
1 1 2 3
1 2 3 3
%%%%
Yes
3 3 1 2
%%%% end
*/
