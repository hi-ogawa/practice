// AFTER EDITORIAL, AC

// Cf. https://codeforces.com/blog/entry/82174?#comment-689672

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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  string s; // ACGT
  cin >> s;
  int n = s.size(); // [1, 10^6]

  array<char, 4> dec = {'A', 'C', 'G', 'T'};
  vector<int> enc(1 << 8);
  FOR(i, 0, 4) { enc[dec[i]] = i; }

  string res;
  array<bool, 4> found = {};
  FOR(i, 0, n) {
    auto c = s[i];
    found[enc[c]] = 1;
    int cnt = accumulate(ALL(found), (int)0);
    if (cnt == 4) {
      res += c;
      found = {};
    }
  }
  assert(accumulate(ALL(found), (int)0) < 4);
  FOR(i, 0, 4) {
    if (!found[i]) {
      res += dec[i];
      break;
    }
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/additional_problems/task1087/main.cpp

%%%% begin
ACGTACGT
%%%%
AAA
%%%% end
*/
