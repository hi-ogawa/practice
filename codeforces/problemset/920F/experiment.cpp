
// Experiment with repeated divisor function

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

#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)

vector<int> makeDivisorFunction(int n) {
  vector<int> sieve(n + 1, 1);
  vector<int> res(n + 1, 1);
  for (int p = 2; p <= n; p++) {
    if (!sieve[p]) { continue; }
    int e = 1;
    ll pe = p;
    for (; pe <= n; e++, pe *= p) {
      int i = 1;
      int x = pe;
      for (; x <= n; i++, x += pe) {
        if (i % p == 0) { continue; }
        sieve[x] = 0;
        res[x] *= (e + 1);
      }
    }
  }
  return res;
};

// Main
void mainCase() {
  int n, m;
  cin >> n >> m;
  auto divisor = makeDivisorFunction(n);

  vector<vector<int>> repeats(m, vector<int>(n + 1));
  iota(ALL(repeats[0]), 0);
  FOR(i, 0, m - 1) {
    FOR(j, 0, n + 1) {
      repeats[i + 1][j] = divisor[repeats[i][j]];
    }
  }

  FOR(i, 0, m) {
    auto& ls = repeats[i];
    auto it = max_element(ALL(ls));
    int x = distance(ls.begin(), it);
    int y = *it;
    dbg(i, x, y);
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/920F/experiment.cpp

%%%% begin
1000000 7
%%%%
i, x, y: (0, 1000000, 1000000)
i, x, y: (1, 720720, 240)
i, x, y: (2, 720720, 20)
i, x, y: (3, 5040, 6)
i, x, y: (4, 5040, 4)
i, x, y: (5, 5040, 3)
i, x, y: (6, 2, 2)
%%%% end
*/
