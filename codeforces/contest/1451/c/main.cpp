// CONTEST, AC

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
  int n, k; // [2, 10^6]
  cin >> n >> k;
  string s1, s2; // lowercase
  cin >> s1 >> s2;

  // Count characters
  const int m = 26;
  vector<int> cnts1(m), cnts2(m);
  for (auto c : s1) {
    cnts1[c - 'a']++;
  }
  for (auto c : s2) {
    cnts2[c - 'a']++;
  }
  dbg(cnts1);
  dbg(cnts2);

  // Match from large ones
  bool ok = 1;
  for (int i = m - 1; i >= 0; i--) {
    if (cnts1[i] > cnts2[i]) { ok = 0; break; }
    int diff = cnts2[i] - cnts1[i];

    // Not divisible
    if (diff % k) { ok = 0; break; }

    // Borrow from smaller ones
    int diffq = diff / k;

    for (int j = i - 1; j >= 0; j--) {
      if (cnts1[j] < k) { continue; }
      int q = cnts1[j] / k;
      int qq = min(q, diffq);
      cnts1[j] -= qq * k;
      diffq -= qq;
    }

    // Couldn't match
    if (diffq > 0) { ok = 0; break; }
  }

  cout << (ok ? "Yes" : "No") << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest/1451/c/main.cpp

%%%% begin
4
3 3
abc
bcd
4 2
abba
azza
2 1
zz
aa
6 2
aaabba
ddddcc
%%%%
No
Yes
No
Yes
%%%% end
*/
