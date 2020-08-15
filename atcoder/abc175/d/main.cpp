// AFTER CONTEST, WIP

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T>            istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  ll n, k; // n <= 10^4, k <= 10^9
  cin >> n >> k;
  vector<int> ls(n, 0); // permutation
  cin >> ls;
  vector<int> ps(n, 0); // |x| <= 10^9
  cin >> ps;
  for (auto& x : ls) { x--; }

  // Connected component by DFS
  vector<vector<int>> compos;
  {
    vector<bool> done(n, 0);
    function<void(int, vector<int>&)> dfs = [&](int v, vector<int>& co) {
      if (done[v]) { return; }
      done[v] = 1;
      co.push_back(v);
      dfs(ls[v], co);
    };
    FOR(v, 0, n) {
      if (!done[v]) {
        dfs(v, compos.emplace_back());
      }
    }
  }
  DD(compos);

  // Utility
  auto boundedMaxSegment = [&](int w, vector<int>& co) -> ll {
    int m = co.size();
    vector<ll> cumsum(m + 1, 0);
    FOR(i, 0, m) { cumsum[i + 1] = cumsum[i] + ps[co[i]]; }
    ll res = 0;
    set<ll> tmp; // active cumsum within window
    // Initial window
    FOR(i, 1, w + 1) {
      tmp.insert(cumsum[i]);
      res = max(res, *tmp.rbegin() - cumsum[0]);
    }
    // Moving window
    FOR(i, 1, m + 1) {
      tmp.insert(cumsum[i + w]);
      if (i <= m) { tmp.erase(tmp.find(cumsum[i])); }
      res = max(res, *tmp.rbegin() - cumsum[i]);
    }
    return res;
  };

  // Score for each component

  int l = compos.size();
  vector<ll> scores(l, 0);
  FOR(j, 0, l) {
    auto& co = compos[j];
    int m = co.size();
    ll co_sum = 0;
    for (auto x : co) { co_sum += ps[x]; }

    // [ k <= m ]
    if (k <= m) {
      // k-bounded max segment
    }

    // [ k > m ]
    if (k > m) {
      if (co_sum <= 0) {
        // max segment
      }

      if (co_sum >= 0) {
        // r-max segment
        int r = k % m;
        ll score = 0;
        score += 0;
        score += co_sum * (k / m);
        scores[j] = score;
      }
    }
  }
}

int main() {
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc175/d/main.cpp --check

%%%% begin
5 2
2 4 5 1 3
3 4 -10 -8 8
%%%%
8
%%%% end
*/
