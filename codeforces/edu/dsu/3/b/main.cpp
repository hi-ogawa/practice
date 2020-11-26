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

struct Dsu {
  vector<int> parents;
  vector<int> sizes;
  vector<int> checkpoints;
  vector<array<int, 2>> history;
  int num_components;

  Dsu(int n) {
    parents.resize(n);
    iota(ALL(parents), 0);
    sizes.assign(n, 1);
    num_components = n;
  }

  int find(int x) {
    if (x == parents[x]) { return x; }
    return find(parents[x]);
  }

  void merge(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) { return; }
    if (sizes[x] > sizes[y]) { swap(x, y); }
    sizes[y] += sizes[x];
    parents[x] = y;
    num_components--;
    history.push_back({x, y});
  }

  void persist() {
    checkpoints.push_back(history.size());
  }

  void rollback() {
    assert(!checkpoints.empty());
    int last = checkpoints.back(); checkpoints.pop_back();
    while ((int)history.size() > last) {
      auto [x, y] = history.back(); history.pop_back();
      sizes[y] -= sizes[x];
      parents[x] = x;
      num_components++;
    }
  }
};

// Main
void mainCase() {
  int n, m; // [1, 5 x 10^4]
  cin >> n >> m;
  vector<array<int, 2>> edges(m);
  cin >> edges;
  int nq; // [1, 5 x 10^4]
  cin >> nq;
  vector<array<int, 2>> qs(nq);
  cin >> qs;
  for (auto& [x, y] : edges) { x--; y--; }
  for (auto& [l, r] : qs) { l--; }

  // Mo's query ordering
  int m_blk = sqrt(m);
  auto compare = [&](auto x, auto y) {
    x[0] /= m_blk; y[0] /= m_blk;
    return x < y;
  };
  vector<int> order(nq);
  iota(ALL(order), 0);
  sort(ALL(order), [&](auto x, auto y) { return compare(qs[x], qs[y]); });

  // State
  Dsu dsu(n);
  dsu.persist(); // Keep empty state
  int lb = -1, r = 0; // [l, r)

  auto insert = [&](int i) {
    auto [x, y] = edges[i];
    dsu.merge(x, y);
  };

  vector<int> res(nq);
  FOR(o, 0, nq) {
    auto iq = order[o];
    auto [ql, qr] = qs[iq];

    // Reset everything when "left" block changes.
    int qlb = ql / m_blk;
    assert(lb <= qlb);
    if (lb < qlb) {
      lb = qlb;
      r = (lb + 1) * m_blk;
      dsu.rollback();
      assert(dsu.num_components == n);
      dsu.persist();
    }

    // Brute force if [ql, qr) is within a single block
    if (qr < r) {
      assert(dsu.num_components == n);
      dsu.persist();
      FOR(i, ql, qr) { insert(i); }
      res[iq] = dsu.num_components;
      dsu.rollback();
      continue;
    }

    // Otherwise
    while (r < qr) { insert(r++); } // Extend right (update state)
    dsu.persist();
    FOR(i, ql, (lb + 1) * m_blk) { insert(i); } // Extend left (brute force)
    res[iq] = dsu.num_components;
    dsu.rollback();
  }

  for (auto x : res) { cout << x << "\n"; }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/edu/dsu/3/b/main.cpp

%%%% begin
3 3
1 2
2 3
1 3
5
1 1
1 2
2 3
3 3
1 3
%%%%
2
1
1
2
1
%%%% end

%%%% begin
8 6
1 2
2 3
3 1
3 4
4 5
5 3
7
3 5
1 6
1 4
3 6
2 4
2 3
5 6
%%%%
5
4
5
5
5
6
6
%%%% end
*/
