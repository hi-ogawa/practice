// AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
template<typename T> struct is_container {
template<typename C> static char test(typename C::const_iterator*); template<typename> static int test(...);
static bool const value = sizeof(test<T>(nullptr)) == sizeof(char) && !std::is_same<std::string, T>::value;
};
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#ifndef DEBUG
#define DEBUG 0
#endif
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  int n; // [3, 2 x 10^5]
  cin >> n;
  string s;
  cin >> s;

  map<char, int> cnts, cnts_l, cnts_r;
  for (auto t : s) { cnts[t]++; }
  cnts_r = cnts;
  cnts_r[s[0]]--;
  cnts_l[s[0]]++;

  constexpr ll modulo = 1e9 + 7;
  auto add = [&](ll x, ll y) { return (x + y) % modulo; };
  auto mul = [&](ll x, ll y) { return (x * y) % modulo; };
  auto pow = [&](ll x, ll e) {
    ll res = 1;
    while (e > 0) {
      if (e & 1) { res = mul(res, x); }
      e >>= 1; x = mul(x, x);
    }
    return res;
  };
  auto addeq = [&](ll& x, ll y) { return x = add(x, y); };
  auto mul3 = [&](ll x, ll y, ll z) { return mul(x, mul(y, z)); };

  ll q_cnt = cnts['?'];
  array<ll, 4> q_cnt_pows;
  FOR(i, 0, 4) { q_cnt_pows[i] = pow(3, q_cnt - i); }

  ll res = 0;
  FOR(i, 1, n - 1) {
    cnts_r[s[i]]--;
    if (s[i] == 'b') {
      addeq(res, mul3(cnts_l['a'], cnts_r['c'], q_cnt_pows[0]));
      addeq(res, mul3(cnts_l['a'], cnts_r['?'], q_cnt_pows[1]));
      addeq(res, mul3(cnts_l['?'], cnts_r['c'], q_cnt_pows[1]));
      addeq(res, mul3(cnts_l['?'], cnts_r['?'], q_cnt_pows[2]));
    }
    if (s[i] == '?') {
      addeq(res, mul3(cnts_l['a'], cnts_r['c'], q_cnt_pows[1]));
      addeq(res, mul3(cnts_l['a'], cnts_r['?'], q_cnt_pows[2]));
      addeq(res, mul3(cnts_l['?'], cnts_r['c'], q_cnt_pows[2]));
      addeq(res, mul3(cnts_l['?'], cnts_r['?'], q_cnt_pows[3]));
    }
    cnts_l[s[i]]++;
  }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest674/f/main.cpp --check

%%%% begin
6
ac?b?c
%%%%
24
%%%% end

%%%% begin
7
???????
%%%%
2835
%%%% end

%%%% begin
9
cccbbbaaa
%%%%
0
%%%% end

%%%% begin
5
a???c
%%%%
46
%%%% end
*/
