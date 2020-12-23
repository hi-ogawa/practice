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

// Probing hash table
#include <ext/pb_ds/assoc_container.hpp>
template<class Key, class Value, class Hash = std::hash<Key>>
using hash_table = __gnu_pbds::gp_hash_table<Key, Value, Hash>;

// 64bit hash by Chris Wellons https://nullprogram.com/blog/2018/07/31/
uint64_t hash64(uint64_t x) {
  x ^= x >> 30;
  x *= 0xbf58476d1ce4e5b9ULL;
  x ^= x >> 27;
  x *= 0x94d049bb133111ebULL;
  x ^= x >> 31;
  return x;
};

const ull kSeed = (ull)new char;

// Main
void mainCase() {
  int nq; // [1, 10^6]
  cin >> nq;

  struct Hash { size_t operator()(ll x) const { return hash64(x ^ kSeed); }; };
  hash_table<ll, ll, Hash> a;

  FOR(_, 0, nq) {
    int t;
    ll k, v; // [0, 10^18]
    cin >> t;
    if (t == 0) {
      cin >> k >> v;
      a[k] = v;
    }
    if (t == 1) {
      cin >> k;
      cout << a[k] << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/associative_array/main_v2.cpp

%%%% begin
8
0 1 2
1 1
1 2
0 2 3
1 1
1 2
0 2 1
1 2
%%%%
2
0
2
3
1
%%%% end
*/
