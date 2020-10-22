// AFTER EDITORIAL, AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (decltype(Y) I = (X); I < (Y); ++I)
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

  //
  // PROP.
  //   a ⨁ b ≠ 0
  //          ≠ x
  //          ≠ a
  //          ≠ a ⨁ x
  //  <=>
  //   a ⨁ b ≠ 0
  //          ≠ x
  //        b ≠ 0
  //          ≠ x
  //
  // N.B.
  //   Thus, sequence is valid \iff
  //     For each prefix,
  //       XOR(a1, ..., ai) ≠ 0, x
  //                        ≠ a1, a1 ⨁ x
  //                        ≠ XOR(a1, a2), XOR(a1, a2) ⨁ x
  //                        ≠ XOR(a1, a2, a3), XOR(a1, a2, a3) ⨁ x
  //                        ≠ ...
  //

  int n, x; // n \in [1, 18], x \in [1, 2^n - 1]
  cin >> n >> x;

  set<int> ls;
  FOR(i, 0, 1 << n) { ls.insert(i); }
  ls.erase(0);
  ls.erase(x);

  vector<int> ps;
  while (!ls.empty()) {
    int p = *ls.begin(); ls.erase(ls.begin());
    ps.push_back(p);
    ls.erase(p ^ x);
  }
  dbg(ps);

  int k = ps.size();
  auto res = ps;
  for (int i = k - 1; i >= 1; i--) {
    res[i] ^= res[i - 1];
  }

  cout << k << "\n";
  FOR(i, 0, k) {
    cout << res[i] << " \n"[i == k - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1174D/main.cpp

%%%% begin
3 5
%%%%
3
6 1 3
%%%% end

%%%% begin
2 4
%%%%
3
1 3 1
%%%% end

%%%% begin
1 1
%%%%
0
%%%% end
*/
