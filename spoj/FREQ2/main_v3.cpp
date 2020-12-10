// AC

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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n, nq; // [1, 10^5]
  cin >> n >> nq;
  vector<int> ls(n); // [0, 10^5]
  cin >> ls;
  vector<array<int, 2>> qs(nq);
  cin >> qs;
  for (auto& [l, r] : qs) { r++; }

  // Mo's ordering
  int blk = sqrt(n);
  auto compare = [&](auto x, auto y) {
    x[0] /= blk; y[0] /= blk;
    return x < y;
  };
  vector<int> order(nq);
  iota(ALL(order), 0);
  sort(ALL(order), [&](auto x, auto y) { return compare(qs[x], qs[y]); });

  // State
  int max_freq = 0;
  int l = blk, r = blk;
  vector<int> freqs(*max_element(ALL(ls)) + 1);

  // Answer query
  vector<int> res(nq);
  FOR(o, 0, nq) {
    auto [ql, qr] = qs[order[o]];

    // Reset when left block changes
    if (l <= ql) {
      l = r = (ql / blk + 1) * blk;
      max_freq = 0;
      fill(ALL(freqs), 0);
    }

    // Extend [r, qr)
    for (; r < qr; r++) {
      max_freq = max(max_freq, ++freqs[ls[r]]);
    }

    // Temporary update [ql, sep)
    int sep = min(qr, l);
    int tmp = max_freq;
    for (int i = sep - 1; i >= ql; i--) {
      tmp = max(tmp, ++freqs[ls[i]]);
    }
    res[order[o]] = tmp;
    for (int i = ql; i < sep; i++) {
      --freqs[ls[i]];
    }
  }

  for (auto x : res) { cout << x << "\n"; }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py spoj/FREQ2/main_v3.cpp

%%%% begin
5 3
1 2 1 3 3
0 2
1 2
0 4
%%%%
2
1
2
%%%% end
*/
