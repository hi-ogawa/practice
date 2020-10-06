// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
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

// Main
void mainCase() {
  int n; // [2, 1000]
  cin >> n;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;

  vector<set<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].insert(y);
    adj[y].insert(x);
  }

  //
  // Strategy:
  //   Test two leaves
  //     if answer is one of two leaves => leaf is the root
  //     otherwise => cull two leaves
  //

  auto ask = [](int x, int y) -> int {
    cout << "? " << (x + 1) << " " << (y + 1) << endl;
    int z;
    cin >> z;
    return z - 1;
  };

  set<int> leaves, rem;
  FOR(v, 0, n) {
    (adj[v].size() == 1 ? leaves : rem).insert(v);
  }

  int res;
  while (true) {
    dbg(leaves, rem);
    assert(leaves.size() >= 1);
    if (leaves.size() == 1) { res = *leaves.begin(); break; }

    int x = *leaves.begin(); leaves.erase(x);
    int y = *leaves.begin(); leaves.erase(y);
    int z = ask(x, y);
    if (z == x) { res = x; break; }
    if (z == y) { res = y; break; }

    adj[*adj[x].begin()].erase(x);
    adj[*adj[y].begin()].erase(y);
    FOR(v, 0, n) {
      if (rem.count(v) && adj[v].size() <= 1) {
        rem.erase(v);
        leaves.insert(v);
      }
    }
  }

  cout << "! " << (res + 1) << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1305D/main.cpp --check

%%%% begin
6
1 4
4 2
5 3
6 3
2 3

3

4

4
%%%%
? 5 6

? 3 1

? 1 2

! 4
%%%% end
*/
