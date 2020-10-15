// AFTER EDITORIAL, AC

// NOTE: Subgroup of S(2n) with n! 2^n elements

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
  int n; // [1, 500]
  cin >> n;
  vector<int> ls1(n), ls2(n);
  cin >> ls1 >> ls2;

  vector<array<int, 2>> ps1(n / 2), ps2(n / 2);
  FOR(i, 0, n / 2) {
    ps1[i] = {ls1[i], ls1[n - 1 - i]};
    ps2[i] = {ls2[i], ls2[n - 1 - i]};
    sort(ALL(ps1[i]));
    sort(ALL(ps2[i]));
  }
  sort(ALL(ps1));
  sort(ALL(ps2));

  bool ok = ps1 == ps2;
  if (n % 2 == 1) { ok = ok && ls1[n / 2] == ls2[n / 2]; }

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
python misc/run.py codeforces/problemset/1365F/main.cpp

%%%% begin
5
2
1 2
2 1
3
1 2 3
1 2 3
3
1 2 4
1 3 4
4
1 2 3 2
3 1 2 2
3
1 2 3
1 3 2
%%%%
yes
yes
No
yes
No
%%%% end
*/
