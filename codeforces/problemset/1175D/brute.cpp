
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
  int n, k; // [1, 3 x 10^5]
  cin >> n >> k;
  vector<ll> ls(n); // [-10^6, 10^6]
  cin >> ls;

  vector<ll> ps(n + 1);
  FOR(i, 0, n) { ps[i + 1] = ps[i] + ls[i];  }

  auto evaluate = [&](const vector<int>& segs) -> ll {
    ll t = 0;
    FOR(i, 1, k + 1) {
      t += i * (ps[segs[i]] - ps[segs[i - 1]]);
    }
    return t;
  };

  const ll kInf = 1e18;
  ll res = - kInf;

  // Generate binom(n, k - 1)
  vector<int> comb(n, 1);
  fill(comb.begin(), comb.begin() + k - 1, 0);
  do {
    if (comb[0] == 0) { continue; } // empty segment is invalid
    vector<int> segs;
    segs.push_back(0);
    FOR(i, 0, n) { if (comb[i] == 0) { segs.push_back(i); } }
    segs.push_back(n);
    ll t = evaluate(segs);
    dbg(segs, t);
    res = max(res, t);
  } while (next_permutation(ALL(comb)));

  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1175D/brute.cpp --check

%%%% begin
7 3
1 −2 −3 4 −5 6 −7
%%%%
1
%%%% end

%%%% begin
5 2
-1 -2 5 -4 8
%%%%
15
%%%% end

%%%% begin
7 6
-3 0 -1 -2 -2 -4 -1
%%%%
-45
%%%% end

%%%% begin
4 1
3 -1 6 0
%%%%
8
%%%% end
*/
