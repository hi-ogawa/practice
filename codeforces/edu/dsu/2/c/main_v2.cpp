// WIP

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
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// DSU
struct Dsu {
  map<int, int> parents;

  Dsu(int n) {
    FOR(i, 0, n) {
      parents[i] = i;
    }
  }

  // Representative of merged segment
  int repr(int i) {
    return parents.lower_bound(i)->first;
  }

  int find(int i) {
    i = repr(i);
    if (i == parents[i]) { return i; }
    return parents[i] = find(parents[i]);
  }

  void merge(int i, int j) {
    i = find(i);
    j = find(j);
    if (i == j) { return; }
    if (i > j) { swap(i, j); }
    parents[i] = j;
  }

  void mergeRange(int i, int j) {
    auto it = parents.lower_bound(i);
    while (it->first < j) {
      int k = it->first;
      it = parents.erase(it);
      merge(k, j);
    }
  }
};

// Main
void mainCase() {
  int n; // [1, 2e5]
  cin >> n;
  int nq; // [1, 5e5]
  cin >> nq;
  vector<array<int, 3>> qs(nq);
  cin >> qs;

  Dsu dsu(n);

  for (auto [t, x, y] : qs) {
    x--; y--;

    if (t == 1) {
      dsu.merge(x, y);
    }

    if (t == 2) {
      dsu.mergeRange(x, y);
    }

    if (t == 3) {
      bool res = dsu.find(x) == dsu.find(y);
      cout << (res ? "YES" : "NO") << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/edu/dsu/2/c/main_v2.cpp

%%%% begin
8 6
3 2 5
1 2 5
3 2 5
2 4 7
2 1 2
3 1 7
%%%%
NO
YES
YES
%%%% end
*/
