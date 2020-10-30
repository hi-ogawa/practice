
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

#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)

// Main
void mainCase() {
  int n = 1000;
  vector<bool> sieve(n + 1, 1);
  sieve[0] = sieve[1] = 0;
  for (int p = 2; p <= sqrt(n); p++) {
    if (!sieve[p]) { continue; }
    for (int x = p * p; x <= n; x += p) {
      sieve[x] = 0;
    }
  }

  // f(x) = min { a | a : non-prime, a + x : prime }
  int k = 100;
  FOR(x, 1, k + 1) {
    int a = 0;
    for (;; a++) {
      if (sieve[a] == 0 && sieve[x + a] == 1) {
        break;
      }
    }
    dbg(x, a, x + a);
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
}

/*
python misc/run.py codeforces/contest/1436/b/experiment.cpp

%%%% begin
%%%%
%%%% end
*/
