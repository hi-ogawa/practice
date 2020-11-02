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
  string s;
  cin >> s;
  int n = s.size(); // [1, 2 x 10^5]

  int k = 10;
  vector<int> cnts(k);
  for (auto c : s) {
    cnts[c - '0']++;
  }
  dbg(cnts);

  // Only 3 low digits matters since 8 | 1000
  vector<string> ls;
  for (int x = 0; x < 1000; x += 8) {
    string t = to_string(x);
    if ((int)t.size() != min(n, 3)) { continue; }
    if (count(ALL(t), '0')) { continue; }
    ls.push_back(t);
  }
  dbg(ls);

  bool res = 0;
  for (auto t : ls) {
    vector<int> t_cnts(k);
    for (auto c : t) {
      t_cnts[c - '0']++;
    }
    bool ok = 1;
    FOR(i, 1, k) {
      if (cnts[i] < t_cnts[i]) {
        ok = 0;
        break;
      }
    }
    if (ok) {
      res = 1;
      break;
    }
  }
  cout << (res ? "Yes" : "No") << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc181/d/main.cpp

%%%% begin
1234
%%%%
Yes
%%%% end

%%%% begin
1333
%%%%
No
%%%% end

%%%% begin
8
%%%%
Yes
%%%% end
*/
