// CONTEST, AC

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
  int n, nq; // [1, 5 x 10^4]
  cin >> n >> nq;
  vector<string> ls(n); // upper case and length <= 20
  cin >> ls;
  vector<array<int, 2>> qs(nq);
  cin >> qs;

  // Distance between alphabets
  const int kInf = 1e9;
  const int k = 26;
  vector<vector<int>> dists(k, vector<int>(k, kInf));

  FOR(i, 0, k) {
    dists[i][i] = 0;
  }

  for (auto& s : ls) {
    for (auto c1 : s) {
      c1 -= 'A';
      for (auto c2 : s) {
        c2 -= 'A';
        if (c1 == c2) { continue; }
        dists[c1][c2] = 1;
        dists[c2][c1] = 1;
      }
    }
  }

  // Floyd Warshall
  FOR(p, 0, k) {
    FOR(i, 0, k) {
      FOR(j, 0, k) {
        dists[i][j] = min(dists[i][j], dists[i][p] + dists[p][j]);
      }
    }
  }

  vector<int> res(nq);
  FOR(iq, 0, nq) {
    auto [i1, i2] = qs[iq];
    i1--; i2--;
    string s1 = ls[i1];
    string s2 = ls[i2];
    int t = kInf;
    for (auto c1 : s1) {
      c1 -= 'A';
      for (auto c2 : s2) {
        c2 -= 'A';
        t = min(t, dists[c1][c2]);
      }
    }
    t += 2; // Add two vertices at start/end
    if (t >= kInf) { t = -1; }
    res[iq] = t;
  }

  FOR(i, 0, nq) {
    cout << res[i] << " \n"[i == nq - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) {
    cout << "Case #" << (i + 1) << ": ";
    mainCase();
  }
  return 0;
}


/*
python misc/run.py google/kickstart-2020-h/4/main.cpp


%%%% begin
2
5 2
LIZZIE KEVIN BOHDAN LALIT RUOYU
1 2
1 3
2 2
KICK START
1 2
1 2
%%%%
Case #1: 2 3
Case #2: -1 -1
%%%% end
*/
