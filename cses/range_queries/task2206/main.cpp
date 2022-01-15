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

constexpr ll kInf = 1e18;

// Segment tree for
//  - Point set
//  - Range min
struct SegmentTree {
  int n = 1;
  vector<ll> data;

  SegmentTree(int n_arg) {
    while (n < n_arg) { n *= 2; }
    data.assign(2 * n, kInf);
  }

  void set(int qi, ll qx) {
    int j = qi + n;
    data[j] = qx;
    j /= 2;
    while (j >= 1) {
      data[j] = std::min(data[2 * j], data[2 * j + 1]);
      j /= 2;
    }
  }

  ll min(int ql, int qr) {
    int jl = ql + n;
    int jr = qr + n;
    ll res = kInf;
    while (jl < jr) {
      if (jl & 1) {
        res = std::min(res, data[jl++]);
      }
      if (jr & 1) {
        res = std::min(res, data[--jr]);
      }
      jl /= 2;
      jr /= 2;
    }
    return res;
  }
};


// Main
void mainCase() {
  int n, nq; // [1, 2 x 10^5]
  cin >> n >> nq;
  vector<ll> ls(n); // [1, 10^9]
  cin >> ls;

  //
  // Define two trees for left side and right side:
  //   TR(i) = ls[i] + i
  //   TL(i) = ls[i] - i
  //
  // Then,
  //   Answer(k) = min(TR.min(k, n) - k, TL.min(0, k) + k)
  //

  SegmentTree tl(n);
  SegmentTree tr(n);
  for (int i = 0; i < n; i++) {
    tr.set(i, ls[i] + i);
    tl.set(i, ls[i] - i);
  }

  for (int iq = 0; iq < nq; iq++) {
    int t;
    cin >> t;
    if (t == 1) {
      int k;
      ll x;
      cin >> k >> x;
      k--;
      tr.set(k, x + k);
      tl.set(k, x - k);
    }
    if (t == 2) {
      int k;
      cin >> k;
      k--;
      ll res = std::min(tr.min(k, n) - k, tl.min(0, k) + k);
      cout << res << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/range_queries/task2206/main.cpp

%%%% begin
6 3
8 6 4 5 7 5
2 2
1 5 1
2 2
%%%%
5
4
%%%% end
*/
