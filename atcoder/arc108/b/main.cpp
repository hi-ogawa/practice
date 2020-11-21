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
  int n; // [1, 2 x 10^5]
  cin >> n;
  string s;
  cin >> s;

  list<char> ls(ALL(s));
  dbg(ls);

  // Probably not correct...?

  auto it = ls.begin();
  int cnt = 0;
  while (it != ls.end()) {
    dbg(distance(ls.begin(), it), ls);
    if (it == ls.begin()) { it++; continue; }
    if (next(it) == ls.end()) { break; }

    if (*prev(it) == 'f' && *it == 'o' && *next(it) == 'x') {
      auto tmp = prev(it, 2);
      bool reset = prev(it) == ls.begin();
      it = prev(it);
      it = ls.erase(it);
      it = ls.erase(it);
      it = ls.erase(it);
      it = tmp;
      if (reset) { it = ls.begin(); }
      cnt++;
    } else {
      it++;
    }
  }
  dbg(cnt);

  int res = n - 3 * cnt;
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/arc108/b/main.cpp

%%%% begin
6
icefox
%%%%
3
%%%% end

%%%% begin
7
firebox
%%%%
7
%%%% end

%%%% begin
48
ffoxoxuvgjyzmehmopfohrupffoxoxfofofoxffoxoxejffo
%%%%
27
%%%% end
*/
