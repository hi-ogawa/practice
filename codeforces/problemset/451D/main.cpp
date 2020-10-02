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
  string s;
  cin >> s;
  int n = s.size(); // [1, 10^5]

  vector<int> ls(n); // 0/1
  FOR(i, 0, n) { ls[i] = s[i] - 'a'; }

  //
  // PROP.
  //   t : bad
  //     \iff  (t[first], t[last]) = (0, 1) or
  //           (t[first], t[last]) = (1, 0)
  //
  // N.B. thus, the problem reduces to counting such pairs.
  //

  // Count 0/1 for each position parity
  array<array<ll, 2>, 2> cnts = {};
  FOR(i, 0, n) {
    cnts[i % 2][ls[i]]++;
  }
  dbg2(cnts);

  // Count bads by parity
  array<ll, 2> bad_cnts = {};
  FOR(i, 0, n) {
    int x = ls[i], p = i % 2;
    cnts[p][x]--;
    bad_cnts[0] += cnts[!p][!x];
    bad_cnts[1] += cnts[p][!x];
  }
  dbg(bad_cnts);

  // Subtract all substrings by bad
  auto binom2 = [](ll n) { return (n * (n - 1)) / 2; };
  ll res0 = binom2(n / 2 + 1) + binom2((n + 1) / 2); // #{even length substrings}
  ll res1 = binom2(n) + n - res0;
  dbg(res0, res1);
  res0 -= bad_cnts[0];
  res1 -= bad_cnts[1];
  cout << res0 << " " << res1 << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/451D/main.cpp --check

%%%% begin
bb
%%%%
1 2
%%%% end

%%%% begin
baab
%%%%
2 4
%%%% end

%%%% begin
babb
%%%%
2 5
%%%% end

%%%% begin
babaa
%%%%
2 7
%%%% end
*/
