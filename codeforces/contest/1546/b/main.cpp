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
  int n, m; // [1, 10^5]
  cin >> n >> m;
  vector<string> xs(n), ys(n - 1);
  cin >> xs >> ys;

  string res;
  FOR(j, 0, m) {
    // Count difference for each character
    map<char, int> cnts;
    FOR(i, 0, n) {
      cnts[xs[i][j]]++;
    }
    FOR(i, 0, n - 1) {
      cnts[ys[i][j]]--;
    }
    vector<char> found;
    for (auto [k, v]: cnts) {
      assert(v == 0 || v == 1);
      if (v == 1) {
        found.push_back(k);
      }
    }
    assert(found.size() == 1);
    res.push_back(found[0]);
  }
  cout << res << "\n" << flush;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; // [1, 100]
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest/1546/b/main.cpp

%%%% begin
3
3 5
aaaaa
bbbbb
ccccc
aaaaa
bbbbb
3 4
aaaa
bbbb
cccc
aabb
bbaa
5 6
abcdef
uuuuuu
kekeke
ekekek
xyzklm
xbcklf
eueueu
ayzdem
ukukuk
%%%%
ccccc
cccc
kekeke
%%%% end
*/
