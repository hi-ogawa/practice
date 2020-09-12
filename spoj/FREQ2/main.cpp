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
  int n, nq;
  cin >> n >> nq;
  vector<int> ls(n);
  vector<array<int, 2>> qs(nq);
  cin >> ls >> qs;
  for (auto& [_x, y] : qs) { y++; }

  int m = sqrt(n);
  auto compare = [&](auto x, auto y) {
    x[0] /= m; y[0] /= m;
    if (x[0] == y[0] && (x[0] & 1)) { x[1] *= -1; y[1] *= -1; }
    return x < y;
  };
  vector<int> order(nq);
  iota(ALL(order), 0);
  sort(ALL(order), [&](auto x, auto y) { return compare(qs[x], qs[y]); });

  int k = *max_element(ALL(ls));
  vector<int> freqs(k + 1);
  multiset<int> heap;
  auto add = [&](int i) {
    int x = ls[i];
    if (freqs[x] > 0) { heap.erase(heap.find(freqs[x])); }
    heap.insert(++freqs[x]);
  };
  auto remove = [&](int i) {
    int x = ls[i];
    heap.erase(heap.find(freqs[x]));
    heap.insert(--freqs[x]);
  };

  int l = 0, r = 0; // [l, r)
  vector<int> res(nq);
  FOR(qi, 0, nq) {
    auto [ql, qr] = qs[order[qi]];
    while (l < ql) { remove(l++); }
    while (ql < l) { add(--l); }
    while (r < qr) { add(r++); }
    while (qr < r) { remove(--r); }
    res[order[qi]] = *heap.rbegin();
  }
  dbg(res);

  for (auto x : res) { cout << x << endl; }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py spoj/FREQ2/main.cpp --check

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
