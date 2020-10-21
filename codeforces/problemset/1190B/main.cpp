// AC

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
  ll n; // [1, 10^5]
  cin >> n;
  vector<ll> ls(n); // [0, 10^9]
  cin >> ls;
  sort(ALL(ls));

  // true \iff 1st win
  auto solve = [&]() -> bool {
    // Check valid initial move
    vector<int> dups;
    FOR(i, 0, n - 1) {
      if (ls[i] == ls[i + 1]) {
        dups.push_back(ls[i]);
      }
    }
    int ndups = dups.size();
    if (ndups >= 2) { return 0; }
    if (ndups == 1) {
      // Check (0, 0, ..)
      if (dups[0] == 0) { return 0; }

      // Check (..., d, d + 1, d + 1, ...)
      if (count(ALL(ls), dups[0] - 1)) { return 0; }
    }

    // Compare parity with the final board (0, 1, 2, ..., n - 1)
    ll x = accumulate(ALL(ls), (ll)0);
    ll y = (n * (n - 1)) / 2;
    return (x & 1) != (y & 1);
  };

  bool first_win = solve();
  cout << (first_win ? "sjfnb" : "cslnb") << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1190B/main.cpp

%%%% begin
1
0
%%%%
cslnb
%%%% end

%%%% begin
2
1 0
%%%%
cslnb
%%%% end

%%%% begin
2
2 2
%%%%
sjfnb
%%%% end

%%%% begin
3
2 3 1
%%%%
sjfnb
%%%% end
*/
