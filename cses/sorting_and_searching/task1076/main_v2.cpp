// AFTER EDITORIAL, AC

// Cf. "Floating Median" from topcoder

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
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  ll n, k; // <= 10^6
  cin >> n >> k;
  vector<ll> ls(n, 0);
  cin >> ls;

  ll k1 = (k + 1) / 2;

  multiset<ll> s1;
  multiset<ll> s2;
  vector<ll> res;

  // Initial k-segment
  s2 = multiset<ll>(ls.begin(), ls.begin() + k);
  FOR(i, 0, k1) {
    s1.insert(*s2.begin());
    s2.erase(s2.begin());
  }
  res.push_back(*--s1.end());
  // DD(tie(s1, s2));

  // Slide k-segments
  FOR(i, 0, n - k) {
    ll x = ls[i];
    ll y = ls[i + k];
    ll m = *--s1.end();
    if (x <= m) {
      if (y <= m) {
        // x <= m, y <= m
        s1.erase(s1.find(x));
        s1.insert(y);
      } else {
        // x <= m, y > m
        s1.erase(s1.find(x));
        s2.insert(y);
        s1.insert(*s2.begin());
        s2.erase(s2.begin());
      }
    } else {
      if (y <= m) {
        // x > m, y <= m
        s2.erase(s2.find(x));
        s1.insert(y);
        s2.insert(*--s1.end());
        s1.erase(--s1.end());
      } else {
        // x > m, y > m
        s2.erase(s2.find(x));
        s2.insert(y);
      }
    }
    res.push_back(*--s1.end());
    // DD(tie(s1, s2));
  }

  FOR(i, 0, (int)res.size()) {
    if (i) cout << " ";
    cout << res[i];
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  mainCase();
  return 0;
  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // FOR(i, 0, t) { mainCase(); }
  // return 0;
}

/*
python misc/run.py cses/sorting_and_searching/task1076/main_v2.cpp --check

%%%% begin
10 9
8 10 6 1 5 10 1 3 4 2
%%%%
5 4
%%%% end

%%%% begin
8 3
2 4 3 5 8 1 2 1
%%%%
3 4 5 5 2 1
%%%% end
*/
