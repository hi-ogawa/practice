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
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Fenwick tree
struct FenwickTree {
  int n_;
  vector<int> data_;
  FenwickTree(int n) { n_ = n; data_.resize(n); }
  void incr(int qi, int qv) {
    while (qi < n_) {
      data_[qi] += qv;
      qi = (qi | (qi + 1));
    }
  }
  int reduce(int qi) {
    ll res = 0;
    while (qi >= 0) {
      res += data_[qi];
      qi = (qi & (qi + 1)) - 1;
    }
    return res;
  }
};

// Hash by Chris Wellons https://nullprogram.com/blog/2018/07/31/
uint32_t hash32(uint32_t x) {
  x ^= x >> 16;
  x *= 0x7feb352dU;
  x ^= x >> 15;
  x *= 0x846ca68bU;
  x ^= x >> 16;
  return x;
}

// Main
void mainCase() {
  int n, nq; // <= 10^6
  cin >> n >> nq;
  vector<int> ls(n, 0); // <= 10^9
  vector<tuple<char, int, int>> qs(nq, {'0', 0, 0});
  cin >> ls >> qs;

  // Compress domain ~ 10^6
  auto ls2 = ls;
  auto qs2 = qs;
  int enc_max = 0;
  {
    vector<int> dec;
    for (auto x : ls) { dec.push_back(x); }
    for (auto [t, a, b] : qs) {
      if (t == '!') { dec.push_back(b); }
      if (t == '?') { dec.push_back(a); dec.push_back(b); }
    }
    sort(ALL(dec));
    dec.erase(unique(ALL(dec)), dec.end());
    enc_max = dec.size();

    struct Hash { size_t operator()(int x) const { return hash32(x); }; };
    unordered_map<int, int, Hash> enc;
    FOR(i, 0, enc_max) { enc[dec[i]] = i; }

    FOR(i, 0, n) {
      ls2[i] = enc[ls[i]];
    }
    FOR(i, 0, nq) {
      auto [t, a, b] = qs[i];
      if (t == '!') {
        qs2[i] = {t, a, enc[b]};
      }
      if (t == '?') {
        qs2[i] = {t, enc[a], enc[b]};
      }
    }
  }

  FenwickTree tree(enc_max);
  for (auto x : ls2) { tree.incr(x, 1); }

  for (auto [t, a, b] : qs2) {
    if (t == '!') {
      a--;
      tree.incr(ls2[a], -1);
      tree.incr(b, 1);
      ls2[a] = b;
    }
    if (t == '?') {
      ll f1 = tree.reduce(a - 1);
      ll f2 = tree.reduce(b);
      ll res = f2 - f1;
      cout << res << endl;
    }
  }
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
python misc/run.py cses/range_queries/task1144/main_v4.cpp --check

%%%% begin
5 3
3 7 2 2 5
? 2 3
! 3 6
? 2 3
%%%%
3
2
%%%% end
*/
