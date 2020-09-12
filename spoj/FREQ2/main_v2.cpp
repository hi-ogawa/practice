// TLE

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
  int n, nq; // [1, 10^5]
  cin >> n >> nq;
  vector<int> ls(n);
  vector<array<int, 2>> qs(nq);
  cin >> ls >> qs;
  for (auto& [_x, y] : qs) { y++; }

  int m = sqrt(n);
  auto compare = [&](auto x, auto y) {
    x[0] /= m; y[0] /= m; return x < y;
  };
  vector<int> order(nq);
  iota(ALL(order), 0);
  sort(ALL(order), [&](auto x, auto y) { return compare(qs[x], qs[y]); });

  vector<int> res(nq);
  int l = m, r = m; // [l, r)
  int max_freq = 0;
  vector<int> freqs(*max_element(ALL(ls)) + 1);

  FOR(qii, 0, nq) {
    int qi = order[qii];
    auto [ql, qr] = qs[qi];

    // Handle small block later by brute force
    if (ql / m == qr / m) { continue; }

    // Otherwise, we can split to [ql, ll) + [ll, qr)
    int ll = ((ql / m) + 1) * m;

    // Reset state when left block changes
    if (l < ll) {
      fill(ALL(freqs), 0); // (hit at most n / m times)
      max_freq = 0;
      l = ll; r = ll;
    }

    // Update state [ll, r) -> [ll, qr)
    assert(r <= qr);
    FOR(i, r, qr) { max_freq = max(max_freq, ++freqs[ls[i]]); }
    r = qr;

    // Add up [ql, ll) by brute force
    res[qi] = max_freq;
    FOR(i, ql, ll) { res[qi] = max(res[qi], ++freqs[ls[i]]); }
    FOR(i, ql, ll) { freqs[ls[i]]--; }
  }

  // Take care smalls blocks
  fill(ALL(freqs), 0);
  max_freq = 0;
  FOR(qi, 0, nq) {
    auto [ql, qr] = qs[qi];
    if (ql / m != qr / m) { continue; }
    FOR(i, ql, qr) { res[qi] = max(res[qi], ++freqs[ls[i]]); }
    FOR(i, ql, qr) { freqs[ls[i]]--; }
  }

  for (auto x : res) { cout << x << endl; }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py spoj/FREQ2/main_v2.cpp --check

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
