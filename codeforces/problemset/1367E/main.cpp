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
  int n, k; // [1, 2000]
  cin >> n >> k;
  string s; // lower case
  cin >> s;

  int m = 26;
  vector<int> cnts(m);
  for (auto c : s) {
    cnts[c - 'a']++;
  }

  // f(l, d) = 1 \iff we can make l-length d-good
  auto evaluate = [&](int l, int d) -> bool {
    assert(l % d == 0);
    int c = l / d; // "c" copy for "d" types
    int t = 0;
    FOR(i, 0, m) {
      t += cnts[i] / c;
    }
    return t >= d;
  };

  vector<int> divisors;
  FOR(d, 1, (int)sqrt(k) + 1) {
    if (k % d == 0) {
      divisors.push_back(d);
      if (d * d < k) {
        divisors.push_back(k / d);
      }
    }
  }

  // Brute force
  int res = 0;
  for (auto d : divisors) {
    for (int l = d; l <= n; l += d) {
      if (evaluate(l, d)) {
        res = max(res, l);
      }
    }
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1367E/main.cpp

%%%% begin
6
6 3
abcbac
3 6
aaa
7 1000
abczgyo
5 4
ababa
20 10
aaebdbabdbbddaadaadc
20 5
ecbedececacbcbccbdec
%%%%
6
3
5
4
15
10
%%%% end
*/
