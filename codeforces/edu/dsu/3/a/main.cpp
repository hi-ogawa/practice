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
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
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
  int n, nq; // [1, 2 x 10^5]
  cin >> n >> nq;

  Dsu dsu(n);

  FOR(_, 0, nq) {
    string t;
    cin >> t;
    if (t == "union") {
      int x, y;
      cin >> x >> y;
      x--; y--;
      dsu.merge(x, y);
      cout << dsu.num_components << "\n";
    }
    if (t == "persist") {
      dsu.persist();
    }
    if (t == "rollback") {
      dsu.rollback();
      cout << dsu.num_components << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/edu/dsu/3/a/main.cpp

%%%% begin
5 10
persist
union 1 2
union 3 4
persist
union 1 4
union 2 3
rollback
union 4 5
rollback
union 1 5
%%%%
4
3
2
2
3
2
5
4
%%%% end
*/
