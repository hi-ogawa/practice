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
  ll n; // [1, 10^18], digit in {1, .., 9}
  cin >> n;

  vector<int> ls;
  while (n > 0) {
    ls.push_back(n % 10);
    n /= 10;
  }
  int k = ls.size();
  dbg(ls);

  int total = accumulate(ALL(ls), 0) % 3;

  const int kInf = 1e9;
  int res = kInf;
  FOR(i0, 0, k) {
    FOR(i1, i0, k + 1) {
      int t = i1 - i0;
      if (t == k) { continue; }

      int s = 0;
      FOR(i, i0, i1) {
        s += ls[i];
      }
      s %= 3;
      if (total == s && t < res) {
        res = t;
      }
    }
  }

  if (res == kInf) { res = -1; }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc182/c/main.cpp

%%%% begin
35
%%%%
1
%%%% end

%%%% begin
369
%%%%
0
%%%% end

%%%% begin
6227384
%%%%
1
%%%% end

%%%% begin
11
%%%%
-1
%%%% end
*/
