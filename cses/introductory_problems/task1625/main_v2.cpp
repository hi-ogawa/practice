// AFTER EDITORIAL, AC

// NOTE: Optimize by precomputing moves

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

// Main
void mainCase() {
  string s;
  cin >> s;

  const int n = 7;
  int n2 = n * n;
  const array<int, 2> kDirs[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

  using Position = int;
  using History = ull;

  auto enc = [](int i, int j) -> Position { return i * n + j; };
  auto encH = [](Position p) -> History { return 1ULL << p; };

  // Precompute moves
  vector<array<Position, 4>> moves(n2); // zero indicates invalid direction
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      FOR(k, 0, 4) {
        auto [di, dj] = kDirs[k];
        int ii = i + di, jj = j + dj;
        if (0 <= ii && ii < n && 0 <= jj && jj < n) {
          moves[enc(i, j)][k] = enc(ii, jj);
        }
      }
    }
  }

  Position p0 = enc(0, 0);
  Position p1 = enc(n - 1, 0);
  History hamiltonian = (1ULL << n2) - 1;

  vector<tuple<Position, History, int>> st; // (current-position, path-history, path-length)
  st.push_back({p0, encH(p0), 0});

  ll res = 0;
  while (!st.empty()) {
    auto [p, hist, len] = st.back(); st.pop_back();
    if (p == p1) {
      if (hist == hamiltonian) { res++; }
      continue;
    }

    array<bool, 4> ok = {};
    FOR(k, 0, 4) {
      auto pp = moves[p][k];
      ok[k] = pp && !(hist & encH(pp));
    }

    // Cull when path splits board
    if ((ok[0] && ok[2]) && (!ok[1] && !ok[3])) { continue; }
    if ((ok[1] && ok[3]) && (!ok[0] && !ok[2])) { continue; }

    char c = s[len];
    char mapping[4] = {'D', 'R', 'U', 'L'};
    FOR(k, 0, 4) {
      if (!ok[k]) { continue; }
      if (c == '?' || c == mapping[k]) {
        auto pp = moves[p][k];
        st.push_back({pp, hist | encH(pp), len + 1});
      }
    }
  }

  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/introductory_problems/task1625/main_v2.cpp

%%%% begin
DRURRRRRDDDLUULDDDLDRRURDDLLLLLURULURRUULDLLDDDD
%%%%
1
%%%% end

%%%% begin
??????R??????U??????????????????????????LD????D?
%%%%
201
%%%% end
*/
