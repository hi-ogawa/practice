// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y){X}; I < (Y); ++I)
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
  int n; // [1, 5 x 10^8]
  cin >> n;
  int a, b; // #{ i | p_{a i + b} <= n } <= 10^6
  cin >> a >> b;

  vector<bool> s(n + 1, 1);
  FOR(p, 2, sqrt(n) + 1) {
    if (!s[p]) { continue; }
    for (int x = p * p; x <= n; x += p) { s[x] = 0; }
  }

  int i = 0;
  int cnt = 0;
  vector<int> res;
  FOR(p, 2, n + 1) {
    if (s[p]) {
      if (cnt == a * i + b) {
        res.push_back(p);
        i++;
      }
      cnt++;
    }
  }

  cout << cnt << " " << i << "\n";
  FOR(j, 0, i) {
    cout << res[j] << " \n"[j == i - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/enumerate_primes/main.cpp

%%%% begin
100 3 1
%%%%
25 8
3 11 19 31 43 59 71 83
%%%% end
*/
