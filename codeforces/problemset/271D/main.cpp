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

// 64bit hash by Chris Wellons https://nullprogram.com/blog/2018/07/31/
ull hash64(ull x) {
  x ^= x >> 30;
  x *= 0xbf58476d1ce4e5b9ULL;
  x ^= x >> 27;
  x *= 0x94d049bb133111ebULL;
  x ^= x >> 31;
  return x;
};

// Main
void mainCase() {
  string s, s_good;
  cin >> s >> s_good;
  int k;
  cin >> k;
  int n = s.size(); // <= 1500

  vector<bool> bs(n); // bads
  FOR(i, 0, n) { bs[i] = s_good[s[i] - 'a'] == '0'; }

  vector<int> ps(n + 1); // cumsum bads
  FOR(i, 0, n) { ps[i + 1] = ps[i] + bs[i]; }
  dbg(bs); dbg(ps);

  // (right)-maximal good ranges
  vector<int> segs(n);
  FOR(i, 0, n) {
    auto it = upper_bound(ALL(ps), k + ps[i]);
    segs[i] = distance(ps.begin(), it) - 1;
  }
  dbg(segs);

  // Distinctness by hashing
  vector<ull> hs;
  FOR(i, 0, n) {
    ull h = 0;
    FOR(j, i, segs[i]) {
      h = hash64(h ^ (ull)s[j]);
      hs.push_back(h);
    }
  }
  sort(ALL(hs));
  hs.erase(unique(ALL(hs)), hs.end());
  dbg(hs);

  ll res = hs.size();
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/271D/main.cpp --check

%%%% begin
ababab
01000000000000000000000000
1
%%%%
5
%%%% end

%%%% begin
acbacbacaa
00000000000000000000000000
2
%%%%
8
%%%% end
*/
