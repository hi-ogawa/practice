
// Brute force solution for debugging main.cpp

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

vector<int> makeDivisorFunction(int n) {
  vector<int> sieve(n + 1, 1);
  vector<int> res(n + 1, 1);
  for (int p = 2; p <= n; p++) {
    if (!sieve[p]) { continue; }
    int e = 1;
    ll pe = p;
    for (; pe <= n; e++, pe *= p) {
      int i = 1;
      int x = pe;
      for (; x <= n; i++, x += pe) {
        if (i % p == 0) { continue; }
        sieve[x] = 0;
        res[x] *= (e + 1);
      }
    }
  }
  return res;
};

// Main
void mainCase() {
  int n, nq; // [1, 3 x 10^5]
  cin >> n >> nq;
  vector<int> ls(n); // [1, 10^6]
  cin >> ls;
  vector<array<int, 3>> qs(nq);
  cin >> qs;

  int k = *max_element(ALL(ls));
  auto divisor = makeDivisorFunction(k);

  auto query1 = [&](int l, int r) {
    FOR(i, l, r) {
      ls[i] = divisor[ls[i]];
    }
  };

  auto query2 = [&](int l, int r) -> ll {
    ll res = 0;
    FOR(i, l, r) {
      res += ls[i];
    }
    return res;
  };

  for (auto [t, l, r] : qs) {
    l--;
    dbg(ls);
    if (t == 1) {
      query1(l, r);
    }
    if (t == 2) {
      auto res = query2(l, r);
      cout << res << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/920F/brute.cpp

%%%% begin
7 6
6 4 1 10 3 2 4
2 1 7
2 4 5
1 3 5
2 4 4
1 5 7
2 1 7
%%%%
30
13
4
22
%%%% end
*/
