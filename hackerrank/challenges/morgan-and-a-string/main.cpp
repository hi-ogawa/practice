// WIP

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
  string s1, s2;
  cin >> s1 >> s2;
  int n1 = s1.size(), n2 = s2.size(); // [1, 10^5]

  // Compress consecutive characters
  vector<pair<char, int>> segs1, segs2; // (character, run-length)
  FOR(i, 0, n1) {
    if (i == 0 || s1[i] != s1[i - 1]) { segs1.push_back({s1[i], 0}); }
    segs1.back().second++;
  }
  FOR(i, 0, n2) {
    if (i == 0 || s2[i] != s2[i - 1]) { segs2.push_back({s2[i], 0}); }
    segs2.back().second++;
  }
  dbg(segs1, segs2);

  // Greedy construction
  vector<pair<char, int>> res;
  int k1 = segs1.size(), k2 = segs2.size();
  int i1 = 0, i2 = 0;
  while (i1 < k1 || i2 < k2) {
    if (i1 == k1) { res.push_back(segs2[i2++]); continue; }
    if (i2 == k2) { res.push_back(segs1[i1++]); continue; }
    auto [t1, l1] = segs1[i1];
    auto [t2, l2] = segs2[i2];
    if (t1 < t2) { res.push_back(segs1[i1++]); continue; }
    if (t1 > t2) { res.push_back(segs2[i2++]); continue; }
    // t1 == t2
    if (i1 + 1 == k1) { res.push_back(segs2[i2++]); continue; }
    if (i2 + 1 == k2) { res.push_back(segs1[i1++]); continue; }
    // TODO
    auto [tt1, _ll1] = segs1[i1 + 1];
    auto [tt2, _ll2] = segs2[i2 + 1];
    if (l1 < l2) {
      if (tt1 < t1) { res.push_back(segs1[i1++]); continue; }
      if (tt1 > t1) { res.push_back(segs2[i2++]); continue; }
      assert(0);
    }
    if (l1 > l2) {
      if (tt2 < t2) { res.push_back(segs2[i2++]); continue; }
      if (tt2 > t2) { res.push_back(segs1[i1++]); continue; }
      assert(0);
    }
    // t1 == t2 and l1 == l2
    if (tt1 <= tt2) {
      res.push_back(segs1[i1++]); continue;
    }
    res.push_back(segs2[i2++]); continue;
  }
  dbg(res);

  string res2;
  for (auto [t, l] : res) {
    res2 += string(l, t);
  }
  cout << res2 << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py hackerrank/challenges/morgan-and-a-string/main.cpp

%%%% begin
1
DAC
DAB
%%%%
DABDAC
%%%% end

%%%% begin
1
AABB
AAAC
%%%%
AAAAABBC
%%%% end

%%%% begin
2
JACK
DANIEL
ABACABA
ABACABA
%%%%
DAJACKNIEL
AABABACABACABA
%%%% end
*/
