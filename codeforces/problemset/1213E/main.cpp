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
  int n; // [1, 10^5]
  cin >> n;
  string s0, s1;
  cin >> s0 >> s1;
  if (s0[0] != s0[1]) { swap(s0, s1); }

  string res(3 * n, '?');

  if (s0[0] == s0[1] && s1[0] == s1[1]) {
    // 012012012...
    FOR(i, 0, 3 * n) {
      res[i] = 'a' + (i % 3);
    }
  }

  if (s0[0] == s0[1] && s1[0] != s1[1]) {
    // 012012... or 210210...
    int k = (s1[1] - s1[0] + 3) % 3;
    assert(k == 1 || k == 2);
    FOR(i, 0, 3 * n) {
      res[i] = 'a' + (i % 3);
    }
    if (k == 1) { reverse(ALL(res)); }
  }

  if (s0[0] != s0[1] && s1[0] != s1[1]) {
    // 0..01..12..2 etc
    array<int, 3> p = {0, 1, 2};
    do {
      bool ok = 1;
      FOR(i, 0, 2) {
        if (p[i] == s0[0] - 'a' && p[i + 1] == s0[1] - 'a') {
          ok = 0; break;
        }
        if (p[i] == s1[0] - 'a' && p[i + 1] == s1[1] - 'a') {
          ok = 0; break;
        }
      }
      if (ok) { break; }
    } while (next_permutation(ALL(p)));

    FOR(i, 0, n)         { res[i] = p[0] + 'a'; }
    FOR(i, n, 2 * n)     { res[i] = p[1] + 'a'; }
    FOR(i, 2 * n, 3 * n) { res[i] = p[2] + 'a'; }
  }

  cout << "YES\n";
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1213E/main.cpp

%%%% begin
2
ab
bc
%%%%
YES
acbbac
%%%% end

%%%% begin
3
aa
bc
%%%%
YES
cacbacbab
%%%% end

%%%% begin
1
cb
ac
%%%%
YES
abc
%%%% end
*/
